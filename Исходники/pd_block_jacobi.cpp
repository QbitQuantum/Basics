void
pd_solver_advance(struct PdSolver *solver, uint32_t const n_iterations)
{
        /* set external force */
        Eigen::VectorXf ext_accel = Eigen::VectorXf::Zero(solver->positions.size());
#pragma omp parallel for
        for (uint32_t i = 0; i < solver->positions.size()/3; ++i)
                for (int j = 0; j < 3; ++j)
                        ext_accel[3*i + j] = solver->ext_force[j];
        Eigen::VectorXf const ext_force = solver->mass_mat*ext_accel;
        Eigen::VectorXf const mass_y = solver->mass_mat*(2.0f*solver->positions - solver->positions_last);

        solver->positions_last = solver->positions;

        for (uint32_t iter = 0; iter < n_iterations; ++iter) {
                /* LOCAL STEP */
                /* LOCAL STEP (we account everything except the global solve */
                struct timespec local_start;
                clock_gettime(CLOCK_MONOTONIC, &local_start);
                uint32_t const n_constraints = solver->n_attachments + solver->n_springs;
                Eigen::VectorXf d(3*n_constraints);
                for (uint32_t i = 0; i < solver->n_attachments; ++i) {
                        struct PdConstraintAttachment c = solver->attachments[i];
                        d.block<3, 1>(3*i, 0) = Eigen::Map<Eigen::Vector3f>(c.position);
                }

                uint32_t const offset = solver->n_attachments;
                for (uint32_t i = 0; i < solver->n_springs; ++i) {
                        struct PdConstraintSpring c = solver->springs[i];
                        Eigen::Vector3f const v = solver->positions.block<3, 1>(3*c.i[1], 0)
                                - solver->positions.block<3, 1>(3*c.i[0], 0);
                        d.block<3, 1>(3*(offset + i), 0) = v.normalized()*c.rest_length;
                }

                Eigen::VectorXf const b = mass_y + solver->t2*(solver->j_mat*d + ext_force);
                struct timespec local_end;
                clock_gettime(CLOCK_MONOTONIC, &local_end);

                /* GLOBAL STEP */
                struct timespec global_start;
                clock_gettime(CLOCK_MONOTONIC, &global_start);
                solve(solver, b);
                struct timespec global_end;
                clock_gettime(CLOCK_MONOTONIC, &global_end);

                solver->global_time = pd_time_diff_ms(&global_start, &global_end);
                solver->local_time = pd_time_diff_ms(&local_start, &local_end);

                solver->global_cma = (solver->global_time + solver->n_iters*solver->global_cma)/(solver->n_iters + 1);
                solver->local_cma = (solver->local_time + solver->n_iters*solver->local_cma)/(solver->n_iters + 1);

                if (!(solver->n_iters % 1000)) {
                        printf("Local CMA: %f ms\n", solver->local_cma);
                        printf("Global CMA: %f ms\n\n", solver->global_cma);
                }

                ++solver->n_iters;
        }
}