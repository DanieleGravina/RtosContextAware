/* 
 * File:   subscribe.cpp
 * Author: nando
 * 
 * Created on May 30, 2014, 11:40 AM
 */

#include "subscribe.h"

subscribe::subscribe() {
    
}

subscribe::subscribe(const subscribe& orig) {
}

subscribe::~subscribe() {
}

void subscribe::setState(bool x){
    subscribe::state=x;
}

bool subscribe::getState(){
    return subscribe::state;
}

void subscribe::change(bool y){
 static bool firstCall = false;
 
 bool preState= subscribe::getState();
 subscribe::setState(y);
    if(!firstCall)
        firstCall=true;
    else
    {
        if(preState == false && subscribe::getState() == true)
            subscribe::setTrans(TRIGGER_rule::IN_OUT);
        if(preState == true && subscribe::getState() == false)
            subscribe::setTrans(TRIGGER_rule::OUT_IN);
    }

}

//void subscribe::addFunction(function_pointer f){
//    subscribe::clients.push_back(f);
//}
//void subscribe::removeFunction(function_pointer f){
//    subscribe::clients.remove(f);
//    
//}

void subscribe::handler(TRIGGER_rule::rules r){

}


bool subscribe::record(TRIGGER_rule::rules x, function_pointer f){
    if(x == TRIGGER_rule::IN_OUT){
        subscribe::getClientsINOUT().push_back(f);
        return true;
    }
    if((x == TRIGGER_rule::OUT_IN)){
        subscribe::getClientsOUTIN().push_back(f);
        return true;
    }
    return false;
    
}

 TRIGGER_rule::rules subscribe::getTrans(){
    return subscribe::trans;
 
 }

 bool subscribe::unrecord(function_pointer f){
     bool flag=false;
     std::list<function_pointer>::iterator it;
     
     //iterator to begin
     it= subscribe::getClientsINOUT().begin();
     while(it !=subscribe::getClientsINOUT().end()){
         if(*it == f){
             subscribe::getClientsINOUT().erase(it);
             flag=true;
         }
         it++;
     }
     //iterator to begin
     it=subscribe::getClientsOUTIN().begin();
     while(it !=subscribe::getClientsOUTIN().end()){
         if(*it == f){
             subscribe::getClientsOUTIN().erase(it);
             flag=true;
         }
         it++;
     }
     
     return flag;
 
 
 }

