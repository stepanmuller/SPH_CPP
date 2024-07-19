#pragma once
void update_boxes(int& box_count_x, int& box_count_y, int& box_count)
{
    float min_x = *(std::min_element(std::begin(x), std::end(x)));
    float min_y = *(std::min_element(std::begin(y), std::end(y)));
    float max_x = *(std::max_element(std::begin(x), std::end(x)));
    float max_y = *(std::max_element(std::begin(y), std::end(y)));
    box_count_x = static_cast<int>((max_x - min_x) / BOX_SIZE) + 1;
    box_count_y = static_cast<int>((max_y - min_y) / BOX_SIZE) + 1;
    box_count = box_count_x * box_count_y;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        float x_shifted = x[i] - min_x;
        float y_shifted = y[i] - min_y;
        int box_x = static_cast<int>(x_shifted / BOX_SIZE);
        int box_y = static_cast<int>(y_shifted / BOX_SIZE);
        pbox[i] = box_x + box_y * box_count_x;
    }
}

void get_I(std::vector<int>& rows, std::vector<int>& cols)
{
    printf("Getting I\n");
    int box_count_x, box_count_y, box_count;
    update_boxes(box_count_x, box_count_y, box_count);
    std::vector<int> box_fill(box_count);
    std::vector<int> box_cummulative(box_count);
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        box_fill[pbox[i]]++;
    }
    for (int i = 1; i < box_count; i++) {
        box_cummulative[i] = box_cummulative[i-1] + box_fill[i-1];
    }
    for (int i = 0; i < box_count; i++) {
        printf("Box %d box_fill %d box_cummulative %d\n", i, box_fill[i], box_cummulative[i]);
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
        printf("box_list element %d stores particle %d\n", i, box_list[i]);
    }
    int interaction_count = 0;
    int mybox = 0;
    int mybox_fill = 0;
    int friend_x = 0;
    int friend_y = 0;
    int friend_box = 0;
    for (int i = 0; i < box_count_x; i++) {
        for (int j = 0; j < box_count_y; j++) {
            mybox = i + j * box_count_x;
            mybox_fill = box_fill[mybox];
            for (int offset_x = -BOX_MULTIPLIER; offset_x <= BOX_MULTIPLIER; offset_x++) {
                for (int offset_y = -BOX_MULTIPLIER; offset_y <= BOX_MULTIPLIER; offset_y++) {
                    friend_x = i + offset_x;
                    friend_y = j + offset_y;
                    friend_box = friend_x + friend_y * box_count_x;
                    if (friend_x >= 0 && friend_x < box_count_x && friend_y >= 0 && friend_y < box_count_y) {
                        printf("Adding interaction of mybox %d with friend_box %d resulting from offset_x %d offset_y %d\n", mybox, friend_box, offset_x, offset_y);
                        interaction_count = interaction_count + mybox_fill * box_fill[friend_box];
                    }
                }
            }
            interaction_count = interaction_count - mybox_fill;
        }
    }
    rows.resize(interaction_count);
    cols.resize(interaction_count);
    int counter = 0;
    printf("Interaction count %d\n", interaction_count);
    for (int i = 0; i < box_count_x; i++) {
        for (int j = 0; j < box_count_y; j++) {
            mybox = i + j * box_count_x;
            mybox_fill = box_fill[mybox];
            for (int offset_x = -BOX_MULTIPLIER; offset_x <= BOX_MULTIPLIER; offset_x++) {
                for (int offset_y = -BOX_MULTIPLIER; offset_y <= BOX_MULTIPLIER; offset_y++) {
                    friend_x = i + offset_x;
                    friend_y = j + offset_y;
                    friend_box = friend_x + friend_y * box_count_x;
                    if (friend_x >= 0 && friend_x < box_count_x && friend_y >= 0 && friend_y < box_count_y) {
                        for (int my_particle = 0; my_particle < mybox_fill; my_particle++) {
                            for (int friend_particle = 0; friend_particle < box_fill[friend_box]; friend_particle++) {
                                if (box_list[box_cummulative[mybox] + my_particle] != box_list[box_cummulative[friend_box] + friend_particle]) {
                                    rows[counter] = box_list[box_cummulative[mybox] + my_particle];
                                    cols[counter] = box_list[box_cummulative[friend_box] + friend_particle];
                                    counter++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < interaction_count; i++) {
        printf("Interaction %d row %d col %d\n", i, rows[i], cols[i]);
    }

}