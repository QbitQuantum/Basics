void MotionPlanningFrame::updateCollisionObjectPose(bool update_marker_position)
{
  QList<QListWidgetItem *> sel = ui_->collision_objects_list->selectedItems();
  if (sel.empty())
    return;
  planning_scene_monitor::LockedPlanningSceneRW ps = planning_display_->getPlanningSceneRW();
  if (ps)
  {
    collision_detection::CollisionWorld::ObjectConstPtr obj = ps->getWorld()->getObject(sel[0]->text().toStdString());
    if (obj && obj->shapes_.size() == 1)
    {
      Eigen::Affine3d p;
      p.translation()[0] = ui_->object_x->value();
      p.translation()[1] = ui_->object_y->value();
      p.translation()[2] = ui_->object_z->value();

      p = Eigen::Translation3d(p.translation()) *
        (Eigen::AngleAxisd(ui_->object_rx->value(), Eigen::Vector3d::UnitX()) *
         Eigen::AngleAxisd(ui_->object_ry->value(), Eigen::Vector3d::UnitY()) *
         Eigen::AngleAxisd(ui_->object_rz->value(), Eigen::Vector3d::UnitZ()));

      ps->getWorldNonConst()->moveShapeInObject(obj->id_, obj->shapes_[0], p);
      planning_display_->queueRenderSceneGeometry();

      // Update the interactive marker pose to match the manually introduced one
      if (update_marker_position && scene_marker_)
      {
        Eigen::Quaterniond eq(p.rotation());
        scene_marker_->setPose(Ogre::Vector3(ui_->object_x->value(), ui_->object_y->value(), ui_->object_z->value()),
                               Ogre::Quaternion(eq.w(), eq.x(), eq.y(), eq.z()), "");
      }
    }
  }
}