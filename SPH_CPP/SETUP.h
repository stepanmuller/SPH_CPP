#pragma once
constexpr float SPACING = 0.01f; // m spacing of particles
constexpr float W_LENGTH = SPACING * 1.45f;
constexpr float G_X = 0; // ms^-2
constexpr float G_Y = -10; // ms^-2
constexpr float KIN_VISCOSITY = 1e-6f; // m^2s^-1
constexpr float RO_0 = 1000; // kgm^-3
constexpr float C0 = 1500; // ms^-1
constexpr float TIMESTEP = 0.000002f; // s
constexpr int FIELD_SIZE = 20; // number of fluid particles in y
constexpr int WALL_THICKNESS = 3; // number of particles across wall
constexpr float BOX_SIZE = W_LENGTH * 1.8214f; // m gives 0.99 area of the weight function

constexpr int particle_count() {
    return (FIELD_SIZE + WALL_THICKNESS * 2) * (FIELD_SIZE + WALL_THICKNESS * 2)
        - static_cast<int>(0.5f * FIELD_SIZE * FIELD_SIZE + 0.5f);
}

constexpr int PARTICLE_COUNT = particle_count();

float x[PARTICLE_COUNT];
float y[PARTICLE_COUNT];
float u[PARTICLE_COUNT];
float v[PARTICLE_COUNT];
float ro[PARTICLE_COUNT];
float p[PARTICLE_COUNT];
float vol[PARTICLE_COUNT];
int ptype[PARTICLE_COUNT];