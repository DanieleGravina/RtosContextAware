/* 
 * File:   subscribe.cpp
 * Author: nando
 * 
 * Created on May 30, 2014, 11:40 AM
 */

#include "subscribe_light_aware.h"

subscribe_light_aware::subscribe_light_aware() :
        mutexHandler(PTHREAD_MUTEX_INITIALIZER), mutexList(PTHREAD_MUTEX_INITIALIZER),
        firstCall(true) 
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

void subscribe_light_aware::setTrans(TRIGGER_rule::rules x) {
    subscribe_light_aware::trans = x;
}

std::list<function_pointer> subscribe_light_aware::getClientsINOUT() {

    return subscribe_light_aware::clients_INOUT;
}

std::list<function_pointer> subscribe_light_aware::getClientsOUTIN() {

    return subscribe_light_aware::clients_OUTIN;
}
//------------------------------------------------------------------------

void subscribe_light_aware::change(bool y) {

    bool preState = state;
    state = y;

    if (firstCall)
        firstCall = false;
    else {
        if (preState == false && state == true)
            trans = TRIGGER_rule::IN_OUT;
        if (preState == true && state == false)
            trans = TRIGGER_rule::OUT_IN;
        
        if ((clients_INOUT.size() + clients_OUTIN.size()) != 0) {
            //pthread_create( &t1, NULL, &subscribe_light_aware::handler_helper, this);
            handler();
        }
    }

}

void *subscribe_light_aware::handler() {
    std::list<function_pointer>::iterator it;
    void (*foo)();

    //pthread_mutex_lock(&mutexList);

    if (trans == TRIGGER_rule::IN_OUT) {
        
        for (it = clients_INOUT.begin(); it != clients_INOUT.end(); ++it) {
            foo = (*it);
            foo();
        }
    }
    else {

        for (it = clients_OUTIN.begin(); it != clients_OUTIN.end(); ++it) {
            foo = (*it);
            foo();
        }
    }
    //pthread_mutex_unlock(&mutexList);
    return 0;
}

bool subscribe_light_aware::record(TRIGGER_rule::rules x, function_pointer f) {

    //pthread_mutex_lock(&mutexList);

    if (x == TRIGGER_rule::IN_OUT) {
        clients_INOUT.push_back(f);
        return true;
    }
    if ((x == TRIGGER_rule::OUT_IN)) {
        clients_OUTIN.push_back(f);
        return true;
    }
    //pthread_mutex_unlock(&mutexList);

    return false;

}

bool subscribe_light_aware::unrecord(function_pointer f) {
    bool flag = false;
    std::list<function_pointer>::iterator it;

    //pthread_mutex_lock(&mutexList);
    for (it = subscribe_light_aware::clients_INOUT.begin(); it != subscribe_light_aware::clients_INOUT.end();) {//do{

        if (*it == f) {
            it = subscribe_light_aware::clients_INOUT.erase(it);
            flag = true;
        } else
            ++it;
    }

    for (it = subscribe_light_aware::clients_OUTIN.begin(); it != subscribe_light_aware::clients_OUTIN.end();) {
        if (*it == f) {
            it = subscribe_light_aware::clients_OUTIN.erase(it);
            flag = true;
        } else
            ++it;
    }
    //pthread_mutex_unlock(&mutexList);
    return flag;

}

