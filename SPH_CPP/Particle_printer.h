#pragma once
int print_particles()
{
    printf("Printing particles\n");
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        printf("Particle %d x %3.2f y %3.2f pbox %d ptype %d\n", i, x[i], y[i], pbox[i], ptype[i]);
    }
    return 0;
}