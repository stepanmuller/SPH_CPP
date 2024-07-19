#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#include "SETUP.h"
#include "Field_generator.h"
#include "Interaction_manager.h"
#include "Iterator.h"
#include "Particle_printer.h"


int main()
{   
    printf("Particle count: %d\n", PARTICLE_COUNT);
    std::fill_n(ro, PARTICLE_COUNT, RO_0);
    std::fill_n(vol, PARTICLE_COUNT, pow(SPACING, 2));
    int index = generate_fluid_particles(0);
    index = generate_wall_particles(index);
    print_particles();
    for (int iteration_count = 0; iteration_count < 1; iteration_count++) {
        printf("\nStarting iteration %d\n", iteration_count);
        run_iteration();
        print_particles();
    }
    return 0;
}