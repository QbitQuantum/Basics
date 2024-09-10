void mainFrameImp::romSelected( wxFileDirPickerEvent& event ){
    gameManager::gm->romSelected(event.GetPath().ToStdString());
}