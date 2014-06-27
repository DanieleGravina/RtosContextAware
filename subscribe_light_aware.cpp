/* 
 * File:   subscribe.cpp
 * Author: nando
 * 
 * Created on May 30, 2014, 11:40 AM
 */

#include "subscribe_light_aware.h"

subscribe_light_aware::subscribe_light_aware():
                mutexHandler(PTHREAD_MUTEX_INITIALIZER), mutexList(PTHREAD_MUTEX_INITIALIZER) 
{
  
}


subscribe_light_aware::~subscribe_light_aware() {
}

void subscribe_light_aware::setState(bool x) {
    subscribe_light_aware::state = x;
}

bool subscribe_light_aware::getState() {
    return subscribe_light_aware::state;
}

TRIGGER_rule::rules subscribe_light_aware::getTrans() {
    return subscribe_light_aware::trans;
}

void subscribe_light_aware::setTrans(TRIGGER_rule::rules x){
    subscribe_light_aware::trans=x;
}

std::list<function_pointer> subscribe_light_aware::getClientsINOUT(){
    
return subscribe_light_aware::clients_INOUT;
}
    
std::list<function_pointer> subscribe_light_aware::getClientsOUTIN(){

return subscribe_light_aware::clients_OUTIN;
}
//------------------------------------------------------------------------

void subscribe_light_aware::change(bool y) {
    subscribe_light_aware::firstCall=false;
    
 
    
    
    bool preState = subscribe_light_aware::getState();
    subscribe_light_aware::setState(y);

    if (!subscribe_light_aware::firstCall)
        subscribe_light_aware::firstCall = true;
    else {
        if (preState == false && subscribe_light_aware::getState() == true)
            subscribe_light_aware::setTrans(TRIGGER_rule::IN_OUT);
        if (preState == true && subscribe_light_aware::getState() == false)
            subscribe_light_aware::setTrans(TRIGGER_rule::OUT_IN);

    }
    printf("\nChange\n");
    if( (subscribe_light_aware::clients_INOUT.size() + subscribe_light_aware::clients_OUTIN.size()) != 0){
        printf("\nPPPPPPPPPPPPPPPP\n");
        //pthread_create( &t1, NULL, &subscribe_light_aware::handler_helper, NULL);
        handler();
    }
    
}

//void subscribe::addFunction(function_pointer f){
//    subscribe::clients.push_back(f);
//}
//void subscribe::removeFunction(function_pointer f){
//    subscribe::clients.remove(f);
//    
//}

void *subscribe_light_aware::handler() {
    std::list<function_pointer>::iterator it;
    void (*foo)();
    
    //pthread_mutex_lock(&mutexList);
    printf("\nhandler\n");
 
    if (subscribe_light_aware::getTrans() == TRIGGER_rule::IN_OUT) {
        printf("in out\n");
        //it = subscribe_light_aware::clients_INOUT.begin();
        for(it = clients_INOUT.begin();it != clients_INOUT.end(); ++it){
            printf("in for\n");
            foo = (*it);
            foo();
        }
    }
    
    else
    {
    it = subscribe_light_aware::clients_OUTIN.begin();
        
        for(it = subscribe_light_aware::clients_OUTIN.begin();it != subscribe_light_aware::clients_OUTIN.end();){//do{
            foo = (*it);
            //foo();
            ++it;
        }
    }
     //pthread_mutex_unlock(&mutexList);
    return 0;
}

bool subscribe_light_aware::record(TRIGGER_rule::rules x, function_pointer f) {    
 
//delete
    void (*foo)();
    foo = f;
    //foo();
    
    pthread_mutex_lock(&mutexList);

    if (x == TRIGGER_rule::IN_OUT) {
        subscribe_light_aware::clients_INOUT.push_back(f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        subscribe_light_aware::clients_OUTIN.push_back(f);
        return true;
    }
    pthread_mutex_unlock(&mutexList);

    return false;

}

bool subscribe_light_aware::unrecord(function_pointer f) {
    bool flag = false;
    std::list<function_pointer>::iterator it;
    
    pthread_mutex_lock(&mutexList);
    for(it = subscribe_light_aware::clients_INOUT.begin();it != subscribe_light_aware::clients_INOUT.end();){//do{
         
          if(*it == f) {
            it= subscribe_light_aware::clients_INOUT.erase(it);
            flag= true; 
          }
          else
                ++it;
     }
    
    for(it = subscribe_light_aware::clients_OUTIN.begin();it != subscribe_light_aware::clients_OUTIN.end();){
          if(*it == f) {
            it= subscribe_light_aware::clients_OUTIN.erase(it);
            flag = true;
          }
          else
                ++it;
     }
     pthread_mutex_unlock(&mutexList);
    return flag;

}

