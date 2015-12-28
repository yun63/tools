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
 * 从数据库拉取数据、转JSON并保存文件
 *
 * @param {Object} mysqlConnect mysql连接实例
 * @param {String} tableName 表名
 * @param {Object} tableMeta 表结构描述元数据
 *
 */
Parser.fetchData2JSONFile = function(mysqlConnect, tableName, tableMeta) {
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
  /* Parser.printTableInfo(table, fields, keys, specKeys, resultset); */
  
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
        /* console.log('%s是JSON格式的字符串，需要stringfy', fields[k], specKeys); */
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
  Parser.writeToJSON(table, _dictContents);
}

Parser.stringfyObject = function(tableName, object, layer, specKeys) {
  var s = '{' + '\n';
  var line = '';
  var index = '  ';

  /* 根据层级缩进 */
  for (var i = 0; i < layer; i++) {
    index += '  ';
  }

  var flag = true, tag;

  for (var k in object) {
    if (!utils.isElementOfArray(k, specKeys) && typeof object[k] === 'string') {
        tag = '\"' + object[k] + '\"';
    } 
    else if (utils.isElementOfArray(k, specKeys) && object[k].length === 0) {
      tag = '{}';
    }
    else if (utils.isElementOfArray(k, specKeys)) {
      try {
        JSON.parse(object[k]);
        tag = object[k];
      }
      catch (e) {
        console.error('®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®');
        console.error('[  表名 ]', tableName);
        console.error('[  原因 ] 数据格式错误 ', e.message);
        console.error('[  数据 ] key: %s, value: %s', k, object[k]);
        console.error('®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®®');
        process.exit(1);
      }
    }
    else {
      tag = object[k];
    }

    if (flag) {
      /* 是首行 */
      line = index + '\"' + k + '\"' + ': ' + tag;
      flag = false;
    } 
    else {
      /* 不是首行 */
      line =  ',' + '\n' + index + '\"' + k + '\"' + ': ' + tag;
    }
    s += line;
  }

  return s + '}';
}

Parser.formatToJSON = function(tableName, dict, specKeys) {
  /* 最外层{ */
  var jsonStr = '{' + '\n';
  var flag = true;
  for (var key in dict) {
    var objectValue = dict[key];
    if (typeof key !== 'string') {
      throw new Error('ƒ key shoule be a string');
    }
    if (typeof objectValue !== 'object') {
      throw new Error('ƒ value should be a object');
    }

    var strTemp = Parser.stringfyObject(tableName, objectValue, 1, specKeys);

    if (flag) {
      line = '  ' + '\"' + key +'\"' + ': ' + strTemp;
      flag = false;
    }
    else {
      line = ',' + '\n' + '  ' + '\"' + key +'\"' + ': ' + strTemp;
    }
    jsonStr += line;
  }

  /* 最后一行添加} */
  jsonStr += '\n' + '}';

  return jsonStr;
}

/**
 * 写JSON文件
 */
Parser.writeToJSON = function(fileName, dictData) {
  var filePath = config.datapath + '/' + fileName + '.json';
  var contents = Parser.formatToJSON(fileName, dictData, tpl[fileName].stringfy);
  /* 写文件 */
  fs.writeFile(filePath, contents, function(err) {
    if (err) {
      return console.error(err);
    }
    console.log('^_^ Congratulations! Generate JSON %s.json successfully!', fileName);
  });
}

Parser.printTableInfo = function(tableName, cols, keys, specKeys, data) {
  console.log('ƒ 表名: ', tableName);
  console.log('ƒ 表列: ', cols);
  console.log('ƒ 表键: ', keys);
  console.log('ƒ 特殊列: ', specKeys);
  console.log('ƒ 行数据: ', data);
}
