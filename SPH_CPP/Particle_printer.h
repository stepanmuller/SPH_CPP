#pragma once
int print_particles()
{
    printf("Printing fluid particles\n");
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        printf("Particle %d x %3.2f y %3.2f box_x %d box_y %d ptype %d\n", i, x[i], y[i], box_x[i], box_y[i], ptype[i]);
    }
    return 0;
}