double MyController::onAction(ActionEvent &evt) {  

  int actionNumber = 2;
  int functionalFeature = 1;
  int targetType = 3;

  myfile << setprecision(2) << std::fixed;

  // handle of target and tool
  SimObj *target = getObj("box_004");
  SimObj *toolName = getObj("TShapeTool_004");


  if (evt.time() < 5.0)
  {
    // cout << "Time" << endl;
    cout << evt.time() << endl;

    toolName->getPosition(currentToolPos); // get the current tool position
    toolName->getRotation(finalToolRotation);
    toolName->getVelocity(finalToolVel);
    isToolAtRest   = checkEntityMotionStatus(toolName);  // checks whether the tool is moving by calculating its velocity

    target->getPosition(currentTargetPos);
    target->getRotation(finalTargetRotation);
    target->getVelocity(finalTargetVel);
    isTargetAtRest = checkEntityMotionStatus(target);    // checks whether the object is moving by calculating its velocity
    
  }

  if (evt.time() > 5.0)
  {
     insideTimer = false;
     counterOfAction ++ ; 
  }

  if(!insideTimer && counterOfAction == 1 )
  {
           myfile << actionNumber  << " , " << functionalFeature << " , " ;
           myfile << initToolRotation.qw() <<  " , " << initToolRotation.qx() <<  " , " << initToolRotation.qy() <<  " , " << initToolRotation.qz() << " , " ;
           myfile << initTargetRotation.qw() <<  " , " << initTargetRotation.qx() <<  " , " << initTargetRotation.qy() <<  " , " << initTargetRotation.qz() << " , " ;
           myfile << finalTargetRotation.qw() <<  " , " << finalTargetRotation.qx() <<  " , " << finalToolRotation.qy() <<  " , " << finalToolRotation.qz() << " , " ;
           myfile << initToolPos.x() << " , " << initToolPos.z() << " , " ;
           myfile << initTargetPos.x() << " , " << initTargetPos.z() << " , " ;
           myfile << forceOnTool_x  << " , " << forceOnTool_z << " , " ;
           myfile << appliedToolVel.x()  << " , " << appliedToolVel.z() << " , " ;
           myfile << toolVelAtHit.x() << " , " << toolVelAtHit.z() << " , " ;
           myfile << targetVelAtHit.x() << " , " << targetVelAtHit.z() << " , " ;
           myfile << currentToolPos.x() << " , " << currentToolPos.z() << " , " ;
           myfile << currentTargetPos.x() << " , " << currentTargetPos.z() << " , " ;
           myfile << finalToolVel.x() << " , " << finalToolVel.z() << " , " ;
           myfile << finalTargetVel.x() << " , " << finalTargetVel.z() << " , " ;
           myfile   << isToolAtRest <<  " , " << isTargetAtRest << " , " ;
           myfile << currentToolPos.x() -  initToolPos.x() << " , " << currentToolPos.z() - initToolPos.z() << " , " ;
           myfile << currentTargetPos.x() -  initTargetPos.x() << " , " << currentTargetPos.z() - initTargetPos.z();
           myfile << "\n"; 
           cout << "The simulation for " << actionNumber << " , " << functionalFeature << " has been recorded" << endl;
           // exit(0);
           flag = false;  
  }

      
  return 0.01;    

 }