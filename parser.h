#pragma once
#include<iostream>
#include"Json.h"
using namespace std;

namespace JSON {
	class Parser {
	public:
		Parser();
		void load(const string &name);//��ʼ������
		Json parse();//�����ܺ���������������ϸ���͵Ľ�������

	private:
		void skip();//�������Կհ׷�
		char get_next_token();//��ȡ��һ���ַ�
		Json parse_null();//����null
		Json parse_bool();//����bool
		Json parse_number();//������������
		Json parse_array();//������������
		Json parse_object();//����map����
		string parse_string();//�����ַ������� 
	private:
		string m_str;
		int m_index;

	};



}