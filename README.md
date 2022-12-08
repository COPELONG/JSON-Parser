# JSON-parser

## 涉及知识点

面向对象设计

构造函数重载

函数重载

函数递归

运算符重载

标准模板库

内存管理：高效的内存使用。

emum、union的巧用

## 功能模块

### API设计与实现

#### 设计Json类

##### 功能函数

![image-20221208122642388](https://github.com/COPELONG/JSON-Parser/blob/master/image/1.png)

![image-20221208122939613](https://github.com/COPELONG/JSON-Parser/blob/master/image/2.png)

![image-20221208123250134](https://github.com/COPELONG/JSON-Parser/blob/master/image/3.png)

##### 类属性

![image-20221208122642388](https://github.com/COPELONG/JSON-Parser/blob/master/image/4.png)

![image-20221208122642388](https://github.com/COPELONG/JSON-Parser/blob/master/image/5.png)

### Parser设计与实现

#### 设计parser类

![image-20221208122642388](https://github.com/COPELONG/JSON-Parser/blob/master/image/6.png)

## 知识碎片

1.cpp的命名空间 就是作用域的衍生 为特定的作用域块定义一个名字就叫名空间

- 作用: 可以避免引入多个库文件发生函数、变量名冲突的情况

```cpp
namespace xxx{
	int a
}
```

2.拷贝构造：为什么拷贝构造函数必须为const

  假如创建的是临时变量，拷贝给对象

  编译器创建的这个临时对象，不能绑定给non-const的引用。因为修改一个编译器创建的临时对象是完全没有意义的，这个临时对象随时都会被析构掉。

```c++
Json(const Json & other);
//防止改变+不能随意的析构
```

3.vector删除操作时，之后位置的迭代器会无效。

4.

```c++
char* c; 
string s="1234"; 
c = s.c_str();//返回值是const char*
```

c 最后指向的内容是垃圾，因为s对象被析构，其内容被处理，同时，编译器也将报错——将一个const char* *赋与一个char* *。

5.

```c++
m_str.compare(m_index, 4, "null")==0//找到了返回值为0.
```

6.

```c++
const string& str = "\"hello lu\"";
//解析字符串类型   \"  表示为   “  。
//当读入 \"  即表示进入字符串解析函数中。
```

7.

```c++
string s = "123.4fdshkjfhs123dkj";
cout<<atoi(s.c_str());
//自动转化为符合数字的字符串，输出为123.
```

8.map的key不能重复，重复则删去多余的key、value对

```c++
	fstream fin("main.json");
	stringstream ss;
	ss << fin.rdbuf();//读取文件流传送到ss。
	const string& str=ss.str();//转换成字符串。
```





