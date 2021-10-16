# FFT from Scratch 
Fast Fourier Transform algorithm implemented from scratch. Adapted from pseudo-code in [[1]](#1).

## Requirements 
A C-compiler is required in order to run the C-code.
Anaconda is required in order to run the Jupyter Notebook.

## Usage
This is by no means better than a library such as fftw3 and UFFT.

### C Implementation
Only the magnitude for the C implementation is calculated. It prints out the magnitude that an FFT would achieve on an arbitrary piece of data.

Run the C code using the following command in the terminal:

    gcc FFT.c -o FFT

Then to run the executable:

    ./FFT

### Jupyter Notebook Implementation 

The code in the Jupyter Notebook is a more in-depth description of what is happening in the FFT. 
This notebook does the following:

1. Calculate a DFT
2. Calculate a Radix-2 Decimation-In-Time FFT
3. Plots the twiddle factor for the different stages in an FFT Butterfly Diagram
4. Calculate the magnitude and phase of the FFT
5. Simulating what an FFT would look like on a DSP boards pixels for both magnitude and phase
6. Does a test between a DFT and FFT to ensure outputs are the same by working with generated signals

## References 
<a id="1">[1]</a>
E. C. Ifeachor and B. W. Jervis, Digital signal processing: a practical approach, 2nd ed. Harlow, England ; New York: Prentice Hall, 2002.
