//-----------------------------------------------------------------------------
//
//	QuadPlot series
//
//-----------------------------------------------------------------------------
void MGL_EXPORT mgl_quadplot_xyzc(HMGL gr, HCDT nums, HCDT x, HCDT y, HCDT z, HCDT a, const char *sch, const char *opt)
{
	long n = x->GetNx(), m = nums->GetNy();
	if(mgl_check_trig(gr,nums,x,y,z,a,"QuadPlot",4))	return;

	long ss=gr->AddTexture(sch);
	gr->SaveState(opt);	gr->SetPenPal("-");
	static int cgid=1;	gr->StartGroup("QuadPlot",cgid++);
	mglPoint p1,p2,p3,p4;

	long nc = a->GetNx();
	bool wire = mglchr(sch,'#');
	if(nc!=n && nc>=m)	// colors per triangle
	{
		gr->Reserve(m*4);
		for(long i=0;i<m;i++)
		{
			register long k1 = long(nums->v(0,i)+0.5);
			p1 = mglPoint(x->v(k1), y->v(k1), z->v(k1));
			register long k2 = long(nums->v(1,i)+0.5);
			p2 = mglPoint(x->v(k2), y->v(k2), z->v(k2));
			register long k3 = long(nums->v(2,i)+0.5);
			p3 = mglPoint(x->v(k3), y->v(k3), z->v(k3));
			register long k4 = floor(nums->v(3,i)+0.5);
			p4 = mglPoint(x->v(k4), y->v(k4), z->v(k4));
			mglPoint q = wire ? mglPoint(NAN,NAN):(p2-p1) ^ (p3-p1);
			k1 = gr->AddPnt(p1,gr->GetC(ss,a->v(k1)),q);
			k2 = gr->AddPnt(p2,gr->GetC(ss,a->v(k2)),q);
			k3 = gr->AddPnt(p3,gr->GetC(ss,a->v(k3)),q);
			k4 = gr->AddPnt(p4,gr->GetC(ss,a->v(k4)),q);
			gr->quad_plot(k1,k2,k3,k4);
		}
	}
	else if(nc>=n)		// colors per point
	{
		gr->Reserve(n);
		long *kk = new long[n];
		mglPoint *pp = new mglPoint[n];
		for(long i=0;i<m;i++)	// add averaged normales
		{
			register long k1 = long(nums->v(0,i)+0.5);
			p1 = mglPoint(x->v(k1), y->v(k1), z->v(k1));
			register long k2 = long(nums->v(1,i)+0.5);
			p2 = mglPoint(x->v(k2), y->v(k2), z->v(k2));
			register long k3 = long(nums->v(2,i)+0.5);
			p3 = mglPoint(x->v(k3), y->v(k3), z->v(k3));
			register long k4 = floor(nums->v(3,i)+0.5);
			p4 = mglPoint(x->v(k4), y->v(k4), z->v(k4));

			if(wire)	pp[k1]=pp[k2]=pp[k3]=pp[k4]=mglPoint(NAN,NAN);
			else
			{
				mglPoint q1 = (p2-p1) ^ (p3-p1);	if(q1.z<0) q1*=-1;
				mglPoint q2 = (p2-p4) ^ (p3-p4);	if(q2.z<0) q2*=-1;
				mglPoint q3 = (p1-p2) ^ (p4-p2);	if(q3.z<0) q3*=-1;
				mglPoint q4 = (p1-p4) ^ (p4-p3);	if(q4.z<0) q4*=-1;
				pp[k1] += q1;	pp[k2] += q2;	pp[k3] += q3;	pp[k4] += q4;
			}
		}
		for(long i=0;i<n;i++)	// add points
			kk[i] = gr->AddPnt(mglPoint(x->v(i), y->v(i), z->v(i)),gr->GetC(ss,a->v(i)), pp[i]);
		for(long i=0;i<m;i++)	// draw quads
		{
			register long k1 = floor(nums->v(0,i)+0.5);
			register long k2 = floor(nums->v(1,i)+0.5);
			register long k3 = floor(nums->v(2,i)+0.5);
			register long k4 = floor(nums->v(3,i)+0.5);
			if(wire)
			{
				gr->line_plot(kk[k1],kk[k2]);	gr->line_plot(kk[k1],kk[k3]);
				gr->line_plot(kk[k4],kk[k2]);	gr->line_plot(kk[k4],kk[k3]);
			}
			else	gr->quad_plot(kk[k1],kk[k2],kk[k3],kk[k4]);
		}
		delete []kk;	delete []pp;
	}
	gr->EndGroup();
}