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
#include "subscribe_light_aware.h"

using namespace std;
using namespace miosix;

/**
 * Test file to show how to use subscription with context aware
 */
void test();



#endif	/* TEST_H */

