void VisualizerWrapper::updateCameraPosition(const Transform & pose)
{
    if(!pose.isNull()) {
        Eigen::Affine3f m = pose.toEigen3f();
        Eigen::Vector3f pos = m.translation();
        Eigen::Vector3f lastPos(0,0,0);
        /*if(_trajectory->size())
        {
            lastPos[0]=_trajectory->back().x;
            lastPos[1]=_trajectory->back().y;
            lastPos[2]=_trajectory->back().z;
        }
        _trajectory->push_back(pcl::PointXYZ(pos[0], pos[1], pos[2]));
        if(_maxTrajectorySize>0) {
            while(_trajectory->size() > _maxTrajectorySize) {
                _trajectory->erase(_trajectory->begin());
            }
        }
        if(_aShowTrajectory->isChecked())
        {
            _visualizer->removeShape("trajectory");
            pcl::PolygonMesh mesh;
            pcl::Vertices vertices;
            vertices.vertices.resize(_trajectory->size());
            for(unsigned int i=0; i<vertices.vertices.size(); ++i)
            {
                vertices.vertices[i] = i;
            }
            pcl::toPCLPointCloud2(*_trajectory, mesh.cloud);
            mesh.polygons.push_back(vertices);
            _visualizer->addPolylineFromPolygonMesh(mesh, "trajectory");
        }*/

        if(pose != _lastPose || _lastPose.isNull()) {
            if(_lastPose.isNull()) {
                _lastPose.setIdentity();
            }

            std::vector<pcl::visualization::Camera> cameras;
            _visualizer->getCameras(cameras);

            /*if(_aLockCamera->isChecked()) {
                //update camera position
                Eigen::Vector3f diff = pos - Eigen::Vector3f(_lastPose.x(), _lastPose.y(), _lastPose.z());
                cameras.front().pos[0] += diff[0];
                cameras.front().pos[1] += diff[1];
                cameras.front().pos[2] += diff[2];
                cameras.front().focal[0] += diff[0];
                cameras.front().focal[1] += diff[1];
                cameras.front().focal[2] += diff[2];
            }*/
            //else if(_aFollowCamera->isChecked()) {
            Eigen::Vector3f vPosToFocal = Eigen::Vector3f(cameras.front().focal[0] - cameras.front().pos[0],
                    cameras.front().focal[1] - cameras.front().pos[1],
                    cameras.front().focal[2] - cameras.front().pos[2]).normalized();
            Eigen::Vector3f zAxis(cameras.front().view[0], cameras.front().view[1], cameras.front().view[2]);
            Eigen::Vector3f yAxis = zAxis.cross(vPosToFocal);
            Eigen::Vector3f xAxis = yAxis.cross(zAxis);
            Transform PR(xAxis[0], xAxis[1], xAxis[2],0,
                    yAxis[0], yAxis[1], yAxis[2],0,
                    zAxis[0], zAxis[1], zAxis[2],0);

            Transform P(PR[0], PR[1], PR[2], cameras.front().pos[0],
                    PR[4], PR[5], PR[6], cameras.front().pos[1],
                    PR[8], PR[9], PR[10], cameras.front().pos[2]);
            Transform F(PR[0], PR[1], PR[2], cameras.front().focal[0],
                    PR[4], PR[5], PR[6], cameras.front().focal[1],
                    PR[8], PR[9], PR[10], cameras.front().focal[2]);
            Transform N = pose;
            Transform O = _lastPose;
            Transform O2N = O.inverse()*N;
            Transform F2O = F.inverse()*O;
            Transform T = F2O * O2N * F2O.inverse();
            Transform Fp = F * T;
            Transform P2F = P.inverse()*F;
            Transform Pp = P * P2F * T * P2F.inverse();

            //_visualizer->removeCoordinateSystem("reference", 0);
            //_visualizer->addCoordinateSystem(0.2, m, "reference", 0);

            _visualizer->setCameraPosition(
                Pp.x(), Pp.y(), Pp.z(),
                Fp.x(), Fp.y(), Fp.z(),
                Fp[8], Fp[9], Fp[10]);
        }
    }

    _lastPose = pose;
}