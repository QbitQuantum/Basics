      Eigen::Vector3d interpolate_3x3(const Eigen::Vector3d &this_vec, const double &time_now, const Eigen::Vector3d &next_vec, const double &time_other, const double &time_between)
      {
	Eigen::Quaternion<double> quat(1.0, 0.0, 0.0, 0.0);
	double this_norm = this_vec.norm();
	double next_norm = next_vec.norm();
	Eigen::Vector3d this_uv = unit_vec(this_vec);
	Eigen::Vector3d next_uv = unit_vec(next_vec);
	double x = this_uv.dot(next_uv);
	double y = limit(x,-1.0, 1.0);
	double theta = acos(y);
	double adjust = (time_between - time_now) / (time_other - time_now);
	double factor = ((next_norm - this_norm) * adjust + this_norm) / this_norm;
	theta = theta * adjust;
	double sto2 = sin(theta / 2.0);
	Eigen::Vector3d ax = next_vec.cross(this_vec);
	Eigen::Vector3d ax_uv = unit_vec(ax);
	double qx, qy, qz, qw;
	qx = ax_uv(0) * sto2;
	qy = ax_uv(1) * sto2;
	qz = ax_uv(2) * sto2;
	qw = cos(theta/2.0);
	quat = Eigen::Quaternion<double>(qw,qx,qy,qz);
	Eigen::Vector3d z = this_vec * factor;
	Eigen::Quaternion<double> z_q(0.0, z(0), z(1), z(2));
	Eigen::Quaternion<double> q1 = z_q * quat;
	Eigen::Quaternion<double> retaq = quat.inverse();
	Eigen::Quaternion<double> q2 = retaq * q1;
	return q2.vec();
      }