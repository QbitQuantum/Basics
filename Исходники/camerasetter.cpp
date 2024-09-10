    });


    auto isAtTarget = [this](){
        Eigen::Vector3f lookat = glwidget_->camera_.getRotation() * -Eigen::Vector3f::UnitZ();
        Eigen::Vector3f look_proj = lookat;
        look_proj[1] = 0;
        look_proj.normalize();
        float rads = acos(lookat.dot(look_proj));
        //qDebug() << "rads" << rads;


        Eigen::Vector3f pos = glwidget_->camera_.getPosition();

        std::cout << "target: " << target_.transpose() << std::endl;
        std::cout << "pos: " << pos.transpose() << std::endl;

        float dist = (pos - target_).norm();
        distance_text_->setText(QString::number(dist));
//        qDebug() << "dist" << dist;

        return dist < 2 && fabs(rads) < 0.2;
    };

    // Start when moving the camera
    connect(&glwidget_->camera_, &Camera::modified, [this, isAtTarget, elapsed_time_text](){
        if(!running_){
            if(ready_to_start_){
                time_.restart();
                running_ = true;
            } else {