#include <iostream>


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


char Lab1(int x, int y, int z) {
    if (x == 1 || x == 2) {
        return 'A';
    }
    else if (y <= 10) {
        return 'B';
    }
    else if (z < 5) {
        return 'C';
    }
    else {
        return 'D';
    }
}


int main() {

    const int TEST_NUM = 10;
    int xData[] = { 1, 2, -1, -1, -1, -1, 3, 3, 3, 3 };
    int yData[] = {NULL, NULL, 9, 10, 11, 11, 9, 10, 11, 11 };
    int zData[] = {NULL, NULL, NULL, NULL, 4, 5, NULL, NULL, 4, 5};

    int expectedResult[] = {'A', 'A', 'B', 'B', 'C', 'D', 'B', 'B', 'C', 'D'};

    for (int i = 0; i < TEST_NUM; i++) {
        char ret = Lab1(xData[i], yData[i], zData[i]);
        if (ret == expectedResult[i]) {
            std::cout << "Test case " << i + 1 << " passed" << std::endl;
        }
        else {
            std::cout << "Test case " << i + 1 << " failed" << std::endl;
        }
    }

	return 0;
}