void QueuedCPUTracker::SetPixelCalibrationImages(float* offset, float* gain)
{
	if (zlut_count > 0) {
		int nelem = cfg.width*cfg.height*zlut_count;

		if (calib_gain == 0 && gain)  {
			calib_gain = new float[nelem];
			memcpy(calib_gain, gain, sizeof(float)*nelem);
		}
		else if (calib_gain && gain == 0) {
			delete[] calib_gain;
			calib_gain = 0;
		}

		if (calib_offset == 0 && offset) {
			calib_offset = new float[nelem];
			memcpy(calib_offset, offset, sizeof(float)*nelem);
		}
		else if (calib_offset && offset == 0) {
			delete[] calib_offset;
			calib_offset = 0;
		}

#ifdef _DEBUG
		std::string path = GetLocalModulePath();
		for (int i=0;i<zlut_count;i++) {
			if(calib_gain) FloatToJPEGFile( SPrintf("%s/gain-bead%d.jpg", path.c_str(), i).c_str(), &calib_gain[cfg.width*cfg.height*i], cfg.width,cfg.height);
			if(calib_offset) FloatToJPEGFile( SPrintf("%s/offset-bead%d.jpg", path.c_str(), i).c_str(), &calib_offset[cfg.width*cfg.height*i], cfg.width,cfg.height);
		}
#endif
	}
}