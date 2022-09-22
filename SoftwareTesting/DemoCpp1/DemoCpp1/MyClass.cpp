#include "MyClass.h"

MyClass::MyClass() {

};

MyClass::MyClass(int age) {
	this->age = age;
};

int MyClass::getAge() {
	return this->age;
};

MyClass::~MyClass() {

};