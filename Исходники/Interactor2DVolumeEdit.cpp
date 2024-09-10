bool Interactor2DVolumeEdit::ProcessMouseDownEvent( wxMouseEvent& event, RenderView* renderview )
{
  RenderView2D* view = ( RenderView2D* )renderview;
// UpdateCursor( event, view );

  if ( event.LeftDown() || ( event.RightDown() && event.LeftIsDown() ) )
  {
    if ( event.CmdDown() && event.ShiftDown() )
      return Interactor2D::ProcessMouseDownEvent( event, renderview );

    LayerCollection* lc = MainWindow::GetMainWindowPointer()->GetLayerCollectionManager()->GetLayerCollection( m_strLayerTypeName.c_str() );
    LayerVolumeBase* mri = ( LayerVolumeBase* )lc->GetActiveLayer();
    if ( (!mri || !mri->IsVisible()) ) //&& ( event.CmdDown() || m_nAction == EM_Polyline ) )
    {
      SendBroadcast( m_strLayerTypeName + "NotVisible", this );
    }
    else if ( !mri->IsEditable() ) //&& ( event.CmdDown() || m_nAction == EM_Polyline ) )
    {
      SendBroadcast( m_strLayerTypeName + "NotEditable", this );
    }
    else if ( m_strLayerTypeName == "MRI" && ((LayerMRI*)mri)->IsTransformed() )
    {
      SendBroadcast( m_strLayerTypeName + "NotEditableForTransformation", this );
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
          mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
        }
        else
        {
          m_bEditing = true;
          mri->SetVoxelByRAS( ras, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
        }
      }
      else if ( m_nAction == EM_Fill ) //&& ( event.CmdDown() ) )
      {
        mri->SaveForUndo( view->GetViewPlane() );
        mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
      }
      else if ( m_nAction == EM_Polyline || m_nAction == EM_Livewire )
      {
        mri->SaveForUndo( view->GetViewPlane() );
        if ( event.CmdDown() )
        {
          mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
        }
        else
        {
          m_bEditing = true;
          double ras2[3];
          view->GetCursor2D()->ClearInterpolationPoints();
          view->GetCursor2D()->GetPosition( ras2 );
          view->GetCursor2D()->SetPosition( ras );
          view->GetCursor2D()->SetPosition2( ras );
          if ( m_dPolylinePoints.size() > 0 )
          {
            if ( m_nAction == EM_Polyline )
              mri->SetVoxelByRAS( ras, ras2, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
            else
              mri->SetLiveWireByRAS( ras, ras2, view->GetViewPlane() );
          }
          else
          {
            // mri->SaveForUndo( view->GetViewPlane() );
            m_dPolylinePoints.push_back( ras[0] );
            m_dPolylinePoints.push_back( ras[1] );
            m_dPolylinePoints.push_back( ras[2] );
            view->GetCursor2D()->SetPosition( ras );
          }
  
          if ( view->GetCapture() == view )
            view->ReleaseMouse();
          view->CaptureMouse();
        }
      }
      else if ( m_nAction == EM_ColorPicker && mri->IsTypeOf( "MRI" ) )
      {
        if ( event.CmdDown() )
        {
          mri->SaveForUndo( view->GetViewPlane() );
          mri->FloodFillByRAS( ras, view->GetViewPlane(), !event.ShiftDown() && !event.RightIsDown() );
        }
        else
        {
          double dValue = ((LayerMRI*)mri)->GetVoxelValue( ras );
          if ( dValue != 0 )
          {
            mri->SetFillValue( (float)dValue );
            mri->SendBroadcast( "LayerActorUpdated", mri );
          }
        }
      }
      else if ( m_nAction == EM_Contour && mri->IsTypeOf( "MRI" ) )
      {
        LayerMRI* mri_ref = (LayerMRI*)MainWindow::GetMainWindowPointer()->GetBrushProperty()->GetReferenceLayer();
        if ( !mri_ref )
        {
          SendBroadcast( m_strLayerTypeName + "ReferenceNotSet", this );
          return false;
        }
          
        Contour2D* c2d = view->GetContour2D();
        if ( event.CmdDown() && event.AltDown() )
        {
          double dValue = mri_ref->GetVoxelValue( ras );
          if ( dValue != 0 )
          {
            m_bEditing = true;
            c2d->SetInput( mri_ref->GetSliceImageData( view->GetViewPlane() ), dValue, ras[view->GetViewPlane()], mri_ref->GetActiveFrame() );
            c2d->SetVisible( true );
            view->NeedRedraw();
          }
          else if ( c2d->IsVisible() )
          {
            m_bEditing = true;
          }
        }
        else if ( event.CmdDown() && !event.AltDown() )
        {
          mri->SaveForUndo( view->GetViewPlane() );
          ((LayerMRI*)mri)->FloodFillByContour2D( ras, c2d );
        }
        else if ( event.ShiftDown() )
        {
          m_bEditing = true;
          c2d->RemoveLine( ras, ras );
          view->NeedRedraw();
        }
        else
        {
          m_bEditing = true;
          c2d->AddLine( ras, ras );
          view->NeedRedraw();
        }
        
      }
      else
        return Interactor2D::ProcessMouseDownEvent( event, renderview );
    }

    return false;
  }
  else if ( m_bEditing )
  {
    m_bEditing = false;
    if ( m_nAction == EM_Polyline || m_nAction == EM_Livewire )
    {
      if ( event.MiddleDown() )
      {
        view->GetCursor2D()->Update();
        view->NeedRedraw();
      }
      else if ( event.RightDown() )
      {
        if ( m_dPolylinePoints.size() > 0 && m_nAction == EM_Polyline )
        {
          LayerCollection* lc = MainWindow::GetMainWindowPointer()->GetLayerCollection( m_strLayerTypeName.c_str() );
          LayerVolumeBase* mri = ( LayerVolumeBase* )lc->GetActiveLayer();

          double ras1[3] = { m_dPolylinePoints[0], m_dPolylinePoints[1], m_dPolylinePoints[2] };
          double ras2[3];
          view->GetCursor2D()->GetPosition( ras2 );
          view->GetCursor2D()->SetPosition2( ras2 );
          view->GetCursor2D()->SetPosition( ras1 );
          mri->SetVoxelByRAS( ras1, ras2, view->GetViewPlane(), !event.ShiftDown() );
        }
        else
        {
          // mri->SetLiveWireByRAS( ras1, ras2, view->GetViewPlane() );
          view->GetCursor2D()->Update();
          view->NeedRedraw();
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