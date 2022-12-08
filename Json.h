#pragma once
#include<string>
#include<map>
#include<list>

#include <stdexcept>
using namespace std;
namespace JSON {
	class Json {
	public:
		enum Type {
			Json_null = 0,
			Json_double,
			Json_int,
			Json_bool,
			Json_array,
			Json_object,
			Json_string
		};
		//重载构造函数
		Json();
		Json(int value);
		Json(bool value);
		Json(double value);
		Json(const string& value);
		Json(const char * value);
		Json(Type type) ;
		Json(const Json & other);//拷贝构造
		//重载运算符
		operator bool(); 
		operator int();//int i = Json(2);
		operator double();
		operator string();
		bool operator ==(const Json& value); //J1 == J2
		bool operator !=(const Json& value);
		Json& operator = (const Json& other); //J1 = J2
		//重载数组运算符
		Json & operator [] (int index);//Json J[0] = 1
		Json& operator [] (const char* key);
		Json& operator [] (const string& key);//Json J["key"]=value;
		//-----------------------------------------
		void copy(const Json& other);//复制
		string str() const;//返回字符串
		void clear();//清除功能：对数组（集合）中的数据清除，然后在delet数组（集合）
		void append(const Json& value);//数组添加数据
		//-----------------------------------------
		//判断是否为当前类型
		bool isNULL() const { return m_type == Json_null; }
		bool isInt() const { return m_type == Json_int; }
		bool isDouble() const { return m_type == Json_double; }
		bool isArray() const { return m_type == Json_array; }
		bool isString() const { return m_type == Json_string; }
		bool isObject() const { return m_type == Json_object; }
		bool isBool() const { return m_type == Json_bool; }
		//查看值，调用返回m_value对应的数据
		int asInt()const;
		double asDouble()const;
		string asString()const;
		bool asBool() const;
		//判断有无对应索引或者key值
		bool has(int index) const;
		bool has(const char* key) const;
		bool has(const string & key) const;
		//删除操作
		void remove(int index);//删除数组对应索引的值
		void remove(const char* key);
		void remove(const string& key);//删除集合中key所对应的值

		typedef list<Json>::iterator  iterator;
		iterator begin() {
			if (m_type!=Json_array) {
				throw new logic_error("NO Json_array");
			}
			return (m_value.m_array)->begin();
		}
		iterator end() {
			if (m_type != Json_array) {
				throw new logic_error("NO Json_array");
			}
			return (m_value.m_array)->end();
		}
		//解析数据
		void parse(const string &str);
	private:
		union Value{
			bool m_bool;
			double m_double;
			int m_int;
			string* m_string;
			list<Json> *  m_array;//定义为指针类型
			map<string, Json> *  m_object;
		};
		Value m_value;
		Type m_type;
	};
}