#pragma once
constexpr float SPACING = 0.01f; // m spacing of particles
constexpr float W_LENGTH = SPACING * 1.45f;
constexpr float G_X = 0; // ms^-2
constexpr float G_Y = -10; // ms^-2
constexpr float KIN_VISCOSITY = 1e-6f; // m^2s^-1
constexpr float RO_0 = 1000; // kgm^-3
constexpr float C_0 = 150; // ms^-1
constexpr float TIMESTEP = 0.00002f; // s
constexpr int FIELD_SIZE = 50; // number of fluid particles in y
constexpr int WALL_THICKNESS = 3; // number of particles across wall
constexpr int BOX_RANGE_X = 0;
constexpr int BOX_RANGE_Y = 5;
float BOX_RANGE = pow(pow(BOX_RANGE_X, 2) + pow(BOX_RANGE_Y, 2), 0.5);
float BOX_SIZE = W_LENGTH * 1.8214f / BOX_RANGE; // m gives 0.99 area of the weight function
const double PI = 3.14159265358979323846;

float INTERACTION_AREA_MULTIPLIER = 0;

constexpr int particle_count() {
    return (FIELD_SIZE + WALL_THICKNESS * 2) * (FIELD_SIZE + WALL_THICKNESS * 2)
        - static_cast<int>(0.5f * FIELD_SIZE * FIELD_SIZE + 0.5f);
}

constexpr int PARTICLE_COUNT = particle_count();

float x[PARTICLE_COUNT];
float y[PARTICLE_COUNT];
float u[PARTICLE_COUNT];
float v[PARTICLE_COUNT];
double ro[PARTICLE_COUNT];
float p[PARTICLE_COUNT];
float vol[PARTICLE_COUNT];
int ptype[PARTICLE_COUNT];
int pbox[PARTICLE_COUNT];

float DroDt[PARTICLE_COUNT];
float DuDt[PARTICLE_COUNT];
float DvDt[PARTICLE_COUNT];

float CALCULATING_TIME_BOXES = 0;
float CALCULATING_TIME_INTERACTIONS = 0;
float TOTAL_INTERACTIONS = 0;