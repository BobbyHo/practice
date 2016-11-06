# A simple Makefile for the recursion program

CC = g++

DEBUG = -g
#CXXFLAGS = -std=c++0x

TARGET = recursion

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(DEBUG) -o $(TARGET) $(TARGET).cpp

clean: 
	$(RM) $(TARGET)
