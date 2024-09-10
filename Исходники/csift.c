void DrawRegion( Region key, float scale ) {
	
	if ( key == NULL ) return;
	
	int stable = key->stable;
	
	char name[256];
	sprintf(name,"/tmp/T%03d.ppm",stable);
	Image out = ReadPPMFile(name);
	
	static int count = 0;
	
	if ( !ImageIsGood(out) ) {
		out = ConvertImage1(CopyImage(key->image));
		sprintf(name,"/tmp/R%05d.ppm",count++);
	} else sprintf(name,"/tmp/T%03d.ppm",stable);
	
	fprintf(stderr,".");
	
	int rv = RandomNumber(0,255);
	int gv = RandomNumber(0,rv);
	int bv = RandomNumber(0,gv);
	
	int color = PIX3(rv,gv,bv);
	
	DrawPolygon(key->border,out,color);
	
	Ellipse e1 = NewEllipse(key->row,key->col,key->maj*scale,key->min*scale,key->phi);
	DrawEllipse(e1,out,color); free(e1);
	Image patch = CreateImage(41*sqrt(2),41*sqrt(2));
	RegionToPatch(key,key->image,patch,scale);

	FVec hist = GenerateOrientationHistogram(patch);
	GaussianBlur1D(hist->values,hist->l,hist->r,2);
	DrawFVec(hist,10,10,200,400,PIX3(0,0,250),out);
	FVecFree(hist);
	
	if ( PolygonIsGood(key->sizes) ) {
		
		struct PointSt p1 = key->sizes->vertices[0];
		struct PointSt p2 = key->sizes->vertices[key->sizes->numberOfVertices-1];

		int i;
		hist = FVecNew(0,255);
		Point p;
		while ( ( p = NextPolygonVertex(key->sizes) ) != NULL ) FVecSetAt(hist,p->y,p->x);
		if ( p1.y < p2.y ) {
			for(i=p1.y;i<=p2.y;i++) if ( hist->values[i] == 0.0 ) FVecAddAt(hist,i,1);
		} else {
			for(i=p2.y;i>=p1.y;i--) if ( hist->values[i] == 0.0 ) FVecAddAt(hist,i,1);
		}
		
		hist->l = MIN(p1.y,p2.y);
		hist->r = MAX(p2.y-1,p1.y-1);
		
		DrawSizeFVec(hist,497,0,1021,1023,color,stable,out);
		DrawSizeFVec(hist,498,0,1022,1023,color,stable,out);
		DrawSizeFVec(hist,499,0,1023,1023,color,stable,out);
		
	}
	
	WritePPM(name,out);
	FreeImage(out);

}