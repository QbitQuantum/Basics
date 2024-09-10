void loadppmimage(char *imagename,struct ppmimg* simg){
	FILE *fp;
	char buff[255];
	int imgwidth,imgheight;
	int imagedepth;
	int datasize;
	int itemp[3];
	unsigned char ctemp[3];
	//struct ppmimg * tmpimg = (struct ppmimg*)malloc(sizeof(struct ppmimg));
	//(*simg) = new struct ppmimg;
	
	if((fp=fopen(imagename,"rt"))==NULL){
		exit(1);
	}
	fgets(buff,255,fp);
	while(buff[0]=='#'){
		fgets(buff,255,fp);
	}
	if(buff[0]=='P'){
		sprintf((simg)->magicnumber,"%s",buff);
		simg->magicnumber[2] = '\0';//fgetsは
	}
	fgets(buff,255,fp);
	while(buff[0]=='#'){
		fgets(buff,255,fp);
	}
	sscanf(buff,"%d %d",&imgwidth,&imgheight);
	fgets(buff,255,fp);
	while(buff[0]=='#'){
		fgets(buff,255,fp);
	}
	sscanf(buff,"%d",&imagedepth);
	//fgets(buff,255,fp);
	//while(buff[0]=='#'){
	//	fgets(buff,255,fp);
	//}
	
	simg->iwidth=imgwidth;
	simg->iheight=imgheight;
	simg->depth=imagedepth;

	printf("%d\n",strcmp(simg->magicnumber,"P2"));
	if(strcmp(simg->magicnumber,"P3")==0){
		simg->cmode = 3;
	}else if(strcmp(simg->magicnumber,"P2")==0){
		simg->cmode = 1;
	}
	datasize = (simg->iwidth)*(simg->iheight)*(simg->cmode);
	simg->dat=(unsigned char *)malloc(sizeof(unsigned char)*datasize);
	//free((*simg)->dat);
	if(simg->cmode==3){
		for(int i=0;i<datasize;i+=simg->cmode){
		//	fscanf(fp,"%d %d %d",&((*simg)->dat[i]),&((*simg)->dat[i+1]),&((*simg)->dat[i+2]));	
			//fscanf(fp,"%d",(*simg)->dat + i);
			//fscanf(fp,"%d",(*simg)->dat + i+1);
			//fscanf(fp,"%d",(*simg)->dat + i+2);
			fscanf(fp,"%d %d %d",&(itemp[0]),&(itemp[1]),&(itemp[2]));
			for(int k=0;k<3;k++){
				simg->dat[i+k] = (unsigned char)itemp[k];
			}
			
		}
	}else{
		for(int i=0;i<datasize;i+=simg->cmode){
			//fscanf(fp,"%d",(*simg)->dat + i);	
			fscanf(fp,"%d",&(itemp[0]));
			simg->dat[i] = (unsigned char)itemp[0];
		}
	}
}