  void TwoDepthImageAlignerNode::processNode(MapNode* node_){
   cerr << "START ITERATION" << endl;
   std::vector<Serializable*> crearedObjects;
    SensingFrameNode* sensingFrame = dynamic_cast<SensingFrameNode*>(node_);
    if (! sensingFrame)
      return;
    
    PinholeImageData* image = dynamic_cast<PinholeImageData*>(sensingFrame->sensorData(_topic));
    if (! image)
      return;
    cerr << "got image"  << endl;
    
    Eigen::Isometry3d _sensorOffset = _config->sensorOffset(image->baseSensor());
    
    // cerr << "sensorOffset: " << endl;
    // cerr << _sensorOffset.matrix() << endl;

    Eigen::Isometry3f sensorOffset;
    convertScalar(sensorOffset,_sensorOffset);
    sensorOffset.matrix().row(3) << 0,0,0,1;

    Eigen::Matrix3d _cameraMatrix = image->cameraMatrix();
    
    ImageBLOB* blob = image->imageBlob().get();
    
    DepthImage depthImage;
    depthImage.fromCvMat(blob->cvImage());
    int r=depthImage.rows();
    int c=depthImage.cols();
    
    DepthImage scaledImage;
    Eigen::Matrix3f cameraMatrix;
    convertScalar(cameraMatrix,_cameraMatrix);
    
    //computeScaledParameters(r,c,cameraMatrix,_scale);
    PinholePointProjector* projector=dynamic_cast<PinholePointProjector*>(_converter->projector());
    cameraMatrix(2,2)=1;
    projector->setCameraMatrix(cameraMatrix);
    projector->setImageSize(depthImage.rows(), depthImage.cols());
    projector->scale(1.0/_scale);

    DepthImage::scale(scaledImage,depthImage,_scale);
    pwn::Frame* frame = new pwn::Frame;
    _converter->compute(*frame,scaledImage, sensorOffset);
  
    MapNodeBinaryRelation* odom=0;

    std::vector<MapNode*> oneNode(1);
    oneNode[0]=sensingFrame;
    MapNodeUnaryRelation* imu = extractRelation<MapNodeUnaryRelation>(oneNode);
    
    if (_previousFrame){
      _aligner->setReferenceSensorOffset(_aligner->currentSensorOffset());
      _aligner->setCurrentSensorOffset(sensorOffset);
      _aligner->setReferenceFrame(_previousFrame);
      _aligner->setCurrentFrame(frame);
      
      PinholePointProjector* projector=(PinholePointProjector*)(_aligner->projector());
      projector->setCameraMatrix(cameraMatrix);
      projector->setImageSize(depthImage.rows(), depthImage.cols());
      projector->scale(1.0/_scale);
      _aligner->correspondenceFinder()->setImageSize(projector->imageRows(), projector->imageCols());

      /*
	cerr << "correspondenceFinder: "  << r << " " << c << endl; 
	cerr << "sensorOffset" << endl;
	cerr <<_aligner->currentSensorOffset().matrix() << endl;
	cerr <<_aligner->referenceSensorOffset().matrix() << endl;
	cerr << "cameraMatrix" << endl;
	cerr << projector->cameraMatrix() << endl;
      */

      std::vector<MapNode*> twoNodes(2);
      twoNodes[0]=_previousSensingFrameNode;
      twoNodes[1]=sensingFrame;
      odom = extractRelation<MapNodeBinaryRelation>(twoNodes);
      cerr << "odom:" << odom << " imu:" << imu << endl;

      Eigen::Isometry3f guess= Eigen::Isometry3f::Identity();
      _aligner->clearPriors();
      if (odom){
      	Eigen::Isometry3f mean;
      	Eigen::Matrix<float,6,6> info;
      	convertScalar(mean,odom->transform());
	mean.matrix().row(3) << 0,0,0,1;
	convertScalar(info,odom->informationMatrix());
	//cerr << "odom: " << t2v(mean).transpose() << endl;
	_aligner->addRelativePrior(mean,info);
 	//guess = mean;
      } 

      if (imu){
      	Eigen::Isometry3f mean;
      	Eigen::Matrix<float,6,6> info;
      	convertScalar(mean,imu->transform());
      	convertScalar(info,imu->informationMatrix());
	mean.matrix().row(3) << 0,0,0,1;
	//cerr << "imu: " << t2v(mean).transpose() << endl;
	_aligner->addAbsolutePrior(_globalT,mean,info);
      }
      _aligner->setInitialGuess(guess);
      cerr << "Frames: " << _previousFrame << " " << frame << endl;

      
      // projector->setCameraMatrix(cameraMatrix);
      // projector->setTransform(Eigen::Isometry3f::Identity());
      // Eigen::MatrixXi debugIndices(r,c);
      // DepthImage debugImage(r,c);
      // projector->project(debugIndices, debugImage, frame->points());

      _aligner->align();
      
      // sprintf(buf, "img-dbg-%05d.pgm",j);
      // debugImage.save(buf);
      //sprintf(buf, "img-ref-%05d.pgm",j);
      //_aligner->correspondenceFinder()->referenceDepthImage().save(buf);
      //sprintf(buf, "img-cur-%05d.pgm",j);
      //_aligner->correspondenceFinder()->currentDepthImage().save(buf);

      cerr << "inliers: " << _aligner->inliers() << endl;
      cerr << "chi2: " << _aligner->error() << endl;
      cerr << "chi2/inliers: " << _aligner->error()/_aligner->inliers() << endl;
      cerr << "initialGuess: " << t2v(guess).transpose() << endl;
      cerr << "transform   : " << t2v(_aligner->T()).transpose() << endl;
      if (_aligner->inliers()>-1){
 	_globalT = _globalT*_aligner->T();
	cerr << "TRANSFORM FOUND" <<  endl;
      } else {
	cerr << "FAILURE" <<  endl;
	_globalT = _globalT*guess;
      }
      if (! (_counter%50) ) {
	Eigen::Matrix3f R = _globalT.linear();
	Eigen::Matrix3f E = R.transpose() * R;
	E.diagonal().array() -= 1;
	_globalT.linear() -= 0.5 * R * E;
      }
      _globalT.matrix().row(3) << 0,0,0,1;
      cerr << "globalTransform   : " << t2v(_globalT).transpose() << endl;

      // char buf[1024];
      // sprintf(buf, "frame-%05d.pwn",_counter);
      // frame->save(buf, 1, true, _globalT);


      cerr << "creating alias" << endl;
      // create an alias for the previous node
      MapNodeAlias* newRoot = new MapNodeAlias(_previousSensingFrameNode,_previousSensingFrameNode->manager());
      _previousSensingFrameNode->manager()->addNode(newRoot);
      
      cerr << "creating alias relation" << endl;
      MapNodeAliasRelation* aliasRel = new MapNodeAliasRelation(newRoot,_previousSensingFrameNode->manager());
      aliasRel->nodes()[0] = newRoot;
      aliasRel->nodes()[1] = _previousSensingFrameNode;
      _previousSensingFrameNode->manager()->addRelation(aliasRel);
      
      cerr << "reparenting old elements" << endl;
      // assign all the used relations to the alias node
      if (imu){
	imu->setOwner(newRoot);
	imu->manager()->addRelation(imu);
      }

      if (odom){
	odom->setOwner(newRoot);
	odom->manager()->addRelation(imu);
      }
      
      cerr << "adding result" << endl;
      
      Relation* newRel = new Relation(_aligner, _converter, 
	       _previousSensingFrameNode, sensingFrame,
	       _topic, _aligner->inliers(), _aligner->error(), _manager);
      newRel->setOwner(newRoot);
      newRel->nodes()[0] = newRoot;
      newRel->nodes()[1] = _previousSensingFrameNode;
      Eigen::Isometry3d iso;
      convertScalar(iso,_aligner->T());
      newRel->setTransform(iso);
      newRel->setInformationMatrix(Eigen::Matrix<double, 6,6>::Identity());
      newRel->manager()->addRelation(newRel);
      

      *os << _globalT.translation().transpose() << endl;

      // create a new alias node for the prior element
      // bind the alias with the prior node

      // add to the alias the relations that have been used to
      // determine the transformation

      // add the alias to the map
      // add the new transformation to the map
      
    } else {
      _aligner->setCurrentSensorOffset(sensorOffset);
      _globalT = Eigen::Isometry3f::Identity();
      if (imu){
      	Eigen::Isometry3f mean;
      	convertScalar(mean,imu->transform());
	_globalT = mean;
      }
    }
    
    cerr << "deleting previous frame" << endl;
    if (_previousFrame)
      delete _previousFrame;
    
    cerr << "deleting blob frame" << endl;
    delete blob;

    cerr << "bookkeeping update" << endl;
    _previousSensingFrameNode = sensingFrame;
    _previousFrame = frame;
    _counter++;
    
    cerr << "END ITERATION" << endl;
  }