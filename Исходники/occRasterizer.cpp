void occRasterizer::on_dbg_render()
{
#if DEBUG
	if( !ps_r2_ls_flags_ext.is(R_FLAGEXT_HOM_DEPTH_DRAW) )
	{
		dbg_HOM_draw_initialized = false;
		return;
	}

	for ( int i = 0; i< occ_dim_0; ++i)
	{
		for ( int j = 0; j< occ_dim_0; ++j)
		{
			if( bDebug )
			{
				Fvector quad,left_top,right_bottom,box_center,box_r;
				quad.set( (float)j-occ_dim_0/2.f, -((float)i-occ_dim_0/2.f), (float)bufDepth_0[i][j]/occQ_s32);
				Device.mProject;

				float z = -Device.mProject._43/(float)(Device.mProject._33-quad.z);
				left_top.set		( quad.x*z/Device.mProject._11/(occ_dim_0/2.f),		quad.y*z/Device.mProject._22/(occ_dim_0/2.f), z);
				right_bottom.set	( (quad.x+1)*z/Device.mProject._11/(occ_dim_0/2.f), (quad.y+1)*z/Device.mProject._22/(occ_dim_0/2.f), z);

				box_center.set		((right_bottom.x + left_top.x)/2, (right_bottom.y + left_top.y)/2, z);
				box_r = right_bottom;
				box_r.sub(box_center);

				Fmatrix inv;
				inv.invert(Device.mView);
				inv.transform( box_center );
				inv.transform_dir( box_r );

				pixel_box& tmp = dbg_pixel_boxes[ i*occ_dim_0+j];
				tmp.center	= box_center;
				tmp.radius	= box_r;
				tmp.z 		= quad.z;
				dbg_HOM_draw_initialized = true;
			}

			if( !dbg_HOM_draw_initialized )
				return;

			pixel_box& tmp = dbg_pixel_boxes[ i*occ_dim_0+j];
			Fmatrix Transform;
			Transform.identity();
			Transform.translate(tmp.center);

			// draw wire
			Device.SetNearer(TRUE);

			RCache.set_Shader	(dxRenderDeviceRender::Instance().m_SelectionShader);
			RCache.dbg_DrawOBB( Transform, tmp.radius, D3DCOLOR_XRGB(u32(255*pow(tmp.z,20.f)),u32(255*(1-pow(tmp.z,20.f))),0) );
			Device.SetNearer(FALSE);
		}
	}
#endif
}