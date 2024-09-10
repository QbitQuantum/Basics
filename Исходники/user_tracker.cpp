void userTracker::loadTfTransformFromFile(string file, tf::Transform &transform) {
    ifstream in(file.data());
    if (!in) {
        cout << "No file found: " << file << endl;

        transform.setOrigin(tf::Vector3(0.0, 0.0, 0.0));
        transform.setRotation(tf::Quaternion(0.0, 0.0, 0.0, 1.0));

        return;
    }

    int columns = 6;
    double tmpVec[6];

    for (int j = 0; j < columns; j++) {
        in >> tmpVec[j];
    }
    in.close();

    // translation
    transform.setOrigin(tf::Vector3(tmpVec[0], tmpVec[1], tmpVec[2]));

    // rotation vector (Rodriguez)
    tf::Vector3 tmpTrans(tmpVec[3], tmpVec[4], tmpVec[5]);
    tf::Quaternion tmpQuat;
    if(tmpTrans.length() > 1e-6)
        tmpQuat.setRotation(tmpTrans.normalized(), tmpTrans.length());
    else {
        tmpQuat.setX(0.); tmpQuat.setY(0.); tmpQuat.setZ(0.); tmpQuat.setW(1.);
    }

    transform.setRotation(tmpQuat);

    return;
}