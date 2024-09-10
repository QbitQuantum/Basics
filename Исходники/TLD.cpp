void TLD::processFrame(const cv::Mat& img1,const cv::Mat& img2,vector<Point2f>& points1,vector<Point2f>& points2,BoundingBox& bbnext,bool& lastboxfound, bool tl, FILE* bb_file){
	vector<BoundingBox> cbb;
	vector<float> cconf;
	int confident_detections=0;
	int didx; //detection index
	///Track
	if(lastboxfound && tl){
		track(img1,img2,points1,points2);
	}
	else{
		tracked = false;
	}
	///Detect
	detect(img2);
	///Integration
	if (tracked){
		bbnext=tbb;
		lastconf=tconf;
		lastvalid=tvalid;
		//printf("Tracked\n");
		if(detected){                                               //   if Detected
			clusterConf(dbb,dconf,cbb,cconf);                       //   cluster detections
			//printf("Found %d clusters\n",(int)cbb.size());
			for (int i=0;i<cbb.size();i++){
				if (bbOverlap(tbb,cbb[i])<0.5 && cconf[i]>tconf){  //  Get index of a clusters that is far from tracker and are more confident than the tracker
					confident_detections++;
					didx=i; //detection index
				}
			}
			if (confident_detections==1){                                //if there is ONE such a cluster, re-initialize the tracker
				//printf("Found a better match..reinitializing tracking\n");
				bbnext=cbb[didx];
				lastconf=cconf[didx];
				lastvalid=false;
			}
			else {
				//printf("%d confident cluster was found\n",confident_detections);
				int cx=0,cy=0,cw=0,ch=0;
				int close_detections=0;
				for (int i=0;i<dbb.size();i++){
					if(bbOverlap(tbb,dbb[i])>0.7){                     // Get mean of close detections
						cx += dbb[i].x;
						cy +=dbb[i].y;
						cw += dbb[i].width;
						ch += dbb[i].height;
						close_detections++;
						//printf("weighted detection: %d %d %d %d\n",dbb[i].x,dbb[i].y,dbb[i].width,dbb[i].height);
					}
				}
				if (close_detections>0){
					bbnext.x = cvRound((float)(10*tbb.x+cx)/(float)(10+close_detections));   // weighted average trackers trajectory with the close detections
					bbnext.y = cvRound((float)(10*tbb.y+cy)/(float)(10+close_detections));
					bbnext.width = cvRound((float)(10*tbb.width+cw)/(float)(10+close_detections));
					bbnext.height =  cvRound((float)(10*tbb.height+ch)/(float)(10+close_detections));









					printf("Tracker bb: %d %d %d %d\n",tbb.x,tbb.y,tbb.width,tbb.height);
					printf("Average bb: %d %d %d %d\n",bbnext.x,bbnext.y,bbnext.width,bbnext.height);
					printf("GOT HERE! \n");
					//+ itoa(tbb.y) + itoa(tbb.width) + itoa(tbb.height)
					char tempString [50];
					char del = '_';
					sprintf(tempString,"%d%c%d%c%d%c%d", tbb.x,del,tbb.y,del,tbb.width,del,tbb.height);
					char* sendString = &tempString[0];
					sock.sendTo(sendString, strlen(sendString), destAddress, destPort);
					printf("GOT HERE BELOW! \n");
					//printf("Weighting %d close detection(s) with tracker..\n",close_detections);
				}
				else{
					//printf("%d close detections were found\n",close_detections);

				}
			}
		}
	}
	else{                                       //   If NOT tracking
		//printf("Not tracking..\n");
		lastboxfound = false;
		lastvalid = false;
		if(detected){                           //  and detector is defined
			clusterConf(dbb,dconf,cbb,cconf);   //  cluster detections
			//printf("Found %d clusters\n",(int)cbb.size());
			if (cconf.size()==1){
				bbnext=cbb[0];
				lastconf=cconf[0];
				//printf("Confident detection..reinitializing tracker\n");
				lastboxfound = true;
			}
		}
	}
	lastbox=bbnext;
	if (lastboxfound){}
	//fprintf(bb_file,"%d,%d,%d,%d,%f\n",lastbox.x,lastbox.y,lastbox.br().x,lastbox.br().y,lastconf);
	else{}
	//fprintf(bb_file,"NaN,NaN,NaN,NaN,NaN\n");

	if (lastvalid && tl)
		learn(img2);
}