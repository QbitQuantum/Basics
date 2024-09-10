bool Interactor2DRegionEdit::ProcessMouseDownEvent( wxMouseEvent& event, RenderView* renderview )
{
  RenderView2D* view = ( RenderView2D* )renderview;
// UpdateCursor( event, view );

  if ( event.LeftDown() )
  {
    // if ( event.CmdDown() )
    //  return Interactor2D::ProcessMouseDownEvent( event, renderview );

    LayerCollection* lc = MainWindow::GetMainWindowPointer()->GetLayerCollectionManager()->GetLayerCollection( "MRI" );
    LayerMRI* mri = ( LayerMRI* )lc->GetActiveLayer();
    if ( (!mri || !mri->IsVisible()) ) //&& ( event.CmdDown() || m_nAction == EM_Polyline ) )
    {
      SendBroadcast( "MRINotVisible", this );
    }
    else if ( !mri->IsEditable() ) //&& ( event.CmdDown() || m_nAction == EM_Polyline ) )
    {
      SendBroadcast( "MRINotEditable", this );
    }
    else
    {
      m_nMousePosX = event.GetX();
      m_nMousePosY = event.GetY();

      double ras[3];
      view->MousePositionToRAS( m_nMousePosX, m_nMousePosY, ras );
      if ( m_nAction == EM_Freehand ) //&& ( event.CmdDown() ) )
      {
        mri->SaveForUndo( view->GetViewPlane() );
        if ( event.CmdDown() )
        {
          mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() );
        }
        else
        {
          m_bEditing = true;
          mri->SetVoxelByRAS( ras, view->GetViewPlane(), !event.ShiftDown() );
        }
      }
      else if ( m_nAction == EM_Fill ) //&& ( event.CmdDown() ) )
      {
        mri->SaveForUndo( view->GetViewPlane() );
        mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() );
      }
      else if ( m_nAction == EM_Polyline )
      {
        m_bEditing = true;
        double ras2[3];
        view->GetCursor2D()->GetPosition( ras2 );
        view->GetCursor2D()->SetPosition( ras );
        view->GetCursor2D()->SetPosition2( ras );
        if ( m_dPolylinePoints.size() > 0 )
        {
          mri->SetVoxelByRAS( ras, ras2, view->GetViewPlane(), !event.ShiftDown() );
        }
        else
        {
          mri->SaveForUndo( view->GetViewPlane() );
          m_dPolylinePoints.push_back( ras[0] );
          m_dPolylinePoints.push_back( ras[1] );
          m_dPolylinePoints.push_back( ras[2] );
        }

        if ( view->GetCapture() == view )
          view->ReleaseMouse();
        view->CaptureMouse();
      }
      else
        return Interactor2D::ProcessMouseDownEvent( event, renderview );
    }

    return false;
  }
  else if ( m_bEditing )
  {
    m_bEditing = false;
    if ( m_nAction == EM_Polyline )
    {
      if ( event.MiddleDown() )
      {
        view->GetCursor2D()->Update();
        view->NeedRedraw();
      }
      else if ( event.RightDown() )
      {
        if ( m_dPolylinePoints.size() > 0 )
        {
          LayerCollection* lc = MainWindow::GetMainWindowPointer()->GetLayerCollection( "MRI" );
          LayerMRI* mri = ( LayerMRI* )lc->GetActiveLayer();

          double ras1[3] = { m_dPolylinePoints[0], m_dPolylinePoints[1], m_dPolylinePoints[2] };
          double ras2[3];
          view->GetCursor2D()->GetPosition( ras2 );
          view->GetCursor2D()->SetPosition2( ras2 );
          view->GetCursor2D()->SetPosition( ras1 );
          mri->SetVoxelByRAS( ras1, ras2, view->GetViewPlane(), !event.ShiftDown() );
        }
      }
    }

    m_dPolylinePoints.clear();
    if ( view->GetCapture() == view )
      view->ReleaseMouse();

    return false;
  }
  return Interactor2D::ProcessMouseDownEvent( event, renderview ); // pass down the event
}