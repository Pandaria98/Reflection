# Reflection

Simple reflection implementation in C++

# Usage

## Application

We can use `Reflect::createObject` to instantiate an object

The class which implements reflection can invoke method `invoke` with a string to invoke the real method(for now, it only supports the member function whose return type and arguments are both `void`)

```cpp
// main.cpp

#include "reflect.h"
#include "testclass.h"


int
main(void) {
    TestClass *test = (TestClass *)Reflect::createObject("TestClass");
    
    // check the definition of TestClass::spam and TestClass::foo below
    test->invoke("spam");  
    test->invoke("foo");

    delete test;
    return 0;
}
```

```
Console Output:
ADDR: [3485b8] ,The Object Name is "TestClass" construced!
spam spam spam
foo was called
ADDR: [3485b8] ,The Object Name is "TestClass" destroyed!
```

## Declaration and Registration

Inherit class `Reflect` for the class needs reflection

Then use `DECLARE_CLASS` to declare the members for reflection, and `REGISTER_METHODS` to register methods

```cpp
// testclass.h
class TestClass : public Reflect {
    DECLARE_CLASS(TestClass)
    REGISTER_METHODS(
        REGISTER_METHOD(TestClass, spam)
        REGISTER_METHOD(TestClass, foo)
    )

public:
    TestClass();
    virtual ~TestClass();

    void spam();
    void foo();
};
```

Also, we need to use `REGISTER_CLASS` to register class outside header file

```cpp
// testclass.cpp
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
    std::cout << "spam" << std::endl;
}

void
TestClass::foo() {
    std::cout << "foo" << std::endl;
}
```

