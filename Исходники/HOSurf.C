void genSurfFile(Element *E, double *x, double *y, double *z, Curve *curve)
{
	register int i;
	int      info,l,lm[4];
	int      q1 = E->qa, q2 = E->qb,*vertid,fid, cnt, cnt1;
	int      ntot = Snp*(Snp+1)/2;
	double   **sj;
	static int *chkfid;

	if(!chkfid)
	{
		chkfid = ivector(0,Snface-1);
		izero(Snface,chkfid,1);
	}

	vertid = curve->info.file.vert;

	if(E->identify() == Nek_Prism)
		q2 = E->qc;

	// find face id;
	cnt = vertid[0] + vertid[1] + vertid[2];
	for(i = 0; i < Snface; ++i)
		if(surfids[i][3] == cnt)
		{ // just search vertices with same vertex id sum
			if(vertid[0] == surfids[i][0])
			{
				if((vertid[1] == surfids[i][1])||(vertid[1] == surfids[i][2]))
				{

					chkfid[i]++;
					if(chkfid[i] > 1) // check form mutiple calls to same face
						fprintf(stderr,"gensurfFile: Error face %d is being "
						        "operated on multiple times\n",i);

					if(vertid[1] == surfids[i][2])
					{
						Rotate(i,1);
						Reflect(i);
					}
					fid = i;
					break;
				}
			}
			else if(vertid[0] == surfids[i][1])
			{
				if((vertid[1] == surfids[i][0])||(vertid[1] == surfids[i][2]))
				{
					chkfid[i]++;
					if(chkfid[i] > 1) // check form mutiple calls to same face
						fprintf(stderr,"gensurfFile: Error face %d is being "
						        "operated on multiple times\n",i);

					if(vertid[1] == surfids[i][0])
						Reflect(i);
					else
						Rotate(i,2);

					fid = i;
					break;
				}
			}
			else if(vertid[0] == surfids[i][2])
			{
				if((vertid[1] == surfids[i][0])||(vertid[1] == surfids[i][1]))
				{

					chkfid[i]++;
					if(chkfid[i] > 1) // check form mutiple calls to same face
						fprintf(stderr,"gensurfFile: Error face %d is being "
						        "operated on multiple times\n",i);

					if(vertid[1] == surfids[i][1])
					{
						Rotate(i,2);
						Reflect(i);
					}
					else
						Rotate(i,1); // set up to rotate Feisal to Nektar
					fid = i;
					break;
				}
			}
		}

	// invert basis
	dgetrs('T', ntot, 1, *CollMat,ntot,CollMatIpiv,SurXpts[fid],ntot,info);
	if(info)
		fprintf(stderr,"Trouble solve collocation X matrix\n");
	dgetrs('T', ntot, 1, *CollMat,ntot,CollMatIpiv,SurYpts[fid],ntot,info);
	if(info)
		fprintf(stderr,"Trouble solve collocation Y matrix\n");
	dgetrs('T', ntot, 1, *CollMat,ntot,CollMatIpiv,SurZpts[fid],ntot,info);
	if(info)
		fprintf(stderr,"Trouble solve collocation Z matrix\n");

	// Take out require modes and Backward transformation

	// base it on LGmax at present although might cause problems with
	// trijbwd if LGmax > qa

	sj = dmatrix(0,2,0,LGmax*(LGmax+1)/2-1);
	dzero(3*LGmax*(LGmax+1)/2,sj[0],1);

	lm[0] = LGmax-2;
	lm[1] = LGmax-2;
	lm[2] = LGmax-2;
	lm[3] = max(LGmax-3,0);

	dcopy(3,SurXpts[fid],1,sj[0],1);
	dcopy(3,SurYpts[fid],1,sj[1],1);
	dcopy(3,SurZpts[fid],1,sj[2],1);

	cnt = cnt1 = 3;
	for(i=0;i<3;++i)
	{
		l   = lm[i];
		dcopy(min(Snp-2,l), SurXpts[fid]+cnt,1,sj[0]+cnt1,1);
		dcopy(min(Snp-2,l), SurYpts[fid]+cnt,1,sj[1]+cnt1,1);
		dcopy(min(Snp-2,l), SurZpts[fid]+cnt,1,sj[2]+cnt1,1);
		cnt  += Snp-2;
		cnt1 += l;
	}

	l = lm[3];

	for(i=0;i<l;++i)
	{
		dcopy(min(Snp-3,l)-i,SurXpts[fid]+cnt,1,sj[0]+cnt1,1);
		dcopy(min(Snp-3,l)-i,SurYpts[fid]+cnt,1,sj[1]+cnt1,1);
		dcopy(min(Snp-3,l)-i,SurZpts[fid]+cnt,1,sj[2]+cnt1,1);
		cnt  += Snp-3-i;
		cnt1 += l-i;
	}

	JbwdTri(q1,q2,LGmax,lm,sj[0],x);
	JbwdTri(q1,q2,LGmax,lm,sj[1],y);
	JbwdTri(q1,q2,LGmax,lm,sj[2],z);

	free_dmatrix(sj,0,0);
}