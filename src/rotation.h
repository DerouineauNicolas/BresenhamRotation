#ifndef ROTATION_H
#define ROTATION_H   

#include <math.h>
#include <string.h> 
#include <vector>
#include <iostream>

void rotate(const uint8_t*  datain, uint8_t*  dataout, int width, int height, int stride, float angleDegree);
void rotate_method1(const uint8_t*  datain, uint8_t*  dataout, int width, int height, int stride, float angleDegree);
void rotate_method2(const uint8_t*  datain, uint8_t*  dataout, int width, int height, int stride, float angleDegree);

#endif