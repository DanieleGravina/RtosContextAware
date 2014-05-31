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

void subscribe::addFunction(function_pointer f){
    subscribe::v.push_back(f);
}
void subscribe::removeFunction(function_pointer f){
    vector <function_pointer> v= subscribe::getV();
    vector <function_pointer>::iterator i = v.begin();
    int pos;
    
   // i= find(v.begin(),v.end(),f);
    pos= distance(v.begin(), i);
    
    //v.erese(pos);
    
}

void subscribe::handler(TRIGGER_rule::rules r){

}


