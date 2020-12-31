/**
  ******************************************************************************
  * @file    pool.c
  * @author  GUO Ran et BARRIGA Ricardo
  * @version V1.0
  * @date    14 Sep 2020
  * @brief   Plain C code for the implementation of Convolutional Neural Networks on FPGA
  * @brief   Design the progress pool1 and pool2 (with method max and average)
  */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lenet_cnn_float.h"

//The methode max pooling
//success rate 94.050003%
void Pool1_24x24x20_2x2x20_2_0(	float 	input[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH], 	    // IN
				float 	output[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH]){         // OUT
  int i=0; //NBOUTPUT
  int j_in=0; //input height
  int k_in=0; //input width
  int j_out=0; //output height
  int k_out=0; //output width

  for (i=0; i<CONV1_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV1_HEIGHT;j_in+=2){
      j_out=j_in/2;
      for(k_in=0;k_in<CONV1_WIDTH;k_in+=2){
	      k_out=k_in/2;
        //at first we compare the 4 value in the cell 2*2
        float max_p=-1000;
        if(input[i][j_in][k_in]>max_p){
          max_p=input[i][j_in][k_in];
        }
        if(input[i][j_in+1][k_in]>max_p){
          max_p=input[i][j_in+1][k_in];
        }
        if(input[i][j_in][k_in+1]>max_p){
          max_p=input[i][j_in][k_in+1];
        }
        if(input[i][j_in+1][k_in+1]>max_p){
          max_p=input[i][j_in+1][k_in+1];
        }
	//we take this max value max_p, and assign it to output
        if(j_out<=POOL1_HEIGHT && k_out<=POOL1_WIDTH){
	        output[i][j_out][k_out]=max_p;	  
        }
        else{
          printf("error: j_out=%d \t k_out=%d \n",j_out,k_out);
        }
      }
    }
  }

}

void Pool2_8x8x40_2x2x40_2_0(	float 	input[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH], 	    // IN
				float 	output[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH]){	// OUT
  int i=0; //NBOUTPUT
  int j_in=0; //conv height
  int k_in=0; //conv width
  int j_out=0; //pool height
  int k_out=0; //pool width

  for (i=0; i<CONV2_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV2_HEIGHT;j_in+=2){
      j_out=j_in/2;
      for(k_in=0;k_in<CONV2_WIDTH;k_in+=2){
        k_out=k_in/2;
        //at first we compare the 4 value in the cell 2*2
        float max_p=-1000;
        if(input[i][j_in][k_in]>max_p){
          max_p=input[i][j_in][k_in];
        }
        if(input[i][j_in+1][k_in]>max_p){
          max_p=input[i][j_in+1][k_in];
        }
        if(input[i][j_in][k_in+1]>max_p){
          max_p=input[i][j_in][k_in+1];
        }
        if(input[i][j_in+1][k_in+1]>max_p){
          max_p=input[i][j_in+1][k_in+1];
        }
        //we take this max value max_p, and assign it to output
        if(j_out<=POOL2_HEIGHT && k_out<=POOL2_WIDTH){
          output[i][j_out][k_out]=max_p;
        }	
      	else{
      	  printf("error: j_out=%d \t k_out=%d \n",j_out,k_out);
	      }	
      }
    }
  }

}


//======================================================================================================================================================================================================================================================================================================================================
//the method average pooling
//success rate 94.580002%
/*
void Pool1_24x24x20_2x2x20_2_0(	float 	input[CONV1_NBOUTPUT][CONV1_HEIGHT][CONV1_WIDTH], 	    // IN
				float 	output[POOL1_NBOUTPUT][POOL1_HEIGHT][POOL1_WIDTH]){         // OUT
  int i=0; //NBOUTPUT
  int j_in=0; //conv height
  int k_in=0; //conv width
  int j_out=0; //pool height
  int k_out=0; //pool width

  for (i=0; i<CONV1_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV1_HEIGHT;j_in+=2){
        
      for(k_in=0;k_in<CONV1_WIDTH;k_in+=2){	
	
	//we take the average value, and assign it to output
        if(j_out<=POOL1_HEIGHT && k_out<=POOL1_WIDTH){
	  output[i][j_out][k_out]=(input[i][j_in][k_in]+input[i][j_in+1][k_in]+input[i][j_in][k_in+1]+input[i][j_in+1][k_in+1])/4.0;	  
        }
	else{
	  printf("error: j_out=%d \t k_out=%d \n",j_out,k_out);
	}
	++k_out;
      }
      ++j_out;
      k_out=0;
    }
    j_out=0;
  }

}

void Pool2_8x8x40_2x2x40_2_0(	float 	input[CONV2_NBOUTPUT][CONV2_HEIGHT][CONV2_WIDTH], 	    // IN
				float 	output[POOL2_NBOUTPUT][POOL2_HEIGHT][POOL2_WIDTH]){	// OUT
  int i=0; //NBOUTPUT
  int j_in=0; //conv height
  int k_in=0; //conv width
  int j_out=0; //pool height
  int k_out=0; //pool width

  for (i=0; i<CONV2_NBOUTPUT;i++){
    for(j_in=0;j_in<CONV2_HEIGHT;j_in+=2){
      for(k_in=0;k_in<CONV2_WIDTH;k_in+=2){

	//we take the average value, and assign it to output
	if(j_out<=POOL2_HEIGHT && k_out<=POOL2_WIDTH){
	   output[i][j_out][k_out]=(input[i][j_in][k_in]+input[i][j_in+1][k_in]+input[i][j_in][k_in+1]+input[i][j_in+1][k_in+1])/4.0;
	}	
      	else{
      	  printf("error: j_out=%d \t k_out=%d \n",j_out,k_out);
	}
	++k_out;
      }
      ++j_out;
      k_out=0;
    }
    j_out=0;
  }

}
*/
