bool CameraFlight::buttonEvent(int type/*, const osg::Matrix & mat*/)
{
//    osg::Matrix curMatrix = SceneManager::instance()->getObjectTransform()->getMatrix();
//    double curScale = SceneManager::instance()->getObjectScale();

 //   osg::Matrix w2o = SceneManager::instance()->getWorldToObjectTransform();
 //   osg::Matrix o2w = SceneManager::instance()->getObjectToWorldTransform();

    if(type == 'p') {
	std::cerr<<"curMatrix"<<endl;
	printMat(curMatrix, curScale);
	
	cout<<"x = "<<latLonHeight.x()<<", y = "<<latLonHeight.y()<<", z = "<<latLonHeight.z()<<endl;
//	std::cerr<<"WorldToObject"<<endl;
//	printMat(w2o, curScale);

//	std::cerr<<"ObjectToWorld"<<endl;
//	printMat(o2w, curScale);
    }

    else if(type == 'd') {
	curMatrix.decompose(trans1, rot1, scale1, so1);

	std::cerr<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	cout<<"Trans = ";
	printVec(trans1);

	cout<<"Scale = ";
	printVec(scale1);

	cout<<"Rotate = ";
	printQuat(rot1);

	cout<<"Scale Orient =";
	printQuat(so1);

	std::cerr<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
	    //osg::Matrix _trans = osg::Matrix::rotate(oldPos,currentPos) * osg::Matrix::translate(trans);
	
	    
	    //osg::Matrix rotMat = osg::Matrix::rotate(oldPos,currentPos);
	    //osg::Matrix wr = o2w * rotMat* w2o; 
//	    osg::Matrix _tmp = w2o * osg::Matrix::rotate(oldPos,currentPos) * o2w;
	    //osg::Matrix _scale = osg::Matrix::scale(scale);
	    //osg::Matrix _temp = osg::Matrix::translate(-trans) * _scale * _trans;

    }

    else if(type == 't') {
	curMatrix.setTrans(osg::Vec3(0.0,1e+09/*6.41844e+09*/,0));
	SceneManager::instance()->setObjectMatrix(curMatrix);
    }

    else if(type == 's') {
	_origMatrix = SceneManager::instance()->getObjectTransform()->getMatrix();
	_origScale = SceneManager::instance()->getObjectScale();
    }

    else if(type == 'z') {
	tstart = time(0);
//	zIn = 1e+10; 
//	zOut = 1e+10;
	cout<<"zpressed"<<endl;
	if (flagZoom == false)
	    flagZoom = true;
    }

    else if(type == 'r') {

	if (flagRot == false) {
	    flagRot = true;
	}
	else {
	    flagRot = false;
	}

	//cout<<"Old Matrix"<<endl;
	//curMatrix = SceneManager::instance()->getObjectTransform()->getMatrix();
	//curScale = SceneManager::instance()->getObjectScale();

//	printMat(curMatrix, curScale);

	
	/*osg::Matrix mat2 = */

        osg::Matrix rotM;	
	rotM.makeRotate(DegreesToRadians(1.0),osg::Vec3(0,1,0)); 
//	printMat(rotM, curScale);
	
	curMatrix= o2w * rotM * w2o;
	
  //      printMat(curMatrix, curScale);

	//curMatrix.setTrans(trans);
	//cout<<"New Matrix"<<endl;
	//printMat(curMatrix, curScale);
	cout<<"x = "<<origPlanetPoint[0]<<", y = "<<origPlanetPoint[1]<<", z = "<<origPlanetPoint[2]<<endl;

	osg::Matrix objMat = SceneManager::instance()->getObjectTransform()->getMatrix();

	objMat.decompose(trans1,rot1,scale1,so1);
	_destMat1.decompose(trans2,rot2,scale2,so2);
//	cout<<"rotate from"<<endl;
//	printQuat(rot1);
//	cout<<"rotate to"<<endl;
//	printQuat(rot2);
	osg::Vec3 vect1, vect2;
	double ang1, ang2;
	rot1.getRotate(ang1, vect1);
	rot2.getRotate(ang2, vect2);
	osg::Vec3 vec1 = rot1.asVec3();
	osg::Vec3 vec2 = rot2.asVec3();
	
	printVec(vect1);
	printVec(vect2);
	osg::Quat rotQuat;
	rotQuat.makeRotate(vect1, vect2);
//	printQuat(rotQuat);

	rotM.makeRotate(rotQuat); 
	osg::Matrix mat = objMat* rotM;
	mat.setTrans(trans1);
	SceneManager::instance()->setObjectMatrix(mat);
    }

    else if(type == 'q') {
	cout<<"Distance = "<<distanceToSurface<<endl;
    }

    else if(type == 'g') {
	flagOut = false;
	flagIn = false;
	flagRot = false;
	flagZoom = true;
	osg::Matrix objMat = SceneManager::instance()->getObjectTransform()->getMatrix();
	
/*      osg::Matrix rotM8;
	rotM8.makeRotate(DegreesToRadians(10.0),osg::Vec3(0,1,0));
	osg::Matrix mat9 = rotM8 * objMat;

	SceneManager::instance()->setObjectMatrix(mat9);
*/

    	objMat.decompose(trans2, rot2, scale2, so2);
	double LFD, PD, FS, PS;

	a = (maxHeight - trans2[1])/25.0;
	t = 0.0;
	total = 0.0;
    }

    else if(type == 'a') {
	SceneManager::instance()->setObjectMatrix(_origMatrix);
    }

    else if(type == 'm') {

 	if(flagRot) {
	    flagRot = false;
	}

	else {
	tstart = time(0);

	zIn = 1e+10; 
	zOut = 1e+10;

	osg::Matrix objMat = SceneManager::instance()->getObjectTransform()->getMatrix();

	
	osg::Vec3d tolatLon(0.573827, -2.04617,0);
	osg::Vec3d tolatLon1(0.622566, 2.43884, 0);
	osg::Vec3d toVec1, toVec2;

	map->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
					tolatLon.x(),tolatLon.y(),tolatLon.z(),
					toVec1.x(),toVec1.y(),toVec1.z());

//	map->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
//					tolatLon1.x(),tolatLon1.y(),tolatLon1.z(),
//					toVec2.x(),toVec2.y(),toVec2.z());

	fromVec = origPlanetPoint;

	toVec1.normalize();
//	toVec2.normalize();
	fromVec.normalize();
/*
	osg::Vec3 offset(0.0,1.0,0.0);

	offset = offset - fromVec;
	fromVec = fromVec + offset;
	toVec1 = toVec1 + offset;
	toVec2 = toVec2 + offset;


	printVec(fromVec);
        printVec(toVec1);
        printVec(toVec2);
*/
	cout<<endl;
	toVec = toVec1;

	double dot = fromVec * toVec;
	angle = acos(dot/((fromVec.length() * toVec.length())));	

	angle = RadiansToDegrees(angle);

	rotAngle = angle/100.0;
	cout<<angle<<endl; 	
	flagRot = true;
}
//	osg::Vec3 crsVec = toVec1^toVec2;
//	crsVec.normalize();

//	cout<<"Where you at"<<endl;
//	printVec(fromVec);

//	cout<<"UCSD"<<endl;
//	printVec(toVec1);

//	cout<<"Tokyo"<<endl;
//	printVec(toVec2);

	//osg::Vec3 rotVec = (fromVec ^ toVec);
	//rotVec.normalize();
	//origPlanetPoint.normalize();
	//latLonHeight.normalize();

//	printVec(crsVec);	
 //       osg::Matrix rotM;
//	rotM.makeRotate(DegreesToRadians(1.0),crsVec);



	//printVec(origPlanetPoint);
//	printVec(origPlanetPoint);
//	printVec(latLonHeight);
//	printMat(rotM, curScale);
	//objMat.decompose(trans1,rot1,scale1,so1);
	//osg::Vec3 vect1, vect2;
	//double ang1, ang2;
	//rot1.getRotate(ang1, vect1);
	//printVec(vect1);
	
//	osg::Matrix mat = objMat* rotM;
//	mat.setTrans(trans1);
//	SceneManager::instance()->setObjectMatrix(mat);
    }

    else if(type == 'x') {
	cout<<"DRAWlING"<<endl;
	osgEarth::MapNode* outMapNode = MapNode::findMapNode(SceneManager::instance()->getObjectsRoot());

	outputMap = outMapNode->getMap();

	double lat = 0.0;
	double lon = -1.5708;
	double hght = 0.0;

	osg::Matrix objMat = SceneManager::instance()->getObjectTransform()->getMatrix();

	
	osg::Vec3d tolatLon(0.573827, -2.04617,0);
	osg::Vec3d tolatLon1(0.622566, 2.43884, 0);
	osg::Vec3d toVec1, toVec2;

	map->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
					lat,lon,hght,
					toVec1.x(),toVec1.y(),toVec1.z());

	osg::Matrixd output, output2;
	map->getProfile()->getSRS()->getEllipsoid()->computeLocalToWorldTransformFromXYZ(
		toVec1.x(), toVec1.y(), toVec1.z(), output);
	
	map->getProfile()->getSRS()->getEllipsoid()->computeLocalToWorldTransformFromXYZ(
		lat, lon, hght, output2);
	printMat(output,10.0);
	printMat(output2,10.0);

	osg::Geode * geode = new osg::Geode();
	osg::Vec3 centerVec(0.0,0.0,-20000.0);
	osg::ShapeDrawable* shape = new osg::ShapeDrawable(
		new osg::Cylinder(centerVec,10000.0, 2000000.0));
	geode->addDrawable(shape);
	
	osg::MatrixTransform * mat1 = new osg::MatrixTransform();

	mat1->setMatrix(output);
	mat1->addChild(geode);
	
	SceneManager::instance()->getObjectsRoot()->addChild(mat1);

	map->getProfile()->getSRS()->getEllipsoid()->convertLatLongHeightToXYZ(
					tolatLon.x(),tolatLon.y(),tolatLon.z(),
					toVec2.x(),toVec2.y(),toVec2.z());

	osg::Matrixd output1;
//	lat = 0.573827;
//	lon = -2.04617;
	map->getProfile()->getSRS()->getEllipsoid()->computeLocalToWorldTransformFromXYZ(
		toVec2.x(), toVec2.y(), toVec2.z(), output1);

	osg::Geode * geode1 = new osg::Geode();
	osg::Vec3 centerVec1(0.0,0.0,-20000.0);
	osg::ShapeDrawable* shape1 = new osg::ShapeDrawable(
		new osg::Cylinder(centerVec1,10000.0, 2000000.0));
	geode1->addDrawable(shape1);
	
	osg::MatrixTransform * mat2 = new osg::MatrixTransform();

	mat2->setMatrix(output1);
	mat2->addChild(geode1);
	
	SceneManager::instance()->getObjectsRoot()->addChild(mat2);
	//geode->addDrawable(shape1);
    }

    return false;

}