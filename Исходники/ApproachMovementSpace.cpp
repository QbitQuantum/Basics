/**************************************************************************************************
 *  Procecure                                                                                     *
 *                                                                                                *
 *  Description: moveHandRelativeToObject                                                         *
 *  Class      : ApproachMovementSpace                                                            *
 **************************************************************************************************/
Matrix4f ApproachMovementSpace::moveHandRelativeToObject(float theta, float phi, float rho, bool update)
{
	RobotPtr     hand = eef  -> getRobot();

	// Don't let the hand collide with the object
	if (rho < 10) rho = 10;

	// Calculate new XYZ coordinates for the hand
	Vector3f new_pos     = object -> getGlobalPose().topLeftCorner (3,3) * calculateCarthesianCoordinates(theta, phi, rho);
	         new_pos    += object -> getGlobalPose().topRightCorner(3,1);

	Matrix4f new_pose    = hand -> getGlobalPose();
	Matrix3f orientation;

	// Calculate First Vector of the orientation Matrix
		// It is colinear with the distance vector between object and hand
	orientation.block(0,0,3,1) = object -> getGlobalPose().topRightCorner(3,1) - new_pos;

	// Calculate the Remainder two orientation vectors
	Matrix3f inertia  = object -> getGlobalPose().topLeftCorner(3,3);
		     inertia *= object -> getInertiaMatrix();

	// Select two vectors from the objects inertia matrix
	     uint vectors_left  = 2;
	for (uint column        = 0; column < 3; column += 1)
	{
		Vector3f v1 = orientation.block(0,0,3,1);

		if( v1.dot( inertia.col(column) ) != 1)
		{
			orientation.block(0,vectors_left,3,1) = inertia.col(column);

			vectors_left -= 1;

			if (vectors_left == 0) break;
		}
	}

	// Check if two new vectors were included
	if ( vectors_left != 0)
	{
		cout << endl << "[Error] Function: moveHandRelativeToObject   |   The two vectors from the object's inertia matrix were not selected.";

		exit(-1);
	}

	// Make the orientation matrix orthonormalized
	orientation  = gramSchmidtNormalization3f(orientation);
	orientation *= offset.topLeftCorner(3,3);

	// Check if the new orientation is mirrored or not
		// If so, correct it
	if ( ( orientation.determinant() - (-1) <  0.01) &&
		 ( orientation.determinant() - (-1) > -0.01) )
	{
		orientation.col(1) *= -1;
	}

	// Update new hand pose
	new_pose.topLeftCorner (3,3) = orientation;
	new_pose.topRightCorner(3,1) = new_pos - orientation * offset.topRightCorner(3,1);

	// Set updated pose
	if (update) hand -> setGlobalPose(new_pose);

	return new_pose;
}