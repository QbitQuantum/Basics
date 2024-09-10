void sipXTabbedCodecPage::OnSelect(wxCommandEvent &event)
{
    wxArrayInt selections;
    UtlString s;
    int index;

    if (!mbCodecByName)
    {
        int numSels = mpCodecList->GetSelections(selections);

        if (numSels)
        {
            mCodecName = "";

            for (int i=0; i<numSels; i++)
            {
                s = mpCodecList->GetString(selections[i]);
                if ((index = s.index(" ")) != UTL_NOT_FOUND)
                {
                    // Only get name up to first space
                    s = s.remove(index, s.length() - index);
                }
                mCodecName = mCodecName + s + " ";
            }
            mbCodecByName = true;
            mpCodecPref->Append("By name:");
            mpCodecPref->SetSelection(3);
            mCodecPref = 3;

            sipXmgr::getInstance().setAudioCodecByName((const char *)mCodecName.data());

            rebuildCodecList(0);
        }
    }
}