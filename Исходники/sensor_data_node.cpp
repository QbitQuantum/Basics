BaseSensorDataNode* SyncSensorDataNodeMaker::makeNode(MapManager* manager, BaseSensorData* data) {
    SynchronizedSensorData* sdata = dynamic_cast<SynchronizedSensorData*>(data);
    if (! sdata)
        return 0;
    SyncSensorDataNode* snode = new SyncSensorDataNode(manager, sdata);
    for (size_t i = 0; i<sdata->sensorDatas.size(); i++) {
        IMUData* imu = dynamic_cast<IMUData*>(sdata->sensorDatas[i]);
        if (imu) {
            MapNodeUnaryRelation* imuRel = new MapNodeUnaryRelation(manager);
            imuRel->nodes()[0] = snode;
            Eigen::Isometry3d t;
            t.setIdentity();
            t.linear() = imu->orientation().toRotationMatrix();
            Eigen::Matrix<double, 6, 6> info;
            info.setZero();
            info.block<3,3>(3,3) = imu->orientationCovariance().inverse();
            //info.block<3,3>(3,3).setIdentity();
            imuRel->setTransform(t);
            imuRel->setInformationMatrix(info);
            snode->setImu(imuRel);
            break;
        }
    }
    return snode;
}