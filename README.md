# Reflection

Simple reflection implementation in C++

# Usage

In declaration, use `DECLARE_CLASS` to declare the members for reflection, and `REGISTER_METHODS` to register methods.

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

And use `REGISTER_CLASS` to register class.

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

Now we can use `Reflect::createObject` to instantiate an object, and the class which implements reflection can invoke method `invoke` with a string to invoke the real method

```cpp
// main.cpp

#include "reflect.h"
#include "testclass.h"


int
main(void) {
    TestClass *test = (TestClass *)Reflect::createObject("TestClass");
    test->invoke("spam");
    test->invoke("foo");
    delete test;
    return 0;
}
```

```
Console Output:
ADDR: [38438] ,The Object Name is "TestClass" construced!
spam
foo
ADDR: [38438] ,The Object Name is "TestClass" destroyed!
```

