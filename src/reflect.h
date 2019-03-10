#pragma once


#include <map>
#include <iostream>


#define DECLARE_CLASS(class_name)                                              \
protected:                                                                     \
    static FullClassInfo<class_name> _classInfo;                               \
                                                                               \
public:                                                                        \
    static Reflect *createObject() { return new class_name; }                  \
    void invoke(std::string methodName) {                                      \
        if (!_classInfo._methodMap) {                                          \
            this->regMethods();                                                \
        }                                                                      \
        auto method = _classInfo.getMethod(methodName);                        \
        (this->*method)();                                                     \
    }


#define REGISTER_METHOD(class_name, method_name)                               \
    _classInfo.regMethod(#method_name, &class_name::method_name);


#define REGISTER_METHODS(methods)                                              \
    public: void regMethods() { methods }


#define REGISTER_CLASS(class_name)                                             \
    FullClassInfo<class_name> class_name::_classInfo(#class_name, class_name::createObject);


#define REFLECT_CLASS(class_name)                                              \
    (class_name *)(Reflect::createObject(#class_name))


class ClassInfo;
class Reflect {
protected:
    std::map<std::string, void (Reflect::*)()> _methodsMap;
    
public:
    Reflect() {}
    virtual ~Reflect() {}

    static bool reg(ClassInfo *info);
    static Reflect *createObject(std::string className);
    
    // virtual void invoke(std::string methodName);
};


typedef Reflect *(*Constructor)(void);


class ClassInfo {
public:
    std::string _className;
    Constructor _constructor;

    ClassInfo(const std::string className, Constructor constructor)
        : _className(className), _constructor(constructor) {
        Reflect::reg(this);
    }

    Reflect *createObject() { return (*_constructor)(); }
};


template<class T>
class FullClassInfo : public ClassInfo {
    typedef void (T::*Method)();
    typedef std::map<std::string, Method> MethodMap;

public:
    MethodMap *_methodMap;

    FullClassInfo(const std::string className, Constructor constructor)
        : ClassInfo(className, constructor), _methodMap(NULL) {
    }

    void regMethod(std::string methodName, Method method) {
        if (!_methodMap) {
            _methodMap = new MethodMap();
        }

        auto m = _methodMap;
        auto name = methodName;
        if (m->find(name) == m->end()) {
            m->insert(MethodMap::value_type(name, method));
        }
    }

    Method getMethod(std::string methodName) {
        auto result = _methodMap->find(methodName);
        return result->second;
        if (result != _methodMap->cend()) {
            return result->second;
        } else {
            return NULL;
        }
    }
};
