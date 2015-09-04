// =====================================================================================
//
//       Filename:  config.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  2015年09月02日 23时53分55秒
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  yunfei_lei (yun63), towardstheway@gmail.com
//   Organization:  
//
// =====================================================================================

#include <cassert>

#include "config.h"

namespace basic_util {

Config::Config() : loaded_(false)
{
}

Config::Config(const string &filename) 
    : config_name_(filename)
    , loaded_(false)
{
}


Config::~Config(void)
{
}

// replace all old_value with new_value in 'str'
std::string &replace_all(std::string &str, const std::string &old_value, const std::string &new_value)
{   
	while (true)
	{   
		std::string::size_type pos(0);
		if ((pos = str.find(old_value)) != std::string::npos)
			str.replace(pos, old_value.length(), new_value);   
		else
			break;   
	}   
	return str;   
}   

// A function to trim whitespace from both sides of a given string
void Trim(std::string& str, const std::string & ChrsToTrim = " \t\n\r", int TrimDir = 0)
{
    std::size_t startIndex = str.find_first_not_of(ChrsToTrim);
    if (startIndex == std::string::npos)
    {
        str.erase();
        return;
    }
	
    if (TrimDir < 2)
        str = str.substr(startIndex, str.size() - startIndex);
    if (TrimDir != 1)
        str = str.substr(0, str.find_last_not_of(ChrsToTrim) + 1);

	// Trim whitespace from both sides of '='
	if (str.at(0) != '#')
		str = replace_all(str, " ", "");
	if (str.at(0) != '#')
		str = replace_all(str, "\t", "");
}

//inline void TrimRight(std::string& str, const std::string & ChrsToTrim = " \t\n\r")
//{
//    Trim(str, ChrsToTrim, 2);
//}

//inline void TrimLeft(std::string& str, const std::string & ChrsToTrim = " \t\n\r")
//{
//    Trim(str, ChrsToTrim, 1);
//}

// A function to transform a string to uppercase if neccessary
//void UCase(std::string& str, bool ucase)
//{
//	if(ucase)
//		transform(str.begin(), str.end(), str.begin(), toupper);
//}

void Config::set_filename(const string& filename)
{
    config_name_ = filename;
}


bool Config::load()
{
    assert(!config_name_.empty());

	if (loaded_)
    {
		return true;
    }

    string s;                                   // 配置文件的一行
    string current_section;                     // 保存当前section name

	std::ifstream infile(config_name_.c_str());
    if (!infile.is_open())
    {
        return false;
    }

    content_.clear(); 

    string comments = ""; // 保存注释

    while (!std::getline(infile, s).eof()) // 循环读取一行知道遇到文件结尾
    {
        Trim(s); // 剪切空白
        if (!s.empty())	
        {
            Entity entity;
            if ((s[0] == '#') || (s[0] == ';'))	// 注释行？
            {
                // 注释行: 没有[和=的行 
                if ((s.find('[') == string::npos) 							
                    && (s.find('=') == string::npos))
                {
                    // 追加注释
                    comments += s + '\n';
                }
                else
                {
                    entity.commented = s[0];	// save the comment character
                    s.erase(s.begin());	// Remove the comment for further processing
                    Trim(s);
                }
            }
            else
            {
                // 标记不是注释
				entity.commented = ' ';
            }

            if (s.find('[') != string::npos) // section?
            {
                // 删除开头的[
                s.erase(s.begin());	
                // 删除结尾的]
                s.erase(s.find(']'));
                // 添加注释
                entity.comments = comments;
                // section名称
                entity.section = s;
                // 默认key
                entity.key = "";
                // 默认value
                entity.value = "";
                current_section = s;
                // 清空注释重信使用
                comments = "";
            }

            if (s.find('=') != string::npos) // key/value行?
            {
                entity.comments = comments;
                comments = "";
                entity.section = current_section;
                entity.key = s.substr(0, s.find('='));
                entity.value = s.substr(s.find('=') + 1);
            }

            if (comments == "") // 不是注释行，保存entity
            {
                content_.push_back(entity);
            }
        }
    }

    infile.close();	

    loaded_ = true;

    return true;
}

bool Config::save()
{
    assert(!config_name_.empty());

	std::ofstream outfile(config_name_.c_str());
    if (!outfile.is_open())
    {
        return false;
    }

    for (int i = 0; i < (int)content_.size(); i++)
    {
        outfile << content_[i].comments;
		if (content_[i].commented != ' ')
        {
			outfile << content_[i].commented;
        }

		if(content_[i].key == "")
        {
			outfile<< "[" << content_[i].section << "]" << std::endl;
        }
		else
        {
			outfile << content_[i].key << "=" << content_[i].value << std::endl;
        }
    }

    outfile.close();

    return true;
}

bool Config::IsFileExist()
{
	assert(!config_name_.empty());
	
    struct stat file_info;

    if (0 == stat(config_name_.c_str(), &file_info))
    {
        return true;
    }

    return false;
}

bool Config::create()
{
    if (IsFileExist())
    {
        return true;
    }

    return save();
}

std::vector<std::string> Config::GetSectionNames()
{
    vector<string> data;
    vector<Entity> &content = content_;

    if (load())
    {
        for (int i = 0; i < (int)content.size(); i++)
        {
            if (content[i].key == "") // If there is no key value, then its a section
            {
                data.push_back(content[i].section);
            }
        }
    }

    return data;
}

std::vector<Config::Entity> Config::sections()
{
    vector<Entity> data;
    vector<Entity>& content = content_;	

    if (load())
    {
        for (int i = 0; i < (int)content.size(); i++)
        {
            if (content[i].key == "") // section
            {
                data.push_back(content[i]);
            }
        }
    }

    return data;
}

std::vector<Config::Entity> Config::section(const string &section_name)
{
    vector<Entity> data;
    vector<Entity>& content = content_;

    if (load())
    {
        for (int i = 0; i < (int)content.size(); i++)
        {
            if (content[i].section == section_name && content[i].key != "")
            {
                data.push_back(content[i]);	
            }
        }
    }

    return data;
}

std::vector<Config::Entity> Config::entity(const string &key, const string &section_name)
{
    vector<Entity> data;
    vector<Entity>& content = content_;

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        if (iter == content.end())
        {
            // Entity没有找到
            return data;
        }

        data.push_back(*iter);
    }

    return data;
}

std::string Config::value(const string &key, const string &section_name)
{
    vector<Entity> ent = entity(key, section_name);

    if (!ent.empty())
    {
        return ent[0].value;
    }

    return "";
}

std::string Config::content()
{
    string s = "";	
    vector<Entity> &content = content_;

    if (load())	
    {
        for (int i = 0; i < (int)content.size(); i++)
        {
            if (content[i].comments != "")
            {
				s += content[i].comments;
            }

            if (content[i].commented != ' ')
            {
				s += content[i].commented;
            }

            if ((content[i].key == ""))	
            {
                s += '[' + content[i].section + ']';
            }
            else
            {
                s += content[i].key + '=' + content[i].value;
            }

            if (i != (int)content.size())
            {
                s += '\n';
            }
        }
        return s;
    }

    return "";
}

bool Config::IsSectionExists(const string &section_name)
{
    vector<Entity>& content = content_;	

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionIs(section_name));

        if (iter == content.end())
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool Config::IsEntityExists(const string &key, const string &section_name)
{
    vector<Entity>& content = content_;	

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        if (iter == content.end())
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool Config::AddSection(const string &section_name, bool saving/* = false*/)
{
    vector<Entity> &content = content_;

    if (!create())
    {
        return false;
    }

    if (load())
    {
        if (!IsSectionExists(section_name))
        {
            // 定义默认实体
 			Entity ent = {"", ' ', section_name, "", ""};	
            // 相当于
            // ent.comments  = "";
            // ent.commented = ' ';
            // ent.section   = section_name;
            // ent.key       = ""
            // ent.value     = "";

            content.push_back(ent);

            if (saving)
            {
                return save();
            }

            return true;
        }
		else
        {
        	return true;
        }
    }

    return false;
}

bool Config::set_value(const string &key, const string &value, const string &section_name, bool saving/* = false*/)
{
    vector<Entity>& content = content_;

    if (!create())
    {
        return false;
    }

    if (load())
    {
        if (!IsSectionExists(section_name))		
        {
            Entity s = { "", ' ', section_name, "", "" };
            Entity r = { "", ' ', section_name, key, value };

            content.push_back(s); // Add the section
            content.push_back(r); // Add the record
        }

        if (!IsEntityExists(key, section_name))
        {
            vector<Entity>::iterator iter = std::find_if(content.begin(),
                content.end(),
                Config::EntitySectionIs(section_name));

            iter++;	
            Entity ent = {"", ' ', section_name, key, value};

            vector<Entity>::iterator orderiter = std::find_if_not(iter,
                content.end(),
                Config::EntitySectionIs(section_name));
            content.insert(orderiter, ent);									// Add the record
        }

        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        iter->value = value;

        if (saving)
        {
            return save();
        }

        return true;
    }

    return false;
}

bool Config::DeleteSection(const string &section_name, bool saving/* = false*/)
{
    vector<Entity>& content = content_;	

    if (load())
    {
        for (int i = (int)content.size() - 1; i > -1; i--)
        {
            if (content[i].section == section_name)	
            {
                content.erase(content.begin() + i);	
            }
        }

        if (saving)
        {
            return save();
        }

        return true;
    }

    return false;
}

bool Config::DeleteEntity(const string &key, const string &section_name, bool saving/* = false*/)
{
    vector<Entity>& content = content_;

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        if (iter == content.end())
        {
            return false;
        }

        content.erase(iter);

        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::RenameSection(const string &old_section_name, const string &new_section_name, bool saving/* = false*/)
{
    vector<Entity>& content = content_;

    if (!IsSectionExists(new_section_name))
    {
        for (vector<Entity>::iterator iter = content.begin();
            iter < content.end(); iter++)
        {
            if (iter->section == old_section_name)
            {
                iter->section = new_section_name;
            }
        }

        if (saving)
        {
            return save();
        }

        return true;
    }

    return false;
}

bool Config::Sort(bool descending, bool saving/* = false*/)
{
    vector<Config::Entity> content;
    vector<Config::Entity> sections = this->sections();

    if (!sections.empty())
    {
        if (descending)
        {
            std::sort(sections.begin(), sections.end(), DescendingSectionSort());
        }
        else
        {
            std::sort(sections.begin(), sections.end(), AscendingSectionSort());
        }

        for (vector<Entity>::iterator iter = sections.begin(); iter != sections.end(); iter++)
        {
            content.push_back(*iter);

            vector<Config::Entity> entities = this->section(iter->section);

            if (descending)
            {
                std::sort(entities.begin(), entities.end(), DescendingEntitySort());
            }
            else
            {
                std::sort(entities.begin(), entities.end(), AscendingEntitySort());
            }

            for (vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
            {
                content.push_back(*it);
            }
        }

        content_.clear();
        std::copy(content.begin(), content.end(), std::back_inserter(content_));

        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::SetSectionComments(const string &comments, const string &section_name, bool saving/* = false*/)
{
	string cs = comments;
    vector<Entity> &content = content_;

    if (load())
    {
        for (vector<Entity>::iterator iter = content.begin(); iter != content.end(); iter++)
        {
            if ((iter->section == section_name) && (iter->key == ""))
            {
                if (comments.size() >= 2)
                {
                    if (comments.substr(comments.size() - 2) != "\n")		// Does the string end in a newline?
                    {
						cs += "\n";
                    }
                }

				iter->comments = cs;

                if (saving)
                {
                    return save();
                }
                return true;
            }
        }
    }

    return false;
}

bool Config::SetEntityComments(const string &comments, const string &key, const string &section_name, bool saving/* = false*/)
{
	string cs = comments;
    vector<Entity>& content = content_;

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        if (iter == content.end())
        {
            return false;
        }

        if (comments.size() >= 2)
        {
            if (comments.substr(comments.size() - 2) != "\n")
            {
				cs += "\n";
            }
        }

		iter->comments = cs;

        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::CommentSection(char c, const string &section_name, bool saving/* = false*/)
{
    vector<Entity> &content = content_;

    if (load())
    {
        for (vector<Entity>::iterator iter = content.begin(); iter != content.end(); iter++)
        {
            if (iter->section == section_name)								// Is this the right section?
            {
                iter->commented = c;							        // Change the comment value
            }
        }
        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::CommentEntity(CommentChar cc, const string &key, const string &section_name, bool saving/* = false*/)
{
    vector<Entity> &content = content_;

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));

        if (iter == content.end())
        {
            return false;
        }

        iter->commented = cc;

        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::UnCommentSection(const string &section_name, bool saving/* = false*/)
{
    vector<Entity> &content = content_;

    if (load())
    {
        for (vector<Entity>::iterator iter = content.begin(); iter != content.end(); iter++)
        {
            if (iter->section == section_name)
            {
                iter->commented = ' ';	// Remove the comment value
            }
        }
        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

bool Config::UnCommentEntity(const string &key, const string &section_name, bool saving/* = false*/)
{
    vector<Entity> &content = content_;

    if (load())
    {
        vector<Entity>::iterator iter = std::find_if(content.begin(),
            content.end(),
            Config::EntitySectionKeyIs(section_name, key));	

        if (iter == content.end())
        {
            return false;
        }

        iter->commented = ' ';

        if (saving)
        {
            return save();
        }
        return true;
    }

    return false;
}

} // namespace basic_util
