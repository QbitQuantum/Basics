transformation objectModelSV::modelToScene(const pcl::PointNormal & pointModel, const Eigen::Affine3f & transformSceneToGlobal, const float alpha)
{
	Eigen::Vector3f modelPoint=pointModel.getVector3fMap();
	Eigen::Vector3f modelNormal=pointModel.getNormalVector3fMap ();

	// Get transformation from model local frame to global frame
	Eigen::Vector3f cross=modelNormal.cross (Eigen::Vector3f::UnitX ()).normalized ();
	Eigen::AngleAxisf rotationModelToGlobal(acosf (modelNormal.dot (Eigen::Vector3f::UnitX ())), cross);

	if (isnan(cross[0]))
	{
		rotationModelToGlobal=Eigen::AngleAxisf(0.0,Eigen::Vector3f::UnitX ());
	}		
	//std::cout<< "ola:" <<acosf (modelNormal.dot (Eigen::Vector3f::UnitX ()))<<std::endl;
	//std::cout <<"X:"<< Eigen::Translation3f( rotationModelToGlobal * ((-1) * modelPoint)).x() << std::endl;
	//std::cout <<"Y:"<< Eigen::Translation3f( rotationModelToGlobal * ((-1) * modelPoint)).y() << std::endl;
	//std::cout <<"Z:"<< Eigen::Translation3f( rotationModelToGlobal * ((-1) * modelPoint)).z() << std::endl;

    Eigen::Affine3f transformModelToGlobal = Eigen::Translation3f( rotationModelToGlobal * ((-1) * modelPoint)) * rotationModelToGlobal;

	// Get transformation from model local frame to scene local frame
    Eigen::Affine3f completeTransform = transformSceneToGlobal.inverse () * Eigen::AngleAxisf(alpha, Eigen::Vector3f::UnitX ()) * transformModelToGlobal;

	//std::cout << Eigen::AngleAxisf(alpha, Eigen::Vector3f::UnitX ()).matrix() << std::endl;

	Eigen::Quaternion<float> rotationQ=Eigen::Quaternion<float>(completeTransform.rotation());

	// if object is symmetric remove yaw rotation (assume symmetry around z axis)
	if(symmetric)
	{
		Eigen::Vector3f eulerAngles;
		// primeiro [0] -> rot. around x (roll) [1] -> rot. around y (pitch) [2] -> rot. around z (yaw)
		quaternionToEuler(rotationQ, eulerAngles[0], eulerAngles[1], eulerAngles[2]);
		//pcl::getEulerAngles(completeTransform,eulerAngles[0], eulerAngles[1], eulerAngles[2]);
		//eulerAngles[2]=0.0;
		eulerToQuaternion(rotationQ, eulerAngles[0], eulerAngles[1], eulerAngles[2]);
		//quaternionToEuler(rotationQ, eulerAngles[2], eulerAngles[1], eulerAngles[2]);
		//std::cout << "EULER ANGLES: " << eulerAngles << std::endl;
	}


	//std::cout << "rotation: " << rotationQ << std::endl;
	return transformation(rotationQ, Eigen::Translation3f(completeTransform.translation()) );
}