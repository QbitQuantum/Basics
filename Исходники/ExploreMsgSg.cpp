/**************************************************************************************
    Function Name    :  SetHorizExtentListBox
    Input(s)         :  CListBox& omListBox
    Output           :  void
    Functionality    :  Sets the Listbox scroll to an extent so as to view the longest
                        string that is inserted.
    Member of        :  CExploreMsgSg
    Author(s)        :  Robin G.K.
    Date Created     :  27.10.2015
    Requirement ID   :  RS_FLX_08_09_10
***************************************************************************************/
void  CExploreMsgSg::SetHorizExtentListBox(CListBox& omListBox)
{
    // Set horizontal extent of the list
    // box to max string availaable
    // so that user can scroll
    CSize   sz;
    CString omStrText;
    CDC*  pDC = omListBox.GetDC();
    if ( pDC != nullptr)
    {
        int nDx = 0;
        for (int nCount = 0;
                nCount < omListBox.GetCount();
                nCount++)
        {
            omListBox.GetText( nCount, omStrText );
            // remove space
            omStrText.TrimRight();
            sz = pDC->GetTextExtent(omStrText);
            if (sz.cx > nDx)
            {
                nDx = sz.cx;
            }
        }
        omListBox.ReleaseDC(pDC);
        // Set the horizontal extent so every character of all
        // strings can be scrolled to.
        omListBox.SetHorizontalExtent(nDx);
    }
}