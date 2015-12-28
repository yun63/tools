/**
 * 将mysql数据库的表数据转换成json格式并且存档文件
 * author: leiyunfei
 * email: towardstheway@gmail.com
 * date: 2015-11-24
 */
var fs = require('fs');
var utils = require('./utils');
var mysqlUtil = require('./mysql_utils');
var config = require('../config/config.json');
var tpl = require('../config/tpl.json');

var Parser = module.exports;

Parser.makeKeyForArray = function() {
  var args = Array.prototype.slice.call(arguments);
  return args[0].join('_');
}

Parser.makeKeyForAgrs = function() {
  var args = Array.prototype.slice.call(arguments);
  return args.join('_');
}

/**
 * 生成lua头文件描述
 * @param {String} tableName 表名
 * @return {String} 头文件描述
 */
Parser.makeHeader = function(tableName) {
  tableName = utils.fromUnderscoreToCamel(tableName);
  return '--\n' +
    '-- ' + tableName + '\n' +
    '-- auto generate by tools\n' +
    '-- Copyright(R) GOW\n' + 
    '--\n' +
    '\n' + tableName + ' = {};\n';
}

/**
 * 生成lua获取数据方法
 * @param {String} table 文件表名
 * @param {Array} keyArray 关键词
 * @return {String} 形如function tableName.get(self, key, ...) return self[key_...]; end
 */
Parser.makeFunc = function(tableName, keyArray, tableLen) {
  /*
   * function TplHero.len(self)
   *    return 100;
   * end
   *
   * function TplHero.get(self, key1, key2)
   *    return self.data["key1" .. "_" .. "key2"];
   * end
   */
  tableName = utils.fromUnderscoreToCamel(tableName);
  if (keyArray.length === 1) {
    return '\n' +
      '\nfunction ' + tableName + '.len(self)\n' +
      '\treturn ' + tableLen + '\n' + 'end\n' +
      '\nfunction ' + tableName + '.get(self, ' + keyArray.join(', ') + ')\n' +
      '\treturn self.data[tostring(' + keyArray[0] + ')]\n' + 'end\n';
  }
  return '\n' +
    '\nfunction ' + tableName + '.len(self)\n' +
    '\treturn ' + tableLen + '\n' + 'end\n' +
    '\nfunction ' + tableName + '.get(self, ' + keyArray.join(', ') + ')\n' +
    '\treturn self.data[' + keyArray.join(' .. \'_\' .. ') + ']\n' + 'end\n';
}


/**
 * 从数据库拉取数据、转Lua并保存文件
 *
 * @param {Object} mysqlConnect mysql连接实例
 * @param {String} tableName 表名
 * @param {Object} tableMeta 表结构描述元数据
 *
 */
Parser.fetchData2LuaFile = function(mysqlConnect, tableName, tableMeta) {
  var fields = tableMeta.fields;
  var keys = tableMeta.keys;
  var specKeys = tableMeta.stringfy;
  mysqlUtil.query(mysqlConnect, tableName, fields, keys, specKeys, Parser.handleTplData);
}

/**
 * 表数据处理
 *
 * @param {String} table 表名
 * @param {Array} fields 导出列
 * @param {Array} keys 键
 * @param {Array} specKeys 特殊列 
 * @param {Array} resultset 行数据结果集
 *
 */
Parser.handleTplData = function(table, fields, keys, specKeys, resultset) {
  /* 打印表相关信息 */
  //Parser.printTableInfo(table, fields, keys, specKeys, resultset);
  //console.log(resultset);
  
  /* 存储整张tpl表 */
  var _dictContents = {};
  var commonFields = {};

  /* 遍历一张表的所有行 */
  for (var i = 0; i < resultset.length; i++) {
    var rowValue = resultset[i];

    /* 解析每一行 */
    for (var k in fields) {
      if (utils.isElementOfArray(fields[k], specKeys)) {
        /* 特殊字段*/
        /* console.log('%s是Lua格式的字符串，需要stringfy', fields[k], specKeys); */
      } else {
        commonFields[fields[k]] = true;
      }
    }

    /* 提取key */
    var array = [];
    for (var ii = 0; ii < keys.length; ii++) {
      array.push(rowValue[keys[ii]]);
    }

    var priKey = Parser.makeKeyForArray(array);
    /* console.log(typeof priKey,  priKey); */
    _dictContents[priKey] = rowValue;
  }
  /* console.log(_dictContents); */
  Parser.write2Lua(table, _dictContents, resultset.length);
}

Parser.parse = function(value) {
  if (typeof value !== 'string') {
    return value;
  }

  var result = '{';

  for (var i = 0; i < value.length; i++) {
    switch (value[i]) {
      case '[':
      case '\"':
      case ']':
        break;
      case ':':
        result += ' = ';
        break;
      default:
        result += value[i];
        break;
    }
  }

  return result + '}';
}

Parser.stringfyObject = function(object, layer, specKeys) {
  var s = '{' + '\n';
  var line = '';
  var index = '\t';

  /* 根据层级缩进 */
  for (var i = 0; i < layer; i++) {
    index += '\t';
  }

  var flag = true, value;

  for (var k in object) {
    value = object[k];
    //console.log(k, value);
    if (utils.isElementOfArray(k, specKeys) &&
        typeof value === 'string') {
      /* value是一个可以解析成JSON的字符串 */
      value = Parser.parse(value);
    }
    else if (typeof value === 'string') {
      value = '\"' + value + '\"';
    }

    if (flag) {
      /* 是首行 */
      line = index + k + ' = ' + value;
      flag = false;
    } else {
      /* 不是首行 */
      line =  ',' + '\n' + index + k + ' = ' + value;
    }
    s += line;
  }

  return s + '\n\t' + '}';
}

Parser.format2Lua = function(tableName, dict) {
  /* 最外层*/
  /* tableName = { */

  var specKeys = tpl[tableName].stringfy;

  tableName = utils.fromUnderscoreToCamel(tableName);
  var jsonStr = tableName + '.data = {' + '\n';

  var flag = true;

  for (var key in dict) {
    var objectValue = dict[key];
    if (typeof key !== 'string') {
      throw new Error('ƒ key shoule be a string');
    }
    if (typeof objectValue !== 'object') {
      throw new Error('ƒ value should be a object');
    }

    var strTemp = Parser.stringfyObject(objectValue, 1, specKeys);
    //console.log(strTemp);

    if (flag) {
      line = '\t' + '[\"' + key + '\"]' + ' = ' + strTemp;
      flag = false;
    }
    else {
      line = ',' + '\n' + '\t' + '[\"' + key + '\"]' + ' = ' + strTemp;
    }
    jsonStr += line;
  }

  /* 最后一行添加} */
  jsonStr += '\n' + '};\n';

  return jsonStr;
}

/**
 * 写Lua文件
 */
Parser.write2Lua = function(fileName, dictData, tableLen) {
  var filePath = config.datapath + '/' + utils.fromUnderscoreToCamel(fileName) + '.lua';
  var header = Parser.makeHeader(fileName);
  var contents = Parser.format2Lua(fileName, dictData);
  var funcstr = Parser.makeFunc(fileName, tpl[fileName].keys, tableLen);
  var fileString = header + '\n' + contents + '\n' + funcstr + '\n';
  /* 写文件 */
  fs.writeFile(filePath, fileString, function(err) {
    if (err) {
      return console.error(err);
    }
    console.log('^_^ Congratulations! Generate %s.lua successfully!', utils.fromUnderscoreToCamel(fileName));
  });
}

Parser.printTableInfo = function(tableName, cols, keys, specKeys, data) {
  console.log('ƒ 表名: ', tableName);
  console.log('ƒ 表列: ', cols);
  console.log('ƒ 表键: ', keys);
  console.log('ƒ 特殊列: ', specKeys);
  console.log('ƒ 行数据: ', data);
}
