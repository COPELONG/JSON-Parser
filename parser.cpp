#include"parser.h"

using namespace JSON;
using namespace std;


Parser::Parser():m_str(""),m_index(0) {

}
void Parser::load(const string& name) {
	m_str = name;
	m_index = 0;
}
void Parser::skip() {
	while (m_str[m_index] == ' ' || m_str[m_index] == '\r' || m_str[m_index] == '\t' || m_str[m_index] == '\n') {
		m_index++;
	}
}
char Parser::get_next_token() {
	skip();
	return m_str[m_index++];
}
Json Parser::parse() {
	char c = get_next_token();
	switch (c)
	{
	case 'n':
		m_index--;
		return parse_null();
	case 't':
	case 'f':
		m_index--;
		return parse_bool();
	case '-':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		m_index--;
		return parse_number();
	case '"':
		return Json(parse_string());
	case '[':
		return parse_array();
	case '{':
		return parse_object();
	default:
		break;
	}
	throw new logic_error("NO!");
}
Json Parser::parse_null() {
	if (m_str.compare(m_index, 4, "null")==0) {
		m_index += 4;
		return Json();
	}
	throw new logic_error("NO Compare");
}
Json  Parser::parse_bool() {
	if (m_str.compare(m_index, 4, "true") == 0) {
		m_index += 4;
		return Json(true);
	}
	if (m_str.compare(m_index, 5, "false") == 0) {
		m_index += 5;
		return Json(false);
	}
	throw new logic_error("NO Compare");
	
}
Json  Parser::parse_number() {
	int pos = m_index;
	if(m_str[m_index]=='-'){
		m_index++;
	}
	while (m_str[m_index]>'9'&& m_str[m_index]<'0') {
		throw new logic_error("NO ");
	}
	while (m_str[m_index] <= '9' && m_str[m_index] >= '0') {
		m_index++;
	}
	
	if (m_str[m_index] != '.') {
		int i = atoi(m_str.c_str() + pos);
		return Json(i);
	}
	m_index++;
	while (m_str[m_index] <= '9' && m_str[m_index] >= '0') {
		m_index++;
	}
	
	double j= atof(m_str.c_str() + pos);
	return Json(j);

	
}

Json  Parser::parse_array() {
	Json arr(Json::Json_array);//创建一个数组
	char ch = get_next_token();
	if (ch == ']') {
		return arr;
	}
	m_index--;
	while (true) {
		arr.append(parse());
		ch = get_next_token();
		if (ch == ']') {
			break;
		}
		if (ch != ',')
		{
			throw std::logic_error("expected ',' in array");
		}
	}
	return arr;
}
Json Parser::parse_object() {
	Json obj(Json::Json_object);
	
	char ch = get_next_token();
	if (ch == '}') {
		return obj;
	}
	m_index--;
	while (true) {
		ch = get_next_token();
		if (ch!='"') {
			throw new logic_error("NO");
		}
		string key = parse_string();
		ch = get_next_token();
		if (ch != ':'){
			throw new logic_error("NO");
		}
		obj[key] = parse();
		ch = get_next_token();
		if (ch == '}')
		{
			break;
		}
		if (ch != ',') {
			throw new logic_error("NO");
		}
		
	}
	return obj;
}
string  Parser::parse_string() {
	int pos = m_index;
	char ch;
	while (true) {
		ch = m_str[m_index++];
		if (ch=='"') {
			break;
		}
		if (ch == '\\') {
			ch = m_str[m_index++];
			switch (ch)
			{
			case 'b':
			case 't':
			case 'n':
			case 'f':
			case 'r':
			case '"':
				break;
			case 'u':
				m_index += 4;
				break;
			default:
				break;
			}
		}
	}
	return m_str.substr(pos, m_index - pos - 1);
}