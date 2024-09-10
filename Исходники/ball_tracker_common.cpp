std::pair<float, float> worldBallPosFromImgCoords(AL::ALMotionProxy motionProxy,
                                                  std::pair<int, int> ballPosCam,
                                                  int imgWidth, int imgHeight,
                                                  int camera)
{
	std::string cameraName = "CameraTop";
	if (camera == 1)
	{
		cameraName = "CameraBottom";
	}

	// Image coordinates of ball
	int u = ballPosCam.first;
	int v = ballPosCam.second;

	// Angles of observation of the ball
	float phi = ((float)u-((float)imgWidth)/2)/(float)imgWidth * img_WFOV;
	float theta = ((float)v-((float)imgHeight)/2)/(float)imgHeight * img_HFOV;

	// Select the right coordinates for the NAO system!
	// x outward from camera, y to the left and z vertically upwards

	// Coefficients for line-equation going from NAO camera to the ball
	float b_c = -sin(phi);
	float c_c = -sin(theta);
	float a_c = sqrt((cos(phi)*cos(phi)+cos(theta)*cos(theta))/2);

	int space = 2; //FRAME_ROBOT
	bool useSensorValues = true;
	std::vector<float> transVec =
		motionProxy.getTransform(cameraName, space, useSensorValues); // Transform camera -> FRAME_ROBOT
	std::vector<float> cameraPos =
		motionProxy.getPosition(cameraName, space, useSensorValues); // Camera position in FRAME_ROBOT


	// std::cout << "Position of bottom camera: " << std::endl;
	// std::cout << cameraPos.at(0) << " " << cameraPos.at(1) << " " << cameraPos.at(2) << std::endl;
	// std::cout << cameraPos.at(3) << " " << cameraPos.at(4) << " " << cameraPos.at(5) << std::endl;


	// Put the camera transform into an Eigen matrix for easy multiplication
	Eigen::Matrix4f trans;
	trans <<
		transVec[0] , transVec[1] , transVec[2] , transVec[3] ,
		transVec[4] , transVec[5] , transVec[6] , transVec[7] ,
		transVec[8] , transVec[9] , transVec[10], transVec[11],
		transVec[12], transVec[13], transVec[14], transVec[15];

	Eigen::Vector4f vec(a_c, b_c, c_c, 1);

	// Transform the line equation from NAO camera coordinate system into FRAME_ROBOT
	Eigen::Vector4f transformedLine = trans*vec;
	// std::cout << "trans*vec = " << transformedLine << std::endl;

	// Solve line-plane intersection with plane at z (floor)
	// Solution from Wikipedia line-plane intersection article
	float z = 0.00;

	Eigen::Matrix3f lineMat;
	lineMat <<
		cameraPos.at(0)-transformedLine[0], 1.0-0.0, 0.0-0.0,
		cameraPos.at(1)-transformedLine[1], 0.0-0.0, 1.0-0.0,
		cameraPos.at(2)-transformedLine[2], z  -  z, z  -  z;

	Eigen::Vector3f lineVec;
	lineVec << cameraPos.at(0)-0.0, cameraPos.at(1)-0.0, cameraPos.at(2)-z;
	Eigen::Vector3f txy = lineMat.inverse()*lineVec;
	std::cout << "Ball is at (x, y): (" << txy[1] << ", " << txy[2] << ")" << std::endl;
	std::pair<float, float> return_value(txy[1], txy[2]);
	return return_value; //Return ball position (x, y)
}