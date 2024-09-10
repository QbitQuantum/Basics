void displayTeapot(Camara &cam, Transformacion marco){
//Dibuja la foto de un Cubo con la cam y la pone en t

	// Transformacion de la camara
	Transformacion rotcam;
	Transformacion rotationx, rotationy;
	Punto newAT = AT;
	rotationx.rotX(rotationX);
	rotationy.rotY(rotationY);

	newAT = newAT.transform(rotationx);
	newAT = newAT.transform(rotationy);
	
	Punto vert = Punto(0.0, 1.0, 0.0);
	vert.transform(rotcam);

	canon.at(newAT);
	canon.lookAt(OR);
	canon.setVertical(vert.asVector());

	Punto newFR = FR;
	newFR = newFR.transform(rotationy);
	frontal.at(newFR);
	frontal.lookAt(OR);

	Punto newPE = PE;
	newPE = newPE.transform(rotationy);
	perfil.at(newPE);
	perfil.lookAt(OR);

	Punto newCE = CE;
	newCE = newCE.transform(rotationy);
	cenital.setVertical(newCE.asVector());
	
	rotationx.reset();
	rotationy.reset();


	Transformacion t = marco * cam.getview();
	
	//Dibujo de la tetera
	Transformacion rot; 
	rot.rotX(-90);
	Transformacion mov;
	mov.translation(Real4(0.0, -1.0, 0.0));

	
	for(int k=0;k<32;k++){
		S[k].getPoints(NVERT, sb);
		S[k].getTangents(NVERT, tgU, tgV);
		S[k].getNormals(NVERT, n);
	
		for(int i=0;i<NVERT*NVERT;i++){	
			sb[i] = sb[i].transform(rot).transform(mov);
			sb[i] =	cam.shot(sb[i]).transform(marco);	
		
			float sup_color[] = {0.5, 0.5, 0.5, 1.0}; //Gris
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sup_color);
		}

		if(inalambrico){
			for(int i=0;i<NVERT-1;i++){
				for(int j=0;j<NVERT-1;j++){			
					glBegin(GL_QUADS);
					glNormal3f(n[NVERT*i+j].x(),n[NVERT*i+j].y(),n[NVERT*i+j].z());
					glVertex3f(sb[NVERT*i+j].x(),sb[NVERT*i+j].y(),sb[NVERT*i+j].z());

					glNormal3f(n[NVERT*(i+1)+j].x(),n[NVERT*(i+1)+j].y(),n[NVERT*(i+1)+j].z());
					glVertex3f(sb[NVERT*(i+1)+j].x(),sb[NVERT*(i+1)+j].y(),sb[NVERT*(i+1)+j].z());

					glNormal3f(n[NVERT*(i+1)+(j+1)].x(),n[NVERT*(i+1)+(j+1)].y(),n[NVERT*(i+1)+(j+1)].z());
					glVertex3f(sb[NVERT*(i+1)+(j+1)].x(),sb[NVERT*(i+1)+(j+1)].y(),sb[NVERT*(i+1)+(j+1)].z());

					glNormal3f(n[NVERT*i+(j+1)].x(),n[NVERT*i+(j+1)].y(),n[NVERT*i+(j+1)].z());
					glVertex3f(sb[NVERT*i+(j+1)].x(),sb[NVERT*i+(j+1)].y(),sb[NVERT*i+(j+1)].z());

					glEnd();
				};	
			};
		}
		else{
			for(int i=0;i<NVERT;i++){
				glBegin(GL_LINE_STRIP);
					for(int j=0;j<NVERT;j++){
						glVertex3f( (GLfloat)((sb[i*NVERT+j]).x()),
									(GLfloat)((sb[i*NVERT+j]).y()),
									(GLfloat)((sb[i*NVERT+j]).z()));
					}
				glEnd();
			}
 			for(int i=0;i<NVERT;i++){
				glBegin(GL_LINE_STRIP);
					for(int j=0;j<NVERT;j++){
						glVertex3f( (GLfloat)((sb[i+j*NVERT]).x()),
									(GLfloat)((sb[i+j*NVERT]).y()),
									(GLfloat)((sb[i+j*NVERT]).z()));
					}
				glEnd();
			}	
		}
	}
}