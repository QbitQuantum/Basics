//-----------------------------------------------------------------------------
void MGL_EXPORT mgl_contf_y_val(HMGL gr, HCDT v, HCDT a, const char *sch, double sv, const char *opt)
{
	long n=a->GetNx(),m=a->GetNy();
	if(n<2 || m<2)	{	gr->SetWarn(mglWarnLow,"ContFY");	return;	}
	gr->SaveState(opt);
	if(mgl_isnan(sv))	sv = gr->GetOrgY('y');
	if(sv<gr->Min.y || sv>gr->Max.y)	{	gr->SetWarn(mglWarnSlc,"ContFY");	gr->LoadState();	return;	}
	static int cgid=1;	gr->StartGroup("ContFY",cgid++);
	mglDataV xx,yy,zz;	mglData aa;
	long ss=gr->AddTexture(sch);

	a = fill_slice_y(gr,sv,a,xx,yy,zz,aa);
#pragma omp parallel for
	for(long i=0;i<v->GetNx()-1;i++)
	{
		mreal v0 = v->v(i);
		mgl_contf_gen(gr,v0,v->v(i+1),a,&xx,&yy,&zz,gr->GetC(ss,v0),0);
	}
	gr->EndGroup();
}