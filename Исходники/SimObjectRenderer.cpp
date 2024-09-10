bool SimObjectRenderer::startDrag(int x, int y, DragType type)
{
  if(dragging)
    return true;

  // look if the user clicked on an object
  dragSelection = 0;
  if(&simObject == Simulation::simulation->scene)
  {
    Vector3<> projectedClick = projectClick(x, y);
    dragSelection = selectObject(projectedClick);

    if(dragSelection)
    {
      switch(dragPlane)
      {
        case xyPlane: dragPlaneVector = Vector3<>(0.f, 0.f, 1.f); break;
        case xzPlane: dragPlaneVector = Vector3<>(0.f, 1.f, 0.f); break;
        case yzPlane: dragPlaneVector = Vector3<>(1.f, 0.f, 0.f); break;
      }
      if(type == dragRotate || type == dragNormalObject)
        dragPlaneVector = dragSelection->pose.rotation * dragPlaneVector;
      if(!intersectRayAndPlane(cameraPos, projectedClick - cameraPos, dragSelection->pose.translation, dragPlaneVector, dragStartPos))
        dragSelection = 0;
      else
      {
        dragSelection->enablePhysics(false);
        if(dragMode == resetDynamics)
          dragSelection->resetDynamics();

        dragging = true;
        dragType = type;
        if(dragMode == adoptDynamics)
          dragStartTime = System::getTime();
        return true;
      }
    }
  }

  if(!dragSelection) // camera control
  {
    dragStartPos.x = x;
    dragStartPos.y = y;
    dragging = true;
    dragType = type;
    return true;
  }
  return false;
}