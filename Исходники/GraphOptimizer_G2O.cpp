int GraphOptimizer_G2O::addVertex(Eigen::Matrix4d& vertexPose, int id, bool isFixed)
{

    g2o::Vector3d t(vertexPose(0,3),vertexPose(1,3),vertexPose(2,3));

    Eigen::Matrix3d rot = vertexPose.block(0,0,3,3);
    g2o::Quaterniond q(rot);
    q.normalize();

    // set up node
    g2o::VertexSE3 *vc = new g2o::VertexSE3();
    Eigen::Isometry3d cam; // camera pose
    cam = q;
    cam.translation() = t;

    vc->setEstimate(cam);
    vc->setId(id);      // vertex id

    //set pose fixed
    if (isFixed) {
        vc->setFixed(true);
    }

    // add to optimizer
    optimizer.addVertex(vc);
    vertexIdVec.push_back(id);

    return id;
}