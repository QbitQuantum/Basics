void MG_vectorGL::drawArrow( MVector vec  ,  MVector upVec , double arrowSizeV ,  MPoint startPointV )
 {
	
	vec.normalize();
	upVec.normalize();

	
	double tipX , tipY , tipZ, 
	      corner1X ,corner1Y ,corner1Z ,
	      corner2X ,corner2Y ,corner2Z ,
	      corner3X ,corner3Y ,corner3Z ,
	      corner4X ,corner4Y ,corner4Z ;
	
	double dot = vec*upVec;
	if (dot >= 0.99 )
	{
	  tipX=(0.0)+startPointV.x;
	  tipY=(1.0*arrowSizeV)+startPointV.y;
	  tipZ=(0.0)+startPointV.z;
	  
	  
	  corner1Y=(0.9*arrowSizeV)+startPointV.y;
	  corner1X=(0.05*arrowSizeV)+startPointV.x ;
	  corner1Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner2Y=(0.9*arrowSizeV)+startPointV.y;
	  corner2X=(0.05*arrowSizeV)+startPointV.x;
	  corner2Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner3Y=(0.9*arrowSizeV)+startPointV.y;
	  corner3X=(-0.05*arrowSizeV)+startPointV.x;
	  corner3Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  corner4Y=(0.9*arrowSizeV)+startPointV.y;
	  corner4X=(-0.05*arrowSizeV)+startPointV.x;
	  corner4Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	}
 	
 	else if (dot <= -0.99)
	{
	  tipX=(0.0)+startPointV.x;
	  tipY=(1.0*arrowSizeV*-1)+startPointV.y;
	  tipZ=(0.0)+startPointV.z;
	  
	  
	  corner1Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner1X=(0.05*arrowSizeV)+startPointV.x ;
	  corner1Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner2Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner2X=(0.05*arrowSizeV)+startPointV.x;
	  corner2Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  
	  corner3Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner3X=(-0.05*arrowSizeV)+startPointV.x;
	  corner3Z=(0.05*arrowSizeV)+startPointV.z;
	  
	  corner4Y=(0.9*arrowSizeV*-1)+startPointV.y;
	  corner4X=(-0.05*arrowSizeV)+startPointV.x;
	  corner4Z=(-0.05*arrowSizeV)+startPointV.z;
	  
	  
	  
	}
	
	else
	{
	  
	   MVector cross1Pos = vec^upVec;
	   cross1Pos.normalize();
	   MVector cross2Pos = cross1Pos^vec;
	   
	   MVector vecScaled = vec*0.9;
	   MVector corner1 = (((cross1Pos*0.07)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner2 = (((cross2Pos*0.07)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner3 = (((cross1Pos*0.07*-1)+vecScaled)*arrowSizeV)+startPointV;
	   MVector corner4 = (((cross2Pos*0.07*-1)+vecScaled)*arrowSizeV)+startPointV;
	   
	   corner1X = corner1.x;
	   corner1Y = corner1.y;
	   corner1Z = corner1.z;
	   
	   corner2X = corner2.x;
	   corner2Y = corner2.y;
	   corner2Z = corner2.z;
	   
	   corner3X = corner3.x;
	   corner3Y = corner3.y;
	   corner3Z = corner3.z;
	   
	   corner4X = corner4.x;
	   corner4Y = corner4.y;
	   corner4Z = corner4.z;
	   
	   tipX = (vec.x*arrowSizeV) +startPointV.x;
	   tipY = (vec.y*arrowSizeV)+startPointV.y;
	   tipZ = (vec.z*arrowSizeV)+startPointV.z;
	}
	  
 	
	glBegin(GL_LINES);
		//draw the reader 
		glVertex3d(0+startPointV.x,0+startPointV.y,0+startPointV.z);
		glVertex3d(tipX,tipY,tipZ);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3d(corner1X,corner1Y,corner1Z);
		glVertex3d(corner2X,corner2Y,corner2Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex3d(corner3X,corner3Y,corner3Z);
		glVertex3d(corner2X,corner2Y,corner2Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3X,corner3Y,corner3Z);
		glVertex3d(corner4X,corner4Y,corner4Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();

	glBegin(GL_TRIANGLES);
		glBegin(GL_TRIANGLES);
		glVertex3d(corner1X,corner1Y,corner1Z);
		glVertex3d(corner4X,corner4Y,corner4Z);
		glVertex3d(tipX,tipY,tipZ);

	glEnd();
 }