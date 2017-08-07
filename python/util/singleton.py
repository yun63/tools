#-*- coding:utf-8 -*-

####################################################################################
#
# Copyright © 2017 TU. All Rights Reserved.
#
####################################################################################

"""

@File: singleton.py

@Author: leiyunfei(leiyunfei@tuyoogame.com)

@Depart: 斗地主项目组

@Create: 2017-04-26 16:04:41

"""


import logging

class Singleton(object):
    def __init__(self, name, bases, dic):
        super(Singleton, self).__init__(name, bases, dic)
        self.__instance = None

    def __call__(self, *args, **kwargs):
        if self.__instance is None:
            logging.debug('Creating a Singleton isinstance of %s' % self.__name__)
            self.__instance = super(Singleton, self).__call__(*args, **kwargs)
        return self.__instance
