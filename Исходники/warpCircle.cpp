// TODO: I can't math D:
void computeRotation(Camera c, sparseSiftFeature *s, sparseModelPoint smp){
    // Turning quaternion to rotation matrix: https://en.wikipedia.org/wiki/Rotation_matrix#Quaternion
    // Confirmation: https://groups.google.com/forum/#!topic/vsfm/V4lhITH2yHw
    double to_camera[3][3];
    double w = c.quaternion[0];  // order right!
    double x = c.quaternion[1];
    double y = c.quaternion[2];
    double z = c.quaternion[3];
    to_camera[0][0] = 1 - 2*y*y - 2*z*z;
    to_camera[0][1] = 2*x*y - 2*z*w;
    to_camera[0][2] = 2*x*z + 2*y*w;
    to_camera[1][0] = 2*x*y + 2*z*w;
    to_camera[1][1] = 1 - 2*x*x - 2*z*z;
    to_camera[1][2] = 2*y*z - 2*x*w;
    to_camera[2][0] = 2*x*z - 2*y*w;
    to_camera[2][1] = 2*y*z + 2*x*w;
    to_camera[2][2] = 1 - 2*x*x - 2*y*y;

    Mat vec1;
    Mat vec2;
    Mat X = Mat::zeros(3,1,CV_64FC1);
    X.col(0).row(2) = 1;
    Mat up = Mat::zeros(3,1,CV_64FC1);
    up.col(0).row(0) = 1;
    vec1 = X.cross(up);
    vec1 = vec1/norm(vec1);
    vec2 = vec1.cross(X);
    vec2 = vec2/norm(vec2);

    Mat R_C2W = Mat::zeros(3,3,CV_64FC1);
    R_C2W.row(0) = vec1.t();
    R_C2W.row(1) = vec2.t();
    R_C2W.row(2) = X.t();


    Mat R_C1W = Mat::zeros(3,3,CV_64FC1);
    R_C1W.col(0).row(0) = 1;
    R_C1W.col(1).row(0) = 0;
    R_C1W.col(2).row(0) = 0;

    R_C1W.col(0).row(1) = 0;
    R_C1W.col(1).row(1) = 0.6428;
    R_C1W.col(2).row(1) = -0.7660;

    R_C1W.col(0).row(2) = 0;
    R_C1W.col(1).row(2) = 0.7660;
    R_C1W.col(2).row(2) = 0.6428;


    // TODO: UNDERSTAND WHICH FINAL TRANSPOSE TO USE
    // R_C1W = R_C1W.t();
    // cout << "toCamera:" << XY_to_camera << "\n";
    // Mat trans = Mat(3,1,CV_64FC1,s->translation);
    // trans = XY_to_camera*trans;
    // Mat Normal_to_XY = MakeRotationMatrix(smp);
    // cout << "toXY:" << Normal_to_XY << "\n";
    // Mat rot = XY_to_camera*Normal_to_XY;
    // // rot = rot.inv();
    Mat R = R_C2W*R_C1W.t();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++){
            s->rotation[i][j] = R.at<double>(i,j);
            s->R_C1W[i][j] = R_C1W.at<double>(i,j);
        }
    }

    //cout << "Rotation: " << rot << "\n";
    
}