	void		calculate	()
	{
		dwFrame					= Device.dwFrame;

		// Calc wind-vector3, scale
		float	tm_rot			= PI_MUL_2*Device.fTimeGlobal/ps_r__Tree_w_rot;
		wind.set				(_sin(tm_rot),0,_cos(tm_rot),0);	wind.normalize	();	wind.mul(ps_r__Tree_w_amp);	// dir1*amplitude
		scale					= 1.f/float(FTreeVisual_quant);

		// setup constants
		wave.set				(ps_r__Tree_Wave.x,	ps_r__Tree_Wave.y,	ps_r__Tree_Wave.z,	Device.fTimeGlobal*ps_r__Tree_w_speed);			// wave
		wave.div				(PI_MUL_2);
	}