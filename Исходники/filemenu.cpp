void filemenu(int mode)
{
	getstats(mode);
	if (button(100,100,170,120,"OPTIMIZE",9,13,base2,false,mode)==DDgui_LeftClick && mode!=DD_AfterCheck) { optimizeproject(); waitleftbutton=true; }
	if (button(100,121,170,141,"TextureO",9,13,base2,false,mode)==DDgui_LeftClick && mode!=DD_AfterCheck) { savetextureusefile(); waitleftbutton=true; }
	if (mode==DD_Draw)
	{
		glColor4f(buttontextlit);
		rectangle(661,120,775,264);
	}	  
	if (mode==DD_Check)
		if (leftclickinwindow(661,121,774,263) && mouseinwindow(661,121,774,260)) fscnselected=min(fscnbarpos+(my-121) / 10,filenum(prjlist)-1);
	if ((mode ==DD_Check) && mouseinwindow(661,121,774,263)) fscnbarpos-=wheel*4;
	scroller(775,120,790,264,15,15,filenum(prjlist),14,fscnbarpos,mode);
	if (mode==DD_Draw)
	{
		pf = prjlist;
		for (x=1;x<=fscnbarpos;x++) pf=pf->next;
		for (x=0;x<=13;x++)
		{
			if (pf!=NULL)
			{
				if (fscnbarpos+x==fscnselected) glColor4f(col4); else glColor4f(buttontextlit);
				glRasterPos2i(665,130+x*10);
				strcpy(st,pf->filedata.cFileName);
				glPrint(st,base2,18);
				pf=pf->next;
			}
		}

		glColor4f(buttontextlit);
		sprintf(s,"%d PROJECTS.",filenum(prjlist));
		glRasterPos2i(683,277);
		glPrint(s,base2);

	}
	glColor4f(1,1,1,1);
	if ((button(686,283,771,299,texbutton1,0,96.0/256.0,85.0/256.0,112.0/256.0,false,mode) == DDgui_LeftClick) && (mode!=DD_AfterCheck))
	{
		pf = prjlist;
		for (x=1;x<=fscnselected;x++) pf=pf->next;
		//sprintf(s,"%s%s",scenedir,pf->filedata.cFileName);
		memset(lastfilename,0,256);
		memcpy(lastfilename,pf->filedata.cFileName,strlen(pf->filedata.cFileName)-4);
		sprintf(s,"%s%s",projectdir,pf->filedata.cFileName);
		//loadaDDictscene(*actualscene,NULL,s,true,true,true,true,true);				
		LoadProject(s);
		modellviews[3].cam=actualscene->editview;
		modellviews[3].cam2=actualscene->editview;
		tTexture *tex=texturelist;
		while ((tex!=NULL) && (tex->number!=selectedtexture)) tex=tex->next;
		memcpy(generatedtexture.commands,tex->commands,sizeof(generatedtexture.commands));
		memcpy(generatedtexture.texts,tex->texts,sizeof(generatedtexture.texts));
		generatedtexture.commandnum=tex->commandnum;
		//memcpy(generatedtexture.layers,tex->layers,sizeof(generatedtexture.layers));
		for (y=0;y<=3;y++)
		{
			glBindTexture(GL_TEXTURE_2D, texlayers[y]);
			glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGBA,GL_UNSIGNED_BYTE,generatedtexture.layers[y]);
		}				
		
		if (materiallist!=NULL)
		{
			matselected=0;
			material *mat=materiallist;
			for (x=1;x<=matselected;x++) mat=mat->next;
			mattexture=mat->handle;
		}				

		waitleftbutton=true;
	}

	if (button(685,300,770,316,texbutton1,0,144.0/256.0,85.0/256.0,160.0/256.0,false,mode) == DDgui_LeftClick) 
	{
		char *ss=readline("Enter Filename (.scn not needed)",210,0,base2,lastfilename);
		if (ss!="")
		{
			//sprintf(s,"%s%s.scn",scenedir,ss);
			//saveaDDictscene(*actualscene,NULL,s,scntexturesave, scncamerasave, scnselectionsave, scnlightsave, scnobjectsave);
			memset(lastfilename,0,256);
			memcpy(lastfilename,ss,strlen(ss));
			sprintf(s,"%s%s.64k",projectdir,ss);
			SaveProject(s);
		}
	}
	if (button(685,317,770,333,texbutton1,0,160.0/256.0,85.0/256.0,176.0/256.0,false,mode) == DDgui_LeftClick) 
	{
		char *ss=readline("Enter Filename (.scn not needed)",210,0,base2,"");
		if (ss!="")
		{
			sprintf(s,"%s%s.m64",minimaldir,ss);
			//SaveMinimalScene(*actualscene,NULL,s);
			saveminimalproject(s,2);
		}
	}
	/*RadioButton(681,341,scntexturesave,"TEXTURES",mode);
	RadioButton(681,355,scncamerasave,"CAMERAS",mode);
	RadioButton(681,369,scnselectionsave,"SELECTIONS",mode);
	RadioButton(681,383,scnlightsave,"LIGHTS",mode);
	RadioButton(681,397,scnobjectsave,"OBJECTS",mode);*/
}