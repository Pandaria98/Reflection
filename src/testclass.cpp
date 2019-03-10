#include "testclass.h"


REGISTER_CLASS(TestClass)


TestClass::TestClass() {
    std::cout << "ADDR: [" << std::hex << (long)this
              << "] ,The Object Name is \"TestClass\" construced!" << std::endl;
}

TestClass::~TestClass() {
    std::cout << "ADDR: [" << std::hex << (long)this
              << "] ,The Object Name is \"TestClass\" destroyed!" << std::endl;
}

void
TestClass::spam() {
    std::cout << "spam spam spam" << std::endl;
}

void
TestClass::foo() {
    std::cout << "foo was called" << std::endl;
}
