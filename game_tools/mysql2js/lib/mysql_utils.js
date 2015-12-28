/**
 * mysql数据库实用工具
 * leiyunfei
 * 2015-11-25
 */

var mysql = require('mysql');
var utils = require('./utils');

var mysqlUtils = {};

/**
 * 创建一个mysql连接实例
 * @param {String} host 主机地址
 * @param {String} user 用户名
 * @param {String} passwd 密码
 * @param {String} db 数据库名
 * @return {Object} 数据库连接实例
 */
mysqlUtils.createConnection = function(host, user, passwd, db) {
  var conf = {
    host: host,
    user: user,
    password: passwd,
    database: db
  };

  return  mysql.createConnection(conf);
}

/**
 * 查询: TODO:  支持插入、更新和删除操作
 * @param {Connection} connection mysql连接实例
 * @param {String} tableName  mysql数据库表名 
 * @param {Array} fields  表字段数组
 * @param {Function} handler  对查询结果解进行的处理函数
 * @return {String} 查询结果的描述 
 */
mysqlUtils.query = function(connection, tableName, fields, keys, specKeys, handler) {
  var sql = 'SELECT ?? FROM ' + tableName;
  var query = connection.query(sql, [fields], function(err, resultset) {
    if (err) {
      return console.error('- [SELECT ERROR] -', err.message);
    }
    if (typeof handler === 'function') {
      utils.invokeCallback(handler, tableName, fields, keys, specKeys, resultset);
    }
  });

  return console.log('+ [SELECT SUCCESS] +', query.sql);
}

/**
 * 关闭数据库连接
 * @param {Object} connection 数据库连接实例
 */
mysqlUtils.close = function(connection) {
  if (connection) {
    connection.end();
  }
}

module.exports = mysqlUtils;
