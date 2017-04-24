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
    def __init__(self, conn):
        self.conn = conn

    def connect(self):
        """ 建立Mysql连接 """
        self.conn = MySQLdb.connect(
            host='localhost',
            port=3306,
            user='root',
            'passwd'='root3gx',
            db='game',
            charset='utf8'
        )

    def cursor(self):
        """ 获得cursor """
        try:
            return self.conn.cursor
        except (AttributeError, MySQLdb.OperationalError):
            self.connect()
            return self.conn.cursor()

    def commit(self):
        """ 提交 """
        return self.conn.commit()

    def close(self):
        """ 关闭连接 """
        return self.conn.close()
