#-*- coding:utf-8 -*-

####################################################################################
#
# Copyright © 2017 TU. All Rights Reserved.
#
####################################################################################

"""

@File: mysql.py

@Author: leiyunfei(leiyunfei@tuyoogame.com)

@Depart: 斗地主项目组

@Create: 2017-04-24 20:14:06

"""

import MySQLdb


class Mysql(object):
    """
    操作Mysql数据库的类
    """
    def __init__(self, **kwargs):
        self.conn = self.connect(
            kwargs.get('host'),
            kwargs.get('port'),
            kwargs.get('user'),
            kwargs.get('passwd'),
            kwargs.get('db')
        )

    @classmethod
    def connect(self, host, port, user, passwd, db):
        # 建立Mysql连接
        return MySQLdb.Connect(
            host=host,
            port=port,
            user=user,
            passwd=passwd,
            db=db,
            charset='utf8'
        )

    def cursor(self):
        # 获得cursor
        return self.conn.cursor

    def query(self, sql):
        # 查询
        assert(isinstance(sql, str))
        self.corsor().execute(sql)
        rows = self.corsor().fetchall()
        return rows

    def commit(self):
        # 提交
        return self.conn.commit()

    def close(self):
        # 关闭连接
        return self.conn.close()
