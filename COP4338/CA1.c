#include <stdio.h>
#include <math.h>
#define PI 3.14159 

double cylinder_vol_calculator(double,double);

int main(void)
{
    double height,radius,volume;
    printf("height\tradius\tvolume\n");

    for(height = 0.5 ; height<=2; height *=2)
    {
        for(radius = 0.5 ; radius <= 2; radius *=2)
        {
            volume = cylinder_vol_calculator(height,radius);
            printf("%.1lf\t%.1lf\t%.2lf\n", height,radius,volume);

        }
    }
}

double cylinder_vol_calculator(double height, double radius)
{
    return height*radius*radius* 3.14;
}