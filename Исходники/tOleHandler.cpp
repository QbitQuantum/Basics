void tOleHandler::SizeSet(LPSIZEL pszl, BOOL fDevice, BOOL fInformObj)
    {
    SIZEL           szl;

    if (!fDevice)
        {
        szl=*pszl;
        m_rcl.right =pszl->cx+m_rcl.left;
        m_rcl.bottom=pszl->cy+m_rcl.top;
        }
    else
        {
        RECT        rc;

        SetRect(&rc, (int)pszl->cx, (int)pszl->cy, 0, 0);
        RectConvertMappings(&rc, NULL, FALSE);

        m_rcl.right =(long)rc.left+m_rcl.left;
        m_rcl.bottom=(long)rc.top+m_rcl.top;

        SETSIZEL(szl, (long)rc.left, (long)rc.top);
        }

    //Tell OLE that this object was resized.
    if (NULL!=m_pIOleObject && fInformObj)
        {
        HRESULT     hr;
        BOOL        fRun=FALSE;

        //Convert our LOMETRIC into HIMETRIC by *=10
        szl.cx*=10;
        szl.cy*=-10;    //Our size is stored negative.

        /*
         * If the MiscStatus bit of OLEMISC_RECOMPOSEONRESIZE
         * is set, then we need to run the object before calling
         * SetExtent to make sure it has a real chance to
         * re-render the object.  We have to update and close
         * the object as well after this happens.
         */

        if (OLEMISC_RECOMPOSEONRESIZE & m_grfMisc)
            {
            if (!OleIsRunning(m_pIOleObject))
                {
                OleRun(m_pIOleObject);
                fRun=TRUE;
                }
            }

        hr=m_pIOleObject->SetExtent(m_fe.dwAspect, &szl);

        /*
         * If the object is not running and it does not have
         * RECOMPOSEONRESIZE, then SetExtent fails.  Make
         * sure that we call SetExtent again (by just calling
         * SizeSet here again) when we next run the object.
         */
        if (SUCCEEDED(hr))
            {
            m_fSetExtent=FALSE;

            if (fRun)
                {
                m_pIOleObject->Update();
                m_pIOleObject->Close(OLECLOSE_SAVEIFDIRTY);
                }
            }
        else
            {
            if (OLE_E_NOTRUNNING==GetScode(hr))
                m_fSetExtent=TRUE;
            }
        }

    return;
    }