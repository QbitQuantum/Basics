// METHOD THAT RECEIVES POINT CLOUDS (OPEN MP)
std::vector<cluster> poseEstimationSV::poseEstimationCore_openmp(pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
Tic();
	std::vector <std::vector < pose > > bestPosesAux;
	bestPosesAux.resize(omp_get_num_procs());

	//int bestPoseAlpha;
	//int bestPosePoint;
	//int bestPoseVotes;
	
	Eigen::Vector3f scenePoint;
	Eigen::Vector3f sceneNormal;


	pcl::PointIndices normals_nan_indices;
	pcl::ExtractIndices<pcl::PointNormal> nan_extract;

	float alpha;
	unsigned int alphaBin,index;
	// Iterators
	//unsigned int sr; // scene reference point
	pcl::PointCloud<pcl::PointNormal>::iterator si;	// scene paired point
	std::vector<pointPairSV>::iterator sameFeatureIt; // same key on hash table
	std::vector<boost::shared_ptr<pose> >::iterator bestPosesIt;

	Eigen::Vector4f feature;
	Eigen::Vector3f _pointTwoTransformed;
	std::cout<< "\tCloud size: " << cloud->size() << endl;
	//////////////////////////////////////////////
	// Downsample point cloud using a voxelgrid //
	//////////////////////////////////////////////

	pcl::PointCloud<pcl::PointXYZ>::Ptr cloudDownsampled(new pcl::PointCloud<pcl::PointXYZ> ());
  	// Create the filtering object
  	pcl::VoxelGrid<pcl::PointXYZ> sor;
  	sor.setInputCloud (cloud);
  	sor.setLeafSize (model->distanceStep,model->distanceStep,model->distanceStep);
  	sor.filter (*cloudDownsampled);
	std::cout<< "\tCloud size after downsampling: " << cloudDownsampled->size() << endl;

	// Compute point cloud normals (using cloud before downsampling information)
	std::cout<< "\tCompute normals... ";
	cloudNormals=model->computeSceneNormals(cloudDownsampled);
	std::cout<< "Done" << endl;

	/*boost::shared_ptr<pcl_visualization::PCLVisualizer> viewer2 = objectModel::viewportsVis(cloudFilteredNormals);

  	while (!viewer2->wasStopped ())
  	{
   		viewer2->spinOnce (100);
    		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  	}*/

	/*boost::shared_ptr<pcl_visualization::PCLVisualizer> viewer2 = objectModel::viewportsVis(model->modelCloud);

  	while (!viewer2->wasStopped ())
  	{
   		viewer2->spinOnce (100);
    		boost::this_thread::sleep (boost::posix_time::microseconds (100000));
  	}*/
	//////////////////////////////////////////////////////////////////////////////
	// Filter again to remove spurious normals nans (and it's associated point) //
	////////////////////////////////////////////////fa//////////////////////////////

	for (unsigned int i = 0; i < cloudNormals->points.size(); ++i) 
	{
		if (isnan(cloudNormals->points[i].normal[0]) || isnan(cloudNormals->points[i].normal[1]) || isnan(cloudNormals->points[i].normal[2]))
		{
	   		normals_nan_indices.indices.push_back(i);
		}
	}

	nan_extract.setInputCloud(cloudNormals);
	nan_extract.setIndices(boost::make_shared<pcl::PointIndices> (normals_nan_indices));
	nan_extract.setNegative(true);
	nan_extract.filter(*cloudWithNormalsDownSampled);
	std::cout<< "\tCloud size after removing NaN normals: " << cloudWithNormalsDownSampled->size() << endl;


	/////////////////////////////////////////////
	// Extract reference points from the scene //
	/////////////////////////////////////////////

	//pcl::RandomSample< pcl::PointCloud<pcl::PointNormal> > randomSampler;
	//randomSampler.setInputCloud(cloudWithNormalsDownSampled);
	// Create the filtering object
	int numberOfPoints=(int) (cloudWithNormalsDownSampled->size () )*referencePointsPercentage;
	int totalPoints=(int) (cloudWithNormalsDownSampled->size ());
	std::cout << "\tUniform sample a set of " << numberOfPoints << "(" << referencePointsPercentage*100 <<  "%)... ";
	referencePointsIndices->indices.clear();
	extractReferencePointsUniform(referencePointsPercentage,totalPoints);
	std::cout << "Done" << std::endl;
	//std::cout << referencePointsIndices->indices.size() << std::endl;

	//////////////
	// Votation //
	//////////////

	std::cout<< "\tVotation... ";

	omp_set_num_threads(omp_get_num_procs());
	//omp_set_num_threads(1);
	//int iteration=0;

        bestPoses.clear();
	#pragma omp parallel for private(alpha,alphaBin,alphaScene,sameFeatureIt,index,feature,si,_pointTwoTransformed) //reduction(+:iteration)  //nowait
	for(unsigned int sr=0; sr < referencePointsIndices->indices.size(); ++sr)
	{
	
		//++iteration;
		//std::cout << "iteration: " << iteration << " thread:" << omp_get_thread_num() << std::endl;
		//printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
		scenePoint=cloudWithNormalsDownSampled->points[referencePointsIndices->indices[sr]].getVector3fMap();
		sceneNormal=cloudWithNormalsDownSampled->points[referencePointsIndices->indices[sr]].getNormalVector3fMap();

		// Get transformation from scene frame to global frame
		Eigen::Vector3f cross=sceneNormal.cross (Eigen::Vector3f::UnitX ()). normalized();

		Eigen::Affine3f rotationSceneToGlobal;
		if(isnan(cross[0]))
		{
			rotationSceneToGlobal=Eigen::AngleAxisf(0.0,Eigen::Vector3f::UnitX ());
		}
		else
			rotationSceneToGlobal=Eigen::AngleAxisf(acosf (sceneNormal.dot (Eigen::Vector3f::UnitX ())),cross);

		Eigen::Affine3f transformSceneToGlobal = Eigen::Translation3f ( rotationSceneToGlobal* ((-1)*scenePoint)) * rotationSceneToGlobal;

		//////////////////////
		// Choose best pose //
		//////////////////////

		// Reset pose accumulator
		for(std::vector<std::vector<int> >::iterator accumulatorIt=accumulatorParallelAux[omp_get_thread_num()].begin();accumulatorIt < accumulatorParallelAux[omp_get_thread_num()].end(); ++accumulatorIt)
		{
			std::fill(accumulatorIt->begin(),accumulatorIt->end(),0); 
		}
		

		//std::cout << std::endl;
		for(si=cloudWithNormalsDownSampled->begin(); si < cloudWithNormalsDownSampled->end();++si)
		{
			// if same point, skip point pair
			if( (cloudWithNormalsDownSampled->points[referencePointsIndices->indices[sr]].x==si->x) && (cloudWithNormalsDownSampled->points[referencePointsIndices->indices[sr]].y==si->y) && (cloudWithNormalsDownSampled->points[referencePointsIndices->indices[sr]].z==si->z))
			{
				//std::cout << si->x << " " << si->y << " " << si->z << std::endl;
				continue;
			}	

			// Compute PPF
			pointPairSV PPF=pointPairSV(cloudWithNormalsDownSampled->points[sr],*si, transformSceneToGlobal);

			// Compute index
			index=PPF.getHash(*si,model->distanceStepInverted);

			// If distance between point pairs is bigger than the maximum for this model, skip point pair
			if(index>pointPairSV::maxHash)
			{
				//std::cout << "DEBUG" << std::endl;
				continue;
			}

			// If there is no similar point pair features in the model, skip point pair and avoid computing the alpha
			if(model->hashTable[index].size()==0)
				continue; 

			for(sameFeatureIt=model->hashTable[index].begin(); sameFeatureIt<model->hashTable[index].end(); ++sameFeatureIt)
			{
				// Vote on the reference point and angle (and object)
				alpha=sameFeatureIt->alpha-PPF.alpha; // alpha values between [-360,360]

				// alpha values should be between [-180,180] ANGLE_MAX = 2*PI
				if(alpha<(-PI))
					alpha=ANGLE_MAX+alpha;
				else if(alpha>(PI))
					alpha=alpha-ANGLE_MAX;
				//std::cout << "alpha after: " << alpha*RAD_TO_DEG << std::endl;
				//std::cout << "alpha after2: " << (alpha+PI)*RAD_TO_DEG << std::endl;
				alphaBin=static_cast<unsigned int> ( round((alpha+PI)*pointPair::angleStepInverted) ); // division is slower than multiplication
				//std::cout << "angle1: " << alphaBin << std::endl;
           			/*alphaBin = static_cast<unsigned int> (floor (alpha) + floor (PI *poseAngleStepInverted));
				std::cout << "angle2: " << alphaBin << std::endl;*/
				//alphaBin=static_cast<unsigned int> ( floor(alpha*poseAngleStepInverted) + floor(PI*poseAngleStepInverted) );
				if(alphaBin>=pointPair::angleBins)
				{	
					alphaBin=0;
					//ROS_INFO("naoooo");
					//exit(1);
				}

//#pragma omp critical
//{std::cout << index <<" "<<sameFeatureIt->id << " " << alphaBin << " " << omp_get_thread_num() << " " << accumulatorParallelAux[omp_get_thread_num()][sameFeatureIt->id][alphaBin] << std::endl;}

				accumulatorParallelAux[omp_get_thread_num()][sameFeatureIt->id][alphaBin]+=sameFeatureIt->weight;
			}
		}
		//ROS_INFO("DISTANCE:%f DISTANCE SQUARED:%f", model->maxModelDist, model->maxModel

		// Choose best pose (highest peak on the accumulator[peak with more votes])

		int bestPoseAlpha=0;
		int bestPosePoint=0;
		int bestPoseVotes=0;

		for(size_t p=0; p < model->modelCloud->size(); ++p)
		{
			for(unsigned int a=0; a < pointPair::angleBins; ++a)
			{
				if(accumulatorParallelAux[omp_get_thread_num()][p][a]>bestPoseVotes)
				{
					bestPoseVotes=accumulatorParallelAux[omp_get_thread_num()][p][a];
					bestPosePoint=p;
					bestPoseAlpha=a;
				}
			}
		}

		// A candidate pose was found
		if(bestPoseVotes!=0)
		{
			// Compute and store transformation from model to scene
			//boost::shared_ptr<pose> bestPose(new pose( bestPoseVotes,model->modelToScene(model->modelCloud->points[bestPosePoint],transformSceneToGlobal,static_cast<float>(bestPoseAlpha)*pointPair::angleStep-PI) ));

			bestPosesAux[omp_get_thread_num()].push_back(pose( bestPoseVotes,model->modelToScene(bestPosePoint,transformSceneToGlobal,static_cast<float>(bestPoseAlpha)*pointPair::angleStep-PI) ));
			//bestPoses.push_back(bestPose);

			//std::cout << bestPosesAux[omp_get_thread_num()].size() <<" " <<omp_get_thread_num()<< std::endl;
		}
		else 
		{
			continue;
		}

		// Choose poses whose votes are a percentage above a given threshold of the best pose
		accumulatorParallelAux[omp_get_thread_num()][bestPosePoint][bestPoseAlpha]=0; 	// This is more efficient than having an if condition to verify if we are considering the best pose again
		for(size_t p=0; p < model->modelCloud->size(); ++p)
		{
			for(unsigned int a=0; a < pointPair::angleBins; ++a)
			{
				if(accumulatorParallelAux[omp_get_thread_num()][p][a]>=accumulatorPeakThreshold*bestPoseVotes)
				{
					// Compute and store transformation from model to scene
					//boost::shared_ptr<pose> bestPose(new pose( accumulatorParallelAux[omp_get_thread_num()][p][a],model->modelToScene(model->modelCloud->points[p],transformSceneToGlobal,static_cast<float>(a)*pointPair::angleStep-PI ) ));


					//bestPoses.push_back(bestPose);
					bestPosesAux[omp_get_thread_num()].push_back(pose( bestPoseVotes,model->modelToScene(bestPosePoint,transformSceneToGlobal,static_cast<float>(bestPoseAlpha)*pointPair::angleStep-PI) ));
					//std::cout << bestPosesAux[omp_get_thread_num()].size() <<" " <<omp_get_thread_num()<< std::endl;
				}
			}
		}
	}

	std::cout << "Done" << std::endl;


	for(int i=0; i<omp_get_num_procs(); ++i)
	{
		for(unsigned int j=0; j<bestPosesAux[i].size(); ++j)
			bestPoses.push_back(bestPosesAux[i][j]);
	}
	std::cout << "\thypothesis number: " << bestPoses.size() << std::endl << std::endl;

	if(bestPoses.size()==0)
	{
		clusters.clear();
		return clusters;
	}

	
	//////////////////////
	// Compute clusters //
	//////////////////////
Tac();
	std::cout << "\tCompute clusters... ";
Tic();
	clusters=poseClustering(bestPoses);
Tac();
	std::cout << "Done" << std::endl;

	return clusters;
}