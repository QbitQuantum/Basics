void execute(struct ed_s *ed)
{
	double a, b, ib;
	unsigned k, iter, neighb;
	index_type i;
	state_type s, s1;
	MPI_Request req_send, req_recv;
	MPI_Request req_send2, req_recv2;
	MPI_Status stat;
	
	b = 0.0;
	for (i = 0; i < ed->nlstates; ++i)
		b += ed->v1[i] * ed->v1[i];
		
	for (iter = 0; iter < ed->max_iter; ++iter) {
		/* calculate beta */
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&b, &ed->beta[iter], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
		ed->beta[iter] = sqrt(fabs(ed->beta[iter]));

		/* normalize v1 */
		ib = 1.0 / ed->beta[iter];
		for (i = 0; i < ed->nlstates; ++i)
			ed->v1[i] *= ib;

		/* send and receive data in advance */
		MPI_Isend(ed->v1, ed->nlstates, MPI_DOUBLE, ed->to_nbs[0], ed->nm - 1, MPI_COMM_WORLD, &req_send);
		MPI_Irecv(ed->vv1, ed->nlstates, MPI_DOUBLE, ed->from_nbs[0], ed->nm - 1, MPI_COMM_WORLD, &req_recv);

		/* matrix vector multiplication */
		/* v2 = A * v1, the same core */
		for (i = 0; i < ed->nlstates; ++i) {
			s = loc_index2state(i, ed->nm, ed->rank);

			/* diagonal part */
			ed->v2[i] = diag(s, ed->n, ed->j) * ed->v1[i];

			/* offdiagonal part */
			for (k = 0; k < ed->nm; ++k) {
				s1 = flip_state(s, k);
				ed->v2[i] += ed->gamma * ed->v1[state2loc_index(s1, ed->nlstates)];
			}
		}

		/* matrix vector multiplication */
		/* v2 = A * v1, offdiagonal part, other cores */
		a = 0.0;
		for (k = ed->nm; k < ed->n; ++k) {
			if (k < ed->n - 1) {
				/* send and receive data in advance */
				neighb = k - ed->nm + 1;
				MPI_Isend(ed->v1, ed->nlstates, MPI_DOUBLE, ed->to_nbs[neighb], k, MPI_COMM_WORLD, &req_send2);
				MPI_Irecv(ed->vv2, ed->nlstates, MPI_DOUBLE, ed->from_nbs[neighb], k, MPI_COMM_WORLD, &req_recv2);
			}

			/* wait until data arrives */
			MPI_Wait(&req_recv, &stat);

			for (i = 0; i < ed->nlstates; ++i) {
				ed->v2[i] += ed->gamma * ed->vv1[i];

				if (k == ed->n - 1)
					a += ed->v1[i] * ed->v2[i];
			}

			req_recv = req_recv2;
			swap(&ed->vv1, &ed->vv2);
		}

		/* calculate alpha */
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Allreduce(&a, &ed->alpha[iter], 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		/* v2 = v2 - v0 * beta1 - v1 * alpha1 */
		b = 0.0;
		for (i = 0; i < ed->nlstates; ++i) {
			ed->v2[i] -= ed->v0[i] * ed->beta[iter] + ed->v1[i] * ed->alpha[iter];
			b += ed->v2[i] * ed->v2[i];
		}

		/* "shift" vectors */
		swap(&ed->v0, &ed->v1); swap(&ed->v1, &ed->v2);

                if (ed->rank == MASTER_CORE && iter > 0) {
                        calc_eigenvalues(ed, iter);
                        printf("%5i %20.12g\n", iter, ed->evals[0]);
                }
	}
}