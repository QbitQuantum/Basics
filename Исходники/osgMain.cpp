void osgMain::drawLine(osg::Vec3 NewPt)
{
	__android_log_print(ANDROID_LOG_ERROR,"jni client","in new line point");
	if(!DrawLine)
		return;
	else
		__android_log_print(ANDROID_LOG_ERROR,"jni client","in new line point 2");
    //newPt=MFPCM->getEye();
	newPt=NewPt;
    getNewPt=true;
	if(line3Pts->size()==3)
	{
		osg::Vec3 pt1=line3Pts->at(0);
		osg::Vec3 pt2=line3Pts->at(1);
		osg::Vec3 pt3=line3Pts->at(2);
		createPipe(pt1,pt2,pt3,mshape,LineStart,currentLineGeode);
		line3Pts->at(0)=line3Pts->at(1);
		line3Pts->at(1)=line3Pts->at(2);
		line3Pts->at(2)=newPt;
		if(LineStart)
			LineStart=false;
	}
	else
		line3Pts->push_back(newPt);
	__android_log_print(ANDROID_LOG_ERROR,"jni client","get new line point");
}