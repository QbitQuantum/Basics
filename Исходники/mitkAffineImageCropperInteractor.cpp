void mitk::AffineImageCropperInteractor::RotateObject (StateMachineAction*, InteractionEvent* interactionEvent)
{
  InteractionPositionEvent* positionEvent = dynamic_cast<InteractionPositionEvent*>(interactionEvent);
  if(positionEvent == NULL)
    return;

  Point2D currentPickedDisplayPoint = positionEvent->GetPointerPositionOnScreen();
  if(currentPickedDisplayPoint.EuclideanDistanceTo(m_InitialPickedDisplayPoint) < 1)
    return;

  vtkRenderer* currentVtkRenderer = interactionEvent->GetSender()->GetVtkRenderer();

  if ( currentVtkRenderer &&  currentVtkRenderer->GetActiveCamera())
  {
    double vpn[3];
    currentVtkRenderer->GetActiveCamera()->GetViewPlaneNormal( vpn );

    Vector3D rotationAxis;
    rotationAxis[0] = vpn[0];
    rotationAxis[1] = vpn[1];
    rotationAxis[2] = vpn[2];
    rotationAxis.Normalize();

    Vector2D move = currentPickedDisplayPoint - m_InitialPickedDisplayPoint;

    double rotationAngle = -57.3 * atan(move[0]/move[1]);
    if(move[1]<0) rotationAngle +=180;

    // Use center of data bounding box as center of rotation
    Point3D rotationCenter = m_OriginalGeometry->GetCenter();
    if(positionEvent->GetSender()->GetMapperID() == BaseRenderer::Standard2D)
      rotationCenter = m_InitialPickedPoint;

    // Reset current Geometry3D to original state (pre-interaction) and
    // apply rotation
    RotationOperation op( OpROTATE, rotationCenter, rotationAxis, rotationAngle );
    Geometry3D::Pointer newGeometry = static_cast<Geometry3D*>(m_OriginalGeometry->Clone().GetPointer());
    newGeometry->ExecuteOperation( &op );
    m_SelectedNode->GetData()->SetGeometry(newGeometry);

    interactionEvent->GetSender()->GetRenderingManager()->RequestUpdateAll();
  }
}