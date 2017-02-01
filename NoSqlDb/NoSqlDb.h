#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2017       //
/////////////////////////////////////////////////////////////////////
/*
* If you elect to use this code, you will need to add
* - manual information
* - maintenance information
* - query mechanism
* - persistance mechanism
* - TestExecutive that demonstrates the requirements you meet
*/
/*
* - fixed bug in NoSqlDb::count() by replacing
*   unordered_map<key,Value>::count() with
*   unordered_map<key,Value>::size();
*/

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../CppProperties/CppProperties.h"
using namespace std;

/////////////////////////////////////////////////////////////////////
// Element class represents a data record in our NoSql database
// - in our NoSql database that is just the value in a key/value pair
// - it needs to store child data, something for you to implement
//
template<typename Data>
class Element
{
public:
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Description = std::string;
	using Children = std::vector<string>;

	Property<Name> name;				// metadata
	Property<Category> category;		// metadata
	Property<TimeDate> timeDate;		// metadata
	Property<Description> description; //metadata
	Property<Children> children;		//children
	Property<Data> data;               // data

	std::string show();
	//void EditValue(string name,string data);
};

template<typename Data>
std::string Element<Data>::show()
{
	// show children when you've implemented them

	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n    " << std::setw(8) << "description" << " : " << description;
	out << "\n    " << std::setw(8) << "children" << " : " << convertVectorToString(children);
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n";
	return out.str();
}




/////////////////////////////////////////////////////////////////////
// NoSqlDb class is a key/value pair in-memory database
// - stores and retrieves elements
// - you will need to add query capability
//   That should probably be another class that uses NoSqlDb
//
template<typename Data>
class NoSqlDb
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	bool deleteKey(Element<Data> ele);
	void AddChildren(string parent, Element<Data> child);
	void DeleteChildren(string parent, Element<Data> child);
	Element<Data> value(Key key);
	void EditValue(string name, string data, string type);
	size_t count();
private:
	using Item = std::pair<Key, Element<Data>>;

	std::unordered_map<Key, Element<Data>> store;
};

template<typename Data>
typename NoSqlDb<Data>::Keys NoSqlDb<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

template<typename Data>
bool NoSqlDb<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}

template<typename Data>
Element<Data> NoSqlDb<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}

template<typename Data>
size_t NoSqlDb<Data>::count()
{
	return store.size();
}

template<typename Data>
bool NoSqlDb<Data>::deleteKey(Element<Data> ele)
{
	if (store.find(ele.name) != store.end()) {
		store.erase(ele.name);
		return 1;
	}
	else {
		cout << "The element is not found in the store" << endl;
		return 0;
	}
}
template<typename Data>
void NoSqlDb<Data>::AddChildren(string parent, Element<Data> child)
{
		Element<Data> element = value(parent);

		vector<string> vec1;
		vec1 = element.children;

		vec1.push_back(child.name);
		element.children = vec1;

		
		store[parent] = element;
}

template<typename Data>
void NoSqlDb<Data>::DeleteChildren(string parent, Element<Data> child)
{
	Element<Data> element = value(parent);

	vector<string> vec1;
	vec1 = element.children;

	//vec1.erase(child.name);
	//int int_to_remove = n;
	vector<string>::iterator result = find(vec1.begin(), vec1.end(), child.name);
	vec1.erase(result);
	element.children = vec1;


	store[parent] = element;
}



template<typename Data>
void NoSqlDb<Data>::EditValue(string name, string data,string type) {
	Element<Data> element = value(name);

	if (type == "description") {
		element.description = data;
	}
	if (type == "category") {
		element.category = data;
	}
	if (type == "data") {
		element.data = data;
	}
	if (type == "timeDate") {
		element.timeDate = data;
	}
	store[name] = element;
	//return ele;
}
/////////////////////////////////////////////////////////////////////
// Persistance class
// - you will need to implement that using the XmlDocument class
//   from Handouts/Repository