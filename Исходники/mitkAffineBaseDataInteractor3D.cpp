void mitk::AffineBaseDataInteractor3D::RotateObject (StateMachineAction*, InteractionEvent* interactionEvent)
{
  InteractionPositionEvent* positionEvent = dynamic_cast<InteractionPositionEvent*>(interactionEvent);
  if(positionEvent == NULL)
    return;

  Point2D currentPickedDisplayPoint = positionEvent->GetPointerPositionOnScreen();
  Point3D currentWorldPoint = positionEvent->GetPositionInWorld();

  vtkCamera* camera = NULL;
  vtkRenderer* currentVtkRenderer = NULL;

  if ((interactionEvent->GetSender()) != NULL)
  {
    camera = interactionEvent->GetSender()->GetVtkRenderer()->GetActiveCamera();
    currentVtkRenderer = interactionEvent->GetSender()->GetVtkRenderer();
  }
  if ( camera && currentVtkRenderer)
  {
    double vpn[3];
    camera->GetViewPlaneNormal( vpn );

    Vector3D viewPlaneNormal;
    viewPlaneNormal[0] = vpn[0];
    viewPlaneNormal[1] = vpn[1];
    viewPlaneNormal[2] = vpn[2];

    Vector3D interactionMove;
    interactionMove[0] = currentWorldPoint[0] - m_InitialPickedWorldPoint[0];
    interactionMove[1] = currentWorldPoint[1] - m_InitialPickedWorldPoint[1];
    interactionMove[2] = currentWorldPoint[2] - m_InitialPickedWorldPoint[2];

    if (interactionMove[0] == 0 && interactionMove[1] == 0  && interactionMove[2] == 0)
      return;

    Vector3D rotationAxis = itk::CrossProduct(viewPlaneNormal, interactionMove);
    rotationAxis.Normalize();

    int* size = currentVtkRenderer->GetSize();
    double l2 =
        (currentPickedDisplayPoint[0] - m_InitialPickedDisplayPoint[0]) *
        (currentPickedDisplayPoint[0] - m_InitialPickedDisplayPoint[0]) +
        (currentPickedDisplayPoint[1] - m_InitialPickedDisplayPoint[1]) *
        (currentPickedDisplayPoint[1] - m_InitialPickedDisplayPoint[1]);

    double rotationAngle = 360.0 * sqrt(l2 / (size[0] * size[0] + size[1] * size[1]));

    // Use center of data bounding box as center of rotation
    Point3D rotationCenter = m_OriginalGeometry->GetCenter();

    int timeStep = 0;
    if ((interactionEvent->GetSender()) != NULL)
      timeStep = interactionEvent->GetSender()->GetTimeStep(this->GetDataNode()->GetData());

    // Reset current Geometry3D to original state (pre-interaction) and
    // apply rotation
    RotationOperation op( OpROTATE, rotationCenter, rotationAxis, rotationAngle );
    Geometry3D::Pointer newGeometry = static_cast<Geometry3D*>(m_OriginalGeometry->Clone().GetPointer());
    newGeometry->ExecuteOperation( &op );
    mitk::TimeGeometry::Pointer timeGeometry = this->GetDataNode()->GetData()->GetTimeGeometry();
    if (timeGeometry.IsNotNull())
      timeGeometry->SetTimeStepGeometry(newGeometry, timeStep);

    interactionEvent->GetSender()->GetRenderingManager()->RequestUpdateAll();
  }
}