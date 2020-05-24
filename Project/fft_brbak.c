#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <complex.h> 
#include "inReal.h"

#define len 16

typedef struct cn 
{
    float real;
    float imag;
} cmplx;

//Complex Multiplication

cmplx cadd(cmplx a , cmplx b){
    cmplx c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;

    return c;
}

cmplx csub(cmplx a , cmplx b){
    cmplx c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;

    return c;
}

cmplx cmul(cmplx a , cmplx b){
    cmplx c;

    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + b.real * a.imag;

    return c;
}

void populate(cmplx *arr){
    for(int i=0; i < len; i++){
        arr[i].real = inReal[i];
    }
}

void cooley_tukey(cmplx *arr, cmplx *oparr)
{
    cmplx tmparr[len]; 
    int n=log2(len), bin[n], storarr[n], nos[n];
    int half = len/2;
    cmplx wm;

    for (int i = 0; i < len; i++){

        int a = i, val = 0, base = 1;

        for(int j = 0; j < n; j++){
            bin[j] = a & 0x01 ? 1 : 0;
            //printf("%d ", bin[j]);
            a>>=1;
        }

        printf("\n");
        
       for (int k = n-1; k > -1; k--){
            val = val + bin[k] * base;
            base = base * 2;
        }
        printf("New Address Order: ");
        printf("%d ", val);

        tmparr[val].real = arr[i].real;
        tmparr[val].imag = arr[i].imag;
    }

    printf("\n \n");

    for (int i = 0; i < len; i++){
        oparr[i].real = tmparr[i].real;
        oparr[i].imag = tmparr[i].imag;
    }
    //Finished Bit reversal.
    printf("Reordered Array vs Original Array:\n");
    for(int y=0; y<len; y++){
        printf("%f + %fi || %f + %fi\n", oparr[y].real, oparr[y].imag, arr[y].real, arr[y].imag);
    }
    printf("\n\n");


    cmplx t;

    for (int i = 0; i < n; i++){
        int s=pow(2,i);
        cmplx oddarr[s], evenarr[s];
        int Li = s, Ki = 0, tf = 0;
        for (int k = 0, l = s; k < Li && l < len && tf < Li;) {
            printf("%d, %d for stride %d\n", k,l,s);

		    t.real = cos(2 * M_PI * tf / len);
            t.imag = -sin(2 * M_PI * tf / len);
            
            t = cmul(t,oparr[l]);

		    oparr[k] = cadd(oparr[k], t);
		    oparr[l] = csub(oparr[k], t);

            printf("TF = %d \n", tf);

            if(k+1<Li){
                k=k+1;
                l=l+1;
                tf++;
            }
            else{
                k =Ki + 2*s;
                l =Li + 2*s;
                Li = l;
                Ki = k;
                tf = 0;
            }
            
        }
        printf("Stride done \n\n");
    }

}

//do dft like in recursive by calculating dft of strides of two then four till len/2 to calculate DFT
void main()
{
    cmplx array[len], oparray[len];
    int stride, half = len/2;
    
    populate(array);

    printf("\n");
    /*printf("Initial Array \n");
    for (int j = 0; j < len; j++)
    {
        printf("%1.1f ", array[j].real);
        if(j==len-1)
            printf("\n \n");
    }*/

    
    cooley_tukey(array,oparray);
    printf("Reordered Array: \n");

    for (int j = 0; j < len; j++)
    {
        printf("%1.1f + %1.1fi, \n", oparray[j].real, oparray[j].imag);
        if(j==len-1)
            printf("\n \n");
    }

}