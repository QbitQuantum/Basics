////////////////////////////////////////////////////////////////////////////
// Function: netset
////////////////////////////////////////////////////////////////////////////
int videoset(char **postvars, int form_method)
{
	FILE *fffd,*fp, *vsfd;
	unsigned long	ulTemp;
	unsigned char	ucbuf[sizeof(video_conf)];
	int iTemp, i, size;
	char pctmp[40];
	char iptmp[20];


	// HTML header, print it here
	printf("Content-type: text/html\r\n\r\n");
	printf("\r\n\r\n");
	printf("<html><head></head>");
	fflush(stdout);
	usleep(1000);

	// If we got post, write it into flash
	if(form_method == POST)
	{
		printf("<body><center><BR><font style=\"font-size:12pt\" face=\"Arial\">");
		// Read and preserve content from flash to buffer
		GetConfValues();

		for (i=0; postvars[i]; i+= 2)
		{
#if DEBUG
			printf("DEBUG: [%s] = [%s]<br>", postvars[i], postvars[i+1]);
#endif

			// Parse for video port
			if(!strcmp(postvars[i], "VIDEOPORT"))
			{
				CONF_VIDEO->ServerPort = (unsigned short)atoi(postvars[i+1]);
			}
			
			// parse for quality method
			if(!strcmp(postvars[i], "QUALITYMETHOD"))
			{
				if(!strcmp(postvars[i+1], "1"))
					CONF_VIDEO->QualityMethod = 1;
				else if(!strcmp(postvars[i+1], "2"))
					CONF_VIDEO->QualityMethod = 2;
			}

			// parse for bitrate
			if(!strcmp(postvars[i], "BITRATE"))
			{
				if(!strcmp(postvars[i+1], "1"))
					CONF_VIDEO->BitRate = 1;
				else if(!strcmp(postvars[i+1], "2"))
					CONF_VIDEO->BitRate = 2;
				else if(!strcmp(postvars[i+1], "3"))
					CONF_VIDEO->BitRate = 3;
				else if(!strcmp(postvars[i+1], "4"))
					CONF_VIDEO->BitRate = 4;
				else if(!strcmp(postvars[i+1], "5"))
					CONF_VIDEO->BitRate = 5;
				else if(!strcmp(postvars[i+1], "6"))
					CONF_VIDEO->BitRate = 6;
				else if(!strcmp(postvars[i+1], "7"))
					CONF_VIDEO->BitRate = 7;
				else if(!strcmp(postvars[i+1], "8"))
					CONF_VIDEO->BitRate = 8;
				else if(!strcmp(postvars[i+1], "9"))
					CONF_VIDEO->BitRate = 9;
				else if(!strcmp(postvars[i+1], "10"))
					CONF_VIDEO->BitRate = 10;
				else if(!strcmp(postvars[i+1], "11"))
					CONF_VIDEO->BitRate = 11;
			}
			
			// parse for quality
			if(!strcmp(postvars[i], "QUALITY"))
			{
				if(!strcmp(postvars[i+1], "1"))
					CONF_VIDEO->Quality = 1;
				else if(!strcmp(postvars[i+1], "2"))
					CONF_VIDEO->Quality = 2;
				else if(!strcmp(postvars[i+1], "3"))
					CONF_VIDEO->Quality = 3;
				else if(!strcmp(postvars[i+1], "4"))
					CONF_VIDEO->Quality = 4;
				else if(!strcmp(postvars[i+1], "5"))
					CONF_VIDEO->Quality = 5;
			}
			
			// parse for resolution
			if(!strcmp(postvars[i], "RESOLUTION"))
			{
				if(!strcmp(postvars[i+1], "1"))
					CONF_VIDEO->Resolution = 1;
				else if(!strcmp(postvars[i+1], "2"))
					CONF_VIDEO->Resolution = 2;
				else if(!strcmp(postvars[i+1], "3"))
					CONF_VIDEO->Resolution = 3;
				else if(!strcmp(postvars[i+1], "4"))
					CONF_VIDEO->Resolution = 4;
				else if(!strcmp(postvars[i+1], "5"))
					CONF_VIDEO->Resolution = 5;
				else if(!strcmp(postvars[i+1], "6"))
					CONF_VIDEO->Resolution = 6;
				else if(!strcmp(postvars[i+1], "7"))
					CONF_VIDEO->Resolution = 7;
				else if(!strcmp(postvars[i+1], "8"))
					CONF_VIDEO->Resolution = 8;
				else if(!strcmp(postvars[i+1], "9"))
					CONF_VIDEO->Resolution = 9;
			}
			
			// parse for frame rate
			if(!strcmp(postvars[i], "FRAMERATE"))
			{
				if(!strcmp(postvars[i+1], "1"))
					CONF_VIDEO->FrameRate = 1;
				else if(!strcmp(postvars[i+1], "2"))
					CONF_VIDEO->FrameRate = 2;
				else if(!strcmp(postvars[i+1], "3"))
					CONF_VIDEO->FrameRate = 3;
				else if(!strcmp(postvars[i+1], "4"))
					CONF_VIDEO->FrameRate = 4;
				else if(!strcmp(postvars[i+1], "5"))
					CONF_VIDEO->FrameRate = 5;
				else if(!strcmp(postvars[i+1], "6"))
					CONF_VIDEO->FrameRate = 6;
			}
			
			// parse for brightness
			if(!strcmp(postvars[i], "BRIGHTNESS"))
			{
				CONF_VIDEO->Brightness = (unsigned short)atoi(postvars[i+1]);
			}
			
			// parse for saturation
			if(!strcmp(postvars[i], "SATURATION"))
			{
				CONF_VIDEO->Saturation = (unsigned short)atoi(postvars[i+1]);
			}
			
			// parse for contrast
			if(!strcmp(postvars[i], "CONTRAST"))
			{
				CONF_VIDEO->Contrast = (unsigned short)atoi(postvars[i+1]);
			}
			
			// parse for hue
			if(!strcmp(postvars[i], "HUE"))
			{
				CONF_VIDEO->Hue = (unsigned short)atoi(postvars[i+1]);
			}
			
		} // end of parse loop
		
#if DEBUG
		// Debug the value in struct
		printf("Write result:<br>\n");
		printf("%d<br>\n", CONF_VIDEO->ServerPort);
		printf("%ld<br>\n", CONF_VIDEO->Resolution);
		printf("%ld<br>\n", CONF_VIDEO->BitRate);
		printf("%d<br>\n", CONF_VIDEO->FrameRate);
		printf("%ld<br>\n", CONF_VIDEO->Quality);
		printf("%ld<br>\n", CONF_VIDEO->Saturation);
		printf("%ld<br>\n", CONF_VIDEO->Contrast);
		printf("%ld<br>\n", CONF_VIDEO->Hue);
		//printf("%s<br>\n", CONF_NET->DeviceName);  // string will cause html arrangement disordered
#endif

		// Copy strcut into buf
		memcpy(ucbuf, CONF_VIDEO, sizeof(video_conf));
		
		// Reset flash buffer
		iTemp = VIDEOOFFSET;
		for(i=iTemp; i<(sizeof(video_conf)+iTemp); i++)
		  pcContentBuf[i] = ucbuf[i-iTemp];
		
#if DEBUG
		for(i=0; i<READBUF; i++)
		{
			printf("%d ", pcContentBuf[i]);
		}
		printf("<br>");
#endif
		
		FlashWriteConfig();
		



		unlink(VIDEOSETCFG);
		
		if( (vsfd=fopen(VIDEOSETCFG, "w")) == NULL )
		{
			perror("videoset cfg file create error: ");
			return 0;
		}
		
		if(CONF_VIDEO->ServerPort == 0)
			CONF_VIDEO->ServerPort = 554;
		fprintf(vsfd, "Port %d\n", CONF_VIDEO->ServerPort);

		switch(CONF_VIDEO->FrameRate)
		{
			case 1: fprintf(vsfd, "%s\n", "VideoFrameRate 5"); break;
			case 2: fprintf(vsfd, "%s\n", "VideoFrameRate 10"); break;
			case 3: fprintf(vsfd, "%s\n", "VideoFrameRate 15"); break;
			case 4: fprintf(vsfd, "%s\n", "VideoFrameRate 20"); break;
			case 5: fprintf(vsfd, "%s\n", "VideoFrameRate 25"); break;
			case 6: fprintf(vsfd, "%s\n", "VideoFrameRate 30"); break;
			default: fprintf(vsfd, "%s\n", "VideoFrameRate 30"); break;
		}
		// video size (resolution)
		switch(CONF_VIDEO->Resolution)
		{
			case 1: fprintf(vsfd, "%s\n", "VideoSize 176x120"); break;
			case 2: fprintf(vsfd, "%s\n", "VideoSize 352x240"); break;
			case 3: fprintf(vsfd, "%s\n", "VideoSize 720x480"); break;
			case 4: fprintf(vsfd, "%s\n", "VideoSize 176x144"); break;
			case 5: fprintf(vsfd, "%s\n", "VideoSize 352x288"); break;
			case 6: fprintf(vsfd, "%s\n", "VideoSize 720x576"); break;
			case 7: fprintf(vsfd, "%s\n", "VideoSize 160x120"); break;
			case 8: fprintf(vsfd, "%s\n", "VideoSize 320x240"); break;
			case 9: fprintf(vsfd, "%s\n", "VideoSize 640x480"); break;
			default: fprintf(vsfd, "%s\n", "VideoSize 352x240"); break;
		}

		if(CONF_VIDEO->QualityMethod==1)
		{		
			// video bitrate
			switch(CONF_VIDEO->BitRate)
			{
				case 1: fprintf(vsfd, "%s\n", "VideoBitRate 64"); break;
				case 2: fprintf(vsfd, "%s\n", "VideoBitRate 128"); break;
				case 3: fprintf(vsfd, "%s\n", "VideoBitRate 256"); break;
				case 4: fprintf(vsfd, "%s\n", "VideoBitRate 512"); break;
				case 5: fprintf(vsfd, "%s\n", "VideoBitRate 768"); break;
				case 6: fprintf(vsfd, "%s\n", "VideoBitRate 1024"); break;
				case 7: fprintf(vsfd, "%s\n", "VideoBitRate 1200"); break;
				case 8: fprintf(vsfd, "%s\n", "VideoBitRate 1536"); break;
				case 9: fprintf(vsfd, "%s\n", "VideoBitRate 2048"); break;
				case 10: fprintf(vsfd, "%s\n", "VideoBitRate 2560"); break;
				case 11: fprintf(vsfd, "%s\n", "VideoBitRate 3072"); break;
				default: fprintf(vsfd, "%s\n", "VideoBitRate 1536"); break;
			}
			fprintf(vsfd, "%s\n", "VideoQMin 1"); 
			fprintf(vsfd, "%s\n", "VideoQMax 31"); 

		}
		else if(CONF_VIDEO->QualityMethod==2)
		{
			fprintf(vsfd, "%s\n", "VideoBitRate 2048");		
			// video bitrate
			switch(CONF_VIDEO->Quality)
			{
				case 1: 
					fprintf(vsfd, "%s\n", "VideoQMin 30"); 
					fprintf(vsfd, "%s\n", "VideoQMax 30"); 
					break;
				case 2: 
					fprintf(vsfd, "%s\n", "VideoQMin 24"); 
					fprintf(vsfd, "%s\n", "VideoQMax 24"); 
					break;
				case 3: 					
					fprintf(vsfd, "%s\n", "VideoQMin 18"); 
					fprintf(vsfd, "%s\n", "VideoQMax 18"); 
					break;
				case 4: 					
					fprintf(vsfd, "%s\n", "VideoQMin 12"); 
					fprintf(vsfd, "%s\n", "VideoQMax 12"); 
					break;
				case 5: 					
					fprintf(vsfd, "%s\n", "VideoQMin 6"); 
					fprintf(vsfd, "%s\n", "VideoQMax 6"); 
					break;
				default: 					
					fprintf(vsfd, "%s\n", "VideoQMin 12"); 
					fprintf(vsfd, "%s\n", "VideoQMax 12"); 
					break;
			}
		}
		
		// video GOP size
		//fprintf(vsfd, "%s\n", "VideoGopSize 15	#30");

		fclose(vsfd);













		// set ff.cfg and bring it up
		unlink(FFCONFIGFILE);
		
		if( (fffd=fopen(FFCONFIGFILE, "w")) == NULL )
		{
			perror("videoset: ");
			return 0;
		}
		
		// set port
		if(CONF_VIDEO->ServerPort == 0)
			CONF_VIDEO->ServerPort = 8090;
		fprintf(fffd, "Port %d\n", CONF_VIDEO->ServerPort);
		
		// set bind addr
		fprintf(fffd, "%s\n", "BindAddress 0.0.0.0");
		
		// set max client
		fprintf(fffd, "%s\n", "MaxClients 10");
		
		// set max bandwidth
		fprintf(fffd, "%s\n", "MaxBandwidth 20480");
		
		// custom log - NO
		fprintf(fffd, "%s\n", "CustomLog -");
		
		// not act as a daemon
		fprintf(fffd, "%s\n\n", "NoDaemon");
		
		// Feed1
		fprintf(fffd, "%s\n", "<Feed feed1.ffm>");
		fprintf(fffd, "%s\n", "File /ffmpeg/feed1.ffm");
		fprintf(fffd, "%s\n", "FileMaxSize 2M");	// file size
		fprintf(fffd, "%s\n", "ACL allow 127.0.0.1");
		fprintf(fffd, "%s\n\n", "</Feed>");
		
		// stream1
		fprintf(fffd, "%s\n", "<Stream test.asf>");
		fprintf(fffd, "%s\n", "Feed feed1.ffm");
		fprintf(fffd, "%s\n", "Format asf");
		fprintf(fffd, "%s\n", "AudioSampleRate 22050");		// audio sample rate
		fprintf(fffd, "%s\n", "AudioChannels 1 ");			// audio channel
		//fprintf(fffd, "%s\n", "NoAudio");
		fprintf(fffd, "%s\n", "AudioCodec adpcm_ms");		// audio codec
		fprintf(fffd, "%s\n", "VideoCodec mpeg4");			// video codec
		
		// video frame rate
		switch(CONF_VIDEO->FrameRate)
		{
			case 1: fprintf(fffd, "%s\n", "VideoFrameRate 5"); break;
			case 2: fprintf(fffd, "%s\n", "VideoFrameRate 10"); break;
			case 3: fprintf(fffd, "%s\n", "VideoFrameRate 15"); break;
			case 4: fprintf(fffd, "%s\n", "VideoFrameRate 20"); break;
			case 5: fprintf(fffd, "%s\n", "VideoFrameRate 25"); break;
			case 6: fprintf(fffd, "%s\n", "VideoFrameRate 30"); break;
			default: fprintf(fffd, "%s\n", "VideoFrameRate 30"); break;
		}

		// video size (resolution)
		switch(CONF_VIDEO->Resolution)
		{
			case 1: fprintf(fffd, "%s\n", "VideoSize 176x120"); break;
			case 2: fprintf(fffd, "%s\n", "VideoSize 352x240"); break;
			case 3: fprintf(fffd, "%s\n", "VideoSize 720x480"); break;
			case 4: fprintf(fffd, "%s\n", "VideoSize 176x144"); break;
			case 5: fprintf(fffd, "%s\n", "VideoSize 352x288"); break;
			case 6: fprintf(fffd, "%s\n", "VideoSize 720x576"); break;
			case 7: fprintf(fffd, "%s\n", "VideoSize 160x120"); break;
			case 8: fprintf(fffd, "%s\n", "VideoSize 320x240"); break;
			case 9: fprintf(fffd, "%s\n", "VideoSize 640x480"); break;
			default: fprintf(fffd, "%s\n", "VideoSize 352x240"); break;
		}

		if(CONF_VIDEO->QualityMethod==1)
		{		
			// video bitrate
			switch(CONF_VIDEO->BitRate)
			{
				case 1: fprintf(fffd, "%s\n", "VideoBitRate 64"); break;
				case 2: fprintf(fffd, "%s\n", "VideoBitRate 128"); break;
				case 3: fprintf(fffd, "%s\n", "VideoBitRate 256"); break;
				case 4: fprintf(fffd, "%s\n", "VideoBitRate 512"); break;
				case 5: fprintf(fffd, "%s\n", "VideoBitRate 768"); break;
				case 6: fprintf(fffd, "%s\n", "VideoBitRate 1024"); break;
				case 7: fprintf(fffd, "%s\n", "VideoBitRate 1200"); break;
				case 8: fprintf(fffd, "%s\n", "VideoBitRate 1536"); break;
				case 9: fprintf(fffd, "%s\n", "VideoBitRate 2048"); break;
				case 10: fprintf(fffd, "%s\n", "VideoBitRate 2560"); break;
				case 11: fprintf(fffd, "%s\n", "VideoBitRate 3072"); break;
				default: fprintf(fffd, "%s\n", "VideoBitRate 1536"); break;
			}
			fprintf(fffd, "%s\n", "VideoQMin 1"); 
			fprintf(fffd, "%s\n", "VideoQMax 31"); 

		}
		else if(CONF_VIDEO->QualityMethod==2)
		{
			fprintf(fffd, "%s\n", "VideoBitRate 2048");		
			// video bitrate
			switch(CONF_VIDEO->Quality)
			{
				case 1: 
					fprintf(fffd, "%s\n", "VideoQMin 30"); 
					fprintf(fffd, "%s\n", "VideoQMax 30"); 
					break;
				case 2: 
					fprintf(fffd, "%s\n", "VideoQMin 24"); 
					fprintf(fffd, "%s\n", "VideoQMax 24"); 
					break;
				case 3: 					
					fprintf(fffd, "%s\n", "VideoQMin 18"); 
					fprintf(fffd, "%s\n", "VideoQMax 18"); 
					break;
				case 4: 					
					fprintf(fffd, "%s\n", "VideoQMin 12"); 
					fprintf(fffd, "%s\n", "VideoQMax 12"); 
					break;
				case 5: 					
					fprintf(fffd, "%s\n", "VideoQMin 6"); 
					fprintf(fffd, "%s\n", "VideoQMax 6"); 
					break;
				default: 					
					fprintf(fffd, "%s\n", "VideoQMin 12"); 
					fprintf(fffd, "%s\n", "VideoQMax 12"); 
					break;
			}
		}
		
		
		// video GOP size
		fprintf(fffd, "%s\n", "VideoGopSize 15	#30");
		
		// audio bitrate
		fprintf(fffd, "%s\n", "AudioBitRate 88	#64");
		//fprintf(fffd, "%s\n", "NoAudio");
		
		// StartSendOnKey
		fprintf(fffd, "%s\n", "StartSendOnKey");

		fprintf(fffd, "%s\n\n", "</Stream>");
		
		// specific stream
		fprintf(fffd, "%s\n", "<Stream stat.html>");
		fprintf(fffd, "%s\n", "Format status");
		fprintf(fffd, "%s\n", "ACL allow localhost");
		fprintf(fffd, "%s\n", "ACL allow 192.168.0.0 192.168.255.255");
		fprintf(fffd, "%s\n\n", "</Stream>");
		
		// redirect
		fprintf(fffd, "%s\n", "<Redirect index.html>");
		fprintf(fffd, "%s\n", "URL http://ffmpeg.sourceforge.net/");
		fprintf(fffd, "%s\n", "</Redirect>");
		
		fclose(fffd);
		
		unlink(CONFIG7113);
		
		if( (fp=fopen(CONFIG7113, "w")) == NULL )
		{
			perror("set7113");
			return 0;
		}
		fprintf(fp, "%s\n", "char *7113_tokens[] = {");
//++ Foster
		CONF_VIDEO->Brightness = (CONF_VIDEO->Brightness ? CONF_VIDEO->Brightness : 0x95);
		CONF_VIDEO->Contrast = (CONF_VIDEO->Contrast ? CONF_VIDEO->Contrast : 0x48);
		CONF_VIDEO->Saturation = (CONF_VIDEO->Saturation ? CONF_VIDEO->Saturation : 0x48);
		CONF_VIDEO->Hue = (CONF_VIDEO->Hue ? CONF_VIDEO->Hue : 0x00);
		fprintf(fp, "\"0x48 0x0A 0x%x\",\n", CONF_VIDEO->Brightness);
		fprintf(fp, "\"0x48 0x0B 0x%x\",\n", CONF_VIDEO->Contrast);
		fprintf(fp, "\"0x48 0x0C 0x%x\",\n", CONF_VIDEO->Saturation);
		fprintf(fp, "\"0x48 0x0D 0x%x\",\n", CONF_VIDEO->Hue);
//-- Foster
		fprintf(fp, "%s\n", "0");
		fprintf(fp, "%s\n", "};");		

		fclose(fp);

		//if( system("alarm > /dev/null &") < 0 )
		if( system("nohup alarm > /dev/null &") < 0 )
		{
			perror("videoset:");
		}
		sleep(1);
		
		unlink(MOTIONCONFIG);
	
		if( (fp=fopen(ALARMPID, "r")) == NULL )
		{
			if( (fp=fopen(ALARMPID, "r")) == NULL )
			{	
				//system("alarm > /dev/null &");
				system("nohup alarm > /dev/null &");
				if( (fp=fopen(ALARMPID, "r")) == NULL )
				{
					printf("read pid error\n");
				}
			}
		}
	
		fgets(pctmp,20,fp);
		close(fp);
			
		if( (fffd=fopen(MOTIONCONFIG, "w")) == NULL )
		{
			perror("videoset: ");
			return 0;
		}
			
		fprintf(fffd, "pid %s\n",pctmp);
			
		// detect interval
		fprintf(fffd, "md_interval %d\n",CONF_MOTION->Interval);
			
		//window1 coordinate
			
		if(CONF_MOTION->StartX1!=0xffff && CONF_MOTION->StartY1!=0xffff && CONF_MOTION->StopX1!=0xffff && CONF_MOTION->StopY1!=0xffff)
		{
			if(CONF_MOTION->StartX1!=0 && CONF_MOTION->StartY1!=0 && CONF_MOTION->StopX1!=0 && CONF_MOTION->StopY1!=0)
			{
				fprintf(fffd, "x0_LU %d\n",(CONF_MOTION->StartX1-1)/16);
				fprintf(fffd, "y0_LU %d\n",(CONF_MOTION->StartY1-1)/16);
				if(CONF_MOTION->StopX1%16)
					fprintf(fffd, "x0_RD %d\n",((CONF_MOTION->StopX1-1)/16)+1);
				else
					fprintf(fffd, "x0_RD %d\n",(CONF_MOTION->StopX1-1)/16);
						
				if(CONF_MOTION->StopY1%16)	
					fprintf(fffd, "y0_RD %d\n",((CONF_MOTION->StopY1-1)/16)+1);
				else
					fprintf(fffd, "y0_RD %d\n",((CONF_MOTION->StopY1-1)/16));
			}
		}
			
		//window2 coordinate
		if(CONF_MOTION->StartX2!=0xffff && CONF_MOTION->StartY2!=0xffff && CONF_MOTION->StopX2!=0xffff && CONF_MOTION->StopY2!=0xffff)
		{
			if(CONF_MOTION->StartX2!=0 && CONF_MOTION->StartY2!=0 && CONF_MOTION->StopX2!=0 && CONF_MOTION->StopY2!=0)
			{
				fprintf(fffd, "x1_LU %d\n",(CONF_MOTION->StartX2-1)/16);
				fprintf(fffd, "y1_LU %d\n",(CONF_MOTION->StartY2-1)/16);
				if(CONF_MOTION->StopX2%16)
					fprintf(fffd, "x1_RD %d\n",((CONF_MOTION->StopX2-1)/16)+1);
				else
					fprintf(fffd, "x1_RD %d\n",((CONF_MOTION->StopX2-1)/16));
						
				if(CONF_MOTION->StopY2%16)
					fprintf(fffd, "y1_RD %d\n",((CONF_MOTION->StopY2-1)/16)+1);
				else
					fprintf(fffd, "y1_RD %d\n",((CONF_MOTION->StopY2-1)/16));
			}
		}
			
		//window3 coordinate
		if(CONF_MOTION->StartX3!=0xffff && CONF_MOTION->StartY3!=0xffff && CONF_MOTION->StopX3!=0xffff && CONF_MOTION->StopY3!=0xffff)
		{
			if(CONF_MOTION->StartX3!=0 && CONF_MOTION->StartY3!=0 && CONF_MOTION->StopX3!=0 && CONF_MOTION->StopY3!=0)
			{
				fprintf(fffd, "x2_LU %d\n",(CONF_MOTION->StartX3-1)/16);
				fprintf(fffd, "y2_LU %d\n",(CONF_MOTION->StartY3-1)/16);
					
				if(CONF_MOTION->StopX3%16)
					fprintf(fffd, "x2_RD %d\n",((CONF_MOTION->StopX3-1)/16)+1);
				else
					fprintf(fffd, "x2_RD %d\n",((CONF_MOTION->StopX3-1)/16));
						
				if(CONF_MOTION->StopY3%16)
					fprintf(fffd, "y2_RD %d\n",((CONF_MOTION->StopY3-1)/16)+1);
				else
					fprintf(fffd, "y2_RD %d\n",((CONF_MOTION->StopY3-1)/16));
			}
		}
			
		//window1 detect parameters
		if(CONF_MOTION->StartX1!=0xffff && CONF_MOTION->StartY1!=0xffff && CONF_MOTION->StopX1!=0xffff && CONF_MOTION->StopY1!=0xffff)
		{
			if(CONF_MOTION->StartX1!=0 && CONF_MOTION->StartY1!=0 && CONF_MOTION->StopX1!=0 && CONF_MOTION->StopY1!=0)
			{
				//motion detection method 1 sensitivity
				fprintf(fffd, "mv_th0 %d\n",CONF_MOTION->Sensitivity1);
				//motion detection method 2 sensitivity, 512-> disabled
				fprintf(fffd, "sad_th0 512\n");		
				//motion detection method 3 sensitivity, 512-> disabled
				//fprintf(fffd, "dev_th0 %d\n",CONF_MOTION->Sensitivity1);
				fprintf(fffd, "dev_th0 512\n");
				// motion detection threshold
				fprintf(fffd, "alarm_idx0 %d\n",CONF_MOTION->Threshold1);
			}
		}
			
		//window2 detect parameters
		if(CONF_MOTION->StartX2!=0xffff && CONF_MOTION->StartY2!=0xffff && CONF_MOTION->StopX2!=0xffff && CONF_MOTION->StopY2!=0xffff)
		{
			if(CONF_MOTION->StartX2!=0 && CONF_MOTION->StartY2!=0 && CONF_MOTION->StopX2!=0 && CONF_MOTION->StopY2!=0)
			{
				//motion detection method 1 sensitivity
				fprintf(fffd, "mv_th1 %d\n",CONF_MOTION->Sensitivity2);
				//motion detection method 2 sensitivity, 512-> disabled
				fprintf(fffd, "sad_th1 512\n");		
				//motion detection method 3 sensitivity, 512-> disabled
				fprintf(fffd, "dev_th1 512\n");
				// motion detection threshold
				fprintf(fffd, "alarm_idx1 %d\n",CONF_MOTION->Threshold2);
			}
		}
			
		//window3 detect parameters
		if(CONF_MOTION->StartX3!=0xffff && CONF_MOTION->StartY3!=0xffff && CONF_MOTION->StopX3!=0xffff && CONF_MOTION->StopY3!=0xffff)
		{
			if(CONF_MOTION->StartX3!=0 && CONF_MOTION->StartY3!=0 && CONF_MOTION->StopX3!=0 && CONF_MOTION->StopY3!=0)
			{
				//motion detection method 1 sensitivity
				fprintf(fffd, "mv_th2 %d\n",CONF_MOTION->Sensitivity3);
				//motion detection method 2 sensitivity, 512-> disabled
				fprintf(fffd, "sad_th2 512\n");		
				//motion detection method 3 sensitivity, 512-> disabled
				fprintf(fffd, "dev_th2 512\n");
				// motion detection threshold
				fprintf(fffd, "alarm_idx2 %d\n",CONF_MOTION->Threshold3);
			}
		}
				
		// snapshot filename
		fprintf(fffd, "filename /%s\n","temp");
			
		fprintf(fffd, "rotate %d\n",CONF_MOTION->Rotate);

		fflush(fffd);
		close(fffd);

		// start ffserver and ffmpeg
		//if( system("/ffmpeg/ffserver -f /ffmpeg/ff.cfg > /dev/null&") < 0 )
		if( system("nohup /ffmpeg/ffserver -f /ffmpeg/ff.cfg > /dev/null&") < 0 )
		{
			perror("videoset:");
		}

		sleep(2);
		if(CONF_MOTION->Detection==1)
			//sprintf(pctmp,"/ffmpeg/ffmpeg -ndisplay -motion %s http://localhost:%d/feed1.ffm > /dev/null&",MOTIONCONFIG, CONF_VIDEO->ServerPort);
			sprintf(pctmp,"nohup /ffmpeg/ffmpeg -ndisplay -motion %s http://localhost:%d/feed1.ffm > /dev/null&",MOTIONCONFIG, CONF_VIDEO->ServerPort);
		else
			//sprintf(pctmp,"/ffmpeg/ffmpeg -ndisplay http://localhost:%d/feed1.ffm > /dev/null&",CONF_VIDEO->ServerPort);
			sprintf(pctmp,"nohup /ffmpeg/ffmpeg -ndisplay http://localhost:%d/feed1.ffm > /dev/null&",CONF_VIDEO->ServerPort);

		//printf(pctmp);
		if( system(pctmp) < 0 )
		{
			perror("videoset:");
		}

		printf("Configuration parameters have been saved successfully<br><br>");
		// printf("<font color=red>To make the change active, please reboot the device.<br></font>");
		printf("</center></body></html>");
		fflush(stdout);

		free(CONF_VIDEO);
		free(CONF_NET);
		free(CONF_MOTION);

		// exit here when write
		return 0;
		
	} // end of "if we got post"
	

	////////////////////////////////////////////
	// Start CGI, Get configuration value here
	////////////////////////////////////////////	
	
	
	GetConfValues();
	get_ip(iptmp);
	
	printf("<html><head></head>\n");
	printf("<center><BR>\n");
	printf("<FORM name=videoset ACTION=/cgi-bin/videoset.cgi METHOD=POST>\n");
	printf("<table border=0 width=80%>\n");
	printf("<tr><td class=header><strong>Video Settings</strong>\n");
	printf("<tr><td><hr>\n");
	printf("<table border=0>\n");
	printf("<tr><td width=50%> \n");
	
#if 1
	if(CONF_VIDEO->Resolution==1)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"176\" height=\"120\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}
	
	if(CONF_VIDEO->Resolution==2)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"352\" height=\"240\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}
	
	if(CONF_VIDEO->Resolution==3)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"720\" height=\"480\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==4)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"176\" height=\"144\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==5)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"352\" height=\"288\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==6)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"720\" height=\"576\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==7)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"160\" height=\"120\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==8)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"320\" height=\"240\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}

	if(CONF_VIDEO->Resolution==9)
	{
		printf("<object classid=\"clsid:E23FE9C6-778E-49D4-B537-38FCDE4887D8\" id=\"VLCPlugin1\" width=\"640\" height=\"480\">\n");
		printf("<param name=\"Src\" value=\"rtsp://%s:%d\">\n", iptmp, CONF_VIDEO->ServerPort);
	}
#endif
	
	printf("</object>\n");

	printf("<td width=50%>\n");
	printf("<table border=0>\n");
	if(CONF_VIDEO->ServerPort>0 && CONF_VIDEO->ServerPort!=255)
		printf("<tr><td>Video Port<td><input type=text name=VIDEOPORT value=%d>\n",CONF_VIDEO->ServerPort);
	else
		printf("<tr><td>Video Port<td><input type=text name=VIDEOPORT>\n");
		
	printf("<tr><td>Quality<td>\n");
	if(CONF_VIDEO->QualityMethod==1)
		printf("<tr><td><input type=radio name=QUALITYMETHOD value=1 checked>Fixed BitRate\n");
	else
		printf("<tr><td><input type=radio name=QUALITYMETHOD value=1>Fixed BitRate\n");
	printf("<td><select  name=BITRATE>\n");

	if(CONF_VIDEO->BitRate==1)
		printf("<option value=1 selected>64Kbps\n");
	else
		printf("<option value=1>64Kbps\n");
		
	if(CONF_VIDEO->BitRate==2)
		printf("<option value=2 selected>128Kbps\n");
	else
		printf("<option value=2>128Kbps\n");
		
	if(CONF_VIDEO->BitRate==3)
		printf("<option value=3 selected>256Kbps\n");
	else
		printf("<option value=3>256Kbps\n");
		
	if(CONF_VIDEO->BitRate==4)
		printf("<option value=4 selected>512Kbps\n");
	else
		printf("<option value=4>512Kbps\n");
		
	if(CONF_VIDEO->BitRate==5)
		printf("<option value=5 selected>768Kbps\n");
	else
		printf("<option value=5>768Kbps\n");
		
	if(CONF_VIDEO->BitRate==6)
		printf("<option value=6 selected>1Mbps\n");
	else
		printf("<option value=6>1Mbps\n");
		
	if(CONF_VIDEO->BitRate==7)
		printf("<option value=7 selected>1.2Mbps\n");
	else
		printf("<option value=7>1.2Mbps\n");
		
	if(CONF_VIDEO->BitRate==8)
		printf("<option value=8 selected>1.5Mbps\n");
	else
		printf("<option value=8>1.5Mbps\n");
		
	if(CONF_VIDEO->BitRate==9)
		printf("<option value=9 selected>2Mbps\n");
	else
		printf("<option value=9>2Mbps\n");
	
	if(CONF_VIDEO->BitRate==10)
		printf("<option value=10 selected>2.5Mbps\n");
	else
		printf("<option value=10>2.5Mbps\n");

	if(CONF_VIDEO->BitRate==11)
		printf("<option value=11 selected>3Mbps\n");
	else
		printf("<option value=11>3Mbps\n");
	
	if(CONF_VIDEO->QualityMethod==2)
		printf("<tr><td><input type=radio name=QUALITYMETHOD checked value=2>Fixed Quality\n");
	else
		printf("<tr><td><input type=radio name=QUALITYMETHOD value=2>Fixed Quality\n");

	printf("<td><select  name=QUALITY>\n");
	
	if(CONF_VIDEO->Quality==1)
		printf("<option value=1 selected>Medium\n");
	else
		printf("<option value=1>Medium\n");
	
	if(CONF_VIDEO->Quality==2)
		printf("<option value=2 selected>Standard\n");
	else
		printf("<option value=2>Standard\n");
		
	if(CONF_VIDEO->Quality==3)
		printf("<option value=3 selected>Good\n");
	else
		printf("<option value=3>Good\n");
		
	if(CONF_VIDEO->Quality==4)
		printf("<option value=4 selected>Detailed\n");
	else
		printf("<option value=4>Detailed\n");
		
	if(CONF_VIDEO->Quality==5)
		printf("<option value=5 selected>Excellent\n");
	else
		printf("<option value=5>Excellent\n");
		
	printf("<tr><td>Resolution<td><select  name=RESOLUTION>\n");
	
	if(CONF_VIDEO->Resolution==1)
		printf("<option  value=1 selected>NTSC(176x120)\n");
	else
		printf("<option  value=1>NTSC(176x120)\n");
		
	if(CONF_VIDEO->Resolution==2)
		printf("<option  value=2 selected>NTSC(352x240)\n");
	else
		printf("<option  value=2>NTSC(352x240)\n");
		
	if(CONF_VIDEO->Resolution==3)
		printf("<option  value=3 selected>NTSC(720x480)\n");
	else
		printf("<option  value=3>NTSC(720x480)\n");
//++ Foster
	if(CONF_VIDEO->Resolution==4)
		printf("<option  value=4 selected>PAL(176x144)\n");
	else
		printf("<option  value=4>PAL(176x144)\n");
	
	if(CONF_VIDEO->Resolution==5)
		printf("<option  value=5 selected>PAL(352x288)\n");
	else
		printf("<option  value=5>PAL(352x288)\n");
	
	if(CONF_VIDEO->Resolution==6)
		printf("<option  value=6 selected>PAL(720x576)\n");
	else
		printf("<option  value=6>PAL(720x576)\n");
	
	if(CONF_VIDEO->Resolution==7)
		printf("<option  value=7 selected>VGA(160x120)\n");
	else
		printf("<option  value=7>VGA(160x120)\n");
	
	if(CONF_VIDEO->Resolution==8)
		printf("<option  value=8 selected>VGA(320x240)\n");
	else
		printf("<option  value=8>VGA(320x240)\n");
	
	if(CONF_VIDEO->Resolution==9)
		printf("<option  value=9 selected>VGA(640x480)\n");
	else
		printf("<option  value=9>VGA(640x480)\n");
//-- Foster
		
	printf("<tr><td>Framerate<td><select  name=FRAMERATE>\n");
	
	if(CONF_VIDEO->FrameRate==1)
		printf("<option  value=1 selected>5fps\n");
	else
		printf("<option  value=1>5fps\n");
		
	if(CONF_VIDEO->FrameRate==2)
		printf("<option  value=2 selected>10fps\n");
	else
		printf("<option  value=2>10fps\n");
		
	if(CONF_VIDEO->FrameRate==3)
		printf("<option  value=3 selected>15fps\n");
	else
		printf("<option  value=3>15fps\n");
		
	if(CONF_VIDEO->FrameRate==4)
		printf("<option  value=4 selected>20fps\n");
	else
		printf("<option  value=4>20fps\n");
		
	if(CONF_VIDEO->FrameRate==5)
		printf("<option  value=5 selected>25fps\n");
	else
		printf("<option  value=5>25fps\n");
		
	if(CONF_VIDEO->FrameRate==6)
		printf("<option  value=6 selected>30fps\n");
	else
		printf("<option  value=6>30fps\n");
//printf("<!--\n");	
	printf("<tr><td>Brightness<td>\n");
	printf("<object classid=\"clsid:F08DF954-8592-11D1-B16A-00C0F0283628\" id=\"Slider1\" width=\"150\" height=\"25\">\n");
	printf("<param name=\"Min\" value=0>\n");
	printf("<param name=\"Max\" value=255>\n");
	printf("<param name=\"Value\" value=%d>\n",CONF_VIDEO->Brightness);
	printf("</object>\n");
	printf("<script>\n");
	printf("function videoset.Slider1::Change()\n");
	printf("{\n");
  	printf("document.all.BRIGHTNESS.value = document.all.Slider1.Value;\n");
	printf("};\n");
	printf("</script>\n");
	printf("<input type=hidden name=BRIGHTNESS value=%d>\n",CONF_VIDEO->Brightness);
	
	printf("<tr><td>Saturation<td>\n");
	printf("<object classid=\"clsid:F08DF954-8592-11D1-B16A-00C0F0283628\" id=\"Slider2\" width=\"150\" height=\"25\">\n");
	printf("<param name=\"Min\" value=0>\n");
	printf("<param name=\"Max\" value=255>\n");
	printf("<param name=\"Value\" value=%d>\n",CONF_VIDEO->Saturation);
	printf("</object>\n");
	printf("<script>\n");
	printf("function videoset.Slider2::Change()\n");
	printf("{\n");
  	printf("document.all.SATURATION.value = document.all.Slider2.Value;\n");
	printf("};\n");
	printf("</script>\n");
	printf("<input type=hidden name=SATURATION value=%d>\n",CONF_VIDEO->Saturation);
	
	printf("<tr><td>Contrast<td>\n");
	printf("<object classid=\"clsid:F08DF954-8592-11D1-B16A-00C0F0283628\" id=\"Slider3\" width=\"150\" height=\"25\">\n");
	printf("<param name=\"Min\" value=0>\n");
	printf("<param name=\"Max\" value=255>\n");
	printf("<param name=\"Value\" value=%d>\n",CONF_VIDEO->Contrast);
	printf("</object>\n");
	printf("<script>\n");
	printf("function videoset.Slider3::Change()\n");
	printf("{\n");
  	printf("document.all.CONTRAST.value = document.all.Slider3.Value;\n");
	printf("};\n");
	printf("</script>\n");
	printf("<input type=hidden name=CONTRAST value=%d>\n",CONF_VIDEO->Contrast);
	
	printf("<tr><td>Hue<td>\n");
	printf("<object classid=\"clsid:F08DF954-8592-11D1-B16A-00C0F0283628\" id=\"Slider4\" width=\"150\" height=\"25\">\n");
	printf("<param name=\"Min\" value=0>\n");
	printf("<param name=\"Max\" value=255>\n");
	printf("<param name=\"Value\" value=%d>\n",CONF_VIDEO->Hue);
	printf("</object>\n");
	printf("<script>\n");
	printf("function videoset.Slider4::Change()\n");
	printf("{\n");
  	printf("document.all.HUE.value = document.all.Slider4.Value;\n");
	printf("};\n");
	printf("</script>\n");
	printf("<input type=hidden name=HUE value=%d>\n",CONF_VIDEO->Hue);
	
//printf("-->\n");
	printf("</table></table>\n");
	printf("<tr><td><hr>\n");
	printf("<tr><td><input type=submit class=button value=Save></td></tr>\n");
	printf("</form></font></center></html>\n");
	
	
	free(CONF_VIDEO);
	free(CONF_NET);
	free(CONF_MOTION);

	return 0;
}