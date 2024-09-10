  void draw(MapWriterInterface *interface)
  {
    if (!initialized_) return;

    hector_worldmodel_msgs::GetObjectModel data;
    if (!service_client_.call(data)) {
      ROS_ERROR_NAMED(name_, "Cannot draw victims, service %s failed", service_client_.getService().c_str());
      return;
    }

    int counter = 0;
    for(hector_worldmodel_msgs::ObjectModel::_objects_type::const_iterator it = data.response.model.objects.begin(); it != data.response.model.objects.end(); ++it) {
      const hector_worldmodel_msgs::Object& object = *it;
      if (!draw_all_objects_ && object.state.state != hector_worldmodel_msgs::ObjectState::CONFIRMED) continue;
      if (!class_id_.empty() && object.info.class_id != class_id_) continue;

      Eigen::Vector2f coords;
      coords.x() = object.pose.pose.position.x;
      coords.y() = object.pose.pose.position.y;
      interface->drawObjectOfInterest(coords, boost::lexical_cast<std::string>(++counter), MapWriterInterface::Color(240,10,10));
    }
  }