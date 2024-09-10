Image2D::SampleResult Image2D::getColor(const Image2D::Point& worldPos) const
	{
	/* Transform the world position to image space: */
	Point imagePos=invTransform.transform(worldPos);
	
	/* Bail out if the image position is outside the image: */
	if(imagePos[0]<imageBox.min[0]||imagePos[0]>=imageBox.max[0]||imagePos[1]<imageBox.min[1]||imagePos[1]>=imageBox.max[1])
		return SampleResult(false,Color(0,0,0));
	
	/* Sample the image: */
	unsigned int cx=(unsigned int)imagePos[0];
	double dx=imagePos[0]-double(cx);
	unsigned int cy=(unsigned int)imagePos[1];
	double dy=imagePos[1]-double(cy);
	const Color* r0=image.getPixelRow(cy);
	const Color* r1=image.getPixelRow(cy+1);
	double p0[3],p1[3];
	for(int i=0;i<3;++i)
		{
		p0[i]=double(r0[cx][i])*(1.0-dx)+double(r0[cx+1][i])*dx;
		p1[i]=double(r1[cx][i])*(1.0-dx)+double(r1[cx+1][i])*dx;
		}
	Color result;
	for(int i=0;i<3;++i)
		{
		double v=p0[i]*(1.0-dy)+p1[i]*dy;
		if(v<0.5)
			result[i]=Color::Scalar(0);
		else if(v>=254.5)
			result[i]=Color::Scalar(255);
		else
			result[i]=Color::Scalar(v+0.5);
		}
	return SampleResult(true,result);
	}