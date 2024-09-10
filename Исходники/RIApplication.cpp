//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
bool RIApplication::closeProject(bool askToSaveIfDirty)
{
    RIMainWindow* mainWnd = RIMainWindow::instance();

    terminateProcess();

    if (false)
    {
        QMessageBox msgBox(mainWnd);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("The project being closed has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        //msgBox.setDefaultButton(QMessageBox::Save);

        int ret = msgBox.exec();
        if (ret == QMessageBox::Save)
        {
            //m_sceneManager->saveAll();
        }
        else if (ret == QMessageBox::Cancel)
        {
            return false;
        }
    }

    mainWnd->cleanupGuiBeforeProjectClose();

    caf::EffectGenerator::clearEffectCache();
    m_project->close();

    onProjectOpenedOrClosed();

    return true;
    
}