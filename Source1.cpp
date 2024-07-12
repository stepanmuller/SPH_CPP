#include <stdio.h>

int main()
{
    float SPACING = 0.01 //m spacing of particles
    float W_LENGTH = SPACING * 1.45
    float G_X = 0 //ms - 2
    float G_Y = -10 //ms - 2
    float KIN_VISCOSITY = 10 * *(-6) * 1 //m2s - 1
    float RO_0 = 1000 //kgm - 3
    float C0 = 1500 //ms - 1
    float TIMESTEP = 0.000002 //s
    float FIELD_SIZE = 20 //number of fluid particles in y
    float WALL_THICKNESS = 3 //number of particles across wall
    float BOX_SIZE = W_LENGTH * 1.8214 //m gives 0.99 area of the weight function
    return 0;
}