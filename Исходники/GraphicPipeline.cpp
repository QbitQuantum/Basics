int GraphicPipeline::enableLight(Light * currentLight, int index) {
	int isSet = false;					
	string lightCount = "GL_LIGHT";
	lightCount += intToChar(index);

	 glEnable(GL_LIGHTING);

	
	float * lightPosition = new float[4] ;
	lightPosition[0] = currentLight->getTranslation()->x;
	lightPosition[1] = currentLight->getTranslation()->y;
	lightPosition[2] = currentLight->getTranslation()->z;
	lightPosition[3] = currentLight->getPos_direct();

   // farbiges licht hinzufuegen
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition );

   if(currentLight->getDiffuse() != NULL) 
	   //glLightfv(index, GL_DIFFUSE, currentLight->getDiffuse());
     glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLight->getDiffuse());
	
   if(currentLight->getAmbient() != NULL) 
		//glLightfv(index, GL_AMBIENT, currentLight->getAmbient());
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLight->getAmbient());
   
   if(currentLight->getSpecular() != NULL) 
		//glLightfv(index, GL_SPECULAR, currentLight->getSpecular());
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLight->getSpecular());

   //for (int i = 0; i < index; i++) {
		//glEnable(index);
   glEnable(GL_LIGHT0);
   //}
	return isSet;
}