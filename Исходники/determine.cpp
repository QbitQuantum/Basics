void Determine::JudgementMouse(CvSeq* circles){
	switch (circles->total){
			case 0:
				OneFinger++;
				//for mouse drag judgement,clear variables after being used
				if(OneFinger==3){
					MouseMoveFlag=0;
					if(LeftButton){
					mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
					LeftButton=false;
					}
					OneFinger=0;
				}
				//left click or double clicks action in interval based on one finger relative action
				if(Temp==1 || Temp==2){
					mouse.LeftClick();
					MouseMoveFlag=1800;//for mouse drag judgement 
				}
	            Initial();
				break;
			case 1:
				if(CaseFlag!=1)
					Initial();
				CaseFlag=1;
				for(int i=0;i<circles->total;i++){
					float* p=(float*)cvGetSeqElem(circles,0);
					X1[0]=cvRound(p[0]);
					X1[1]=cvRound(p[1]);
				}
				Temp++;
				if(Temp==1){
					CooX=X1[0];
					CooY=X1[1];
				}
				MouseMoveFlag++;
				if(MouseMoveFlag==1801){
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//press left button and not release
					LeftButton=true;
					GetCursorPos(&pt);//get current mouse pointer location
			     	SetCursorPos(pt.x+X1[0]-CooX,pt.y+CooY-X1[1]);//set mouse pointer to a new coordinate
				    CooX=X1[0];
			    	CooY=X1[1];//replace previous location with current one
					MouseMoveFlag=1800;
			    	break;
				}
				else{
					GetCursorPos(&pt);
				    SetCursorPos(pt.x+X1[0]-CooX,pt.y+CooY-X1[1]);
			    	CooX=X1[0];
		    		CooY=X1[1];
					MouseMoveFlag=0;
			    	break;
				}
			case 2:
				if(CaseFlag!=2)
					Initial();
				CaseFlag=2;
				for(int i=0;i<circles->total;i++){
					float* p=(float*)cvGetSeqElem(circles,i);
					X2[i][0]=cvRound(p[0]);
					X2[i][1]=cvRound(p[1]);
				}
				Temp++;
				//initial,calculate the distance between two points and the angle relative to X axis
				if(Temp==1){
					InitialDistance=(double)(pow((X2[0][0]-X2[1][0]),2)+pow((X2[0][1]-X2[1][1]),2));
					InitialAngle=(X2[0][1]+X2[1][1])/(X2[0][0]+X2[1][0]);
					InitialAngle=atan(InitialAngle);//angle
					InitialDistance=sqrt(InitialDistance);//distance
				}
				else{
					double ProcessedDistance=(double)(pow((X2[0][0]-X2[1][0]),2)+pow((X2[0][1]-X2[1][1]),2));
					//calculate the distance of two points in following frame
					ProcessedDistance=sqrt(ProcessedDistance);
					ProcessedAngle=(X2[0][1]+X2[1][1])/(X2[0][0]+X2[1][0]);//distance
					ProcessedAngle=atan(ProcessedAngle);//angle
					//calculate two angles in vector
					if((InitialAngle-ProcessedAngle)>(3.1415926/20)){
						gesture.RotateClockWise();
						InitialAngle=ProcessedAngle;
						break;
					}
					//calculate two angles in vector,picture clockwise
					if((ProcessedAngle-InitialAngle)>(3.1415926/20)){
						gesture.RotateAntiClockWise();
						InitialAngle=ProcessedAngle;
						break;
					}
					//picture zoom out
					//calclate the distance, only when difference value greater than a certain number will following codes run
					if((ProcessedDistance+80)<InitialDistance){
						gesture.ZoomIn();
			    		InitialDistance=ProcessedDistance;
				    	break;
					}
					//picture zoom in
					if((ProcessedDistance-80)>InitialDistance){
						gesture.ZoomOut();
					    InitialDistance=ProcessedDistance;
					    break;
					}
					//double click
					if(abs(ProcessedDistance-InitialDistance)<10 && Temp==6){
						mouse.RightClick();
						break;
					}
				}
				break;
			case 3:
				if(CaseFlag!=3)
					Initial();//clear all used variable when switch among different fingers action
				CaseFlag=3;
				ProcessedDistance=0;
				for(int i=0;i<circles->total;i++){
					float* p = (float*)cvGetSeqElem(circles,i);//get each point's coordinate
					ProcessedDistance=ProcessedDistance+cvRound(p[0]);//sum three fingers' X asix value
				}
				Temp++;
				if (Temp==1){
					InitialDistance=ProcessedDistance;//initial
				}
				else{
					Judge=WindowsJudge();//distinguish what kind of this window is
					if(Judge==2){//if browser
						if((ProcessedDistance-180)>InitialDistance){//tag forward
							gesture.TagForward();
						    InitialDistance=ProcessedDistance;//replace initial sum with current sum of x axis
						    break;
						}
	                 	if((ProcessedDistance+180)<InitialDistance){//tag back
					    	gesture.TagBack();
							InitialDistance=ProcessedDistance;
					    	break;
						}
					}
					//if current window is picture viewer
					else if(Judge==1){
						if((ProcessedDistance-180)>InitialDistance){//change to next picture
							gesture.NextPicture();
						    InitialDistance=ProcessedDistance;
						    break;
						}
	                 	if((ProcessedDistance+180)<InitialDistance){//change to previous picture
							gesture.PreviousPicture();
							InitialDistance=ProcessedDistance;
					    	break;
						}
					}
				}
				break;
			case 4:
				if(CaseFlag!=4)
					Initial();
				CaseFlag=4;
				ProcessedDistance=0;
				for(int i=0;i<circles->total;i++){
					float* p = (float*)cvGetSeqElem(circles,i);
					ProcessedDistance=ProcessedDistance+cvRound(p[1]);//sum up four fingers' Y axis value
				}
				Temp++;
				if (Temp==1){
					InitialDistance=ProcessedDistance;//initial
				}
				else{
					//movement should greater than a certain distance from bottom to top
					if((ProcessedDistance-160)>InitialDistance){
						gesture.UndoMinimizeAll();//call certain modual
						InitialDistance=ProcessedDistance;
						break;
					}
					//move from top to bottom
					if((ProcessedDistance+160)<InitialDistance){
						InitialDistance=ProcessedDistance;
						gesture.MinimizeAll();
						break;
					}
				}
				break;
			default:
				Initial();//do not support more than 4 fingers' actions
				break;
		}		
}