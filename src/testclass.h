#pragma once


#include "reflect.h"


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
