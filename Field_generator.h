#pragma once
int generate_fluid_particles(int index)
{
    printf("Generating fluid particles\n");
    int half_field_size = static_cast<int>(FIELD_SIZE / 2 + 0.5f);
    for (int i = 0; i < half_field_size; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            //printf("Generating fluid particle %d %d\n", i, j);
            x[index] = (WALL_THICKNESS + i) * SPACING;
            y[index] = (WALL_THICKNESS + j) * SPACING;
            ptype[index] = 1;
            index++;
        }
    }
    return index;
}

int generate_wall_particles(int index)
{
    printf("Generating wall particles\n");
    for (int i = 0; i < FIELD_SIZE + WALL_THICKNESS * 2; i++) {
        for (int j = 0; j < FIELD_SIZE + WALL_THICKNESS * 2; j++) {
            int overlap_x = std::max(-i + WALL_THICKNESS, i - WALL_THICKNESS - FIELD_SIZE + 1);
            int overlap_y = std::max(-j + WALL_THICKNESS, j - WALL_THICKNESS - FIELD_SIZE + 1);
            int overlap = std::max(overlap_x, overlap_y);
            if (overlap > 0) {
                //printf("Generating wall particle %d %d\n", i, j);
                x[index] = i * SPACING;
                y[index] = j * SPACING;
                ptype[index] = 0;
                index++;
            }
        }
    }
    return index;
}