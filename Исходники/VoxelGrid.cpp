void VoxelGrid<PointSourceType>::computeCentroidAndCovariance()
{
	for (int i = 0; i < voxel_num_; i++) {
		int ipoint_num = points_id_[i].size();
		double point_num = static_cast<double>(ipoint_num);
		Eigen::Vector3d pt_sum = centroid_[i];

		if (ipoint_num > 0) {
			centroid_[i] /= point_num;
		}

		if (ipoint_num >= min_points_per_voxel_) {

			covariance_[i] = (covariance_[i] - 2 * (pt_sum * centroid_[i].transpose())) / point_num + centroid_[i] * centroid_[i].transpose();
			covariance_[i] *= (point_num - 1.0) / point_num;

			SymmetricEigensolver3x3 sv(covariance_[i]);

			sv.compute();
			Eigen::Matrix3d evecs = sv.eigenvectors();
			Eigen::Matrix3d evals = sv.eigenvalues().asDiagonal();

			if (evals(0, 0) < 0 || evals(1, 1) < 0 || evals(2, 2) <= 0) {
				points_per_voxel_[i] = -1;
				continue;
			}

			double min_cov_eigvalue = evals(2, 2) * 0.01;

			if (evals(0, 0) < min_cov_eigvalue) {
				evals(0, 0) = min_cov_eigvalue;

				if (evals(1, 1) < min_cov_eigvalue) {
					evals(1, 1) = min_cov_eigvalue;
				}

				covariance_[i] = evecs * evals * evecs.inverse();
			}

			icovariance_[i] = covariance_[i].inverse();
		}
	}
}