MObject VMesh::createFeather()
{
	MStatus stat;
	MFnMeshData dataCreator;
	MObject outMeshData = dataCreator.create(&stat);
	
	int numVertex = 0;
	int numPolygon = 0;
	MPointArray vertexArray;
	MFloatArray uArray, vArray;
	MIntArray polygonCounts, polygonConnects, polygonUVs;

	MFnMesh meshFn(pgrow, &stat);
	MItMeshVertex vertIter(pgrow, &stat);
	MItMeshPolygon faceIter(pgrow,  &stat);
	
	MPoint S;
	MVector N, tang, ttang, binormal, dir, hair_up;
	MColor Cscale, Cerect, Crotate, Ccurl, Cwidth;
	float rot, lengreal;
	MATRIX44F hair_space;
	
	MString setScale("fb_scale");
	MString setErect("fb_erect");
	MString setRotate("fb_rotate");
	MString setCurl("fb_curl");
	MString setWidth("fb_width");
	MIntArray conn_face;
	
	for( int i=0; !vertIter.isDone(); vertIter.next(), i++ )
	{
		if(vertIter.onBoundary()) continue;
		vertIter.getNormal(N, MSpace::kWorld);
		N.normalize();
		
		vertIter.getColor(Cscale, &setScale);
		vertIter.getColor(Cerect, &setErect);
		vertIter.getColor(Crotate, &setRotate);
		vertIter.getColor(Ccurl, &setCurl);
		vertIter.getColor(Cwidth, &setWidth);
		
		vertIter.getConnectedFaces(conn_face);
		tang = MVector(0,0,0);
		for(int j=0; j<conn_face.length(); j++)
		{
			meshFn.getFaceVertexTangent (conn_face[j], i, ttang,  MSpace::kWorld);
			ttang.normalize();
			tang += ttang;
		}
		tang /= conn_face.length();
		conn_face.clear();
		tang.normalize();
		tang = N^tang;
		tang.normalize();
		
		binormal = N^tang;
		
		if(Crotate.r<0.5)
		{
			rot = (0.5 - Crotate.r)*2;
			tang = tang + (binormal-tang)*rot;
			tang.normalize();
			binormal = N^tang;
		}
		else
		{
			rot = (Crotate.r-0.5)*2;
			tang = tang + (binormal*-1-tang)*rot;
			tang.normalize();
			binormal = N^tang;
		}
		
		dir = tang + (N - tang)*Cerect.r;
		dir.normalize();
		
		//S = S+dir*Cscale.r*m_scale;
		//glVertex3f(S.x, S.y, S.z);
		
		hair_up = dir^binormal;
		
		hair_space.setIdentity();
		hair_space.setOrientations(XYZ(binormal.x, binormal.y, binormal.z), XYZ(hair_up.x, hair_up.y, hair_up.z), XYZ(dir.x, dir.y, dir.z));
		
		S = vertIter.position(MSpace::kWorld);
		
		hair_space.setTranslation(XYZ(S.x, S.y, S.z));
		
		lengreal = Cscale.r*m_scale;
		
		fb->create(lengreal, 0, lengreal*(Ccurl.r-0.5)*2);
		
		XYZ pw;
		MPoint pvx;
		
		MPoint pright = S + binormal*Cwidth.r*m_width*lengreal;
		MPoint pleft = S - binormal*Cwidth.r*m_width*lengreal;
		
		MPoint phit;
		int polyhit;
		meshFn.getClosestPoint (pright,  phit,  MSpace::kObject, &polyhit);
		MVector topright = phit - S;
		topright.normalize();
		topright *= Cwidth.r*m_width*lengreal;
		
		meshFn.getClosestPoint (pleft,  phit,  MSpace::kObject, &polyhit);
		MVector topleft = phit - S;
		topleft.normalize();
		topleft *= Cwidth.r*m_width*lengreal;
		
		//tws_binormal  = binormal*cos(0.2) + hair_up*sin(0.2);
	
		for(int j=0; j<NUMBENDSEG+1; j++)
		{
			fb->getPoint(j, pw);
			hair_space.transform(pw);
			
			pvx = MPoint(pw.x, pw.y, pw.z) + topleft;//- tws_binormal*Cwidth.r*m_width*lengreal;
			vertexArray.append(pvx);
			pvx = MPoint(pw.x, pw.y, pw.z);
			vertexArray.append(pvx);
			pvx = MPoint(pw.x, pw.y, pw.z) + topright;//tws_binormal*Cwidth.r*m_width*lengreal;
			vertexArray.append(pvx);
			
			uArray.append(0.0);
			vArray.append((float)j/NUMBENDSEG);
			
			uArray.append(0.5);
			vArray.append((float)j/NUMBENDSEG);
			
			uArray.append(1.0);
			vArray.append((float)j/NUMBENDSEG);
		}

		for(int j=0; j<NUMBENDSEG; j++)
		{
			polygonConnects.append(j*3 + numVertex);
			polygonConnects.append(j*3+3 + numVertex);
			polygonConnects.append(j*3+4 + numVertex);
			polygonConnects.append(j*3+1 + numVertex);
			
			polygonCounts.append(4);
			
			polygonConnects.append(j*3+1 + numVertex);
			polygonConnects.append(j*3+4 + numVertex);
			polygonConnects.append(j*3+5 + numVertex);
			polygonConnects.append(j*3+2 + numVertex);
			
			polygonCounts.append(4);
			
			polygonUVs.append(j*3 + numVertex);
			polygonUVs.append(j*3+3 + numVertex);
			polygonUVs.append(j*3+4 + numVertex);
			polygonUVs.append(j*3+1 + numVertex);
			
			polygonUVs.append(j*3+1 + numVertex);
			polygonUVs.append(j*3+4 + numVertex);
			polygonUVs.append(j*3+5 + numVertex);
			polygonUVs.append(j*3+2 + numVertex);
		}
		
		numVertex += (NUMBENDSEG+1)*3;
		numPolygon += NUMBENDSEG*2;
	}
	
	MIntArray connvert; 
	int idxpre;
	float averg_scale, averg_erect, averg_rotate, averg_curl, averg_width;
	for( int i=0; !faceIter.isDone(); faceIter.next(), i++ )
	{
		if(faceIter.onBoundary()) continue;
		faceIter.getNormal(N, MSpace::kWorld);
		N.normalize();
		
		faceIter.getVertices(connvert);
		
		averg_scale=averg_erect=averg_rotate=averg_curl=0;
		for(int j=0; j<connvert.length(); j++)
		{
			vertIter.setIndex(connvert[j], idxpre);
			
			vertIter.getColor(Cscale, &setScale);
			vertIter.getColor(Cerect, &setErect);
			vertIter.getColor(Crotate, &setRotate);
			vertIter.getColor(Ccurl, &setCurl);
			vertIter.getColor(Cwidth, &setWidth);
			
			averg_scale += Cscale.r;
			averg_erect += Cerect.r;
			averg_rotate += Crotate.r;
			averg_curl += Ccurl.r;
			averg_width += Cwidth.r;
		}
		
		averg_scale /= connvert.length();
		averg_erect /= connvert.length();
		averg_rotate /= connvert.length();
		averg_curl /= connvert.length();
		averg_width /= connvert.length();
		
		tang = MVector(0,0,0);
		for(int j=0; j<connvert.length(); j++)
		{
			meshFn.getFaceVertexTangent (i, connvert[j], ttang,  MSpace::kWorld);
			ttang.normalize();
			tang += ttang;
		}
		//tang /= conn_face.length();
		connvert.clear();
		tang.normalize();
		tang = N^tang;
		tang.normalize();
		
		binormal = N^tang;
		
		if(averg_rotate<0.5)
		{
			rot = (0.5 - averg_rotate)*2;
			tang = tang + (binormal-tang)*rot;
			tang.normalize();
			binormal = N^tang;
		}
		else
		{
			rot = (averg_rotate-0.5)*2;
			tang = tang + (binormal*-1-tang)*rot;
			tang.normalize();
			binormal = N^tang;
		}
		
		dir = tang + (N - tang)*averg_erect;
		dir.normalize();
		
		//S = S+dir*Cscale.r*m_scale;
		//glVertex3f(S.x, S.y, S.z);
		
		hair_up = dir^binormal;
		
		hair_space.setIdentity();
		hair_space.setOrientations(XYZ(binormal.x, binormal.y, binormal.z), XYZ(hair_up.x, hair_up.y, hair_up.z), XYZ(dir.x, dir.y, dir.z));
		
		S = faceIter.center(MSpace::kWorld);
		
		hair_space.setTranslation(XYZ(S.x, S.y, S.z));
		
		lengreal = Cscale.r*m_scale;
		
		fb->create(lengreal, 0, lengreal*(averg_curl-0.5)*2);
		
		MPoint pright = S + binormal*Cwidth.r*m_width*lengreal;
		MPoint pleft = S - binormal*Cwidth.r*m_width*lengreal;
		
		XYZ pw;
		MPoint pvx;
		
		MPoint phit;
		int polyhit;
		meshFn.getClosestPoint (pright,  phit,  MSpace::kObject, &polyhit);
		MVector topright = phit - S;
		topright.normalize();
		topright *= Cwidth.r*m_width*lengreal;
		
		meshFn.getClosestPoint (pleft,  phit,  MSpace::kObject, &polyhit);
		MVector topleft = phit - S;
		topleft.normalize();
		topleft *= Cwidth.r*m_width*lengreal;
		//tws_binormal  = binormal*cos(0.2) + hair_up*sin(0.2);
	
		for(int j=0; j<NUMBENDSEG+1; j++)
		{
			fb->getPoint(j, pw);
			hair_space.transform(pw);
			
			pvx = MPoint(pw.x, pw.y, pw.z) + topleft;//- tws_binormal*averg_width*m_width*lengreal;
			vertexArray.append(pvx);
			pvx = MPoint(pw.x, pw.y, pw.z);
			vertexArray.append(pvx);
			pvx = MPoint(pw.x, pw.y, pw.z) + topright;//tws_binormal*averg_width*m_width*lengreal;
			vertexArray.append(pvx);
			
			uArray.append(0.0);
			vArray.append((float)j/NUMBENDSEG);
			
			uArray.append(0.5);
			vArray.append((float)j/NUMBENDSEG);
			
			uArray.append(1.0);
			vArray.append((float)j/NUMBENDSEG);
		}

		for(int j=0; j<NUMBENDSEG; j++)
		{
			polygonConnects.append(j*3 + numVertex);
			polygonConnects.append(j*3+3 + numVertex);
			polygonConnects.append(j*3+4 + numVertex);
			polygonConnects.append(j*3+1 + numVertex);
			
			polygonCounts.append(4);
			
			polygonConnects.append(j*3+1 + numVertex);
			polygonConnects.append(j*3+4 + numVertex);
			polygonConnects.append(j*3+5 + numVertex);
			polygonConnects.append(j*3+2 + numVertex);
			
			polygonCounts.append(4);
			
			polygonUVs.append(j*3 + numVertex);
			polygonUVs.append(j*3+3 + numVertex);
			polygonUVs.append(j*3+4 + numVertex);
			polygonUVs.append(j*3+1 + numVertex);
			
			polygonUVs.append(j*3+1 + numVertex);
			polygonUVs.append(j*3+4 + numVertex);
			polygonUVs.append(j*3+5 + numVertex);
			polygonUVs.append(j*3+2 + numVertex);
		}
		
		numVertex += (NUMBENDSEG+1)*3;
		numPolygon += NUMBENDSEG*2;
		
	}

	
	MFnMesh meshCreateFn;
	meshCreateFn.create( numVertex, numPolygon, vertexArray, polygonCounts, polygonConnects, outMeshData, &stat );
	
	meshCreateFn.setUVs ( uArray, vArray );
	meshCreateFn.assignUVs ( polygonCounts, polygonUVs );
	
	return outMeshData;
}