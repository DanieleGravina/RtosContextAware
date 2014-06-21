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
<<<<<<< HEAD
    subscribe::state = x;
}

bool subscribe::getState() {
    return subscribe::state;
=======
    state = x;
}

bool subscribe::getState() {
    return state;
>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
}

void subscribe::change(bool y) {
    static bool firstCall = false;
<<<<<<< HEAD
    pthread_t t1;
    
    
    bool preState = subscribe::getState();
    subscribe::setState(y);
=======

    bool preState = getState();
    setState(y);

>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
    if (!firstCall)
        firstCall = true;
    else {
        if (preState == false && subscribe::getState() == true)
<<<<<<< HEAD
            subscribe::setTrans(TRIGGER_rule::IN_OUT);
        if (preState == true && subscribe::getState() == false)
            subscribe::setTrans(TRIGGER_rule::OUT_IN);
=======
            setTrans(TRIGGER_rule::IN_OUT);
        if (preState == true && subscribe::getState() == false)
            setTrans(TRIGGER_rule::OUT_IN);
>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
    }
    
    if( (subscribe::getClientsINOUT().size() + subscribe::getClientsOUTIN().size()) != 0)
            
        pthread_create( &t1, NULL, &subscribe::handler, NULL);

    
    

}

//void subscribe::addFunction(function_pointer f){
//    subscribe::clients.push_back(f);
//}
//void subscribe::removeFunction(function_pointer f){
//    subscribe::clients.remove(f);
//    
//}

<<<<<<< HEAD
void *subscribe::handler(void) {
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
=======
void subscribe::handler(TRIGGER_rule::rules r) {

>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
}

bool subscribe::record(TRIGGER_rule::rules x, function_pointer f) {
    if (x == TRIGGER_rule::IN_OUT) {
<<<<<<< HEAD
        subscribe::getClientsINOUT().push_back(f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        subscribe::getClientsOUTIN().push_back(f);
=======
        getClientsINOUT().push_back(f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        getClientsOUTIN().push_back(f);
>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
        return true;
    }
    return false;

<<<<<<< HEAD
}

TRIGGER_rule::rules subscribe::getTrans() {
    return subscribe::trans;

}

=======
}

TRIGGER_rule::rules subscribe::getTrans() {
    return trans;

}

void subscribe::setTrans(TRIGGER_rule::rules x) {
    //TODO
}

>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
bool subscribe::unrecord(function_pointer f) {
    bool flag = false;
    std::list<function_pointer>::iterator it;

    //iterator to begin
<<<<<<< HEAD
    it = subscribe::getClientsINOUT().begin();
    while (it != subscribe::getClientsINOUT().end()) {
        if (*it == f) {
            subscribe::getClientsINOUT().erase(it);
            flag = true;
        }
        it++;
=======
    it = getClientsINOUT().begin();
    while (it != getClientsINOUT().end()) {
        if (*it == f) {
            getClientsINOUT().erase(it);
            flag = true;
            it = getClientsINOUT().begin();
        } else {
            it++;
        }
>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
    }
    //iterator to begin
    it = subscribe::getClientsOUTIN().begin();
    while (it != subscribe::getClientsOUTIN().end()) {
        if (*it == f) {
<<<<<<< HEAD
            subscribe::getClientsOUTIN().erase(it);
            flag = true;
        }
        it++;
    }

    return flag;


=======
            getClientsOUTIN().erase(it);
            flag = true;
            it = getClientsOUTIN().begin();
        } else {
            it++;
        }
    }

    return flag;
>>>>>>> e5222b9e2f8c74d67c64a64e99d8708e145f5654
}

