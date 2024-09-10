bool wxListCtrl::SetItem(wxListItem& info)
{
    const long id = info.GetId();
    QTreeWidgetItem *qitem = QtGetItem(id);
    if ( qitem != NULL )
    {
        if ((info.m_mask & wxLIST_MASK_TEXT) && !info.GetText().IsNull() )
            qitem->setText(info.GetColumn(), wxQtConvertString(info.GetText()));
        qitem->setTextAlignment(info.GetColumn(), wxQtConvertTextAlign(info.GetAlign()));

        if ( info.m_mask & wxLIST_MASK_DATA )
        {
            QVariant variant = qVariantFromValue(info.GetData());
            qitem->setData(0, Qt::UserRole, variant);
        }
        if (info.m_mask & wxLIST_MASK_STATE)
        {
            if ((info.m_stateMask & wxLIST_STATE_FOCUSED) &&
                (info.m_state & wxLIST_STATE_FOCUSED))
                    m_qtTreeWidget->setCurrentItem(qitem, 0);
            if (info.m_stateMask & wxLIST_STATE_SELECTED)
                qitem->setSelected(info.m_state & wxLIST_STATE_SELECTED);
        }
        if (info.m_mask & wxLIST_MASK_IMAGE)
        {
            if (info.m_image >= 0)
            {
                wxImageList *imglst = GetImageList(InReportView() ? wxIMAGE_LIST_SMALL : wxIMAGE_LIST_NORMAL);
                wxCHECK_MSG(imglst, false, "invalid listctrl imagelist");
                const wxBitmap* bitmap = imglst->GetBitmapPtr(info.m_image);
                if (bitmap != NULL)
                {
                    // set the new image:
                    qitem->setIcon( info.GetColumn(), QIcon( *bitmap->GetHandle() ));
                }
            }
            else
            {
                // remove the image using and empty qt icon:
                qitem->setIcon( info.GetColumn(), QIcon() );
            }
        }
        for (int col=0; col<GetColumnCount(); col++)
        {
            if ( info.GetFont().IsOk() )
                qitem->setFont(col, info.GetFont().GetHandle() );
            if ( info.GetTextColour().IsOk() )
                qitem->setTextColor(col, info.GetTextColour().GetHandle());
            if ( info.GetBackgroundColour().IsOk() )
                qitem->setBackgroundColor(col, info.GetBackgroundColour().GetHandle());
        }
        return true;
    }
    else
        return false;
}