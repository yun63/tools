#ifndef __CONFIG_H_
#define __CONFIG_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include <sys/stat.h>

// 建议使用标准库作相关类型的转换
template<class RT, class IT>
static RT convert(const IT &t)
{
    RT result;
    try
    {
		std::stringstream stream;
        stream << t;
        stream >> result;
        stream.clear();
    }
    catch (...) {}

    return result;
}


using namespace std;

namespace basic_util {

class Config
{
public:
    struct Entity
    {
        string comments;
        char commented;
        string section;
        string key;
        string value;
    };

    enum CommentChar
    {
        kPound = '#',
        kSemiColon = ';'
    };

    Config();
    Config(const string &filename);
    virtual ~Config();

    void set_filename(const string &filename);
    bool create();

    vector<Entity> section(const string &section_name);
    vector<Entity> entity(const string &key, const string &section_name);
    bool set_value(const string &key, const string &value, const string &section_name, bool saving = false);
    string value(const string &key, const string &section_name);
    string content();

    bool IsFileExist();
    bool IsSectionExists(const string &section_name);
    bool IsEntityExists(const string &key, const string &section_name);

    bool AddSection(const string &section_name, bool saving = false);

    vector<string> GetSectionNames();

    bool DeleteSection(const string &section_name, bool saving = false);
    bool DeleteEntity(const string &key, const string &section_name, bool saving = false);

    bool RenameSection(const string &old_section_name, const string &new_section_name, bool saving = false);
    bool Sort(bool descending, bool saving = false);

    bool SetSectionComments(const string &comments, const string &section_name, bool saving = false);
    bool SetEntityComments(const string &comments, const string &key, const string &section_name, bool saving = false);

    bool CommentSection(char c, const string &section_name, bool saving = false);
    bool CommentEntity(CommentChar cc, const string &key, const string &section_name, bool saving = false);

    bool UnCommentSection(const string &section_name, bool saving = false);
    bool UnCommentEntity(const string &key, const string &section_name, bool saving = false);

	bool save();

private:
	bool load();	
	vector<Entity> sections();

	struct EntitySectionIs : std::unary_function<Entity, bool>
	{
		std::string section;

		EntitySectionIs(const std::string &s): section(s) {}

		bool operator()(const Entity &e) const
		{
			return section == e.section;
		}
	};

	struct EntitySectionKeyIs : std::unary_function<Entity, bool>
	{
		std::string section;
		std::string key;

		EntitySectionKeyIs(const std::string &s, const std::string &k)
            : section(s),key(k) {}

		bool operator()(const Entity &e) const
		{
			return ((section == e.section) && (key == e.key));
		}
	};

	struct AscendingSectionSort
	{
		bool operator()(const Entity &a, const Entity &b)
		{
			return a.section < b.section;
		}
	};

	struct DescendingSectionSort
	{
		bool operator()(const Entity &a, const Entity &b)
		{
			return a.section > b.section;
		}
	};

	struct AscendingEntitySort
	{
		bool operator()(const Entity &a, const Entity &b)
		{
			return a.key < b.key;
		}
	};

	struct DescendingEntitySort
	{
		bool operator()(const Entity &a, const Entity &b)
		{
			return a.key > b.key;
		}
	};

private:
    string config_name_;
    bool loaded_;
    vector<Entity> content_;
};

} // namespace basic_util

#endif
