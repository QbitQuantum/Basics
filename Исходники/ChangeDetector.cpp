//coverage the minimum intersection requirement, gap the maximum distance between pixels 
//to become a candidate matched edge pixel
void ChangeDetector::MorphDiff(float coverage, float gap){
	int i,j,k,amount=refList1.size();
	CvMat Ma, Mb;
	int x0,y0,h0,w0,mx,my,mh,mw;
	int pos,dest,total,cand,bl,nbl;
	CRect meg;
	//compute distance of boundaries in segmentation 1 to that of segmentation 2
	for(i=0;i<amount;++i){
		if((float)refList1[i].section/regList1[i].size<coverage){
				continue;
		}

		cand=refList1[i].bestp;
		meg.UnionRect(&regList1[i].boundBox, &regList2[cand].boundBox);
		h0=meg.Height();
		w0=meg.Width();
		BYTE*patch=new BYTE[h0*w0];
		float *pool=new float[h0*w0];
		memset(patch,1,sizeof(BYTE)*h0*w0);
		cvInitMatHeader( &Ma, h0, w0, CV_8UC1, patch);
		cvInitMatHeader( &Mb, h0, w0, CV_32FC1, pool);

		x0=meg.left;
		y0=meg.top;
		mx=regList2[cand].boundBox.left;
		my=regList2[cand].boundBox.top;
		mw=regList2[cand].boundBox.Width();
		mh=regList2[cand].boundBox.Height();

		pos=my*width+mx;
		total=0;//number of pixel in a region
//		bl=0;//boundary length
		for(j=0;j<mh;++j)
		{			
			for(k=0;k<mw;++k)
			{
				if(tag2[pos]==cand)
				{
					if(CheckNei(tag2,width,height,pos)!=4){
					//	++bl;
						dest=(j+my-y0)*w0+(k+mx-x0);
						patch[dest]=0;
					}					
					++total;
				}
				++pos;
			}
			pos+=width-mw;
		}
		
		assert(total==regList2[cand].size);
	
		cvDistTransform(&Ma,&Mb,CV_DIST_L2,3);
//sum up the pixels of distance less than gap
		mx=regList1[i].boundBox.left;
		my=regList1[i].boundBox.top;
		mw=regList1[i].boundBox.Width();
		mh=regList1[i].boundBox.Height();

		pos=my*width+mx;
		total=0;
		bl=0;
		nbl=0;//matched boundry length
		for(j=0;j<mh;++j)
		{			
			for(k=0;k<mw;++k)
			{
				if(tag1[pos]==i)
				{
					if(CheckNei(tag1,width,height,pos)!=4){
						++bl;
						dest=(j+my-y0)*w0+(k+mx-x0);
						nbl+=pool[dest]<=gap?1:0;
					}
					++total;
				}
				++pos;
			}
			pos+=width-mw;
		}
		assert(nbl<=bl);
		refList1[i].gDist=(float)nbl/bl;
		assert(total==regList1[i].size);
		delete[]patch;
		delete[]pool;
	}
	amount=refList2.size();
	//compute distance of boundaries in segmentation 2 to that of segmentation 1
	for(i=0;i<amount;++i){
		if((float)refList2[i].section/regList2[i].size<coverage)
			continue;
	
		cand=refList2[i].bestp;
		meg.UnionRect(&regList2[i].boundBox, &regList1[cand].boundBox);
		h0=meg.Height();
		w0=meg.Width();
		BYTE*patch=new BYTE[h0*w0];
		float *pool=new float[h0*w0];
		memset(patch,1,sizeof(BYTE)*h0*w0);
		cvInitMatHeader( &Ma, h0, w0, CV_8UC1, patch);
		cvInitMatHeader( &Mb, h0, w0, CV_32FC1, pool);

		x0=meg.left;
		y0=meg.top;
		mx=regList1[cand].boundBox.left;
		my=regList1[cand].boundBox.top;
		mw=regList1[cand].boundBox.Width();
		mh=regList1[cand].boundBox.Height();

		pos=my*width+mx;
		total=0;//number of pixel in a region
//		bl=0;//boundary length
		for(j=0;j<mh;++j)
		{			
			for(k=0;k<mw;++k)
			{
				if(tag1[pos]==cand)
				{
					if(CheckNei(tag1,width,height,pos)!=4){
					//	++bl;
						dest=(j+my-y0)*w0+(k+mx-x0);
						patch[dest]=0;
					}					
					++total;
				}
				++pos;
			}
			pos+=width-mw;
		}
		
		assert(total==regList1[cand].size);
	
		cvDistTransform(&Ma,&Mb,CV_DIST_L2,3);
//sum up the pixels of distance less than gap
		mx=regList2[i].boundBox.left;
		my=regList2[i].boundBox.top;
		mw=regList2[i].boundBox.Width();
		mh=regList2[i].boundBox.Height();

		pos=my*width+mx;
		total=0;
		bl=0;
		nbl=0;//matched boundry length
		for(j=0;j<mh;++j)
		{			
			for(k=0;k<mw;++k)
			{
				if(tag2[pos]==i)
				{
					if(CheckNei(tag2,width,height,pos)!=4){
						++bl;
						dest=(j+my-y0)*w0+(k+mx-x0);
						nbl+=pool[dest]<=gap?1:0;
					}
					++total;
				}
				++pos;
			}
			pos+=width-mw;
		}
		assert(nbl<=bl);
		refList2[i].gDist=(float)nbl/bl;
		assert(total==regList2[i].size);
		delete[]patch;
		delete[]pool;
	}
}