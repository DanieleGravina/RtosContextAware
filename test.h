/* 
 * File:   test.h
 * Author: daniele
 *
 * Created on 27 giugno 2014, 15.42
 */

#ifndef TEST_H
#define	TEST_H

#include "miosix.h"
#include "light_aware.h"
#include <fft.h>
#include <goertzel_algorithm.h>
#include <complex.h>
#include <miosix/_examples/context_aware/adc.h>
#include "subscribe.h"
#include "subscribe_light_aware.h"

using namespace std;
using namespace miosix;

typedef Gpio<GPIOD_BASE,14> led1;
typedef Gpio<GPIOD_BASE,15> led2;

typedef Gpio<GPIOC_BASE,0> led3;

typedef Gpio<GPIOB_BASE,0> adcIn;

int test();



#endif	/* TEST_H */

