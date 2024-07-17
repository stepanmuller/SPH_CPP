#pragma once
int update_boxes()
{
    printf("Updating boxes\n");
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        box_x[i] = static_cast<int>(x[i] / BOX_SIZE);
        box_y[i] = static_cast<int>(y[i] / BOX_SIZE);
    }
    return 0;
}