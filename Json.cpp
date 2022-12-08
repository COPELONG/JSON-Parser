#include"Json.h"
#include"parser.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include<map>
#include<list>

using namespace std;
using namespace JSON;

Json::Json(int value) :m_type(Json_int){
	m_value.m_int = value;
}
Json::Json(bool value) :m_type(Json_bool) {
	m_value.m_bool = value;
}
Json::Json(double value) :m_type(Json_double) {
	m_value.m_double = value;
}
Json::Json(const string& value) :m_type(Json_string) {
	m_value.m_string = new string(value);
}
Json::Json(const char* value) :m_type(Json_string) {
	m_value.m_string = new string(value);
}
Json::Json(Type type)  :m_type(type) {
	switch (m_type)
	{
	case Json::Json_null:
		break;
	case Json::Json_double:
		m_value.m_double = 0.0;
		break;
	case Json::Json_int:
		m_value.m_int = 0;
		break;
	case Json::Json_bool:
		m_value.m_bool = false;
		break;
	case Json::Json_array:
		m_value.m_array = new list<Json>();
		break;
	case Json::Json_object:
		m_value.m_object = new map<string, Json>();
		break;
	case Json::Json_string:
		m_value.m_string = new string("");
		break;
	default:
		break;
	}
}
Json::Json() :m_type(Json_null) {

}
Json::Json(const Json& other) : m_type(Json_null) {
	
	copy(other);

}
Json::operator bool(){
	if (m_type != Json_bool) {
		throw new  logic_error("type error");
	}
	return m_value.m_bool;
}
Json::operator int() {
	if (m_type != Json_int) {
		throw new  logic_error("type error");
	}
	return m_value.m_int;
}
Json::operator double() {
	if (m_type != Json_double) {
		throw new  logic_error("type error");
	}
	return m_value.m_double;
}
Json::operator string() {
	if (m_type != Json_string) {
		throw new  logic_error("type error");
	}
	return *(m_value.m_string);
}
Json& Json::operator [](int index) {
	if (index < 0)
	{
		throw std::logic_error("function [] index less than 0");
	}
	if (m_type != Json_array)
	{
		throw std::logic_error("function [] not an array");
	}
	int size = (m_value.m_array)->size();
	if (index >= size)
	{
		throw std::logic_error("function [] out of range");
	}
	auto it = (m_value.m_array)->begin();
	for (int i = 0; i < index; i++)
	{
		it++;
	}
	
	return *it;
}
void Json::append( const Json& value) {
	if (m_type != Json_array) {
		clear();
		m_type = Json_array;
		m_value.m_array = new list<Json>();
	}
	(m_value.m_array)->push_back(value);
}
void Json::copy(const Json& other)
{
	m_type = other.m_type;
	m_value = other.m_value;
}

Json& Json::operator = (const Json& other)
{
	clear();
	copy(other);
	return *this;
}

Json& Json::operator [] (const char* key)
{
	string name = key;
	return (*this)[name];
}

Json& Json::operator [] (const string& key)
{
	if (m_type != Json_object)
	{
		clear();
		m_type = Json_object;
		m_value.m_object = new std::map<string, Json>();
	}
	return (*(m_value.m_object))[key];
}
string Json::str() const
{
	stringstream ss;
	switch (m_type)
	{
	case Json_null:
		ss << "null";
		break;
	case Json_bool:
		if (m_value.m_bool)
		{
			ss << "true";
		}
		else
		{
			ss << "false";
		}
		break;
	case Json_int:
		ss << m_value.m_int;
		break;
	case Json_double:
		ss << m_value.m_double;
		break;
	case Json_string:
		ss << "\"";
		ss << *(m_value.m_string);
		ss << "\"";
		break;
	case Json_array:
	{
		ss << "[";
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		{
			if (it != (m_value.m_array)->begin())
			{
				ss << ",";
			}
			ss << (*it).str();
		}
		ss << "]";
	}
	break;
	case Json_object:
	{
		ss << "{";
		for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
		{
			if (it != (m_value.m_object)->begin())
			{
				ss << ",";
			}
			ss << "\"" << it->first << "\":" << it->second.str();
		}
		ss << "}";
	}
	break;
	default:
		break;
	}
	return ss.str();
}

void Json::clear()
{
	switch (m_type)
	{
	case Json_null:
	case Json_bool:
	case Json_int:
	case Json_double:
		break;
	case Json_string:
	{
		delete m_value.m_string;
	}
	break;
	case Json_array:
	{
		for (auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++)
		{
			it->clear();
		}
		delete m_value.m_array;
	}
	break;
	case Json_object:
	{
		for (auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++)
		{
			it->second.clear();
		}
		delete m_value.m_object;
	}
	break;
	default:
		break;
	}
	m_type = Json_null;
}

bool Json::operator ==(const Json& value) {
	if (m_type != value.m_type) {
		return false;
	}
	switch (value.m_type)
	{
	case Json_null:
		return true;
	case Json_bool:
		return m_value.m_bool == value.m_value.m_bool;
	case Json_int:
		return m_value.m_int == value.m_value.m_int;
	case Json_double:
		return  m_value.m_double == value.m_value.m_double;
	case Json_array:
		return m_value.m_array == value.m_value.m_array;
	case Json_object:
		return m_value.m_object == value.m_value.m_object;
	case Json_string:
		return *m_value.m_string == *value.m_value.m_string;
	default:
		break;
	}

	return false;

}
bool Json::operator !=(const Json& value) {
	return !((*this)==value);
} 

int Json::asInt() const {
	if (m_type!=Json_int) {
		throw new logic_error("Type error");
	}
	return m_value.m_int;
}

double Json::asDouble()const {
	if (m_type != Json_double) {
		throw new logic_error("Type error");
	}
	return m_value.m_double;
}
string Json::asString()const {
	if (m_type != Json_string) {
		throw new logic_error("Type error");
	}
	return *(m_value.m_string);
}
bool Json::asBool() const {
	if (m_type != Json_bool) {
		throw new logic_error("Type error");
	}
	return m_value.m_bool;
}

bool Json::has(int index) const{
	if (m_type!= Json_array) {
		return false;
	}
	if (m_value.m_array->size() <= index && index < 0) {
		return  false;
	}
	return true;
}
bool Json::has(const char* key) const {
	string name(key);
	return (*this).has(name);
}
bool Json::has(const string& key) const {
	if (m_type != Json_object) {
		return false;
	}
	return m_value.m_object->find(key) == m_value.m_object->end();
}
void Json::remove(int index) {
	if (m_type != Json_array)
	{
		return;
	}
	int size = (m_value.m_array)->size();
	if (index < 0 || index >= size)
	{
		return;
	}
	auto it = (m_value.m_array)->begin();
	for (int i = 0; i < index; i++)
	{
		it++;
	}
	it->clear();
	(m_value.m_array)->erase(it);

}
void Json::remove(const char* key) {
	string name(key);
	return remove(name);
}
void Json::remove(const string& key) {
	/*if (!has(key)) {
		throw new logic_error("NO key");
	}*/
	auto it = m_value.m_object->find(key);
	if (it == m_value.m_object->end()) {
		return;
	}
	it->second.clear();
	m_value.m_object->erase(key);
}
void Json::parse(const string& str) {
	Parser p;
	p.load(str);
	*this = p.parse();
	
}
