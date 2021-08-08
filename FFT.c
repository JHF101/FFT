#include <math.h>
#define pi 3.14159265358979323846
/* Standard Library of Complex Numbers */
#include <complex.h>
/* Standard Library of Input and Output */
#include <stdio.h>

/*_______________________________________________________________*/
/*            FFT Algorithm Implementation Variables             */
/*_______________________________________________________________*/
int reverseBits(unsigned int num, unsigned int powerNum);
void fftAlgorithm(double[],int);
void bitReversalIndexFunc(int);
void fftNormalize(int);

int bitReversal[] = {};                                 // Bit reversed array 
double adcOutput[] = {1.0,2.6,1.5,2.0,10,1.2,1.5,1.0};  // Test Array
double complex fftOut[] = {};                           // FFT Output Array
double fftMag[] = {};                                   // FFT Magnitude Array
/*_______________________________________________________________*/


int main()
{   
    /*_____________________________________________*/
    /*              FFT Algorithm                  */
    /*_____________________________________________*/
    int numN = sizeof(adcOutput)/sizeof(*adcOutput);
	fftAlgorithm(adcOutput, numN);

}

/* ============================================================= */
/*                           Bit Reversal                        */
/* ______________________________________________________________*/
/* This bitReversalIndexFunc return an array containing only the */
/* indexes, the mapping of those values is handled in the FFTAlgo*/
/* ============================================================= */
void bitReversalIndexFunc(int numN){
    
    int powerNum = log(numN)/log(2);
    int numberOfVals = pow(2,powerNum);
    
    for (int i=0; i<numN; i++) {
        bitReversal[i]=reverseBits(i,powerNum);
    }
    
}

/* ======================================================================================== */
/*             Function to reverse bits of num                                              */
/*__________________________________________________________________________________________*/
// Code adapted from:                                                                       //
// https://www.geeksforgeeks.org/write-an-efficient-c-program-to-reverse-bits-of-a-number/  //
/* ======================================================================================== */
int reverseBits(unsigned int num, unsigned int numOfBits)
{
    // num: is the index value postion
    // numOfBits: is x in the 2^(x) of the number of samples
    
    unsigned int reversedNumber = 0;
    
    // Reflecting the bits
    for (int i = 0; i < numOfBits; i++)
    {   
        if((num & (1 << i)))
           reversedNumber |= 1 << ((numOfBits - 1) - i);  
    }
    return reversedNumber;
}

/* ============================================================= */
/*                           FFT Algorithm                       */
/* ______________________________________________________________*/
/* This bitReversalIndexFunc return an array containing only the */
/* indexes, the mapping of those values is handled in the FFTAlgo*/
/* ============================================================= */
void fftAlgorithm(double *x_input, int numN) {
    
    double complex x_in[numN]; 
    
    // Changing the bitreversal array	
	bitReversalIndexFunc(numN);

    // temporary array where the values of x_input can be handled
    double complex new_x[numN];

    // Reindexing with values in the array
    for (int i=0; i<numN; i++) {
        int bitReversalInt = bitReversal[i];
        new_x[i] = x_input[bitReversalInt];
    }
    
    // Assigning the new_x array to the x_in array to work with
    for (int i=0; i<numN; i++ ) {
        x_in[i] = new_x[i];
    }
    
    // m is x in the 2^(x) of the number of samples
    int m = log(numN)/log(2);

    // ========================================================= //
    // Adapted from pseudocode pg 131 "Digital Signal Processing://
    // A Practical Approach" - Second Edition by Emmanuel        //
    // C. Ifeachor and Barrie Jervis                             //
    // ========================================================= //
    for (int s=1; s<m+1; s++){

        double bSeperation = pow(2,s);
        double bWidth = pow(2,s-1);

        for (int j=0;j<bWidth;j++){

            double theta = 2*pi*j/bSeperation;
            double complex wn = cos(theta)-I*sin(theta);

            for (int top=j;top<numN;top+=bSeperation) {
                int bottom = top + bWidth;

                double complex temp = x_in[bottom] * wn;

                x_in[bottom] = x_in[top] - temp;
                x_in[top] = x_in[top] + temp;
            }
        }
    }
    // ========================================================= //
    
    for (int i=0; i<numN; i++ ) {
        fftOut[i] = x_in[i];
    }
    
    fftNormalize(numN);
}

/* ============================================================= */
/*                     Normalizing the FFT                       */
/* ______________________________________________________________*/
/* Obtaining the normalized logorithmic values from FFTAlgo      */
/* ============================================================= */
void fftNormalize(int numN) {
    
    printf("Magntitude: \n");

    // Handling the DC offset 
    fftMag[0] = 20*log10( ( sqrt( pow( creal(fftOut[0]),2 ) + pow( cimag(fftOut[0]),2 ) ) ) /numN);
    printf("%lf + i%lf\n", creal(fftMag[0]), cimag(fftMag[0]));
    printf("\n");
    
    // magnitude 
    for (int i=1; i<numN; i++) {
        fftMag[i] = 20*log10( ( sqrt ( pow( creal(fftOut[i]),2 ) + pow( cimag(fftOut[i]),2) )*2) / numN);
        printf("%lf + i%lf\n", creal(fftMag[i]), cimag(fftMag[i]));
        printf("\n");
    }

}