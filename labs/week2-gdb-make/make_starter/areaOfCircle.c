#include<stdio.h>
 
float areaOfCircle(float radius) {
   float area;
 
   printf("\nEnter the radius of Circle : \n");
   scanf("%f", &radius);
 
   area = 3.14 * radius * radius;
   printf("\nArea of Circle : %f \n", area);
 
   return area;
}
