void
Chain::solveJacobian(const float stepSize, 
                     const int maxIterations,
                     const vec2& desiredPos, 
                     std::vector<float>* iterPose)
{
    vec3 G = vec3(desiredPos, 1); 
    vec3 endEffector; worldEndPos(endEffector);
   
    Eigen::Vector2f error;
    error(0) = G.x - endEffector.x;
    error(1) = G.y - endEffector.y;
    
    int iter = 0;
    int linkCount = count();
    while (iter < maxIterations  && error.norm() > EPSILON) { 
        Eigen::Vector2f dx = error * stepSize;
        
        // Calculate jacobian
        Eigen::MatrixXf jacobian(2,linkCount); 
        for (int j = 0; j < linkCount; j++) {
            vec3 jo; worldJointPos(j, jo);
            vec3 w = endEffector - jo;
            vec3 temp = cross(vec3(0,0,1.0f),vec3(w.x, w.y, 1));
            jacobian(0,j) = temp.x;
            jacobian(1,j) = temp.y;
        }
        Eigen::MatrixXf jacobianT = jacobian.transpose();
        Eigen::MatrixXf invJacobian = jacobian * jacobianT;
        invJacobian = jacobianT * invJacobian.inverse(); 
        Eigen::Vector4f delta = invJacobian * dx;
        for (int i = 0; i < linkCount; i++) {
            Link * l = getLink(i);
            if (delta(i) != delta(i)) {
                // Nudge angles arbitrarily to
                // break singularity for next iteration
                l->angle += 1;
            } else {
                l->angle += delta(i); 
            }
            if (iterPose) {
                iterPose->push_back(l->angle);
            }
        }
        
        // Update world frames for all joints and end effector
        worldEndPos(endEffector);    

        error(0) = G.x - endEffector.x;
        error(1) = G.y - endEffector.y;
        iter++;
    }
}