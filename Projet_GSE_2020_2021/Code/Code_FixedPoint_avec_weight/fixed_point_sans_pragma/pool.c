/**
  ******************************************************************************
  * @file    pool.c
  * @author  GUO Ran et BARRIGA Ricardo
  * @version V1.0
  * @date    14 Dec 2020
  * @brief   Plain C code for the implementation of Convolutional Neural Networks on FPGA
  * @brief   Design the progress pool1 and pool2 (with method max and average)
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lenet_cnn_fixed_point.h"


void Pool1_24x24x20_2x2x20_2_0(	short 	input[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH], 	    // IN
					short 	output[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH]){         // OUT

  unsigned short i=0; //NBOUTPUT
  unsigned short j_in=0; //input height
  int k_in=0; //input width

  for (i=0; i<CONV1_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV1_HEIGHT;j_in+=POOL1_STRIDE){
      for(k_in=0;k_in<CONV1_WIDTH;k_in+=POOL1_STRIDE){
	      //at first we compare the 4 value in the cell 2*2
    	  short max_p=0;
    	  short max_tem=0;

        max_p= (input[i][j_in][k_in]>input[i][j_in+1][k_in])? input[i][j_in][k_in]:input[i][j_in+1][k_in];
        max_tem= (input[i][j_in][k_in+1]>input[i][j_in+1][k_in+1])? input[i][j_in][k_in+1]:input[i][j_in+1][k_in+1];
        max_p= (max_tem>max_p)? max_tem:max_p;

	      //we take this max value max_p, and assign it to output
	      output[i][j_in/2][k_in/2]=(max_p>0)? max_p : 0 ;	  
        
      }
    }
  }
}

void Pool2_8x8x40_2x2x40_2_0(	short 	input[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH], 	    // IN
				short 	output[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH]){	// OUT


  int i=0; //NBOUTPUT
  int j_in=0; //conv height
  int k_in=0; //conv width

  for (i=0; i<CONV2_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV2_HEIGHT;j_in+=POOL2_STRIDE){
      for(k_in=0;k_in<CONV2_WIDTH;k_in+=POOL2_STRIDE){

        //at first we compare the 4 value in the cell 2*2
        short max_p=0;
        short max_tem=0;

        max_p= (input[i][j_in][k_in]>input[i][j_in+1][k_in])? input[i][j_in][k_in]:input[i][j_in+1][k_in];
        max_tem= (input[i][j_in][k_in+1]>input[i][j_in+1][k_in+1])? input[i][j_in][k_in+1]:input[i][j_in+1][k_in+1];
        max_p= (max_tem>max_p)? max_tem:max_p;

        //we take this max value max_p, and assign it to output
        output[i][j_in/2][k_in/2]=(max_p>0)? max_p : 0;			
      
      }
    }
  }
}
