TerrainVertex  ChunkHandler::getVertexforPos(const ofVec3f &pos, int detailLevel)
{
	TerrainVertex  vert ;
	vert.position.y =0;
	
	Chunk *chunk = getClosestChunk(pos,  detailLevel);
	if (chunk==NULL) {
	return vert;
	}

	ofVec2f posSearch;
	posSearch.x = pos.x;
	posSearch.y= pos.z;
	posSearch.x-=chunk->center.x-chunkSize/2;
	posSearch.y-=chunk->center.z-chunkSize/2;

	posSearch.x/=4.0f;
	posSearch.y/=4.0f;

	int posX0 =floor( posSearch.x+0.5);
	int posY0 =floor(  posSearch.y+0.5);

	v0 =  chunk->getVertexForXY( posX0,posY0);
	float difx = posSearch.x-posX0;
	float dify = posSearch.y;
	int	posX1= posX0 ;
	int	posX2= posX0 ;
	int	posY1= posY0 ;
	int	posY2= posY0 ;

	if (pos.x <v0->position.x)
	{
		if (pos.z >v0->position.z)
		{
			posX2-=1;
			posY2+=1;
	
			v1 =  chunk->getVertexForXY( posX0-1,posY0);
			v2 =  chunk->getVertexForXY( posX0,posY0+1);

			if(pos.distance(v1->position)<pos.distance(v2->position))
			{
				posX1-=1;
			
			
			}else
			{
				posY1+=1;
				
			}

		}else
		{
			
			posY2-=1;
			posX1-=1;
		}
	}else
	{
		if (pos.z >v0->position.z)
		{
			posY2+=1;
			posX1+=1;
		
		}else
		{
			posX2+=1;
			posY2-=1;
		
			v1 =  chunk->getVertexForXY( posX0+1,posY0);
			v2 =  chunk->getVertexForXY( posX0,posY0-1);
			if(pos.distance(v1->position)<pos.distance(v2->position))
			{
				posX1+=1;
				
			}
			else
			{
				posY1-=1;
					
			}

		}
	}
	

	v1 =  chunk->getVertexForXY( posX1,posY1);
	v2 =  chunk->getVertexForXY( posX2,posY2);


	ofVec3f normal= terrainFunctions->getNormal(v0->position,v1->position,v2->position);

	///
	
	ofVec3f  rayStartPoint;
	rayStartPoint.set(pos.x,10000,pos.z);
	ofVec3f  raydir;
	raydir.set(0,-1,0);
	if (normal.y<0)normal*=-1;
	ofVec3f  tv0 = rayStartPoint -v0->position;    
	float a  = normal.dot(tv0);
	float b = normal.dot(raydir);
			
				
		
           float r  = -a / b;        
	if (b==0){r =10000;}


			
		
	
                

	ofVec3f intersectionPoint ;
	intersectionPoint.set(rayStartPoint.x + (raydir.x * r), rayStartPoint.y + (raydir.y * r), rayStartPoint.z + (raydir.z * r));
	vert.position = intersectionPoint;

	



	ofVec3f vp1,vp2,vp0;
	vp0.set(v0->position.x,v0->position.y,v0->position.z);
	vp1.set(v1->position.x,v1->position.y,v1->position.z);
	vp2.set(v2->position.x,v2->position.y,v2->position.z);
	
	float  b0  = barMass(intersectionPoint, vp1, vp2);
	float  b1  = barMass(intersectionPoint, vp0, vp2);
	float  b2  = barMass(intersectionPoint, vp0, vp1);
	
	float  bn = b0 + b1 + b2;
	b0 /= bn;
	b1 /= bn;
	b2 /= bn;
	
	
	vert.normal=(v0->normal *b0)+(v1->normal *b1)+(v2->normal *b2);
	return vert;
	
}