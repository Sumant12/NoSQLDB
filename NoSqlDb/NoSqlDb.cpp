/////////////////////////////////////////////////////////////////////
// NoSqlDb.cpp - key/value pair in-memory database                 //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////

#include "NoSqlDb.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

using StrData = std::string;
using intData = int;
using Key = NoSqlDb<StrData>::Key;
using Keys = NoSqlDb<StrData>::Keys;

std::string convertVectorToString(vector<string> vec) {
	std::ostringstream oss;
	string res;

	// Convert all but the last element to avoid a trailing ","
	if (!vec.empty()) {
		std::copy(vec.begin(), vec.end() - 1,
			std::ostream_iterator<string>(oss, ","));

		// Now add the last element with no delimiter
		oss << vec.back();

		res = oss.str();

	}

	return res;
}

int main()
{
	std::cout << "\n  Demonstrating NoSql Helper Code";
	std::cout << "\n =================================\n";

	std::cout << "\n  Creating and saving NoSqlDb elements with string data";
	std::cout << "\n -------------------------------------------------------\n";

	NoSqlDb<StrData> db;
	// current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	std::string dt = ctime(&now);
	Element<StrData> elem1;
	vector<string> vec1;
	vec1.push_back("childelement1");
	vec1.push_back("childelement2");
	vec1.push_back("childelement3");
	elem1.name = "elem1";
	elem1.category = "test";
	elem1.data = "elem1's StrData";
	elem1.description = "First Element";
	elem1.timeDate = dt;
	//elem1.children = vec1;


	db.save(elem1.name, elem1);
	vector<string> vec2;
	//vec2.push_back("childElement4");
	//vec2.push_back("childElement5");
	vec2.push_back(elem1.name);

	Element<StrData> elem2;
	elem2.name = "elem2";
	elem2.category = "test";
	elem2.data = "elem2's StrData";
	elem2.description = "Second Element";
	elem2.timeDate = dt;
	elem2.children = vec2;

	db.save(elem2.name, elem2);

	////Adding children to the element
	//db.addChildren(elem1, elem2);
	//db.save(elem1.name, elem1);
	//db.save(elem2.name, elem2);

	Element<StrData> elem3;
	vector<string> vec3;
	//vec3.push_back("childElement6");
	//vec3.push_back("childElement7");
	//vec3.push_back("childElement8");
	vec3.push_back(elem2.name);
	elem3.name = "elem3";
	elem3.category = "test";
	elem3.data = "elem3's StrData";
	elem3.description = "Third Element";
	elem3.timeDate = dt;
	elem3.children = vec3;

	db.save(elem3.name, elem3);

	std::cout << "\n  Retrieving elements from NoSqlDb<string>";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys = db.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	db.deleteKey(elem3);


	std::cout << "\n  Retrieving elements from NoSqlDb<string> after deletion of a element";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys1 = db.keys();
	for (Key key : keys1)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	//Editing Values
	db.EditValue(elem1.name, "The new desc","description");
	db.EditValue(elem1.name, "The new category", "description");
	db.EditValue(elem1.name, "The new category", "category");
	db.EditValue(elem1.name, "The new data", "data");
	//db.EditValue(elem1.category, "The new timeDate", dt+);
	
	
	std::cout << "\n  Retrieving elements from NoSqlDb<string> after editing the information of the first element";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys2 = db.keys();
	for (Key key : keys2)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";

	db.AddChildren(elem1.name, elem3);



	std::cout << "\n  Retrieving elements from NoSqlDb<string> after adding children from the first element";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys3 = db.keys();
	for (Key key : keys3)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}



	db.DeleteChildren(elem1.name, elem3);


	std::cout << "\n  Retrieving elements from NoSqlDb<string> after deleting children from the first element";
	std::cout << "\n ------------------------------------------\n";

	std::cout << "\n  size of db = " << db.count() << "\n";
	Keys keys4 = db.keys();
	for (Key key : keys4)
	{
		std::cout << "\n  " << key << ":";
		std::cout << db.value(key).show();
	}
	std::cout << "\n\n";




	std::getchar();
}