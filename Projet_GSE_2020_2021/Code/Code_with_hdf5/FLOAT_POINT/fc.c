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

#include "lenet_cnn_float.h"


void Fc1_40_400(	float 	input[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH], 			        // IN
		        float 	kernel[FC1_NBOUTPUT][POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH],	// IN
			      float 	bias[FC1_NBOUTPUT],							                        // IN
			      float 	output[FC1_NBOUTPUT]){ 							                    // OUT

  int i_out=0; //Fc1_NBoutput=400;
  int i_in=0; //Pool2_NBoutput=40
  int j=0; //pool2_height=4;
  int k=0; //pool2_width=4;
  
  for(i_out=0;i_out<FC1_NBOUTPUT;i_out++){
    output[i_out]=0;
    for(i_in=0;i_in<POOL2_NBOUTPUT;i_in++){
      for(j=0;j<POOL2_HEIGHT;j++){
        for(k=0;k<POOL2_WIDTH;k++){
          output[i_out]+=input[i_in][j][k]*kernel[i_out][i_in][j][k];
        }
      }
    }
    output[i_out]+=bias[i_out];
    output[i_out]=(output[i_out]>0)? output[i_out]:0;
  } 
}

void Fc2_400_10(	float 	input[FC1_NBOUTPUT], 			        // IN
		        float 	kernel[FC2_NBOUTPUT][FC1_NBOUTPUT],	    // IN
		        float 	bias[FC2_NBOUTPUT],			            // IN
		      	float 	output[FC2_NBOUTPUT]){ 			        // OUT

  for(int i=0;i<FC2_NBOUTPUT;i++){
    output[i]=0;
    for(int j=0;j<FC1_NBOUTPUT;j++){
      output[i]+=input[j]*kernel[i][j];
    }
    output[i]+=bias[i];
    output[i]=(output[i]>0)? output[i]:0;
  }
}

void Softmax(float vector_in[FC2_NBOUTPUT], float vector_out[FC2_NBOUTPUT]){
  float sum=0.0;

  for(int i=0;i<FC2_NBOUTPUT;i++){
    vector_out[i]=(vector_in[i]>=0)? vector_in[i]:0 ;
    sum+= expf(vector_out[i]);
  }
  for(int i=0;i<FC2_NBOUTPUT;i++){
    vector_out[i] = expf(vector_out[i])/sum;
  }
}
