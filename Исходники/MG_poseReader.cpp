void MG_poseReader::drawArrowMatrix(const int aimAxis,const double arrowSizeV,const MMatrix poseM ,const MMatrix readerM)
 {

	
	 MVector tipV,corner1V,corner2V,corner3V,corner4V;
	 MMatrix tipM,corner1M,corner2M,corner3M,corner4M,baseM;
	 baseM.setToIdentity();
	 baseM*=poseM;
	 baseM*=readerM.inverse();
	 switch ( aimAxis )
			{

				case 0:
					if (aimAxis==0)
					{
						
						tipV.x=1*arrowSizeV;
						tipV.y=0.0;
						tipV.z=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.x=0.9*arrowSizeV;
						corner1V.y=0.05*arrowSizeV;
						corner1V.z=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						corner1M*=readerM.inverse();

						

						corner2V.x=0.9*arrowSizeV;
						corner2V.y=0.05*arrowSizeV;
						corner2V.z=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.x=0.9*arrowSizeV;
						corner3V.y=-0.05*arrowSizeV;
						corner3V.z=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.x=0.9*arrowSizeV;
						corner4V.y=-0.05*arrowSizeV;
						corner4V.z=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

						
					}
				case 1:
					if (aimAxis==1)
					{
						tipV.y=1*arrowSizeV;
						tipV.x=0.0;
						tipV.z=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.y=0.9*arrowSizeV;
						corner1V.x=0.05*arrowSizeV;
						corner1V.z=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						
						corner1M*=readerM.inverse();

						

						corner2V.y=0.9*arrowSizeV;
						corner2V.x=0.05*arrowSizeV;
						corner2V.z=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.y=0.9*arrowSizeV;
						corner3V.x=-0.05*arrowSizeV;
						corner3V.z=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.y=0.9*arrowSizeV;
						corner4V.x=-0.05*arrowSizeV;
						corner4V.z=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

					}

				case 2:
					if (aimAxis==2)
					{
						tipV.z=1*arrowSizeV;
						tipV.x=0.0;
						tipV.y=0.0;
						tipM=fromVecToMatrix(tipV);
						tipM*=poseM;
						tipM*=readerM.inverse();

						corner1V.z=0.9*arrowSizeV;
						corner1V.x=0.05*arrowSizeV;
						corner1V.y=-0.05*arrowSizeV;
						corner1M=fromVecToMatrix(corner1V);
						corner1M*=poseM;
						
						corner1M*=readerM.inverse();

						

						corner2V.z=0.9*arrowSizeV;
						corner2V.x=0.05*arrowSizeV;
						corner2V.y=0.05*arrowSizeV;
						corner2M=fromVecToMatrix(corner2V);
						corner2M*=poseM;
						corner2M*=readerM.inverse();


						corner3V.z=0.9*arrowSizeV;
						corner3V.x=-0.05*arrowSizeV;
						corner3V.y=0.05*arrowSizeV;
						corner3M=fromVecToMatrix(corner3V);
						corner3M*=poseM;
						corner3M*=readerM.inverse();


						corner4V.z=0.9*arrowSizeV;
						corner4V.x=-0.05*arrowSizeV;
						corner4V.y=-0.05*arrowSizeV;
						corner4M=fromVecToMatrix(corner4V);
						corner4M*=poseM;
						corner4M*=readerM.inverse();

					}


			}

	glBegin(GL_LINES);
		
		glVertex3d(baseM[3][0],baseM[3][1],baseM[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);


	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner1M[3][0],corner1M[3][1],corner1M[3][2]);
		glVertex3d(corner2M[3][0],corner2M[3][1],corner2M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3M[3][0],corner3M[3][1],corner3M[3][2]);
		glVertex3d(corner2M[3][0],corner2M[3][1],corner2M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner3M[3][0],corner3M[3][1],corner3M[3][2]);
		glVertex3d(corner4M[3][0],corner4M[3][1],corner4M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();


	glBegin(GL_TRIANGLES);
		glVertex3d(corner1M[3][0],corner1M[3][1],corner1M[3][2]);
		glVertex3d(corner4M[3][0],corner4M[3][1],corner4M[3][2]);
		glVertex3d(tipM[3][0],tipM[3][1],tipM[3][2]);

	glEnd();

	


 }