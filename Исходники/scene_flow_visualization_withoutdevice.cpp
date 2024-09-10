PD_flow_mrpt::PD_flow_mrpt(unsigned int cam_mode_config, unsigned int fps_config, unsigned int rows_config)
{     
    rows = rows_config;      //Maximum size of the coarse-to-fine scheme - Default 240 (QVGA)
    cols = rows*320/240;
    cam_mode = cam_mode_config;   // (1 - 640 x 480, 2 - 320 x 240), Default - 1
    ctf_levels = round(log2(rows/15)) + 1;
    fovh = M_PI*62.5f/180.f;
    fovv = M_PI*45.f/180.f;
	fps = fps_config;		//In Hz, Default - 30

	//Iterations of the primal-dual solver at each pyramid level.
	//Maximum value set to 100 at the finest level
	for (int i=5; i>=0; i--)
	{
		if (i >= ctf_levels - 1)
			num_max_iter[i] = 100;	
		else
			num_max_iter[i] = num_max_iter[i+1]-15;
	}

    //Compute gaussian mask
	float v_mask[5] = {1.f,4.f,6.f,4.f,1.f};
    for (unsigned int i=0; i<5; i++)
        for (unsigned int j=0; j<5; j++)
            g_mask[i+5*j] = v_mask[i]*v_mask[j]/256.f;

    //Matrices that store the original and filtered images with the image resolution
    colour_wf.setSize(480/cam_mode,640/cam_mode);
    depth_wf.setSize(480/cam_mode,640/cam_mode);

    //Resize vectors according to levels
    dx.resize(ctf_levels); dy.resize(ctf_levels); dz.resize(ctf_levels);

    const unsigned int width = colour_wf.getColCount();
    const unsigned int height = colour_wf.getRowCount();
    unsigned int s, cols_i, rows_i;

    for (unsigned int i = 0; i<ctf_levels; i++)
    {
        s = pow(2.f,int(ctf_levels-(i+1)));
        cols_i = cols/s; rows_i = rows/s;
        dx[ctf_levels-i-1].setSize(rows_i,cols_i);
        dy[ctf_levels-i-1].setSize(rows_i,cols_i);
        dz[ctf_levels-i-1].setSize(rows_i,cols_i);
    }

    //Resize pyramid
    const unsigned int pyr_levels = round(log2(width/cols)) + ctf_levels;
    colour.resize(pyr_levels);
    colour_old.resize(pyr_levels);
    depth.resize(pyr_levels);
    depth_old.resize(pyr_levels);
    xx.resize(pyr_levels);
    xx_old.resize(pyr_levels);
    yy.resize(pyr_levels);
    yy_old.resize(pyr_levels);

    for (unsigned int i = 0; i<pyr_levels; i++)
    {
        s = pow(2.f,int(i));
        colour[i].resize(height/s, width/s);
        colour_old[i].resize(height/s, width/s);
        colour[i].assign(0.0f);
        colour_old[i].assign(0.0f);
        depth[i].resize(height/s, width/s);
        depth_old[i].resize(height/s, width/s);
        depth[i].assign(0.0f);
        depth_old[i].assign(0.0f);
        xx[i].resize(height/s, width/s);
        xx_old[i].resize(height/s, width/s);
        xx[i].assign(0.0f);
        xx_old[i].assign(0.0f);
        yy[i].resize(height/s, width/s);
        yy_old[i].resize(height/s, width/s);
        yy[i].assign(0.0f);
        yy_old[i].assign(0.0f);
    }

    //Parameters of the variational method
    lambda_i = 0.04f;
    lambda_d = 0.35f;
    mu = 75.f;
}