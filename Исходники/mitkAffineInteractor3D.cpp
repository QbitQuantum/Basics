bool AffineInteractor3D
::ExecuteAction( Action *action, StateEvent const *stateEvent )
{
  bool ok = false;

  // Get data object
  BaseData *data = m_DataNode->GetData();
  if ( data == NULL )
  {
    MITK_ERROR << "No data object present!";
    return ok;
  }

  // Get Event and extract renderer
  const Event *event = stateEvent->GetEvent();
  BaseRenderer *renderer = NULL;
  vtkRenderWindow *renderWindow = NULL;
  vtkRenderWindowInteractor *renderWindowInteractor = NULL;
  vtkRenderer *currentVtkRenderer = NULL;
  vtkCamera *camera = NULL;

  if ( event != NULL )
  {
    renderer = event->GetSender();
    if ( renderer != NULL )
    {
      renderWindow = renderer->GetRenderWindow();
      if ( renderWindow != NULL )
      {
        renderWindowInteractor = renderWindow->GetInteractor();
        if ( renderWindowInteractor != NULL )
        {
          currentVtkRenderer = renderWindowInteractor
            ->GetInteractorStyle()->GetCurrentRenderer();
          if ( currentVtkRenderer != NULL )
          {
            camera = currentVtkRenderer->GetActiveCamera();
          }
        }
      }
    }
  }

  // Check if we have a DisplayPositionEvent
  const DisplayPositionEvent *dpe =
    dynamic_cast< const DisplayPositionEvent * >( stateEvent->GetEvent() );
  if ( dpe != NULL )
  {
    m_CurrentPickedPoint = dpe->GetWorldPosition();
    m_CurrentPickedDisplayPoint = dpe->GetDisplayPosition();
  }

  // Get the timestep to also support 3D+t
  int timeStep = 0;
  ScalarType timeInMS = 0.0;
  if ( renderer != NULL )
  {
    timeStep = renderer->GetTimeStep( data );
    timeInMS = renderer->GetTime();
  }

  // If data is an mitk::Surface, extract it
  Surface *surface = dynamic_cast< Surface * >( data );
  vtkPolyData *polyData = NULL;
  if ( surface != NULL )
  {
    polyData = surface->GetVtkPolyData( timeStep );

    // Extract surface normal from surface (if existent, otherwise use default)
    vtkPointData *pointData = polyData->GetPointData();
    if ( pointData != NULL )
    {
      vtkDataArray *normal = polyData->GetPointData()->GetVectors( "planeNormal" );
      if ( normal != NULL )
      {
        m_ObjectNormal[0] = normal->GetComponent( 0, 0 );
        m_ObjectNormal[1] = normal->GetComponent( 0, 1 );
        m_ObjectNormal[2] = normal->GetComponent( 0, 2 );
      }
    }
  }

  // Get geometry object
  m_Geometry = data->GetGeometry( timeStep );


  // Make sure that the data (if time-resolved) has enough entries;
  // if not, create the required extra ones (empty)
  data->Expand( timeStep+1 );


  switch (action->GetActionId())
  {
  case AcDONOTHING:
    ok = true;
    break;


  case AcCHECKOBJECT:
    {
      // Re-enable VTK interactor (may have been disabled previously)
      if ( renderWindowInteractor != NULL )
      {
        renderWindowInteractor->Enable();
      }

      // Check if we have a DisplayPositionEvent
      const DisplayPositionEvent *dpe =
        dynamic_cast< const DisplayPositionEvent * >( stateEvent->GetEvent() );
      if ( dpe == NULL )
      {
        ok = true;
        break;
      }

      // Check if an object is present at the current mouse position
      DataNode *pickedNode = dpe->GetPickedObjectNode();
      StateEvent *newStateEvent;
      if ( pickedNode == m_DataNode )
      {
        // Yes: object will be selected
        newStateEvent = new StateEvent( EIDYES );
      }
      else
      {
        // No: back to start state
        newStateEvent = new StateEvent( EIDNO );
      }

      this->HandleEvent( newStateEvent );

      ok = true;
      break;
    }

  case AcDESELECTOBJECT:
    {
      // Color object white
      m_DataNode->SetColor( 1.0, 1.0, 1.0 );
      RenderingManager::GetInstance()->RequestUpdateAll();

      // Colorize surface / wireframe as inactive
      this->ColorizeSurface( polyData,
        m_CurrentPickedPoint, -1.0 );

      ok = true;
      break;
    }

  case AcSELECTPICKEDOBJECT:
    {
      // Color object red
      m_DataNode->SetColor( 1.0, 0.0, 0.0 );
      RenderingManager::GetInstance()->RequestUpdateAll();

      // Colorize surface / wireframe dependend on distance from picked point
      this->ColorizeSurface( polyData,
        m_CurrentPickedPoint, 0.0 );

      ok = true;
      break;
    }

  case AcINITMOVE:
    {
      // Disable VTK interactor until MITK interaction has been completed
      if ( renderWindowInteractor != NULL )
      {
        renderWindowInteractor->Disable();
      }

      // Check if we have a DisplayPositionEvent
      const DisplayPositionEvent *dpe =
        dynamic_cast< const DisplayPositionEvent * >( stateEvent->GetEvent() );
      if ( dpe == NULL )
      {
        ok = true;
        break;
      }

      //DataNode *pickedNode = dpe->GetPickedObjectNode();

      m_InitialPickedPoint = m_CurrentPickedPoint;
      m_InitialPickedDisplayPoint = m_CurrentPickedDisplayPoint;

      if ( currentVtkRenderer != NULL )
      {
        vtkInteractorObserver::ComputeDisplayToWorld(
          currentVtkRenderer,
          m_InitialPickedDisplayPoint[0],
          m_InitialPickedDisplayPoint[1],
          0.0, //m_InitialInteractionPickedPoint[2],
          m_InitialPickedPointWorld );
      }


      // Make deep copy of current Geometry3D of the plane
      data->UpdateOutputInformation(); // make sure that the Geometry is up-to-date
      m_OriginalGeometry = static_cast< Geometry3D * >(
        data->GetGeometry( timeStep )->Clone().GetPointer() );

      ok = true;
      break;
    }

  case AcMOVE:
    {
      // Check if we have a DisplayPositionEvent
      const DisplayPositionEvent *dpe =
        dynamic_cast< const DisplayPositionEvent * >( stateEvent->GetEvent() );
      if ( dpe == NULL )
      {
        ok = true;
        break;
      }

      if ( currentVtkRenderer != NULL )
      {
        vtkInteractorObserver::ComputeDisplayToWorld(
          currentVtkRenderer,
          m_CurrentPickedDisplayPoint[0],
          m_CurrentPickedDisplayPoint[1],
          0.0, //m_InitialInteractionPickedPoint[2],
          m_CurrentPickedPointWorld );
      }


      Vector3D interactionMove;
      interactionMove[0] = m_CurrentPickedPointWorld[0] - m_InitialPickedPointWorld[0];
      interactionMove[1] = m_CurrentPickedPointWorld[1] - m_InitialPickedPointWorld[1];
      interactionMove[2] = m_CurrentPickedPointWorld[2] - m_InitialPickedPointWorld[2];

      if ( m_InteractionMode == INTERACTION_MODE_TRANSLATION )
      {
        Point3D origin = m_OriginalGeometry->GetOrigin();

        Vector3D transformedObjectNormal;
        data->GetGeometry( timeStep )->IndexToWorld(
          m_ObjectNormal, transformedObjectNormal );

        data->GetGeometry( timeStep )->SetOrigin(
          origin + transformedObjectNormal * (interactionMove * transformedObjectNormal) );
      }
      else if ( m_InteractionMode == INTERACTION_MODE_ROTATION )
      {
        if ( camera )
        {
          double vpn[3];
          camera->GetViewPlaneNormal( vpn );

          Vector3D viewPlaneNormal;
          viewPlaneNormal[0] = vpn[0];
          viewPlaneNormal[1] = vpn[1];
          viewPlaneNormal[2] = vpn[2];

          Vector3D rotationAxis =
            itk::CrossProduct( viewPlaneNormal, interactionMove );
          rotationAxis.Normalize();

          int *size = currentVtkRenderer->GetSize();
          double l2 =
            (m_CurrentPickedDisplayPoint[0] - m_InitialPickedDisplayPoint[0]) *
            (m_CurrentPickedDisplayPoint[0] - m_InitialPickedDisplayPoint[0]) +
            (m_CurrentPickedDisplayPoint[1] - m_InitialPickedDisplayPoint[1]) *
            (m_CurrentPickedDisplayPoint[1] - m_InitialPickedDisplayPoint[1]);

          double rotationAngle = 360.0 * sqrt(l2/(size[0]*size[0]+size[1]*size[1]));

          // Use center of data bounding box as center of rotation
          Point3D rotationCenter = m_OriginalGeometry->GetCenter();;

          // Reset current Geometry3D to original state (pre-interaction) and
          // apply rotation
          RotationOperation op( OpROTATE, rotationCenter, rotationAxis, rotationAngle );
          Geometry3D::Pointer newGeometry = static_cast< Geometry3D * >(
            m_OriginalGeometry->Clone().GetPointer() );
          newGeometry->ExecuteOperation( &op );
          data->SetClonedGeometry(newGeometry, timeStep);
        }
      }

      RenderingManager::GetInstance()->RequestUpdateAll();
      ok = true;
      break;
    }



  default:
    return Superclass::ExecuteAction( action, stateEvent );
  }

  return ok;
}