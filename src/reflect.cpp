#include <map>

#include "reflect.h"


static std::map<std::string, ClassInfo *> *_classInfoMap = NULL;


bool
Reflect::reg(ClassInfo *info) {
    if (!_classInfoMap) {
        _classInfoMap = new std::map<std::string, ClassInfo *>();
    }
    
    if (!info) {
        return false;
    }

    auto m = _classInfoMap;
    auto name = info->_className;
    if (m->find(name) == m->end()) {
        m->insert(std::map<std::string, ClassInfo *>::value_type(name, info));
    }
    return true;
}


Reflect *
Reflect::createObject(std::string className) {
    auto result = _classInfoMap->find(className);
    if (result != _classInfoMap->end()) {
        return result->second->createObject();
    } else {
        return NULL;
    }
}
