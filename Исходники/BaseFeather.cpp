void BaseFeather::computeTexcoord()
{
	Vector2F puv = m_uv;
	float *q = quilly();
	int i, j;
	for(i=0; i <= numSegment(); i++) {
		*segmentQuillTexcoord(i) = puv;
		if(i < numSegment()) {
			puv += Vector2F(0.f, *q);
			q++;
		}
	}
	
	q = quilly();
	puv = m_uv;
	
	Vector2F pvane;
	for(i=0; i <= numSegment(); i++) {
		
		pvane = puv;
		Vector2F * vanes = uvDisplaceAt(i, 0);
		
		for(j = 0; j < 3; j++) {
			pvane += vanes[j];
			*segmentVaneTexcoord(i, 0, j) = pvane;
		}

		pvane = puv;
		vanes = getUvDisplaceAt(i, 1);
		
		for(j = 0; j < 3; j++) {
			pvane += vanes[j];
			*segmentVaneTexcoord(i, 1, j) = pvane;
		}
		
		if(i < numSegment()) {
			puv += Vector2F(0.f, *q);
			q++;
		}
	}
	
	for(i = 0; i < numWorldP(); i++) {

		texcoord()[i] /= 32.f;
	}
		
	computeBounding();
	computeLength();
}