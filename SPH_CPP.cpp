#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
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
    //print_particles();
    for (int iteration_count = 0; iteration_count < 10001; iteration_count++) {
        run_iteration();
        if (iteration_count % 1000 == 0 && iteration_count > 0) {
            printf("\nFinished iteration %d\n", iteration_count);
            printf("Average calculating time getting I %3.1f ms\n", ((CALCULATING_TIME_BOXES / iteration_count) / 1000));
            printf("Average calculating time interactions %3.1f ms\n",((CALCULATING_TIME_INTERACTIONS / iteration_count) / 1000));
            printf("Average number of interactions %6.1f\n", ((TOTAL_INTERACTIONS/ iteration_count)));
            printf("Interaction area multiplier %6.3f\n", ((INTERACTION_AREA_MULTIPLIER)));
            //print_particles();
        }
    }
    return 0;
}