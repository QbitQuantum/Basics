        void NWindow::Draw(HDC hDc)
        {
            GUARD_SCOPE(false, _T("NWindow Draw takes too long"));
            Base::NRect clientRect;
            ::GetClientRect(window_, clientRect);
            render_->Init(hDc, clientRect);

            Base::NRect clipRect;
            int nResult = GetClipBox(hDc, clipRect);
            if(nResult == NULLREGION)
                ::GetClientRect(window_, clipRect);
            OnDraw(render_, clipRect);

            render_->DrawBack(IsLayered());
        }