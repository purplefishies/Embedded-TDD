#
# Simple makefile for google test and Embedded TDD
#
CXX	:= g++

GOOGLELIBS		:= -lgtest
LED_DRIVER_FILES	:= LedDriver.c

%:	%.c
	$(CXX) -g -I. $< $(LED_DRIVER_FILES) $(GOOGLELIBS)
