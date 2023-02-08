#include <stdio.h>
#include<math.h>
#include "areaOfRectangle.h"
#include "areaOfCircle.h"
#include "areaOfRectangle.h"

int main( int argc, char *argv[] )  {
   int aor;
   float circle = 1;
   float result;
   int square;
   

   aor = areaOfRectangle(10,80);
   
   printf("Area of Recctangle: %d \n", aor);

   // printf("Area of Circle: %f \n", result);

   square = areaOfRectangle(2, 2);
   printf("Area of Square: %d \n", square);

   result = areaOfCircle(1.0);

}
