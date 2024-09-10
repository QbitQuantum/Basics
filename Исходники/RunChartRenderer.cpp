  void Create(const DialogLook &look, PixelSize size) {
    SingleWindow::Create(_T("RunChartRenderer"), size);

    const PixelRect rc = GetClientRect();

    WindowStyle with_border;
    with_border.Border();

    const PixelRect list_rc(0, 0, 250, rc.bottom - 30);

    type_list = new ListControl(*this, look, list_rc,
                                with_border, 25);

    type_list->SetItemRenderer(this);
    type_list->SetCursorHandler(this);
    type_list->SetLength(ARRAY_SIZE(chart_names));

    PixelRect chart_rc = rc;
    chart_rc.left = list_rc.right;
    chart.Create(*this, chart_rc, with_border);

    PixelRect button_rc = rc;
    button_rc.right = list_rc.right;
    button_rc.top = button_rc.bottom - 30;
    close_button.Create(*this, *button_look, _T("Close"), button_rc,
                        WindowStyle(),
                        *this, CLOSE);

    type_list->SetFocus();
  }