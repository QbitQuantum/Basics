//switch between mouse and gesture
void Recognition::MouseGestureSwitch(CvSeq* TouchBlobList){
	switch (TouchBlobList->total){
		//initial, button release,left click,two left click is double click
			case 0:
				OneFinger++;// a counter
				//for mouse drag,clear variables after being used
				if(OneFinger==3){
					MouseDragFlag=0;
					if(LeftButton){
					mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);//release left button
					LeftButton=false;//flag, left button not pressed
					}
					OneFinger=0;
				}
				//left click or double clicks action in interval based on one finger relative action
				if(Counter==1 || Counter==2){
					mouse.LeftClick();
					MouseDragFlag=FlagForMouseDrag;//for mouse drag Recognition 
				}
	            Initial();
				break;
				//mouse drag,mouse move
			case 1:
				//if switch from another case,first initialize variables
				if(CaseFlag!=1)
					Initial();
				CaseFlag=1;//set CaseFlag equal to 1 
				for(int i=0;i<TouchBlobList->total;i++){
					float* p=(float*)cvGetSeqElem(TouchBlobList,0);
					PointForCaseOne.x=cvRound(p[0]);
					PointForCaseOne.y=cvRound(p[1]);
				}//evaluate
				Counter++;
				//when first point comes,cursor location is current point location
				if(Counter==1){
					CursorInitialPosition.x=PointForCaseOne.x;
					CursorInitialPosition.y=PointForCaseOne.y;
				}
				//this is for mouse drag
				MouseDragFlag++;
				if(MouseDragFlag==(FlagForMouseDrag+1)){
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);//press left button and not release
					LeftButton=true;
					GetCursorPos(&pt);//get current mouse pointer location
					//set cursorlocation according to point relative movement
					SetCursorPos(pt.x+PointForCaseOne.x-CursorInitialPosition.x,pt.y+CursorInitialPosition.y-PointForCaseOne.y); 
					CursorInitialPosition.x=PointForCaseOne.x;
					CursorInitialPosition.y=PointForCaseOne.y;//replace previous location with current one
					MouseDragFlag=FlagForMouseDrag;
			    	break;
				}
				else{
					//mouse movement, set sursor location according to point relatice movement
					GetCursorPos(&pt);
					SetCursorPos(pt.x+PointForCaseOne.x-CursorInitialPosition.x,pt.y+CursorInitialPosition.y-PointForCaseOne.y);
					CursorInitialPosition.x=PointForCaseOne.x;
					CursorInitialPosition.y=PointForCaseOne.y;
					MouseDragFlag=0;
			    	break;
				}
				//right click,clockwise,anticlockwise,zoom in,zoom out
			case 2:
				if(CaseFlag!=2)//if switch from another case,first initialize variables
					Initial();
				CaseFlag=2;
				for(int i=0;i<TouchBlobList->total;i++){
					float* p=(float*)cvGetSeqElem(TouchBlobList,i);
					PointForCaseTwo[i].x=cvRound(p[0]);
					PointForCaseTwo[i].y=cvRound(p[1]);
				}//evaluate
				Counter++;
				//when first point comes,initialize,calculate the distance between two points and the angle relative to X axis
				if(Counter==1){
					InitialDistance=(double)(pow(double(PointForCaseTwo[0].x-PointForCaseTwo[1].x),2)+pow(double(PointForCaseTwo[0].y-PointForCaseTwo[1].y),2));
					InitialAngle=(PointForCaseTwo[0].y+PointForCaseTwo[1].y)/(PointForCaseTwo[0].x+PointForCaseTwo[1].x);
					InitialAngle=atan(InitialAngle);//angle
					InitialDistance=sqrt(InitialDistance);//distance
				}
				else{
					double ProcessedDistance=(double)(pow(double(PointForCaseTwo[0].x-PointForCaseTwo[1].x),2)+pow(double(PointForCaseTwo[0].y-PointForCaseTwo[1].y),2));
					//calculate the distance of two points in following frame
					ProcessedDistance=sqrt(ProcessedDistance);
					ProcessedAngle=(PointForCaseTwo[0].y+PointForCaseTwo[1].y)/(PointForCaseTwo[0].x+PointForCaseTwo[1].x);
					ProcessedAngle=atan(ProcessedAngle);//angle
					//calculate two angles in vector,only beyond a certain angle will work
					if((InitialAngle-ProcessedAngle)>(3.1415926/40)){
						gesture.RotateClockWise();
						InitialAngle=ProcessedAngle;
						break;
					}else if((ProcessedAngle-InitialAngle)>(3.1415926/40)){//calculate two angles in vector,picture clockwise
						gesture.RotateAntiClockWise();
						InitialAngle=ProcessedAngle;
						break;
					}else if((ProcessedDistance+160)<InitialDistance){//picture zoom out
					//calclate the distance, only when difference value greater than a certain number will following codes run
						gesture.ZoomIn();
			    		InitialDistance=ProcessedDistance;
						break;
					}else if((ProcessedDistance-160)>InitialDistance){//picture zoom in
						gesture.ZoomOut();
					    InitialDistance=ProcessedDistance;
						break;
					}else if(abs(ProcessedDistance-InitialDistance)<5 && Counter==6){//double click
						mouse.RightClick();
						break;
					}
				}
				break;
				//prevous or next picture,tag back and forwards 
			case 3:
				if(CaseFlag!=3)
					Initial();//clear all used variable when switch among different fingers action
				CaseFlag=3;
				ProcessedDistance=0;
				for(int i=0;i<TouchBlobList->total;i++){
					float* p = (float*)cvGetSeqElem(TouchBlobList,i);//get each point's coordinate
					ProcessedDistance=ProcessedDistance+cvRound(p[0]);//sum three fingers' X asix value
				}
				Counter++;
				if (Counter==1){
					InitialDistance=ProcessedDistance;//initial
				}
				else{
					WindowType=WindowsRecognition();//Recognition what kind of this window is
					if(WindowType==2){//if browser
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
					else if(WindowType==1){
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
				//if jump from another case,fist initialize
				if(CaseFlag!=4)
					Initial();
				CaseFlag=4;//set CaseFlag equal to 4
				ProcessedDistance=0;
				for(int i=0;i<TouchBlobList->total;i++){
					float* p = (float*)cvGetSeqElem(TouchBlobList,i);
					ProcessedDistance=ProcessedDistance+cvRound(p[1]);//sum up four fingers' Y axis value
				}
				Counter++;
				if (Counter==1){
					InitialDistance=ProcessedDistance;//initialize at begin
				}
				else{
					//movement should greater than a certain distance from bottom to top
					if((ProcessedDistance-160)>InitialDistance){
						gesture.UndoMinimizeAll();//call certain function
						InitialDistance=ProcessedDistance;
						break;
					}
					//move from top to bottom
					if((ProcessedDistance+160)<InitialDistance){
						InitialDistance=ProcessedDistance;
						gesture.MinimizeAll();//call certain function
						break;
					}
				}
				break;
			//do not support more than 4 fingers' actions
			default:
				Initial();
				break;
		}		
}