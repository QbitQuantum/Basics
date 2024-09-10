void Hrtf::get_kemar_data(kemar_ptr & kemar_data, int & elev_n, const v3f &pos) {
	
	kemar_data = 0;
	elev_n = 0;
	if (pos.is0())
		return;

#ifdef _WINDOWS
       float len = (float)_hypot(pos.x, pos.y);
#else
       float len = (float)hypot(pos.x, pos.y);
#endif

	int elev_gr = (int)(180 * atan2f(pos.z, len) / (float)M_PI);
	//LOG_DEBUG(("elev = %d (%g %g %g)", elev_gr, pos.x, pos.y, pos.z));

	for(size_t i = 0; i < KemarElevationCount; ++i)
	{
		const kemar_elevation_data &elev = ::kemar_data[i];
		if (elev_gr < elev.elevation + KemarElevationStep / 2)
		{
			//LOG_DEBUG(("used elevation %d", elev.elevation)); 
			kemar_data = elev.data;
			elev_n = elev.samples;
			break;
		}
	}
}