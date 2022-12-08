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
		//���ع��캯��
		Json();
		Json(int value);
		Json(bool value);
		Json(double value);
		Json(const string& value);
		Json(const char * value);
		Json(Type type) ;
		Json(const Json & other);//��������
		//���������
		operator bool(); 
		operator int();//int i = Json(2);
		operator double();
		operator string();
		bool operator ==(const Json& value); //J1 == J2
		bool operator !=(const Json& value);
		Json& operator = (const Json& other); //J1 = J2
		//�������������
		Json & operator [] (int index);//Json J[0] = 1
		Json& operator [] (const char* key);
		Json& operator [] (const string& key);//Json J["key"]=value;
		//-----------------------------------------
		void copy(const Json& other);//����
		string str() const;//�����ַ���
		void clear();//������ܣ������飨���ϣ��е����������Ȼ����delet���飨���ϣ�
		void append(const Json& value);//�����������
		//-----------------------------------------
		//�ж��Ƿ�Ϊ��ǰ����
		bool isNULL() const { return m_type == Json_null; }
		bool isInt() const { return m_type == Json_int; }
		bool isDouble() const { return m_type == Json_double; }
		bool isArray() const { return m_type == Json_array; }
		bool isString() const { return m_type == Json_string; }
		bool isObject() const { return m_type == Json_object; }
		bool isBool() const { return m_type == Json_bool; }
		//�鿴ֵ�����÷���m_value��Ӧ������
		int asInt()const;
		double asDouble()const;
		string asString()const;
		bool asBool() const;
		//�ж����޶�Ӧ��������keyֵ
		bool has(int index) const;
		bool has(const char* key) const;
		bool has(const string & key) const;
		//ɾ������
		void remove(int index);//ɾ�������Ӧ������ֵ
		void remove(const char* key);
		void remove(const string& key);//ɾ��������key����Ӧ��ֵ

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
		//��������
		void parse(const string &str);
	private:
		union Value{
			bool m_bool;
			double m_double;
			int m_int;
			string* m_string;
			list<Json> *  m_array;//����Ϊָ������
			map<string, Json> *  m_object;
		};
		Value m_value;
		Type m_type;
	};
}