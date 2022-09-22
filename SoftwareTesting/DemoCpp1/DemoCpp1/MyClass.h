#pragma once
#include <string>

class MyClass {
private:
	//std::string name;
	int age;
public:
	MyClass();
	MyClass(int age);
	int getAge();
	~MyClass();
};