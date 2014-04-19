#ifndef _FFT_H_
#define _FFT_H_

#include "complex.h"
#include "math.h"

class CFFT
{
public:
        /**
         * Compute the FFT on the sample data vector
         * @param Data -input and output data
         * @param N -length of sample data
         * @return true if no errors occured
         */
	static bool Forward(complex *const Data, const unsigned int N);

	
        
        /**
         * Compute the avarage of data
         * @param Data
         * @param N -length of sample data 
         * @return the avarage 
         */
        static double Avg(const complex *const Data, const unsigned int N);

private:
	/**
         * Rearrange data
         * @param Data
         * @param N
         */
	static void Rearrange(complex *const Data, const unsigned int N);

	/**
         * Perform FFT
         * @param Data
         * @param N
         * @param Inverse
         */
	static void Perform(complex *const Data, const unsigned int N, const bool Inverse = false);

        /**
         * Scaling of inverse FFT result
         * @param Data
         * @param N
         */
	static void Scale(complex *const Data, const unsigned int N);
};

#endif
