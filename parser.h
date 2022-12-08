#pragma once
#include<iostream>
#include"Json.h"
using namespace std;

namespace JSON {
	class Parser {
	public:
		Parser();
		void load(const string &name);//初始化数据
		Json parse();//解析总函数，用来调用详细类型的解析函数

	private:
		void skip();//解析忽略空白符
		char get_next_token();//获取下一个字符
		Json parse_null();//解析null
		Json parse_bool();//解析bool
		Json parse_number();//解析数字类型
		Json parse_array();//解析数组类型
		Json parse_object();//解析map类型
		string parse_string();//解析字符串类型 
	private:
		string m_str;
		int m_index;

	};



}