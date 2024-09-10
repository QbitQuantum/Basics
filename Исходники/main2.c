void initParticleSystem()
{
    srand((unsigned int)time(NULL));

    int i;
    float max = 2, max2 = 1;
    for(i = 0; i < MAX_PARTICLES; i++)
    {
    	par_sys[i].mMatrix = IdentityMatrix();

    	par_sys[i].mMatrix.m[3] = max * ((float)rand()/(float)RAND_MAX - 0.5);  //x
        par_sys[i].mMatrix.m[7] = max2 * ((float)rand()/(float)RAND_MAX - 0.1); //y
        par_sys[i].mMatrix.m[11] = max * ((float)rand()/(float)RAND_MAX - 0.5); //z

        par_sys[i].position = SetVector(par_sys[i].mMatrix.m[3], par_sys[i].mMatrix.m[7], par_sys[i].mMatrix.m[11]);

        particlePositionData[16 * i + 0] = par_sys[i].mMatrix.m[0]; 	//0,0
        particlePositionData[16 * i + 1] = par_sys[i].mMatrix.m[4]; 	//0,1
        particlePositionData[16 * i + 2] = par_sys[i].mMatrix.m[8]; 	//0,2
        particlePositionData[16 * i + 3] = par_sys[i].mMatrix.m[12]; 	//0,3
        particlePositionData[16 * i + 4] = par_sys[i].mMatrix.m[1]; 	//1,0
        particlePositionData[16 * i + 5] = par_sys[i].mMatrix.m[5]; 	//1,1
        particlePositionData[16 * i + 6] = par_sys[i].mMatrix.m[9]; 	//1,2
        particlePositionData[16 * i + 7] = par_sys[i].mMatrix.m[13]; 	//1,3
        particlePositionData[16 * i + 8] = par_sys[i].mMatrix.m[2]; 	//2,0
        particlePositionData[16 * i + 9] = par_sys[i].mMatrix.m[6]; 	//2,1
        particlePositionData[16 * i + 10] = par_sys[i].mMatrix.m[10]; 	//2,2
        particlePositionData[16 * i + 11] = par_sys[i].mMatrix.m[14]; 	//2,3
        particlePositionData[16 * i + 12] = par_sys[i].mMatrix.m[3]; 	//3,0
        particlePositionData[16 * i + 13] = par_sys[i].mMatrix.m[7]; 	//3,1
        particlePositionData[16 * i + 14] = par_sys[i].mMatrix.m[11]; 	//3,2
        particlePositionData[16 * i + 15] = par_sys[i].mMatrix.m[15]; 	//3,3

    }

}