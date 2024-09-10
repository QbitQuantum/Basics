    /**
     * @brief Computes the trackball's rotation, using stored initial and final position vectors.
     */
    void computeRotationAngle (void)
    {
        //Given two position vectors, corresponding to the initial and final mouse coordinates, calculate the rotation of the sphere that will keep the mouse always in the initial position.

        if(initialPosition.norm() > 0) {
            initialPosition.normalize();
        }
        if(finalPosition.norm() > 0) {
            finalPosition.normalize();
        }

        //cout << "Initial Position: " << initialPosition.transpose() << " Final Position: " << finalPosition.transpose() << endl << endl;

        Eigen::Vector3f rotationAxis = initialPosition.cross(finalPosition);

        if(rotationAxis.norm() != 0) {
            rotationAxis.normalize();
        }

        float dot = initialPosition.dot(finalPosition);

        float rotationAngle = (dot <= 1) ? acos(dot) : 0;//If, by losing floating point precision, the dot product between the initial and final positions is bigger than one, ignore the rotation.

        Eigen::Quaternion<float> q (Eigen::AngleAxis<float>(rotationAngle,rotationAxis));

        quaternion = q * quaternion;
        quaternion.normalize();
    }