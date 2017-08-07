#-*- coding:utf-8 -*-

####################################################################################
#
# Copyright © 2017 TU. All Rights Reserved.
#
####################################################################################

"""

@File: test.py

@Author: leiyunfei(leiyunfei@tuyoogame.com)

@Depart: 斗地主项目组

@Create: 2017-04-26 16:11:22

"""

from util.singleton import Singleton

class RobotManager(object):
    __metaclass__ = Singleton
    def __init__(self):
        self.free_robot_users = []
        self.busy_robot_users = []
        self.callup_delay_seconds = -1

if __name__ == '__main__':
    robot_manager = RobotManager()
    robot_manager2 = RobotManager()
    robot_manager.free_robot_users = [1, 2, 3]
    assert(robot_manager2.free_robot_users == [1, 2, 3])
    assert(robot_manager == robot_manager2)
    assert(id(robot_manager) == id(robot_manager2))
