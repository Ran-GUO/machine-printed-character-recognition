/**
  ******************************************************************************
  * @file    fc.c
  * @author  GUO Ran et BARRIGA Ricardo
  * @version V1.0
  * @date    14 Sep 2020
  * @brief   Plain C code for the implementation of Convolutional Neural Networks on FPGA
  * @brief   Design the progress Fc1 and Fc2 et Softmax
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "lenet_cnn_fixed_point.h"


void Fc1_40_400(	short 	input[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH], 			        // IN
		              short 	kernel[FC1_NBOUTPUT][POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH],	// IN
                  short 	bias[FC1_NBOUTPUT],							                        // IN
                  short 	output[FC1_NBOUTPUT]){ 							                    // OUT
      int i_out=0; //Fc1_NBoutput=400;
      int i_in=0; //Pool2_NBoutput=40
      int j=0; //pool2_height=4;
      int k=0; //pool2_width=4;
      int tmp;
  for(i_out=0;i_out<FC1_NBOUTPUT;i_out++){
    tmp=0;
    for(i_in=0;i_in<POOL2_NBOUTPUT;i_in++){
      for(j=0;j<POOL2_HEIGHT;j++){
	      for(k=0;k<POOL2_WIDTH;k++){
	        tmp+=input[i_in][j][k]*kernel[i_out][i_in][j][k];
	      }
      }
    }
    tmp=(tmp >> FIXED_POINT)+bias[i_out];
    tmp=(tmp>0)? tmp:0;
    output[i_out]=(short)tmp;
  } 
}

void Fc2_400_10(	short 	input[FC1_NBOUTPUT], 			        // IN
		        short 	kernel[FC2_NBOUTPUT][FC1_NBOUTPUT],	    // IN
		        short 	bias[FC2_NBOUTPUT],			            // IN
			      short 	output[FC2_NBOUTPUT]){ 			        // OUT
  int tmp;
  for(int i=0;i<FC2_NBOUTPUT;i++){
    tmp=0;
    for(int j=0;j<FC1_NBOUTPUT;j++){
      tmp+=input[j]*kernel[i][j];
    }
    tmp=(tmp >> FIXED_POINT)+bias[i];
    output[i]=(tmp>0)? (short)tmp:0;
  }
}

void Softmax(short vector_in[FC2_NBOUTPUT], float vector_out[FC2_NBOUTPUT]){
  float sum=0.0;

  for(int i=0;i<FC2_NBOUTPUT;i++){
    vector_out[i]=(vector_in[i]>=0)? (double)vector_in[i]:0 ;
    sum += expf((double)vector_out[i]/(double)(1<<FIXED_POINT));
  }
  for(int i=0;i<FC2_NBOUTPUT;i++){
    vector_out[i] = expf((double)vector_out[i]/(double)(1<<FIXED_POINT))/sum;
  }
}



















