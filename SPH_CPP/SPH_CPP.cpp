#include <stdio.h>
#include <cmath>
#include <algorithm>
using namespace std;

#include "SETUP.h"
#include "Field_generator.h"

int main()
{
    printf("Particle count: %d\n", PARTICLE_COUNT);
    std::fill_n(ro, PARTICLE_COUNT, RO_0);
    std::fill_n(vol, PARTICLE_COUNT, pow(SPACING, 2));
    int index = generate_fluid_particles(0);
    index = generate_wall_particles(index);
    print_particles();
    return 0;
}