#-*- coding:utf-8 -*-

####################################################################################
#
# Copyright © 2017 TU. All Rights Reserved.
#
####################################################################################

"""

@File: code_generator.py

@Author: leiyunfei(leiyunfei@tuyoogame.com)

@Depart: 斗地主项目组

@Create: 2017-04-19 20:31:50

"""

import random
import string

def output(func):
    def print_decorating(number):
        for i in func(number):
            print i
    return print_decorating

class CodeGenerator(object):
    """
    生成指定数量的兑换码
    """
    KEY_LEN = 20
    def __init__(self, number):
        self._number = number

    @classmethod
    def base_string(cls):
        return (string.letters + string.digits)

    @classmethod
    def key_gen(cls):
        keys = [random.choice(cls.base_string()) for i in range(cls.KEY_LEN)]
        return "".join(keys)

    def gen(self, result = None):
        if result is None:
            result = []
        for i in range(self._number):
            result.append(self.key_gen())
        return result


if __name__ == '__main__':
    cg = CodeGenerator(200)
    codes = cg.gen()
    print codes
