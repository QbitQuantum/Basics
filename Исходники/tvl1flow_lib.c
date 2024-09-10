/**
 *
 * Function to compute the optical flow in one scale
 *
 **/
void Dual_TVL1_optic_flow(
		float *I0,           // source image
		float *I1,           // target image
		float *u1,           // x component of the optical flow
		float *u2,           // y component of the optical flow
		const int   nx,      // image width
		const int   ny,      // image height
		const float tau,     // time step
		const float lambda,  // weight parameter for the data term
		const float theta,   // weight parameter for (u - v)²
		const int   warps,   // number of warpings per scale
		const float epsilon, // tolerance for numerical convergence
		const bool  verbose  // enable/disable the verbose mode
		)
{
	const int   size = nx * ny;
	const float l_t = lambda * theta;

	size_t sf = sizeof(float);
	float *I1x    = malloc(size*sf);
	float *I1y    = xmalloc(size*sf);
	float *I1w    = xmalloc(size*sf);
	float *I1wx   = xmalloc(size*sf);
	float *I1wy   = xmalloc(size*sf);
	float *rho_c  = xmalloc(size*sf);
	float *v1     = xmalloc(size*sf);
	float *v2     = xmalloc(size*sf);
	float *p11    = xmalloc(size*sf);
	float *p12    = xmalloc(size*sf);
	float *p21    = xmalloc(size*sf);
	float *p22    = xmalloc(size*sf);
	float *div    = xmalloc(size*sf);
	float *grad   = xmalloc(size*sf);
	float *div_p1 = xmalloc(size*sf);
	float *div_p2 = xmalloc(size*sf);
	float *u1x    = xmalloc(size*sf);
	float *u1y    = xmalloc(size*sf);
	float *u2x    = xmalloc(size*sf);
	float *u2y    = xmalloc(size*sf);

	centered_gradient(I1, I1x, I1y, nx, ny);

	// initialization of p
	for (int i = 0; i < size; i++)
	{
		p11[i] = p12[i] = 0.0;
		p21[i] = p22[i] = 0.0;
	}

	for (int warpings = 0; warpings < warps; warpings++)
	{
		// compute the warping of the target image and its derivatives
		bicubic_interpolation_warp(I1,  u1, u2, I1w,  nx, ny, true);
		bicubic_interpolation_warp(I1x, u1, u2, I1wx, nx, ny, true);
		bicubic_interpolation_warp(I1y, u1, u2, I1wy, nx, ny, true);

#pragma omp parallel for
		for (int i = 0; i < size; i++)
		{
			const float Ix2 = I1wx[i] * I1wx[i];
			const float Iy2 = I1wy[i] * I1wy[i];

			// store the |Grad(I1)|^2
			grad[i] = (Ix2 + Iy2);

			// compute the constant part of the rho function
			rho_c[i] = (I1w[i] - I1wx[i] * u1[i]
						- I1wy[i] * u2[i] - I0[i]);
		}

		int n = 0;
		float error = INFINITY;
		while (error > epsilon * epsilon && n < MAX_ITERATIONS)
		{
			n++;
			// estimate the values of the variable (v1, v2)
			// (thresholding opterator TH)
#pragma omp parallel for
			for (int i = 0; i < size; i++)
			{
				const float rho = rho_c[i]
					+ (I1wx[i] * u1[i] + I1wy[i] * u2[i]);

				float d1, d2;

				if (rho < - l_t * grad[i])
				{
					d1 = l_t * I1wx[i];
					d2 = l_t * I1wy[i];
				}
				else
				{
					if (rho > l_t * grad[i])
					{
						d1 = -l_t * I1wx[i];
						d2 = -l_t * I1wy[i];
					}
					else
					{
						if (grad[i] < GRAD_IS_ZERO)
							d1 = d2 = 0;
						else
						{
							float fi = -rho/grad[i];
							d1 = fi * I1wx[i];
							d2 = fi * I1wy[i];
						}
					}
				}

				v1[i] = u1[i] + d1;
				v2[i] = u2[i] + d2;
			}

			// compute the divergence of the dual variable (p1, p2)
			divergence(p11, p12, div_p1, nx ,ny);
			divergence(p21, p22, div_p2, nx ,ny);

			// estimate the values of the optical flow (u1, u2)
			error = 0.0;
#pragma omp parallel for reduction(+:error)
			for (int i = 0; i < size; i++)
			{
				const float u1k = u1[i];
				const float u2k = u2[i];

				u1[i] = v1[i] + theta * div_p1[i];
				u2[i] = v2[i] + theta * div_p2[i];

				error += (u1[i] - u1k) * (u1[i] - u1k) +
					(u2[i] - u2k) * (u2[i] - u2k);
			}
			error /= size;

			// compute the gradient of the optical flow (Du1, Du2)
			forward_gradient(u1, u1x, u1y, nx ,ny);
			forward_gradient(u2, u2x, u2y, nx ,ny);

			// estimate the values of the dual variable (p1, p2)
#pragma omp parallel for
			for (int i = 0; i < size; i++)
			{
				const float taut = tau / theta;
				const float g1   = hypot(u1x[i], u1y[i]);
				const float g2   = hypot(u2x[i], u2y[i]);
				const float ng1  = 1.0 + taut * g1;
				const float ng2  = 1.0 + taut * g2;

				p11[i] = (p11[i] + taut * u1x[i]) / ng1;
				p12[i] = (p12[i] + taut * u1y[i]) / ng1;
				p21[i] = (p21[i] + taut * u2x[i]) / ng2;
				p22[i] = (p22[i] + taut * u2y[i]) / ng2;
			}
		}

		if (verbose)
			fprintf(stderr, "Warping: %d, "
					"Iterations: %d, "
					"Error: %f\n", warpings, n, error);
	}

	// delete allocated memory
	free(I1x);
	free(I1y);
	free(I1w);
	free(I1wx);
	free(I1wy);
	free(rho_c);
	free(v1);
	free(v2);
	free(p11);
	free(p12);
	free(p21);
	free(p22);
	free(div);
	free(grad);
	free(div_p1);
	free(div_p2);
	free(u1x);
	free(u1y);
	free(u2x);
	free(u2y);
}