#include <iostream>
//#include "MyClass.h"
#include <vector>

int test1(int a, int b, int c) {
    int t = 0;
    switch (a) {
    case 2:
        if (b > 9)
            t = 1;
        else t = 8;
        break;
    case 7:
        if ((b < 0) || (b > 10))
            t = 0;
        else
            if (c >= 3)
                t = 3;
            else t = 4;
        break;
    default:
        t = 5;
    }
    return t;
};


int TimSoDuongNhoNhat(int a, int b, int c) {
    const int MAX = 999;
    if (a > MAX || b > MAX || c > MAX) {
       std::cout << "a, b, c phai nho hon " + MAX;
       return -1;
    }

    std::vector<int> arrSoDuong;

    if (a > 0) {
        arrSoDuong.push_back(a);
    }
    else if (b > 0) {
        arrSoDuong.push_back(b);
    }
    else if (c > 0) {
        arrSoDuong.push_back(c);
    }

    // min
    int min = 999999;
    for (int num : arrSoDuong) {
        if (num < min) {
            min = num;
        }
    }

    return min;
};

int UT_Func1(int a, int b, int c, int d) {
    if (a == 0 || a == 3) {
        return a;
    }
    else if (b > 5) {
        return b;
    }
    else if (c > 5) {
        return c;
    }
    
    return -1;
}


int main() {


	int a = test1(0, 5, 3);




	/*std::cout << "Xin chao";
	MyClass mc(10);
	std::cout << "mc name: " << std::to_string(mc.getAge());*/
	return 0;
}

