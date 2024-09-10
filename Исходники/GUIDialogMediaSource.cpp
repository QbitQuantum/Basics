bool CGUIDialogMediaSource::ShowAndEditMediaSource(const CStdString &type, const CMediaSource &share)
{
    CStdString strOldName = share.strName;
    CGUIDialogMediaSource *dialog = (CGUIDialogMediaSource *)g_windowManager.GetWindow(WINDOW_DIALOG_MEDIA_SOURCE);
    if (!dialog) return false;
    dialog->Initialize();
    dialog->SetShare(share);
    dialog->SetTypeOfMedia(type, true);
    dialog->DoModal();
    bool confirmed(dialog->IsConfirmed());
    if (confirmed)
    {   // yay, add this share
        unsigned int i,j=2;
        bool bConfirmed=false;
        VECSOURCES* pShares = g_settings.GetSourcesFromType(type);
        CStdString strName = dialog->m_name;
        while (!bConfirmed)
        {
            for (i=0; i<pShares->size(); ++i)
            {
                if ((*pShares)[i].strName.Equals(strName))
                    break;
            }
            if (i < pShares->size() && (*pShares)[i].strName != strOldName) // found a match -  try next
                strName.Format("%s (%i)",dialog->m_name,j++);
            else
                bConfirmed = true;
        }

        CMediaSource newShare;
        newShare.FromNameAndPaths(type, strName, dialog->GetPaths());
        g_settings.UpdateShare(type, strOldName, newShare);
    }
    dialog->m_paths->Clear();
    return confirmed;
}