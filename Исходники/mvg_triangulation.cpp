CvMat * mvg_triangulation_RANSAC(
	const CvMat * projection_matrices[],
	const CvMat * projected_points,
	const bool affine,
	const bool normalize_A /*= false*/, 
	const int min_inliers_to_triangulate /*= MVG_MIN_INLIERS_TO_TRIANGULATE*/,
	const int min_inliers_to_triangulate_weaker /*= MVG_MIN_INLIERS_TO_TRIANGULATE_WEAKER*/,
	const int trials /*= MVG_RANSAC_TRIANGULATION_TRIALS*/,
	const double threshold /*= MVG_MEASUREMENT_THRESHOLD*/, 
	bool * inliers /*= NULL*/
)
{
	// printf("Triangulating: ");

	// transform input 
	const int n = projected_points->cols;
	const double threshold_sq = threshold * threshold;

	// fail immediately if the solution is underdetermined 
	if (n < 2)
	{
		return false;
	}

	// allocate
	bool * best_status = ALLOC(bool, n), * status = ALLOC(bool, n);
	int best_inliers_count = -1;

	// do this many times 
	for (int i = 0; i < trials; i++) 
	{
		// pick randomly 2 points
		memset(status, 0, sizeof(bool) * n);
		int samples[2];
		for (int count = 0; count < 2;)
		{
			const int pick = rand() % n; 
			if (!status[pick])
			{
				status[pick] = true; 
				samples[count] = pick;
				count++;
			}
		}

		// calculate using mvg_triangulation_SVD_affine
		CvMat * X = 
			affine ? mvg_triangulation_SVD_affine(projection_matrices, projected_points, normalize_A, 2, samples, 2)
			       : mvg_triangulation_SVD(projection_matrices, projected_points, normalize_A, 2, samples, 2);
		if (!X)
		{
			continue;
		}

		// count and mark the inliers
		int inliers_count = 0;
		for (int j = 0; j < n; j++)
		{
			double reprojection[2];
			// note that here we're using "dirty" projection method which is suitable only for visualization; on the upside, it shouldn't matter because
			// if a point is projected on pi_infinity, there's something wrong with it anyway
			if (affine) 
			{
				opencv_vertex_projection_visualization(projection_matrices[j], OPENCV_ELEM(X, 0, 0), OPENCV_ELEM(X, 1, 0), OPENCV_ELEM(X, 2, 0), reprojection);
			}
			else
			{
				opencv_vertex_projection_visualization(projection_matrices[j], OPENCV_ELEM(X, 0, 0), OPENCV_ELEM(X, 1, 0), OPENCV_ELEM(X, 2, 0), OPENCV_ELEM(X, 3, 0), reprojection);
			}

			const double
				dx = reprojection[0] - OPENCV_ELEM(projected_points, 0, j), 
				dy = reprojection[1] - OPENCV_ELEM(projected_points, 1, j);
			
			if (dx * dx + dy * dy <= threshold_sq)
			{
				inliers_count++; 
				status[j] = true; 
			}
			else
			{
				status[j] = false;
			}
		}

		cvReleaseMat(&X);

		// check for the best sample 
		if (inliers_count > best_inliers_count)
		{
			bool * temp = best_status; 
			best_status = status; 
			status = temp;
			best_inliers_count = inliers_count; 
		}

		// debug 
		// printf("{%d/%d} ", inliers_count, n);
	}

	FREE(status);
	if (best_inliers_count < 2)
	{
		FREE(best_status);
		return false;
	}

	// calculate camera calibration using only inliers
	int * samples = ALLOC(int, best_inliers_count);
	int j = 0;
	int outliers = 0, min = min_inliers_to_triangulate; 
	for (int i = 0; i < n; i++)
	{
		if (best_status[i]) 
		{
			samples[j++] = i;
		}
		else
		{
			outliers++;
		}
	}

	if (outliers == 0) min = min_inliers_to_triangulate_weaker;
	CvMat * X = affine ? mvg_triangulation_SVD_affine(projection_matrices, projected_points, true, min, samples, best_inliers_count)
	                   : mvg_triangulation_SVD(projection_matrices, projected_points, true, min, samples, best_inliers_count);
	if (!X)
	{
		// printf("failed to estimate\n"); 
		if (inliers) 
		{
			memset(inliers, 0, sizeof(bool) * n);
		}
	}
	else if (inliers)
	{
		memcpy(inliers, best_status, sizeof(bool) * n);
	}

	// release resources
	FREE(samples);
	FREE(best_status);

	// printf("\n");
	return X;
}