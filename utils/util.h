// =====================================================================================
//
//       Filename:  util.h
//
//    Description:  常用的一些算法和辅助工具函数定义及实现
//
//        Version:  1.0
//        Created:  2015年09月05日 23时22分13秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  yunfei_lei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#ifndef __UTIL_H_
#define __UTIL_H_

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

namespace basic_util {

static inline vector<string> compact(const vector<string> &tokens)
{
    vector<string> compacted;

    for (size_t i = 0; i < tokens.size(); ++i)
    {
        if (!tokens[i].empty())
        {
            compacted.push_back(tokens[i]);
        }
    }

    return compacted;
}

static inline vector<string> split(const string &str, const string &delim, bool trim_empty = false)
{
    size_t pos;
    size_t last_pos = 0;
    size_t len;
    vector<string> tokens;

    while (true)
    {
        pos = str.find(delim, last_pos);
        if (pos == std::string::npos)
        {
            pos = str.size();
        }

        len = pos - last_pos;
        if (!trim_empty || len != 0)
        {
            tokens.push_back(str.substr(last_pos, len));
        }

        if (pos == str.size()) 
        {
            break;
        }
        else 
        {
            last_pos = pos + delim.size();
        }
    }

    return tokens;
}



} // namespace basic_util

#endif
