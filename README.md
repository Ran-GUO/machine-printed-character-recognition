# machine-printed-character-recognition
PROJECT_GSE_GUO_BARRIGA_2020_2021
Polytech Nice Sophia Antipolis

## Embedded AI on FPGA using High Level Synthesis

Final year project for the specialization program in Embedded Systems Engineering.

The goal of the project is the full development of a Convolutional Neural Network (CNN) accelerated on a CPU / FPGA system using High Level Synthesis (HLS).

HLS, also referred to as C synthesis, electronic system-level (ESL) synthesis, algorithmic synthesis or behavioral synthesis, is an automated design process that inputs a C / C++ like piece of code and outputs a hardware (RTL) accelerator in VHDL, Verilog or SystemC.

The CNN we want to accelerate on FPGA using HLS is based on LeNet for handwritten and machine-printed character recognition and the FPGA target is a ZedBoard platform featuring a Zynq-7000 SoC (ARM dual core Cortex-A9 / Xilinx FPGA).

# Demonstration video

https://www.youtube.com/watch?v=K3EwXGJWzeI&feature=youtu.be&fbclid=IwAR0BRoRfYfC3Q20iejlREfuPvoDNPbH7KSfbq8YA-VKav8VTYg0dE4dtjj8

# Prerequisite, compile and run

Ubuntu 18.04 / gcc 7.5.0
TensorFlow and Keras for Deep Learning
Python
Vivado
C
ZedBoard platform
SDsoc

# Command lines used in Ubuntu Terminal

To compile the project
  make && ./lenet_cnn_float
