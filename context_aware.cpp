#include "context_aware.h"
        
ContextAware::ContextAware(subscribe& sub){
    _sub = sub;
}

ContextAware::~ContextAware(){
    
}

bool ContextAware::registration(TRIGGER_rule::rules t, function_pointer f){
    _sub.record(t, f);
}

bool ContextAware::unregistration(function_pointer f){
    _sub.unrecord(f);
}
