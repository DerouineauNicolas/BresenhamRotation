#include "rotation.h"

#define PI 3.14159265

struct points {
    int x;
    int y;
};

void bresenham(int x0, int y0, int x1, int y1, std::vector<points>& points_output)
{
  int dx = abs(x1-x0);
  int sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0);
  int sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
  points_output.clear();
 
  for(;;){
    //setPixel(x0,y0);
    points_output.push_back({x0, y0});
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void rotate_method1(const uint8_t*  datain, uint8_t*  dataout, int width, int height, int stride, float angleDegree){
/*
This method use the bruteforce call to the rotation matrix to get output pixels positions.
There is a lot of aliasing in the output. Bilinear filtering should be applied afterwards.

*/
    //int width = srce.GetWidth();
    //int height = srce.GetHeight();
    int x0 = width/2;
    int y0 = height/2;
    int new_x, new_y;
    float cos_tmp, sin_tmp;
    cos_tmp = cos(angleDegree *PI/180 );
    sin_tmp = sin(angleDegree*PI/180);

    memset(dataout, 0, width*height);
    
    for (auto x=0; x< width;x++){
        for (auto y=0; y<height;y++){

            new_x = ((x-x0) * cos_tmp) - ((y-y0) * sin_tmp) + x0;
            new_y = ((x-x0) * sin_tmp) + ((y-y0) * cos_tmp) + y0;
            //printf(" new_x = %d \n",  new_x);
            //printf(" new_y = %d \n",  new_y);
            if ((new_x < width) && (new_y < height) 
                && (new_y > 0) && (new_x > 0))
                dataout[new_x  +stride*new_y] = datain[x+stride*y];
            
        }
    }
}


void rotate_method2(const uint8_t*  datain, uint8_t*  dataout, int width, int height, int stride, float angleDegree){
/*
This method use bessenham algorithm to reduce the number of call to the rotation matrix.
There is still a lot of aliasing in the output. Bilinear filtering should be applied afterwards.
*/
    int x0 = width/2;
    int y0 = height/2;
    float cos_tmp, sin_tmp;
    int new_x_1, new_y_1, new_x_2, new_y_2;
    std::vector<points> intermediatespoints;
    cos_tmp = cos(angleDegree *PI/180 );
    sin_tmp = sin(angleDegree*PI/180);

    memset(dataout, 0, width*height);
    
    for (auto y=0; y<height;y++){

            new_x_1 = ((0-x0) * cos_tmp ) - ((y-y0) * sin_tmp) + x0;
            new_y_1 = ((0-x0) * sin_tmp) + ((y-y0) * cos_tmp) + y0;
            new_x_2 = ((width-1-x0) * cos_tmp) - ((y-y0) * sin_tmp) + x0;
            new_y_2 = ((width-1-x0) * sin_tmp) + ((y-y0) * cos_tmp) + y0;

            bresenham(new_x_1, new_y_1, new_x_2, new_y_2, intermediatespoints);
            for (unsigned i=0; i<intermediatespoints.size(); i++){
                if ((intermediatespoints[i].x < width) && (intermediatespoints[i].y < height) 
                && (intermediatespoints[i].y > 0) && (intermediatespoints[i].x > 0)){
                    
                    dataout[intermediatespoints[i].x +stride*intermediatespoints[i].y] = datain[i+stride*y];
                }
            }
    }

}
