//=====================================================
///Execute the skill.  This is the main part of the skill, where you tell the
///robot how to perform the skill.
void CutGoalSkill::execute()
{		 
	///If not active, dont do anything!
	if(!initialized)
	{
		return;  
	}
	else
	{
		//grab the ball location
		
    if(!presetBall){
		  ball = strategy->getCurrentRoboCupFrame()->getDefensiveBallLocation();
    }
		

    ///Calculate the angle bisector of the area we want to cover
    float theta;
	  float theta1=angleBetween(sp->field.OUR_GOAL_LINE,point1,ball.getX(),ball.getY());
    float theta2=angleBetween(sp->field.OUR_GOAL_LINE,point2,ball.getX(),ball.getY());
    theta=(theta1+theta2)/2.0f;
    theta=normalizeAngle(theta+PI);
    float halfAngle=ABS(angleDifference(theta1,theta2)/2.0f);

    //calculate midpoint to extend from
		Pair midpoint;
		midpoint.setY((sp->field.OUR_GOAL_LINE-ball.getX()) * TAN(theta) + ball.getY());
	  midpoint.setX(sp->field.OUR_GOAL_LINE);

    /*debugging helpful stuff
    GUI_Record.debuggingInfo.setDebugPoint(robotID,6,midpoint);   
    GUI_Record.debuggingInfo.setDebugPoint(robotID,7,sp->field.OUR_GOAL_LINE,point1);   
    GUI_Record.debuggingInfo.setDebugPoint(robotID,8,sp->field.OUR_GOAL_LINE,point2);   
    Pair ang1(ball.getX()+.2f,ball.getY());
    Pair ang2(ball.getX()+.2f,ball.getY());
    rotateAboutPoint(ang1,ball,theta1,ang1);
    rotateAboutPoint(ang2,ball,theta2,ang2);
    GUI_Record.debuggingInfo.setDebugPoint(robotID,3,ang1);   
    GUI_Record.debuggingInfo.setDebugPoint(robotID,4,ang2);  
    
    Pair t(ball.getX()+.2f,ball.getY());
    rotateAboutPoint(t,ball,theta,t);
    GUI_Record.debuggingInfo.setDebugPoint(robotID,5,t);  
    */

	  // The ideal point we want the robot to be in this circumstances
	  Pair dest;
	  float distance = sp->general.PLAYER_RADIUS / SIN(ABS(halfAngle)) ;
	  //char msg[80]; sprintf(msg,"dist: %5.2f",distance);GUI_Record.debuggingInfo.addDebugMessage(msg);


	  extendPoint(midpoint,ball,-distance,dest);

	  // We have to check if the destination point is between the Upper and lower limit
	  //	  float slope =  (midpoint.getY() - ball.getY()) / (midpoint.getX() - ball.getY()) ;
	  // If it is above the limit
	  if(dest.getX() > UPPER_X){
	    extrapolateForY(midpoint,ball,UPPER_X,dest);
	  }
	  // If it is below the limit
	  if(dest.getX() < LOWER_X){
	    extrapolateForY(midpoint,ball,LOWER_X,dest);
	  }
	  command->setControl(OMNI_NORMAL);
	  command->setPos(dest);

	  command->setRotation(angleBetween(getLocation(robotID, *currentVisionData, *sp),
                                      ball));
      
    strategy->getCurrentFrame()->setMessage(robotID,"Covering Goal");

	}
}