void mitk::GizmoInteractor::RotateAroundAxis(StateMachineAction*,
                                               InteractionEvent* interactionEvent)
{
  auto positionEvent = dynamic_cast<const InteractionPositionEvent*>(interactionEvent);
  if(positionEvent == NULL)
  {
    return;
  }

  Vector2D originalVector = m_InitialClickPosition2D - m_InitialGizmoCenter2D;
  Vector2D currentVector = positionEvent->GetPointerPositionOnScreen() - m_InitialGizmoCenter2D;

  originalVector.Normalize();
  currentVector.Normalize();

  double angle_rad = std::atan2(currentVector[1], currentVector[0]) -
                     std::atan2(originalVector[1], originalVector[0]);

  ApplyRotationToManipulatedObject(vtkMath::DegreesFromRadians(angle_rad));
  RenderingManager::GetInstance()->ForceImmediateUpdateAll();
}