bool MainWindow::LoadDatasetInternal(QStringList files, QString targetFilename,
                                     bool bNoUserInteraction)
{

  if(files.empty()) {
    T_ERROR("No files!");
    return false;
  }

  PleaseWaitDialog pleaseWait(this);
  pleaseWait.SetText("Loading dataset, please wait  ...");
  pleaseWait.AttachLabel(&m_MasterController);

  // First check to make sure the list of files we've been given makes sense.
  for(QStringList::const_iterator fn = files.begin();
      fn != files.end(); ++fn) {
    if(fn->isEmpty()) {
      T_ERROR("Empty filelist");
      return false;
    }
    if(!SysTools::FileExists(std::string(fn->toAscii()))) {
      QString strText = tr("File %1 not found.").arg(*fn);
      T_ERROR("%s", strText.toStdString().c_str());
      if(!bNoUserInteraction) {
        ShowCriticalDialog( "Load Error", strText);
      }
      return false;
    }
  }

  // now determine if we've been given a UVF, and can just open it and be done,
  // or if we need to convert the files.
  // If we were given multiple files, we don't need to do any work; we *know*
  // that needs to be converted.
  shared_ptr<LuaScripting> ss(m_MasterController.LuaScript());
  bool needs_conversion = true;
  if(files.size() == 1) {
    // check to see if we need to convert this file to a supported format.

    if(!ss->cexecRet<bool>("tuvok.io.needsConversion",files[0].toStdString())) {
      needs_conversion = false;

      // It might also be the case that the checksum is bad && we need to
      // report an error, but we don't bother with the checksum if they've
      // asked us not to in the preferences.
      if(!m_bQuickopen && 
         false == ss->cexecRet<bool>("tuvok.io.verify", files[0].toStdString()))
      {
        QString strText = tr("File %1 appears to be a broken UVF file: "
                             "the header looks ok, "
                             "but the checksum does not match.").arg(files[0]);
        T_ERROR("%s", strText.toStdString().c_str());
        if (!bNoUserInteraction) {
          ShowCriticalDialog("Load Error", strText);
        }
        return false;
      }
    }
  }

  QString filename = files[0];
  if(needs_conversion) {
    if (!bNoUserInteraction && targetFilename.isEmpty()) {
      targetFilename = GetConvFilename(files[0]);
    }
    if (targetFilename.isEmpty()) {
      T_ERROR("User interaction disabled but no targetFilename given");
      return false;
    }

    std::list<std::string> stdfiles;
    for(QStringList::const_iterator fn = files.begin();
        fn != files.end(); ++fn) {
      stdfiles.push_back(std::string(fn->toAscii()));
    }

    PleaseWaitDialog pleaseWait(this);
    pleaseWait.SetText("Converting, please wait  ...");
    pleaseWait.AttachLabel(&m_MasterController);

    try {
      ss->cexec("tuvok.io.convertDataset", stdfiles, 
                std::string(targetFilename.toAscii()), m_strTempDir, 
                bNoUserInteraction, false);
      filename = targetFilename;
    } catch(const tuvok::io::IOException& e) {
      // create a (hopefully) useful error message
      std::ostringstream error;
      error << "Unable to convert ";
      std::copy(stdfiles.begin(), stdfiles.end(),
                std::ostream_iterator<std::string>(error, ", "));
      error << " into " << std::string(targetFilename.toAscii())
            << ": " << e.what();
      T_ERROR("%s", error.str().c_str());
      if(!bNoUserInteraction) {
        ShowCriticalDialog("Conversion Error", QString(error.str().c_str()));
      }

      // now close that dialog and bail.
      pleaseWait.close();
      return false;
    }

    pleaseWait.close();
  }

  RenderWindow *renderWin = NULL;
  try {
    renderWin = CreateNewRenderWindow(filename);

    if(renderWin == NULL) {
      T_ERROR("Renderwindow creation failed.  Bailing...");
      return false;
    }

    renderWin->GetQtWidget()->show();  // calls RenderWindowActive automatically
    UpdateMenus();
    AddFileToMRUList(filename);
  } catch(tuvok::io::DSBricksOversized&) {
    WARNING("Bricks are too large.  Querying the user to see if we should "
            "rebrick the dataset.");
    if(renderWin) { delete renderWin; renderWin = NULL; }
    if(bNoUserInteraction) {
      T_ERROR("Dataset needs rebricking but ImageVis3D is not running interactively.");
      return false;
    }
    if(QMessageBox::Yes ==
       QMessageBox::question(NULL, "Rebricking required",
        "The bricking scheme in this dataset is not compatible with "
        "your current brick size settings.  Do you want to convert this "
        "dataset so that it can be loaded?  Note that this operation can "
        "take as long as originally converting the data took!",
        QMessageBox::Yes, QMessageBox::No)) {
      // m_bIgnoreLoadDatasetFailure is an ugly hack, but I can't see any other
      // *good* options.
      // 
      // An alternative to m_bIgnoreLoadDatasetFailure is to throw a custom 
      // exception which would include bNoUserInteraction's value, and catch  
      // the exception in MainWindow::LoadDataset(std::string strFilename). 
      // (and MainWindow::LoadDataset(), and MainWindow::OpenRecentFile).
      // We would perform the rebricking upon catching the exception.
      // This method seemed equally hacky so I opted for the smallest code 
      // footprint and inserted this boolean flag.
      //
      // Also, we can use the flag when the user specifies 'no' on the dialog.
      // It doesn't make much sense to tell the user that we failed to
      // load the RenderWindow because they told us to not load it =P.
      //
      // The problem: if we reach here, we were in the process of creating
      // a series of Lua classes to support a render window. Since we are no
      // longer creating a viable render window (renderWin was deleted, and 
      // RebrickDataset is creating a new render window), lua needs to be 
      // notified and clean up any supporting classes.
      //
      // The only way to notify Lua is to do 1 of 2 things:
      // 1) Return false from this function (behaving as if the requested 
      //    dataset failed to load -- which it did).
      // 2) Or throw an exception and let lua capture and rethrow it.
      //
      // I opted for #1.
      RebrickDataset(filename, targetFilename, bNoUserInteraction);
      m_bIgnoreLoadDatasetFailure = true;
      return false;
    } else {
      m_bIgnoreLoadDatasetFailure = true;
      return false;
    }
  }

  if (renderWin) RenderWindowActive(renderWin);
  if (CheckForMeshCapabilities(bNoUserInteraction, files)) return true;

  if(renderWin) {
    LuaClassInstance ds = renderWin->GetRendererDataset();
    shared_ptr<LuaScripting> ss = m_MasterController.LuaScript();
    UINT64VECTOR3 dom_sz = ss->cexecRet<UINT64VECTOR3>(ds.fqName() + 
                                                       ".getDomainSize", 
                                                       size_t(0), 
                                                       size_t(0));
    // Disable lighting for 2D datasets (images).
    if(dom_sz[2] == 1) {
      checkBox_Lighting->setChecked(false);
      checkBox_Lighting->setEnabled(false);
      SetLighting(false);
    }
  }

  return true;
}