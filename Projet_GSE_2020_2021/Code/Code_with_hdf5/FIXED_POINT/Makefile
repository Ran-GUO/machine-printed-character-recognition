CC=gcc

IDIR = /usr/include/hdf5/serial/
CFLAGS = -I$(IDIR) -O3
LIBS = -lhdf5_serial -lm

lenet_cnn_fixed_point: lenet_cnn_fixed_point.o fc.o pool.o conv.o utils.o
	$(CC) -o lenet_cnn_fixed_point lenet_cnn_fixed_point.o fc.o pool.o conv.o utils.o $(LIBS)


fc.o: fc.c 
	$(CC) -c fc.c $(CFLAGS)

pool.o: pool.c 
	$(CC) -c pool.c $(CFLAGS)

conv.o: conv.c 
	$(CC) -c conv.c $(CFLAGS)

utils.o: utils.c 
	$(CC) -c utils.c $(CFLAGS)

lenet_cnn_fixed_point.o: lenet_cnn_fixed_point.c 
	$(CC) -c lenet_cnn_fixed_point.c $(CFLAGS)

clean: 
	rm -r lenet_cnn_fixed_point.o utils.o lenet_cnn_fixed_point conv.o pool.o fc.o
