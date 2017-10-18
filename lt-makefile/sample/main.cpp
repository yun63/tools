/***************************************************************************
 *
 * Copyright © 2016 LT. All Rights Reserved.
 *
 ***************************************************************************/

/**
 *
 * @file: main.cpp
 *
 * @breaf: 
 *
 * @author: Lei Yunfei(towardstheway@gmail.com)
 *
 * @create: 2017/10/18 15时12分21秒
 *
 **/

#include <iostream>

#include "common/hash.h"
#include "util/lt_util.h"

int main() {
    std::cout << lt::atof("123.23") << std::endl;
    std::cout << base::SuperFastHash("Hello", 5) << std::endl;
    return 0;
}
