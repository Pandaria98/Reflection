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
