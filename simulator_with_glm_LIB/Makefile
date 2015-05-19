CC=g++
NVCC=nvcc
CFLAGS=-c -Wall
NVCCFLAGS=-c -arch=compute_30 -code=sm_30
INCLUDES= #-I/usr/local/cuda-6.0/include
LDFLAGS= #-L/usr/local/cuda-6.0/lib64 -lcudart
SOURCES=main.cpp Body_sphere.cpp CollisionDetection.cpp Contact.cpp lcpDynamics.cpp pgs.cpp Simulation.cpp
GPU_SOURCES= #CollisionDetectionGPU.cu
OBJECTS=$(SOURCES:.cpp=.o)
GPU_OBJECTS= #$(GPU_SOURCES:.cu=.o)
EXECUTABLE=rpi-sim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(GPU_OBJECTS)
		$(CC) $(OBJECTS) $(GPU_OBJECTS) -o $@ $(LDFLAGS)

%.o : %.cpp
		$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

%.o : %.cu
		$(NVCC) $(NVCCFLAGS) $< -o $@

clean: 
	  rm -rf *o $(EXECUTABLE) 
