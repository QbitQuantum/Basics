void InterpolationHelper::interpolateTransform(){

    Matrix4f transformOne, transformTwo;

    Matrix4f resultingTransform;

	Matrix3f rotationOne;
    Matrix3f rotationTwo;

    Matrix3f resultingRotation;

    double timeKeyOne;
    double timeKeyTwo;

    currentTime=renderer->currentTime-startTime;

    //move forward if we are at end of key
    while (currentTime> keyFrames[currentKeyTransform+1]->timeKey ){
    //if (currentTime> keyFrames[currentKey+1]->timeKey ){
          currentKeyTransform++;
          if (currentKeyTransform+1 >= (int)keyFrames.size()){
            bFinishedTransform=true;
            return;
            }
          }

    timeKeyOne=keyFrames[currentKeyTransform]->timeKey;
    timeKeyTwo=keyFrames[currentKeyTransform+1]->timeKey;

    //get the time difference
    double timeDifference=timeKeyTwo-timeKeyOne;

    //map time difference to 0.0 - 1.0
    double keyTime=currentTime-timeKeyOne; //-> current Position, in the beginning 0.0;
    float relativeTime=(float) (keyTime/timeDifference); //-> will go from 0.0 to 1.0 between the keys

/*
        relativeTime=relativeTime*100.0;
        relativeTime=(int)relativeTime/30;
        relativeTime=relativeTime*0.3;
*/
    if (bAdditive){
        transformOne=moveActor->transformMatrix;                //
        relativeTime*=relativeTime;      //
    }else{
        transformOne=keyFrames[currentKeyTransform]->transformKey;
    }


    transformTwo=keyFrames[currentKeyTransform+1]->transformKey;

       float x=relativeTime*2.0f;
        float y=0.0f;

        if (x< 1)
            y=x*x;
        else
            y=2-( (x-2) * (x-2) );

        y=y* 0.5;

        if (bLinear)
            y=relativeTime;


	rotationOne=getRotationMatrix(transformOne);
	rotationTwo=getRotationMatrix(transformTwo);
	resultingRotation=rotationOne.lerp(y,rotationTwo);


    //interpolate between them
    resultingTransform=transformOne.lerp(y,transformTwo); //calculate resulting position


	//normalize rotations!
	resultingRotation=normalizeRotations(resultingRotation);
	resultingTransform.setRotation(resultingRotation);

    //apply resulting position
    if (bRelative){
		//apply rotation
		moveActor->transformMatrix=baseTransform* resultingTransform;
        }
    else{
		//apply rotation
		moveActor->transformMatrix=resultingTransform;
	}
}