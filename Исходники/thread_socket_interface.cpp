// (1) right         (2) left
void getDeviceState (Vector3d &leftPosition, Matrix3d &leftRotation, Vector3d &rightPosition, Matrix3d &rightRotation) {
    if (receiver.recv(buf)) {
        while (receiver.recv(buf));
    
        boost::split(vectbuf, buf, boost::is_any_of("\n"));
        parse(vectbuf[0], vect1);
        parse(vectbuf[1], vect2);
         
       /*
        // Build transformation matrix
        for (i=0; i<4; i++) {
            for (j=0; j<4; j++) {
                t1[i][j] = boost::lexical_cast<double>(vect1[i*4 + j].c_str());
                t2[i][j] = boost::lexical_cast<double>(vect2[i*4 + j].c_str());
            }
        }
        
        // Extract rotation matrix from transformation matrix
        t1.getRotationMatrix(r1);
        t2.getRotationMatrix(r2);
        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                leftRotation (i,j)  = r2[i][j];
                rightRotation (i,j) = r1[i][j];
            }
        }
        
        // Extract position vector from transformation matrix
        for (i=0; i<3; i++) {
            leftPosition(i)  = t2[3][i];
            rightPosition(i) = t1[3][i];
        }
        */

        // Extract rotation matrix from transformation matrix
        for (i=0; i<3; i++) {
            for (j=0; j<3; j++) {
                leftRotation(i,j) = boost::lexical_cast<double>(vect2[i*3 + j].c_str());
                rightRotation(i,j) = boost::lexical_cast<double>(vect1[i*3 + j].c_str());
            }
        }
        
        // Extract position vector from transformation matrix
        for (j=0; j<3; j++) {
            leftPosition(j)  = boost::lexical_cast<double>(vect2[9 + j].c_str());
            rightPosition(j) = boost::lexical_cast<double>(vect1[9 + j].c_str());
        }
             
        /*
        for (i=0; i<3; i++)
            leftPosition(i) = boost::lexical_cast<double>(vect2[i+9].c_str());
        for (i=0; i<3; i++)
            leftRotation(0,i) = boost::lexical_cast<double>(vect2[i].c_str());
        for (i=0; i<3; i++)
            leftRotation(1,i) = boost::lexical_cast<double>(vect2[i+3].c_str());
        for (i=0; i<3; i++)
            leftRotation(2,i) = boost::lexical_cast<double>(vect2[i+6].c_str());
        //leftRotation.transpose();
            
        for (i=0; i<3; i++)
            rightPosition(i) = boost::lexical_cast<double>(vect1[i+9].c_str());
        for (i=0; i<3; i++)
            rightRotation(0,i) = boost::lexical_cast<double>(vect1[i].c_str());
        for (i=0; i<3; i++)
            rightRotation(1,i) = boost::lexical_cast<double>(vect1[i+3].c_str());
        for (i=0; i<3; i++)
            rightRotation(2,i) = boost::lexical_cast<double>(vect1[i+6].c_str());
        //rightRotation.transpose();
        */
    }
}