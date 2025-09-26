#include <iostream>

int fun2(int a) {
    return a + 2;
}

int fun1(int a) {
    return fun2(a + 1);
}

int main() {
    std::cout << fun1(0x42424242) << std::endl;
    return 0;
}
