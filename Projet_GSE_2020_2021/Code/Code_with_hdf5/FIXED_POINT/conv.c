/**
  ******************************************************************************
  * @file    conv.c
  * @author  GUO Ran et BARRIGA Ricardo
  * @version V1.0
  * @date    14 Sep 2020
  * @brief   Plain C code for the implementation of Convolutional Neural Networks on FPGA
  * @brief   Design the progress conv1 and conv2
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lenet_cnn_fixed_point.h"


void Conv1_28x28x1_5x5x20_1_0(	short 		    input[IMG_DEPTH][IMG_HEIGHT][IMG_WIDTH], 	                // IN
			        short 		    kernel[CONV1_NBOUTPUT][IMG_DEPTH][CONV1_DIM][CONV1_DIM], 	// IN
		       	short 		    bias[CONV1_NBOUTPUT],			                // IN
				short 		    output[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH]){  	// OUT
	unsigned short i=0; //le depth apres convolution (0-20)
	unsigned short j_out=0; //HEIGHT=24
	unsigned short k_out=0; //WIDTH=24
	int sum;
  
  for(i=0;i<CONV1_NBOUTPUT;++i){ //20  
    for(j_out=0;j_out<(CONV1_HEIGHT );j_out+=CONV1_STRIDE){//24
      for(k_out=0;k_out< (CONV1_WIDTH);k_out+=CONV1_STRIDE){//24
			sum=0;
			for(int h_conv=0;h_conv<CONV1_DIM;++h_conv){
			  for(int w_conv=0;w_conv<CONV1_DIM;++w_conv){
			    sum+=(kernel[i][IMG_DEPTH-1][h_conv][w_conv]) * (input[0][j_out + h_conv][k_out+w_conv]);

		      }
		     }
			  output[i][j_out][k_out]=(sum >> FIXED_POINT) + bias[i];
			  output[i][j_out][k_out]= (output[i][j_out][k_out]>0)? output[i][j_out][k_out]:0;		       
		    }                   
  		}
	  }
	}



void Conv2_12x12x20_5x5x40_1_0( short input[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH], 	            // IN
			        short kernel[CONV2_NBOUTPUT][POOL1_NBOUTPUT][CONV2_DIM][CONV2_DIM], 	// IN
	       	        short bias[CONV2_NBOUTPUT], 						                    // IN
				short output[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH]){		        // OUT
	int i_out=0;//le depth apres convolution 40
	int j_out=0;//HEIGHT=8
	int k_out=0;//WIDTH=8

	for(i_out=0;i_out<CONV2_NBOUTPUT;++i_out){//40
		for(j_out=0;j_out<(CONV2_HEIGHT);j_out+=CONV2_STRIDE){//8
			for(k_out=0;k_out<(CONV2_WIDTH);k_out+=CONV2_STRIDE){//8
				int sum=0;
				for(int n=0;n<POOL1_NBOUTPUT;n++){
					for(int h_conv=0;h_conv<CONV2_DIM;++h_conv){
						for(int w_conv=0;w_conv<CONV2_DIM;++w_conv){
							sum+=kernel[i_out][n][h_conv][w_conv] * input[n][j_out+h_conv][k_out+w_conv];
						}
					}
				}
	  			output[i_out][j_out][k_out]=(sum >> FIXED_POINT) + bias[i_out];	
	  			output[i_out][j_out][k_out]= (output[i_out][j_out][k_out]>0)? output[i_out][j_out][k_out]:0;
      		}
    	}
  	}    

}

