void MyFrame::OnLoadLinearModes(wxCommandEvent& event)
{
  wxFileDialog *dlg = new wxFileDialog(this, _T("Load linear modes"), uiState.currentWorkingDirectory, _T(""), _T("Modal Matrix Files(*.Ulin)|*.Ulin|Modal Matrix Files(*.U)|*.U|All files(*.*)|*.*"), wxFD_OPEN /*| wxHIDE_READONLY*/, wxDefaultPosition);

  if ( dlg->ShowModal() == wxID_OK )
  {
    wxString linearModesFilename( dlg->GetPath());
    SaveCurrentWorkingDirectory(linearModesFilename);
    if( !linearModesFilename.empty() )
    {
      int newr;
      double * newLinearModes = NULL;

      int n1;
      SetCursor(*wxHOURGLASS_CURSOR);
      const char * filename = linearModesFilename.mb_str();
      int code = ReadMatrixFromDisk((char*)filename, &n1, &newr, &newLinearModes);
      SetCursor(*wxSTANDARD_CURSOR);

      if (code != 0)
      {
        this->errMsg( _T("Loading error"),  _T("Unable to load linear modes from ") + linearModesFilename );
        dlg->Destroy();
        return;
      }

      if (n1 != 3 * precomputationState.simulationMesh->getNumVertices())
      {
        this->errMsg( _T("Loading error"), _T("The number of vertices in ") + linearModesFilename + _T(" does not match the simulation mesh."));
        free(newLinearModes);
        dlg->Destroy();
        return;
      }

      if (precomputationState.frequenciesAvailable)
      {
        // check that the number of modes is consistent with the existing number of frequencies
        if (newr != precomputationState.rLin)
        {
          wxMessageDialog * confirmationDialog = new wxMessageDialog (this, _T("Warning: number of existing frequencies does not match the number of modes. Delete existing frequencies?"), _T("Mismatch in the number of frequencies"), wxYES_NO | wxICON_EXCLAMATION);

          if (confirmationDialog->ShowModal() != wxID_YES)
          {
            free(newLinearModes);
            delete(confirmationDialog);
            dlg->Destroy();
            return;
          }
          else
          {
            delete(confirmationDialog);
            free(precomputationState.frequencies);
            precomputationState.frequenciesAvailable = false;
          }
        }
      }

      // success
      delete(precomputationState.linearModalMatrix);
      precomputationState.rLin = newr;
      precomputationState.linearModalMatrix = new ModalMatrix(
        precomputationState.simulationMesh->getNumVertices(), precomputationState.rLin, newLinearModes);
      free(newLinearModes);

      precomputationState.linearModesAvailable = true;

      uiState.numComputedNonLinearModes = 2 * (precomputationState.rLin - precomputationState.numRigidModes);
      uiState.eraseRangeHi = precomputationState.rLin;

      modeSelectionControl->SetValue(1);

      SelectView(UIState::VIEW_LINEAR_MODES);
      SetAutoRenderingMagnitude(precomputationState.linearModalMatrix);

      UpdateMenus();

      myGLCanvas->UpdateLinearModesRenderData();

      Refresh();
    }
  }

  dlg->Destroy();
}