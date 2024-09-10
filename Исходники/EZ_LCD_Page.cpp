HRESULT CEzLcdPage::SetText(HANDLE handle, LPCTSTR text, BOOL resetScrollingTextPosition)
{
    CLCDBase* myObject = GetObject(handle);

    if (NULL != myObject)
    {
        if (!((LG_STATIC_TEXT == myObject->GetObjectType() || LG_SCROLLING_TEXT == myObject->GetObjectType() || LG_RIGHTFOCUS_TEXT == myObject->GetObjectType() )))
            return E_FAIL;

        if (LG_STATIC_TEXT == myObject->GetObjectType())
        {
            CLCDText* staticText = static_cast<CLCDText*>(myObject);
            if (NULL == staticText)
                return E_FAIL;

            staticText->SetText(text);
            return S_OK;
        }
        else if (LG_SCROLLING_TEXT == myObject->GetObjectType())
        {
            CLCDStreamingText* streamingText = static_cast<CLCDStreamingText*>(myObject);
            if (NULL == streamingText)
                return E_FAIL;

            streamingText->SetText(text);
            if (resetScrollingTextPosition)
            {
                streamingText->ResetUpdate();
            }
            return S_OK;
        }
        else if (LG_RIGHTFOCUS_TEXT == myObject->GetObjectType())
        {
            CLCDText* rightFocusText = static_cast<CLCDText*>(myObject);
            if (NULL == rightFocusText)
                    return E_FAIL;
            
            rightFocusText->SetText(text);
            rightFocusText->CalculateExtent(true);
            // if out of focus, set alignment to right in order to follow what is written
            if (rightFocusText->GetHExtent().cx>=rightFocusText->GetSize().cx)
                rightFocusText->SetAlignment(DT_RIGHT);
            else
                rightFocusText->SetAlignment(DT_LEFT);

            return S_OK;
        }
    }

    return E_FAIL;
}