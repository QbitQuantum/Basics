//load seeds
float* get_grid_vec_data(int* grid_res)//get vec data at each grid point
{
	osuflow->GetFlowField()->getDimension(grid_res[0],grid_res[1],grid_res[2]);

	float * vectors=new float[grid_res[0]*grid_res[1]*grid_res[2]*3];
	for(int k=0; k<grid_res[2];k++)
	{
		for(int j=0; j<grid_res[1];j++)
		{
			for(int i=0; i<grid_res[0];i++)
			{
				VECTOR3 data;
				osuflow->GetFlowField()->at_vert(i,j,k,0,data);//t=0, static data
				int idx=i+j*grid_res[0]+k*grid_res[0]*grid_res[1];

				data.Normalize();
				vectors[idx*3+0]=data.x();
				vectors[idx*3+1]=data.y();
				vectors[idx*3+2]=data.z();
			}
		}
	}
	return vectors;
}