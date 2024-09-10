void MyFrame::OnQuery(wxCommandEvent& WXUNUSED(event))
{
    m_textCtrl->Clear();
    IAccessible* accessibleFrame = NULL;
    if (S_OK != AccessibleObjectFromWindow((HWND) GetHWND(), OBJID_CLIENT,
        IID_IAccessible, (void**) & accessibleFrame))
    {
        Log(wxT("Could not get object."));
        return;
    }
    if (accessibleFrame)
    {
        //Log(wxT("Got an IAccessible for the frame."));
        LogObject(0, accessibleFrame);
        Log(wxT("Checking children using AccessibleChildren()..."));

        // Now check the AccessibleChildren function works OK
        long childCount = 0;
        if (S_OK != accessibleFrame->get_accChildCount(& childCount))
        {
            Log(wxT("Could not get number of children."));
            accessibleFrame->Release();
            return;
        }
        else if (childCount == 0)
        {
            Log(wxT("No children."));
            accessibleFrame->Release();
            return;
        }


        long obtained = 0;
        VARIANT *var = new VARIANT[childCount];
        int i;
        for (i = 0; i < childCount; i++)
        {
            VariantInit(& (var[i]));
            var[i].vt = VT_DISPATCH;
        }

        if (S_OK == AccessibleChildren(accessibleFrame, 0, childCount, var, &obtained))
        {
            for (i = 0; i < childCount; i++)
            {
                IAccessible* childAccessible = NULL;
                if (var[i].pdispVal)
                {
                    if (var[i].pdispVal->QueryInterface(IID_IAccessible, (LPVOID*) & childAccessible) == S_OK)
                    {
                        var[i].pdispVal->Release();

                        wxString name, role;
                        GetInfo(childAccessible, 0, name, role);
                        wxString str;
                        str.Printf(wxT("Found child %s/%s"), name.c_str(), role.c_str());
                        Log(str);
                        childAccessible->Release();
                    }
                    else
                    {
                        var[i].pdispVal->Release();
                    }
                }
            }
        }
        else
        {
            Log(wxT("AccessibleChildren failed."));
        }
        delete[] var;


        accessibleFrame->Release();
    }
}