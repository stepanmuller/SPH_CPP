#pragma once
void update_boxes(int& box_count_x, int& box_count_y, int& box_count)
{
    //printf("Updating boxes\n");
    int offset_range = static_cast<int>(ceil(BOX_RANGE) + 0.1);
    float min_x = *(std::min_element(std::begin(x), std::end(x)));
    float min_y = *(std::min_element(std::begin(y), std::end(y)));
    float max_x = *(std::max_element(std::begin(x), std::end(x)));
    float max_y = *(std::max_element(std::begin(y), std::end(y)));
    box_count_x = static_cast<int>((max_x - min_x) / BOX_SIZE) + 1 + offset_range * 2;
    box_count_y = static_cast<int>((max_y - min_y) / BOX_SIZE) + 1 + offset_range * 2;
    box_count = box_count_x * box_count_y;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        float x_shifted = x[i] - min_x + BOX_SIZE * offset_range;
        float y_shifted = y[i] - min_y + BOX_SIZE * offset_range;
        int box_x = static_cast<int>(x_shifted / BOX_SIZE);
        int box_y = static_cast<int>(y_shifted / BOX_SIZE);
        pbox[i] = box_x + box_y * box_count_x;
    }
}

int get_neighbours(int box_count_x, std::vector<int>& neighbours)
{
    int neighbour_count = 0;
    int offset_range = static_cast<int>(ceil(BOX_RANGE) + 0.1);
    int relative_index = 0;
    for (int offset_y = -offset_range; offset_y <= offset_range; offset_y++) {
        for (int offset_x = -offset_range; offset_x <= offset_range; offset_x++) {
            int i = (abs(offset_x) - 1);
            int j = (abs(offset_y) - 1);
            i = (i < 0) ? 0 : i;
            j = (j < 0) ? 0 : j;
            if (pow(i, 2) + pow(j, 2) < pow((BOX_RANGE - 0.01), 2)) {
                neighbour_count += 1;
            }
        }
    }
    neighbours.resize(neighbour_count);
    neighbour_count = 0;
    for (int offset_y = -offset_range; offset_y <= offset_range; offset_y++) {
        for (int offset_x = -offset_range; offset_x <= offset_range; offset_x++) {
            int i = (abs(offset_x) - 1);
            int j = (abs(offset_y) - 1);
            i = (i < 0) ? 0 : i;
            j = (j < 0) ? 0 : j;
            if (pow(i, 2) + pow(j, 2) < pow((BOX_RANGE - 0.01), 2)) {
                neighbours[neighbour_count] = offset_x + offset_y * box_count_x;
                neighbour_count += 1;
            }
        }
    }
    INTERACTION_AREA_MULTIPLIER = neighbour_count / (pow(BOX_RANGE, 2) * PI);
    return neighbour_count;
}

int get_I(std::vector<int>& rows, std::vector<int>& cols)
{
    auto start = std::chrono::high_resolution_clock::now();
    //printf("Getting I\n");
    int box_count_x, box_count_y, box_count;
    update_boxes(box_count_x, box_count_y, box_count);
    std::vector<int> box_fill(box_count);
    std::vector<int> box_cummulative(box_count);
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        box_fill[pbox[i]]++;
    }
    for (int i = 1; i < box_count; i++) {
        box_cummulative[i] = box_cummulative[i - 1] + box_fill[i - 1];
    }
    for (int i = 0; i < box_count; i++) {
        //printf("Box %d box_fill %d box_cummulative %d\n", i, box_fill[i], box_cummulative[i]);
    }
    std::fill(box_fill.begin(), box_fill.end(), 0);
    int box_list[PARTICLE_COUNT];
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        int box = pbox[i];
        int index = box_cummulative[box] + box_fill[box];
        box_list[index] = i;
        box_fill[box]++;
    }
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        //printf("box_list element %d stores particle %d\n", i, box_list[i]);
    }

    std::vector<int> neighbours;
    int neighbour_count = get_neighbours(box_count_x, neighbours);
    int interaction_count = 0;
    int mybox = 0;
    int friend_box = 0;
    for (int p = 0; p < PARTICLE_COUNT; p++) {
        mybox = pbox[p];
        for (int i = 0; i < neighbour_count; i++) {
            friend_box = mybox + neighbours[i];
            if (friend_box >= 0 && friend_box < box_count) {
                //printf("Adding interaction of mybox %d with friend_box %d resulting from offset_x %d offset_y %d\n", mybox, friend_box, offset_x, offset_y);
                interaction_count = interaction_count + box_fill[friend_box];
            }
        }
    }
    interaction_count = interaction_count - PARTICLE_COUNT;
    rows.resize(interaction_count);
    cols.resize(interaction_count);
    int counter = 0;
    //printf("Interaction count %d\n", interaction_count);
    for (int p = 0; p < PARTICLE_COUNT; p++) {
        mybox = pbox[p];
        for (int i = 0; i < neighbour_count; i++) {
            friend_box = mybox + neighbours[i];
            if (friend_box >= 0 && friend_box < box_count) {
                for (int friend_particle = 0; friend_particle < box_fill[friend_box]; friend_particle++) {
                    if (p != box_list[box_cummulative[friend_box] + friend_particle]) {
                        rows[counter] = p;
                        cols[counter] = box_list[box_cummulative[friend_box] + friend_particle];
                        counter++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < interaction_count; i++) {
        //printf("Interaction %d row %d col %d\n", i, rows[i], cols[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int microseconds = static_cast<int>(duration.count());
    CALCULATING_TIME_BOXES += (static_cast<int>(duration.count()));
    return interaction_count;
}