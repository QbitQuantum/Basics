GLvoid LoadGLTexturesHigh(GLvoid) {
	
//-----------------------------------------------------------------------------------------------------------
	// Stores the texture
	Image *image[texcount];
	Image *aimage[atexcount];

	// Allocate space for texture
	
// ********************
	image[0] = (Image *) malloc(sizeof(Image));
	if (image[0] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/land1.bmp", image[0])) 
	{
		exit(1);
	}
// // ********************
	image[1] = (Image *) malloc(sizeof(Image));
	if (image[1] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/house1.bmp", image[1])) 
	{
		exit(1);
	}
// // ********************
	image[2] = (Image *) malloc(sizeof(Image));
	if (image[2] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/house2.bmp", image[2])) 
	{
		exit(1);
	}
// // ********************
	image[3] = (Image *) malloc(sizeof(Image));
	if (image[3] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/anub.bmp", image[3])) 
	{
		exit(1);
	}
// // ********************
	image[4] = (Image *) malloc(sizeof(Image));
	if (image[4] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/fountain.bmp", image[4])) 
	{
		exit(1);
	}
// // ********************
	image[5] = (Image *) malloc(sizeof(Image));
	if (image[5] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/signpost.bmp", image[5])) 
	{
		exit(1);
	}
// // ********************
	image[6] = (Image *) malloc(sizeof(Image));
	if (image[6] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/temple.bmp", image[6])) 
	{
		exit(1);
	}
// // *******************
	image[7] = (Image *) malloc(sizeof(Image));
	if (image[7] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/tree1.bmp", image[7])) 
	{
		exit(1);
	}
// // ********************
	image[8] = (Image *) malloc(sizeof(Image));
	if (image[8] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/tree2.bmp", image[8])) 
	{
		exit(1);
	}
// // ********************
	image[9] = (Image *) malloc(sizeof(Image));
	if (image[9] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/padestal.bmp", image[9])) 
	{
		exit(1);
	}
// // ********************
	image[10] = (Image *) malloc(sizeof(Image));
	if (image[10] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/bezer.bmp", image[10])) 
	{
		exit(1);
	}
// // ********************
	image[11] = (Image *) malloc(sizeof(Image));
	if (image[11] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/water.bmp", image[11])) 
	{
		exit(1);
	}
// // ********************

	image[12] = (Image *) malloc(sizeof(Image));
	if (image[12] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/sky.bmp", image[12])) 
	{
		exit(1);
	}
// // ********************
	image[13] = (Image *) malloc(sizeof(Image));
	if (image[13] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/ship.bmp", image[13])) 
	{
		exit(1);
	}
// // ********************
	image[14] = (Image *) malloc(sizeof(Image));
	if (image[14] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/well.bmp", image[14])) 
	{
		exit(1);
	}
// // ********************
	image[15] = (Image *) malloc(sizeof(Image));
	if (image[15] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/dung1.bmp", image[15])) 
	{
		exit(1);
	}
// // ********************
	image[16] = (Image *) malloc(sizeof(Image));
	if (image[16] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/tavern.bmp", image[16])) 
	{
		exit(1);
	}
// // ********************
	image[17] = (Image *) malloc(sizeof(Image));
	if (image[17] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/arrow.bmp", image[17])) 
	{
		exit(1);
	}
// // ********************
	image[18] = (Image *) malloc(sizeof(Image));
	if (image[18] == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}

	if (!ImageLoad("./Textures/High/Objects/spider.bmp", image[18])) 
	{
		exit(1);
	}
// // ********************
//----------------------------------------------------------------------------------------------------------------	

	// create Texture
    glGenTextures(texcount, &texture[0]);
    glGenTextures(atexcount, &atexture[0]);	
//------------------------------------------------------------------------------------------------------------------------
    // texturos is image'u
    	int j = 0;
	for(j=0; j< texcount; j++)
	{
    	 	glBindTexture(GL_TEXTURE_2D, texture[j]);   // 2d texture (x and y size)
   	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
   	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
   	 	glTexImage2D(GL_TEXTURE_2D, 0, 3, image[j]->sizeX, image[j]->sizeY, 0, GL_BGR, GL_UNSIGNED_BYTE, image[j]->data);
	}//eofor

	for(j=0; j< atexcount; j++)
	{
    	 	glBindTexture(GL_TEXTURE_2D, atexture[j]);   // 2d texture (x and y size)
   	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
   	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture
   	 	glTexImage2D(GL_TEXTURE_2D, 0, 3, aimage[j]->sizeX, aimage[j]->sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, aimage[j]->data);
	}//eofor
	LoadTGA(&insideT[0],"./Textures/High/Buildings/temple_i.tga");
	LoadTGA(&insideT[1],"./Textures/High/Buildings/house_i.tga");
	LoadTGA(&insideT[2],"./Textures/High/Buildings/ship_i.tga");
	LoadTGA(&insideT[3],"./Textures/High/Buildings/tavern_i.tga");
	if(!LoadTGA(&insideT[DungEnter],"./Textures/High/Buildings/dungI.tga"))printf("Dungeon bitmap fail\n");

//------------------------------------------------------------------------------------------------------------------------

}