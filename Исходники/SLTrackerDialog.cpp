void SLTrackerDialog::showPoseEstimate(const Eigen::Affine3f & T){

    if(ui->poseTab->isVisible()){
        ui->poseWidget->showPoseEstimate(T);
    } else if(ui->traceTab->isVisible()){
        Eigen::Vector3f t(T.translation());
        Eigen::Quaternionf q(T.rotation());

        ui->translationTraceWidget->addMeasurement("tx", t(0));
        ui->translationTraceWidget->addMeasurement("ty", t(1));
        ui->translationTraceWidget->addMeasurement("tz", t(2));
        ui->translationTraceWidget->draw();

        ui->rotationTraceWidget->addMeasurement("qw", q.w());
        ui->rotationTraceWidget->addMeasurement("qx", q.x());
        ui->rotationTraceWidget->addMeasurement("qy", q.y());
        ui->rotationTraceWidget->addMeasurement("qz", q.z());
        ui->rotationTraceWidget->draw();
    }
}