/**
 * @file servo.cpp
 *
 */
/* Copyright (C) 2017-2018 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <iostream> 
#include "pca9685servo.h"
using namespace std; 

int msleep(unsigned long milisec)   
{   
    struct timespec req={0};   
    time_t sec=(int)(milisec/1000);   
    milisec=milisec-(sec*1000);   
    req.tv_sec=sec;   
    req.tv_nsec=milisec*1000000L;   
    while(nanosleep(&req,&req)==-1)   
        continue;   
    return 1;   
}   

int main(int argc, char **argv) 
{
	if (getuid() != 0) 
	{
		fprintf(stderr, "Program is not started as \'root\' (sudo)\n");
		return -1;
	}

	PCA9685Servo servo;

	// MG90S Micro Servo
	servo.SetLeftUs(700);
	servo.SetRightUs(2400);

	servo.Dump();
	printf("Starting ......");
    printf("\n");

	servo.SetAngle(CHANNEL(0), ANGLE(90));
	servo.SetAngle(CHANNEL(1), ANGLE(90));


	sleep(1);


		for(int x =90; x<140; x++)
		{
		  servo.SetAngle(CHANNEL(0), ANGLE(x));
		  servo.SetAngle(CHANNEL(1), ANGLE(x));
          printf("Angle: %i", x);
          printf("\n");
		  msleep(200); 
	    }
	    
		for(int x =140; x>90; x--)
		{
		  servo.SetAngle(CHANNEL(0), ANGLE(x));
		  servo.SetAngle(CHANNEL(1), ANGLE(x));
          printf("Angle: %i", x);
          printf("\n");
		  msleep(200);
	    }

	return 0;
}
