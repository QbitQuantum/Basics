void post()
{
	//calculate offsetY
	for(int i=0;i<num_jewels;i++)
	{
		int col = i % 8;
		int row = i / 8;
		float offsetY = *(offsetYs+i);
		float dragX = *(dragXs+i);
		float dragY = *(dragYs+i);
		float paddingX = 2.0;
		float paddingY = 2.0;
		int type = *(jewels+i);
		// fprintf(flog,"type:%d\n",type);
		int color = type & COLOR_BITS;//126 == 1111110
		int dir = type & DIR_BITS;
		int bomb = type & BOMB_BITS;
		if(dir)
		{
			fprintf(flog,"dir:%d\n",dir);
		}
		if(bomb)
		{
			fprintf(flog,"bomb:%d\n",bomb);
		}
		float ltx = col * GRID_SIZE + dragX+paddingX;
		float lty = row * GRID_SIZE - offsetY + dragY + paddingY;
		// printf("%d\n",i);
		int r = log2((float)color);
		int o = 0;
		// printf("r:%d,type:%d\n",r,type);
		if(bomb & JEWEL_BOMB)
		{
			if(dir & JEWEL_DIR_NONE)
			{
				r += 13;
			}
			else if(dir & JEWEL_DIR_HERIZ)
			{
				r += 6;
				fprintf(flog,"r += 5\n");
			}
			else if(dir & JEWEL_DIR_VERTI)
			{
				r += 6;
				o = 1;
				fprintf(flog,"r += 5,o = 1\n");
			}
		}
		else if(bomb & JEWEL_DIAMOND)
		{
			r = 13;
		}
		
		for(int j=0;j<4;j++)
		{
			*(vertices+i*16+0+j*4) = (ltx + j%2*GRID_SIZE);//x
			*(vertices+i*16+1+j*4) = (lty + j/2*GRID_SIZE);//y
			float u = tex_coords[r][j][0];
			float v = tex_coords[r][j][1];
			if(o)
			{
				
				u = tex_coords[r][rotateIndex(j)][0];
				v = tex_coords[r][rotateIndex(j)][1];
			}
			*(vertices+i*16+2+j*4) = u;//u
			*(vertices+i*16+3+j*4) = v;//v
		}
		*(indices+6*i+0) = 4 * i + 0;
		*(indices+6*i+1) = 4 * i + 1;
		*(indices+6*i+2) = 4 * i + 3;
		*(indices+6*i+3) = 4 * i + 3;
		*(indices+6*i+4) = 4 * i + 2;
		*(indices+6*i+5) = 4 * i + 0;
	}
	glBufferData(GL_ARRAY_BUFFER,num_jewels*4*4*sizeof(GLfloat),vertices,GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,num_jewels*6*sizeof(GLushort),indices,GL_DYNAMIC_DRAW);
}