#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

void bitreorder(float *arr, int N){
    int tmparr[N], n=log2(N), bin[n], storarr[n], nos[n];

    int  val = 0, base = 1;

    for (int i = 0; i < N; i++){
        int a=i;
        for(int j = 0; j < n; j++){
            bin[j] = a & 0x01 ? 1 : 0;
            printf("%d ", bin[j]);
            a>>=1;
        }
        printf("\n");
        
       for (int i = n-1; i > -1; i--){
            val = val + bin[i] * base;
            base = base * 2;
        }
        printf("Decimal Value = %d \n", val);

        tmparr[val] = arr[i];
    }

    for (int i = 0; i < N; i++){
        arr[i] =tmparr[i];
    }
}

void main(){
    float array[8] = {0,1,2,3,4,5,6,7};

    bitreorder(array,8);
    printf("Final Array: ");

    for (int i = 0; i < 8; i++){
        printf("%1.1f ", array[i]);
        if(i==7)
            printf("\n");
    }



}