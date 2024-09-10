int Hsh::loadData(FILE* file, int width, int height, int basisTerm, bool urti, CallBackPos * cb,const QString& text)
{
	type = "HSH";
	w = width;
	h = height;

	ordlen = basisTerm;
	bands = 3;
	fread(gmin, sizeof(float), basisTerm, file);
	fread(gmax, sizeof(float), basisTerm, file);

	if (feof(file))
		return -1;

	int offset = 0;

	int size = w * h * basisTerm;
	float* redPtr = new float[size];
	float* greenPtr = new float[size];
	float* bluePtr = new float[size];
	
	unsigned char c;

	if (!urti)
	{
		for(int j = 0; j < h; j++)
		{
			if (cb != NULL && j % 50 == 0)(*cb)(j * 50.0 / h, text);
			for(int i = 0; i < w; i++)
			{				
				offset = j * w + i;
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					redPtr[offset*basisTerm + k] = (((float)c) / 255.0) * (gmax[k] - gmin[k]) + gmin[k];
				}
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					greenPtr[offset*basisTerm + k] = (((float)c) / 255.0) * (gmax[k] - gmin[k]) + gmin[k];
				}
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					bluePtr[offset*basisTerm + k] = (((float)c) / 255.0) * (gmax[k] - gmin[k]) + gmin[k];
				}
			}
		}
	}
	else
	{
		for(int j = 0; j < h; j++)
		{
			if (cb != NULL && j % 50 == 0)(*cb)(j * 50 / h, text);
			for(int i = 0; i < w; i++)
			{				
				offset = j * w + i;
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					redPtr[offset*basisTerm + k] = (((float)c) / 255.0) * gmin[k] + gmax[k];
				}
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					greenPtr[offset*basisTerm + k] = (((float)c) / 255.0) * gmin[k] + gmax[k];
				}
				for (int k = 0; k < basisTerm; k++)
				{
					if (feof(file))
						return -1;
					fread(&c, sizeof(unsigned char), 1, file);
					bluePtr[offset*basisTerm + k] = (((float)c) / 255.0) * gmin[k] + gmax[k];
				}
			}
		}
	}
	
	fclose(file);

	mipMapSize[0] = QSize(w, h);

	redCoefficients.setLevel(redPtr, size, 0);
	greenCoefficients.setLevel(greenPtr, size, 0);
	blueCoefficients.setLevel(bluePtr, size, 0);
	
	// Computes mip-mapping.
	if (cb != NULL)	(*cb)(50, "Mip mapping generation...");
	
	for (int level = 1; level < MIP_MAPPING_LEVELS; level++)
	{
		int width = mipMapSize[level - 1].width();
		int height = mipMapSize[level - 1].height();
		int width2 = ceil(width / 2.0);
		int height2 = ceil(height / 2.0);
		size = width2*height2*basisTerm;
		redCoefficients.setLevel(new float[size], size, level);
		greenCoefficients.setLevel(new float[size], size, level);
		blueCoefficients.setLevel(new float[size], size, level);
		int th_id;
		#pragma omp parallel for
		for (int i = 0; i < height - 1; i+=2)
		{
			th_id = omp_get_thread_num();
			if (th_id == 0)
			{
				if (cb != NULL && i % 50 == 0)	(*cb)(50 + (level-1)*8 + i*8.0/height, "Mip mapping generation...");
			}
			for (int j = 0; j < width - 1; j+=2)
			{
				int index1 = (i * width + j)*ordlen;
				int index2 = (i * width + j + 1)*ordlen;
				int index3 = ((i + 1) * width + j)*ordlen;
				int index4 = ((i + 1) * width + j + 1)*ordlen;
				int offset = (i/2 * width2 + j/2)*ordlen;
				for (int k = 0; k < basisTerm; k++)
				{
					redCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k, index3 + k , index4 + k);
					greenCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k, index3 + k , index4 + k);
					blueCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k, index3 + k , index4 + k);
				}
			}
		}
		if (width2 % 2 != 0)
		{
			for (int i = 0; i < height - 1; i+=2)
			{
				int index1 = ((i + 1) * width - 1)*ordlen;
				int index2 = ((i + 2) * width - 1)*ordlen;
				int offset = ((i/2 + 1) * width2 - 1)*ordlen;
				for (int k = 0; k < basisTerm; k++)
				{
					redCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
					greenCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
					blueCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
				}
			}
		}
		if (height % 2 != 0)
		{
			for (int i = 0; i < width - 1; i+=2)
			{
				int index1 = ((height - 1) * width + i)*ordlen;
				int index2 = ((height - 1) * width + i + 1)*ordlen;
				int offset = ((height2 - 1) * width2 + i/2)*ordlen;
				for (int k = 0; k < basisTerm; k++)
				{
					redCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
					greenCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
					blueCoefficients.calcMipMapping(level, offset + k, index1 + k, index2 + k);
				}
			}
		}
		if (height % 2 != 0 && width % 2 != 0)
		{
			int index1 = (height*width - 1)*ordlen;
			int offset = (height2*width2 - 1)*ordlen;
			for (int k = 0; k < basisTerm; k++)
			{
				redCoefficients.calcMipMapping(level, offset + k, index1 + k);
				greenCoefficients.calcMipMapping(level, offset + k, index1 + k);
				blueCoefficients.calcMipMapping(level, offset + k, index1 + k);
			}
		}
		mipMapSize[level] = QSize(width2, height2);
	}

	//Compute normals.
	if (cb != NULL) (*cb)(75 , "Normals generation...");
	Eigen::Vector3d l0(sin(M_PI/4)*cos(M_PI/6), sin(M_PI/4)*sin(M_PI/6), cos(M_PI/4));
	Eigen::Vector3d l1(sin(M_PI/4)*cos(5*M_PI / 6), sin(M_PI/4)*sin(5*M_PI / 6), cos(M_PI/4));
	Eigen::Vector3d l2(sin(M_PI/4)*cos(3*M_PI / 2), sin(M_PI/4)*sin(3*M_PI / 2), cos(M_PI/4));
    float hweights0[16], hweights1[16], hweights2[16];
	getHSH(M_PI / 4, M_PI / 6, hweights0, ordlen);
	getHSH(M_PI / 4, 5*M_PI / 6, hweights1, ordlen);
	getHSH(M_PI / 4, 3*M_PI / 2, hweights2, ordlen);
	
	
	Eigen::Matrix3d L;
	L.setIdentity();
	L.row(0) = l0;
	L.row(1) = l1;
	L.row(2) = l2;
	Eigen::Matrix3d LInverse = L.inverse();
	
	for (int level = 0; level < MIP_MAPPING_LEVELS; level++)
	{
		const float* rPtr = redCoefficients.getLevel(level);
		const float* gPtr = greenCoefficients.getLevel(level);
		const float* bPtr = blueCoefficients.getLevel(level);
		vcg::Point3f* temp = new vcg::Point3f[mipMapSize[level].width()*mipMapSize[level].height()];
		if (cb != NULL) (*cb)(75 + level*6, "Normal generation...");

		#pragma omp parallel for
		for (int y = 0; y < mipMapSize[level].height(); y++)
		{
			for (int x = 0; x < mipMapSize[level].width(); x++)
			{
				int offset= y * mipMapSize[level].width() + x;
				Eigen::Vector3d f(0, 0, 0);
				for (int k = 0; k < ordlen; k++)
				{
					f(0) += rPtr[offset*ordlen + k] * hweights0[k];
					f(1) += rPtr[offset*ordlen + k] * hweights1[k];
					f(2) += rPtr[offset*ordlen + k] * hweights2[k];
				}
				for (int k = 0; k < ordlen; k++)
				{
					f(0) += gPtr[offset*ordlen + k] * hweights0[k];
					f(1) += gPtr[offset*ordlen + k] * hweights1[k];
					f(2) += gPtr[offset*ordlen + k] * hweights2[k];
				}
				for (int k = 0; k < ordlen; k++)
				{
					f(0) += bPtr[offset*ordlen + k] * hweights0[k];
					f(1) += bPtr[offset*ordlen + k] * hweights1[k];
					f(2) += bPtr[offset*ordlen + k] * hweights2[k];
				}
				f /= 3.0;
				Eigen::Vector3d normal = LInverse * f;
				temp[offset] = vcg::Point3f(normal(0), normal(1), normal(2));
				temp[offset].Normalize();
			}
		}
		normals.setLevel(temp, mipMapSize[level].width()*mipMapSize[level].height(), level);
	}
	

	return 0;

}