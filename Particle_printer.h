#pragma once
int print_particles()
{
    printf("Printing particles\n");
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        printf("Particle %d x %10.9f y %10.9f u %10.9f v %10.9f ro %16.15f p %10.9f ptype %d\n", i, x[i], y[i], u[i], v[i], ro[i], p[i], ptype[i]);
    }
    return 0;
}