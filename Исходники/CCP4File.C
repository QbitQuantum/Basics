	bool CCP4File::readHeader()
	{
		// first read the complete 1024 bytes of header information
		char header[1024];
		std::fstream::read(header, 1024);

		if (gcount() != 1024)
		{
			Log.error() << "CCP4File::readHeader(): File does not contain a proper CCP4 header. Aborting read." << std::endl;

			return false;
		}
		// Currently only data_mode=2 is allowed, which stores density values as 4-byte float values	
		Index data_mode = readBinValueasInt_(header, 3);
		
		if (data_mode != 2)
		{
			// try to change endianness
			swap_bytes_= true;

			data_mode = readBinValueasInt_(header, 3);
			if (data_mode != 2)
			{
				Log.error() << "CCP4File::readHeader(): Corrupt CCP4 header: data mode not supported, only 32-bit float supported" << std::endl;
				return false;
			}
		}
		
		//check if file claims to have symmetry reocrds stored	
		Size size_of_symops = readBinValueasInt_(header, 23);
		if (size_of_symops != 0)
		{
			offset_symops_ = size_of_symops;
		}
		
		// check internal ordering of coordinate axis
		col_axis_ = readBinValueasInt_(header, 16)-1;
		row_axis_ = readBinValueasInt_(header, 17)-1;
		sec_axis_ = readBinValueasInt_(header, 18)-1;

		extent_.x = (float)readBinValueasInt_(header, 0+col_axis_);
		extent_.y = (float)readBinValueasInt_(header, 0+row_axis_);
		extent_.z = (float)readBinValueasInt_(header, 0+sec_axis_);
		
		start_.x = (float)readBinValueasInt_(header, 4+col_axis_);
		start_.y = (float)readBinValueasInt_(header, 4+row_axis_);
		start_.z = (float)readBinValueasInt_(header, 4+sec_axis_);
		
		sampling_rate_.x = (float)readBinValueasInt_(header, 7);
		sampling_rate_.y = (float)readBinValueasInt_(header, 8);
		sampling_rate_.z = (float)readBinValueasInt_(header, 9);
		
		cell_dimension_.x = readBinValueasFloat_(header, 10);
		cell_dimension_.y = readBinValueasFloat_(header, 11);
		cell_dimension_.z = readBinValueasFloat_(header, 12);
		
		// Angle values of 0 don't make sense, set the Angles to 90 deg
		if (		readBinValueasFloat_(header, 13) == 0
				||	readBinValueasFloat_(header, 14) == 0
				||	readBinValueasFloat_(header, 15) == 0)
		{
			alpha_ = Angle(90.,false);
			beta_ = Angle(90.,false);
			gamma_ = Angle(90.,false);
		}
		else
		{
			alpha_ = Angle(readBinValueasFloat_(header, 13),false);
			beta_ = Angle(readBinValueasFloat_(header, 14),false);
			gamma_ = Angle(readBinValueasFloat_(header, 15),false);
		}	
		
		mean_density_ = readBinValueasFloat_(header, 21);
		space_group_ = readBinValueasInt_(header, 22);
		deviation_sigma_ = readBinValueasFloat_(header, 54);

		Log.info() << "Mean from file: " << mean_density_ << std::endl;
		Log.info() << "Sigma from file: " << deviation_sigma_ << std::endl;
		
		// convert from grid space to cartesian coordinates
		Vector3 scaled_axes(cell_dimension_.x/sampling_rate_.x,
												cell_dimension_.y/sampling_rate_.y,
												cell_dimension_.z/sampling_rate_.z);
		
		Vector3 x_tmp(scaled_axes.x, 0., 0.);
		
		Vector3 y_tmp(cos(gamma_.toRadian()), sin(gamma_.toRadian()), 0.);
		y_tmp *= scaled_axes.y;
		
		Vector3 z_tmp( cos(beta_.toRadian()), 
									(cos(alpha_.toRadian()) - cos(beta_.toRadian())*cos(gamma_.toRadian())) / sin(gamma_.toRadian()),
									0.);
		z_tmp.z = sqrt(1.0 - z_tmp.x*z_tmp.x - z_tmp.y*z_tmp.y);
		z_tmp *= scaled_axes.z;

		origin_.x = x_tmp.x * start_.x + y_tmp.x * start_.y + z_tmp.x * start_.z;
		origin_.y = y_tmp.y * start_.y + z_tmp.y * start_.z;
		origin_.z = z_tmp.z * start_.z;

		xaxis_.x = x_tmp.x * (extent_.x - 1);
		xaxis_.y = 0.;
		xaxis_.z = 0.;

		yaxis_.x = y_tmp.x * (extent_.y - 1);
		yaxis_.y = y_tmp.y * (extent_.y - 1);
		yaxis_.z = 0.;

		zaxis_.x = z_tmp.x * (extent_.z - 1);
		zaxis_.y = z_tmp.y * (extent_.z - 1);
		zaxis_.z = z_tmp.z * (extent_.z - 1);
		
		// that's it. we're done
		return true;
	}