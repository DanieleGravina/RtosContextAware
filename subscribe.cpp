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

void subscribe::setState(bool x) {
    state = x;
}

bool subscribe::getState() {
    return state;
}

void subscribe::change(bool y) {
    static bool firstCall = false;

    bool preState = getState();
    setState(y);

    if (!firstCall)
        firstCall = true;
    else {
        if (preState == false && subscribe::getState() == true)
            setTrans(TRIGGER_rule::IN_OUT);
        if (preState == true && subscribe::getState() == false)
            setTrans(TRIGGER_rule::OUT_IN);
    }

}

//void subscribe::addFunction(function_pointer f){
//    subscribe::clients.push_back(f);
//}
//void subscribe::removeFunction(function_pointer f){
//    subscribe::clients.remove(f);
//    
//}

void subscribe::handler(TRIGGER_rule::rules r) {

}

bool subscribe::record(TRIGGER_rule::rules x, function_pointer f) {
    if (x == TRIGGER_rule::IN_OUT) {
        getClientsINOUT().push_back(f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        getClientsOUTIN().push_back(f);
        return true;
    }
    return false;

}

TRIGGER_rule::rules subscribe::getTrans() {
    return trans;

}

void subscribe::setTrans(TRIGGER_rule::rules x) {
    //TODO
}

bool subscribe::unrecord(function_pointer f) {
    bool flag = false;
    std::list<function_pointer>::iterator it;

    //iterator to begin
    it = getClientsINOUT().begin();
    while (it != getClientsINOUT().end()) {
        if (*it == f) {
            getClientsINOUT().erase(it);
            flag = true;
            it = getClientsINOUT().begin();
        } else {
            it++;
        }
    }
    //iterator to begin
    it = subscribe::getClientsOUTIN().begin();
    while (it != subscribe::getClientsOUTIN().end()) {
        if (*it == f) {
            getClientsOUTIN().erase(it);
            flag = true;
            it = getClientsOUTIN().begin();
        } else {
            it++;
        }
    }

    return flag;
}

