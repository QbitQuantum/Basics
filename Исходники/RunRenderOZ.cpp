    void Create(const DialogLook &look, PixelSize size) {
        SingleWindow::Create(_T("RunRenderOZ"), size);

        const PixelRect rc = GetClientRect();

        WindowStyle with_border;
        with_border.Border();

        PixelRect oz_rc = rc;
        oz_rc.left = oz_rc.right / 2;
        oz.Create(*this, oz_rc, with_border);

        const PixelRect list_rc(0, 0, rc.right / 2, rc.bottom - 30);

        type_list = new ListControl(*this, look, list_rc,
                                    with_border, 25);

        type_list->SetItemRenderer(this);
        type_list->SetCursorHandler(this);
        type_list->SetLength(NUM_OZ_TYPES);

        PixelRect button_rc = rc;
        button_rc.right = (rc.left + rc.right) / 2;
        button_rc.top = button_rc.bottom - 30;
        close_button.Create(*this, _T("Close"), ID_CLOSE, button_rc);

        oz.set_shape(ObservationZone::Shape::LINE);

        type_list->SetFocus();
    }