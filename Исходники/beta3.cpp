void load(int data[12], int position[8]){
// initialize variables
	 int x1,y1,x2,y2,x3,y3,x4,y4,dis[6],dismin,dismax,pos1x,pos1y,pos2x,pos2y,pos3x,pos3y,pos4x,pos4y; 
    
    int score1 = 0;
    int score2 = 0;
    int score3 = 0;
    int score4 = 0;

	int maxscore;
	int minscore;

  ////start loding the data from the camera sensor////////
    x1 = data[0];      y1 = data[1];	       x2 = data[3];	    y2 = data[4];
    x3 = data[6];      y3 = data[7];	       x4 = data[9];        y4 = data[10];
   
   
   
   //calculate the distance between detected points
    dis[0] = distance (x1,y1,x2,y2);      dis[1] = distance (x1,y1,x3,y3);  //12,13
    dis[2] = distance (x1,y1,x4,y4);      dis[3] = distance (x2,y2,x3,y3);  //14,23
    dis[4] = distance (x4,y4,x2,y2);      dis[5] = distance (x4,y4,x3,y3);  //42,43
    dismin = min(dis);     dismax = max(dis);
   
   
   
 ///////////////start assign scores///////////  
 //find the which one is the min and which one is max.  
  
   if (dismin==dis[0]){
        minscore=0;
     }
    if (dismax==dis[0]){
		maxscore=0;
     }
    if (dismin==dis[1]){
		minscore=1;
     }
    if (dismax==dis[1]){
		maxscore=1;
        
    }
    if (dismin==dis[2]){
		minscore=2;
        
    }
    if (dismax==dis[2]){
		maxscore=2;
        
    }
    if (dismin==dis[3]){
		minscore=3;
        
    }
    if (dismax==dis[3]){
        
    }
    if (dismin==dis[4]){
		minscore=4;
        
    }
    if (dismax==dis[4]){
		maxscore=4;
        
    }
    if (dismin==dis[5]){
		minscore=5;
        
    }
    if (dismax==dis[5]){
		maxscore=5;
        
    }
//assign scores
	 switch(maxscore){
	 case 0:
	    score1 += 2;
        score2 += 2;
		break;
	 case 1:
	 	score1 += 2;
        score3 += 2;
		break;
	 case 2:
	 	score1 += 2;
        score4 += 2;
		break;
	 case 3:
	 	score2 += 2;
        score3 += 2;
		break;
	 case 4:
	 	score4 += 2;
        score2 += 2;
		break;
	 case 5:
	 	score4 += 2;
        score3 += 2;
		break;
	 }

	 switch(minscore){
	 case 0:
	    score1 += 1;
        score2 += 1;
		break;
	 case 1:
	 	score1 += 1;
        score3 += 1;
		break;
	 case 2:
	 	score1 += 1;
        score4 += 1;
		break;
	 case 3:
	 	score2 += 1;
        score3 += 1;
		break;
	 case 4:
	 	score4 += 1;
        score2 += 1;
		break;
	 case 5:
	 	score4 += 1;
        score3 += 1;
		break;
	 }

//assign the position according to the score.
//assign value for x1 and y1
	if (score1==0)
	{
		pos1x = x1;
        pos1y = y1;	
	}else if  (score1==1)
	{
		pos2x = x1;
        pos2y = y1;
	}else if  (score1==2)
	{
		pos3x = x1;
        pos3y = y1;
	}else if  (score1==3)
	{
		pos4x = x1;
        pos4y = y1;
	}
//assign value for x2 and y2
		if (score2==0)
	{
		pos1x = x2;
        pos1y = y2;	
	}else if  (score2==1)
	{
		pos2x = x2;
        pos2y = y2;
	}else if  (score2==2)
	{
		pos3x = x2;
        pos3y = y2;
	}else if  (score2==3)
	{
		pos4x = x2;
        pos4y = y2;
	}
//assign value for x3 and y3
		if (score3==0)
	{
		pos1x = x3;
        pos1y = y3;	
	}else if  (score3==1)
	{
		pos2x = x3;
        pos2y = y3;
	}else if  (score3==2)
	{
		pos3x = x3;
        pos3y = y3;
	}else if  (score3==3)
	{
		pos4x = x3;
        pos4y = y3;
	}	
//assign value for x4 and y4	
		if (score4==0)
	{
		pos1x = x4;
        pos1y = y4;	
	}else if  (score4==1)
	{
		pos2x = x4;
        pos2y = y4;
	}else if  (score4==2)
	{
		pos3x = x4;
        pos3y = y4;
	}else if  (score4==3)
	{
		pos4x = x4;
        pos4y = y4;
	}		
	
//assign the position according to the score.

    position[0] = pos1x;      position[1] = pos1y;		      position[2] = pos2x;		    position[3] = pos2y;
    position[4] = pos3x;	  position[5] = pos3y;	          position[6] = pos4x;		    position[7] = pos4y;
}