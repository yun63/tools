// TestConfig::cpp : Defines the entry point for the console application.
//
#include <string>
#include <vector>

#include "src/config.h"

using namespace std;
using namespace basic_util;

void Show(Config &cfg)
{
	cout << endl 
		 << "++++++++++++++++++++++++++++++++++++++++"
		 << endl
		 << "+ Contents of the file are below       +"
		 << endl
		 << "++++++++++++++++++++++++++++++++++++++++"
		 << endl
         << cfg.content()
		 << endl
		 << "++++++++++++++++++++++++++++++++++++++++"
		 << endl << endl;
}

int main(int argc, char *argv[])
{
    string str_num = "555";
    cout << convert<int>(str_num) << endl;

    float f_num = 666.0f;
    cout << convert<string>(f_num) << endl;

    Config cfg("test.init");

	// Create a new file
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to create a new file called \"test.ini\"" << endl << endl;
	cout << "string FileName = \"test.ini\";" << endl;
	cout << "Config::create(FileName);" << endl << endl;
    if (cfg.create()) cout << "File was successfully created" << endl << endl;
	else cout << "Failed to create the file" << endl << endl;
	Show(cfg);

	// Create a new section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to create a new section called [MySection]" << endl << endl;
	cout << "Config::AddSection(\"MySection\", FileName);" << endl << endl;
    if (cfg.AddSection("MySection")) cout << "Section was successfully created" << endl << endl;
	else cout << "Failed to create the section" << endl << endl;
	Show(cfg);

	// Add a key to the section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to add a new key/value (MyKey=MyValue) to [MySection]" << endl << endl;
	cout << "Config::set_value(\"MyKey\",\"MyValue\",\"MySection\",FileName);" << endl << endl;
    if (cfg.set_value("MyKey", "MyValue", "MySection")) cout << "Entity was successfully created" << endl << endl;
	else cout << "Failed to create the record" << endl << endl;
	Show(cfg);

	// Add a key and create a section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to add a new key/value (TestKey=TestValue)" << endl << "and create a new section [TestSection] at the same time" << endl << endl;
	cout << "Config::set_value(\"TestKey\",\"TestValue\",\"TestSection\",FileName);" << endl << endl;
    if (cfg.set_value("TestKey", "TestValue", "TestSection")) cout << "Entity and section were successfully created" << endl << endl;
	else cout << "Failed to create the record and section" << endl << endl;
	Show(cfg);

	// Change a key value
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to change the key/value for (MyKey=MyValue) to (MyKey=YourValue)" << endl << endl;
	cout << "Config::set_value(\"MyKey\",\"YourValue\",\"MySection\",FileName);" << endl << endl;
    if (cfg.set_value("MyKey", "YourValue", "MySection")) cout << "Entity was successfully changed" << endl << endl;
	else cout << "Failed to change the record" << endl << endl;
	Show(cfg);

	// Get a value
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to get the value of MyKey" << endl << endl;
	cout << "Config::value(\"MyKey\",\"MySection\",FileName);" << endl << endl;
    string v = cfg.value("MyKey", "MySection");
	cout << "The value of MyKey is: " << v.c_str() << endl << endl;
	Show(cfg);

	// Get a list of Sections
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to get a list of sections" << endl << endl;
	cout << "Config::GetSectionNames(FileName);" << endl << endl;
    vector<string> s = cfg.GetSectionNames();
	cout << "The sections are returned as a std::vector<std::string>\n\n";
	for(int i=0; i < (int)s.size(); i++)
		cout << s[i].c_str() << endl;
	Show(cfg);

	// Section Exists
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to verify that [MySection] exists" << endl << endl;
	cout << "Config::IsSectionExists(\"MySection\",FileName);" << endl << endl;
    if (cfg.IsSectionExists("MySection")) cout << "Section exists" << endl << endl;
	else cout << "Section does not exist" << endl << endl;
	Show(cfg);

	// Entity Exists
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to verify that MyKey exists" << endl << endl;
	cout << "Config::IsEntityExists(\"MyKey\",\"MySection\",FileName);" << endl << endl;
    if (cfg.IsEntityExists("MyKey", "MySection")) cout << "Entity exists" << endl << endl;
	else cout << "Entity does not exist" << endl << endl;
	Show(cfg);

	// Case Sensitive
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "BE CAREFUL - functions in cfg are CASE-SENSITIVE" << endl << endl;
	cout << "Config::IsEntityExists(\"mykey\",\"MySection\",FileName);" << endl << endl;
    if (cfg.IsEntityExists("mykey", "MySection")) cout << "Entity exists" << endl << endl;
	else cout << "Entity does not exist" << endl << endl;
	Show(cfg);
    
	// Add a comment to the section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to add comments to [MySection]" << endl << endl;
	cout << "Config::SetSectionComments(\"# This Section was created by Config\",\"MySection\",FileName);" << endl << endl;
    if (cfg.SetSectionComments("# This Section was created by Config", "MySection")) cout << "Comments were successfully added" << endl << endl;
	else cout << "Failed to add the comments" << endl << endl;
	Show(cfg);

	// Add a comment to the record
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to add comments to MyKey" << endl << endl;
	cout << "Config::SetEntityComments(\"# This Key was created by Config\",\"MyKey\",\"MySection\",FileName);" << endl << endl;
    if (cfg.SetEntityComments("# This Key was created by Config", "MyKey", "MySection")) cout << "Comments were successfully added" << endl << endl;
	else cout << "Failed to add the comments" << endl << endl;
	Show(cfg);

	// Rename Section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to rename [MySection] to [YourSection]" << endl << endl;
	cout << "Config::RenameSection(\"MySection\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.RenameSection("MySection", "YourSection")) cout << "Section was successfully changed" << endl << endl;
	else cout << "Failed to change the section" << endl << endl;
	Show(cfg);

	// Multiple comments
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Multiple comments can be added by putting \\n# in the comments string" << endl << endl;
	cout << "Config::SetSectionComments(\"# This Section was created by Config\\n# Kids, don't try this at home \\n\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.SetSectionComments("# This Section was created by Config\n# Kids, don't try this at home", "YourSection")) cout << "Comments were successfully added" << endl << endl;
	else cout << "Failed to add the comments" << endl << endl;
	Show(cfg);

	// Remove comments
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Comments are removed by setting them to \"\"" << endl << endl;
	cout << "Config::SetEntityComments(\"\",\"MyKey\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.SetEntityComments("", "MyKey", "YourSection")) cout << "Comments were successfully removed" << endl << endl;
	else cout << "Failed to remove the comments" << endl << endl;
	Show(cfg);

	// Comment entire section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to comment the entire section [YourSection]" << endl << endl;
	cout << "Config::CommentSection(\"#\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.CommentSection('#', "YourSection")) cout << "Section was successfully commented" << endl << endl;
	else cout << "Failed to comment the section" << endl << endl;
	Show(cfg);

	// UnComment entire section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to un-comment the entire section [YourSection]" << endl << endl;
	cout << "Config::UnCommentSection(\"YourSection\",FileName);" << endl << endl;
    if (cfg.UnCommentSection("YourSection")) cout << "Section was successfully un-commented" << endl << endl;
	else cout << "Failed to un-comment the section" << endl << endl;
	Show(cfg);

	// Comment a single record
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to comment the record MyKey" << endl << endl;
	cout << "(Note that both # and ; are recognized as commented lines by cfg)" << endl << endl;
	cout << "Config::CommentEntity(Config::CommentChar::Pound,\"MyKey\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.CommentEntity(Config::CommentChar::kPound, "MyKey", "YourSection")) cout << "Entity was successfully commented" << endl << endl;
	else cout << "Failed to comment the record" << endl << endl;
	Show(cfg);

	// UnComment a single record
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to un-comment the record MyKey" << endl << endl;
	cout << "Config::UnCommentEntity(\"MyKey\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.UnCommentEntity("MyKey", "YourSection")) cout << "Entity was successfully un-commented" << endl << endl;
	else cout << "Failed to un-comment the record" << endl << endl;
	Show(cfg);

	// Sort
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to sort the file - false means ASCENDING, true means DESCENDING" << endl << endl;
	cout << "(Note that the comments will stay with their targets)" << endl << endl;
	cout << "Config::Sort(FileName,false);" << endl << endl;
    if (cfg.Sort(false)) cout << "File was successfully sorted" << endl << endl;
	else cout << "Failed to sort the file" << endl << endl;
	Show(cfg);

	// Delete entire section
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to delete the entire section [TestSection]" << endl << endl;
	cout << "Config::DeleteSection(\"TestSection\",FileName);" << endl << endl;
    if (cfg.DeleteSection("TestSection")) cout << "Section was successfully deleted" << endl << endl;
	else cout << "Failed to delete the section" << endl << endl;
	Show(cfg);

	// Delete record
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Attempting to delete the record <yKey" << endl << endl;
	cout << "Config::DeleteEntity(\"MyKey\",\"YourSection\",FileName);" << endl << endl;
    if (cfg.DeleteEntity("MyKey", "YourSection")) cout << "Entity was successfully deleted" << endl << endl;
	else cout << "Failed to delete the record" << endl << endl;
	Show(cfg);

	// Content
	cout << "Testcfg - Demo program for the Config Class" << endl << endl;
	cout << "Finally, the content of the file can be retrieved as a std::string" << endl << endl;
	cout << "Config::Content(FileName);" << endl << endl;
	cout << "The contents of the file throughout this demo have used this function to display the contents below" << endl;
	Show(cfg);

	cfg.save();

	return 0;
}
