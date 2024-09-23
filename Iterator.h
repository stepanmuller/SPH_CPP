#pragma once
void run_iteration()
{
    std::vector<int> rows, cols;
    int interaction_count = get_I(rows, cols);
    TOTAL_INTERACTIONS += interaction_count;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<float> Dx(interaction_count);
    std::vector<float> Dy(interaction_count);
    std::vector<float> Du(interaction_count);
    std::vector<float> Dv(interaction_count);
    std::vector<float> Dro(interaction_count);
    std::vector<float> Dp(interaction_count);

    std::vector<float> Mr2(interaction_count);
    std::vector<float> Wsize(interaction_count);
    std::vector<float> Wx(interaction_count);
    std::vector<float> Wy(interaction_count);
    std::vector<float> Mpi(interaction_count);

    for (int i = 0; i < interaction_count; i++) {
        Dx[i] = x[cols[i]] - x[rows[i]];
        Dy[i] = y[cols[i]] - y[rows[i]];
        Du[i] = u[cols[i]] - u[rows[i]];
        Dv[i] = v[cols[i]] - v[rows[i]];
        Dro[i] = ro[cols[i]] - ro[rows[i]];
        Dp[i] = p[cols[i]] + p[rows[i]];

        Mr2[i] = pow(Dx[i], 2) + pow(Dy[i], 2);
        Wsize[i] = exp((-Mr2[i] / pow(W_LENGTH, 2))) * 2 / (PI * pow(W_LENGTH, 4));
        Wx[i] = Dx[i] * Wsize[i];
        Wy[i] = Dy[i] * Wsize[i];
        Mpi[i] = 8 * (Du[i] * Dx[i] + Dv[i] * Dy[i]) / Mr2[i];
        //printf("Interaction %d Dx %3.2f Dy %3.2f Du %3.2f Dv %3.2f Dro %3.2f Dp %3.2f  Wsize %3.2f  Wx %3.2f  Wy %3.2f  Mpi %3.2f \n", 
        //   i, Dx[i], Dy[i], Du[i], Dv[i], Dro[i], Dp[i], Wsize[i], Wx[i], Wy[i], Mpi[i]);
    }

    float data;
    std::fill_n(DroDt, PARTICLE_COUNT, 0);
    std::fill_n(DuDt, PARTICLE_COUNT, G_X);
    std::fill_n(DvDt, PARTICLE_COUNT, G_Y);

    //printf("INTERACTION COUNT %d\n", interaction_count);
    for (int i = 0; i < interaction_count; i++) {
        data = Du[i] * Wx[i] + Dv[i] * Wy[i];
        //printf("row %d col %d data %10.9f\n", rows[i], cols[i], data);
        DroDt[rows[i]] += -ro[rows[i]] * data * vol[cols[i]]; //Divergence member

        data = C_0 * Dro[i] * (Dx[i] * Wx[i] + Dy[i] * Wy[i]) / pow(Mr2[i], 0.5f);
        DroDt[rows[i]] += data * vol[cols[i]]; //Diffusion member

        data = -Dp[i] * Wx[i] + KIN_VISCOSITY * RO_0 * Mpi[i] * Wx[i];
        DuDt[rows[i]] += (1 / ro[rows[i]]) * data * vol[cols[i]]; //Pressure and viscious member

        data = -Dp[i] * Wy[i] + KIN_VISCOSITY * RO_0 * Mpi[i] * Wy[i];
        DvDt[rows[i]] += (1 / ro[rows[i]]) * data * vol[cols[i]]; //Pressure and viscious member
    }

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        //printf("i %d DroDt %10.9f\n", i, DroDt[i]);
        ro[i] += DroDt[i] * TIMESTEP;
        u[i] += DuDt[i] * TIMESTEP;
        v[i] += DvDt[i] * TIMESTEP;
        p[i] = pow(C_0, 2) * (ro[i] - RO_0);
        u[i] = u[i] * ptype[i]; //enforcing wall boundary condition
        v[i] = v[i] * ptype[i]; //enforcing wall boundary condition
        x[i] += u[i] * TIMESTEP;
        y[i] += v[i] * TIMESTEP;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int microseconds = static_cast<int>(duration.count());
    CALCULATING_TIME_INTERACTIONS += (static_cast<int>(duration.count()));
}