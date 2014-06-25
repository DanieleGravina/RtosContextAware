/* 
 * File:   subscribe.cpp
 * Author: nando
 * 
 * Created on May 30, 2014, 11:40 AM
 */

#include "subscribe.h"

subscribe::subscribe() {
   
}


subscribe::~subscribe() {
}

void subscribe::setState(bool x) {
    subscribe::state = x;
}

bool subscribe::getState() {
    return subscribe::state;
}

TRIGGER_rule::rules subscribe::getTrans() {
    return subscribe::trans;
}

void subscribe::setTrans(TRIGGER_rule::rules x){
    subscribe::trans=x;
}

std::list<function_pointer> subscribe::getClientsINOUT(){
    
return subscribe::clients_INOUT;
}
    
std::list<function_pointer> subscribe::getClientsOUTIN(){

return subscribe::clients_OUTIN;
}
//------------------------------------------------------------------------

void subscribe::change(bool y) {
    static bool firstCall = false;
    
    
    bool preState = subscribe::getState();
    subscribe::setState(y);

    if (!firstCall)
        firstCall = true;
    else {
        if (preState == false && subscribe::getState() == true)
            subscribe::setTrans(TRIGGER_rule::IN_OUT);
        if (preState == true && subscribe::getState() == false)
            subscribe::setTrans(TRIGGER_rule::OUT_IN);

    }
    
    if( (subscribe::getClientsINOUT().size() + subscribe::getClientsOUTIN().size()) != 0)
        pthread_create( &t1, NULL, &subscribe::handler_helper, NULL);
    
}

//void subscribe::addFunction(function_pointer f){
//    subscribe::clients.push_back(f);
//}
//void subscribe::removeFunction(function_pointer f){
//    subscribe::clients.remove(f);
//    
//}

void *subscribe::handler() {
    std::list<function_pointer>::iterator it;
    void (*foo)();

    if (subscribe::getTrans() == TRIGGER_rule::IN_OUT) {
        it = subscribe::getClientsINOUT().begin();
        while (it != subscribe::getClientsINOUT().end()) {
            foo = (*it);
            foo();
            it++;
        }
    }
    else
    {
    it = subscribe::getClientsOUTIN().begin();
        while (it != subscribe::getClientsOUTIN().end()) {
            foo = (*it);
            foo();
            it++;
        }
    
    }
    return 0;
}

bool subscribe::record(TRIGGER_rule::rules x, function_pointer f) {    
 
    void (*foo)();
    
    foo = *f;
   
    
    if (x == TRIGGER_rule::IN_OUT) {
         foo();
        subscribe::clients_INOUT.push_back(*f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        subscribe::clients_OUTIN.push_back(*f);
        return true;
    }
    return false;

}

bool subscribe::unrecord(function_pointer f) {
    bool flag = false;
    std::list<function_pointer>::iterator it;
        
    for(it = subscribe::clients_INOUT.begin();it != subscribe::clients_INOUT.end();){//do{
         
          if(*it == *f) {
            it=subscribe::clients_INOUT.erase(it);
            flag = true;
          }
          else
                ++it;
     }
    
    for(it = subscribe::clients_OUTIN.begin();it != subscribe::clients_OUTIN.end();){
          if(*it == *f) {
            it=subscribe::clients_OUTIN.erase(it);
            flag = true;
          }
          else
                ++it;
     }
    

    return flag;

}

