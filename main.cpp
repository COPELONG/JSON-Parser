#include<iostream>
#include<sstream>
#include<fstream>
#include"Json.h"
using namespace std;
using namespace JSON;
int main() {

	fstream fin("main.json");
	stringstream ss;
	ss << fin.rdbuf();
	const string& str=ss.str();
	Json v;
	v.parse(str);
	cout << v.str() << endl;

    // Json v1 = true;
        // Json v2 = 123;
        // Json v3 = 1.23;
        // Json v4 = "hello world";
        // const string & s = v4;
        // std::cout << s << std::endl;
        // std::cout << v1.str() << std::endl;
        // std::cout << v2.str() << std::endl;
        // std::cout << v3.str() << std::endl;
        // std::cout << v4.str() << std::endl;

        // bool b = v1;
        // int i = v2;
        // double f = v3;
        // const string & s = v4;

        // Json null;
        // std::cout << null.str() << std::endl;
        // return 0;

        // Json arr;
        // arr.append(123);
        // arr.append(1.23);
        // arr.append("hello world");
        // std::cout << arr.str() << std::endl;
        // std::cout << arr[0] << "," << arr[1] << "," << arr[2] << std::endl;
        // return 0;

        // // object value
        // Json obj;
        // obj["name"] = "jun";
        // obj["age"] = 18;
        // obj["arr"] = arr;
        // std::cout << obj.str() << std::endl;
        // obj.clear();
        // return 0;

	return 0;
}