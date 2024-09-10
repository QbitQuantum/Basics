void
dlgQuickMenuShowModal(SingleWindow &parent)
{
  const Menu *menu = InputEvents::GetMenu(_T("RemoteStick"));
  if (menu == NULL)
    return;

  const DialogLook &dialog_look = UIGlobals::GetDialogLook();

  WindowStyle dialogStyle;
  dialogStyle.Hide();
  dialogStyle.ControlParent();

  wf = new WndForm(parent, dialog_look, parent.GetClientRect(),
                   _T("Quick Menu"), dialogStyle);

  ContainerWindow &client_area = wf->GetClientAreaWindow();

  PixelRect r = client_area.GetClientRect();

  WindowStyle grid_view_style;
  grid_view_style.ControlParent();

  grid_view = new GridView(client_area,
                           r.left, r.top,
                           r.right - r.left, r.bottom - r.top,
                           dialog_look, grid_view_style);

  WindowStyle buttonStyle;
  buttonStyle.TabStop();

  for (unsigned i = 0; i < menu->MAX_ITEMS; ++i) {
    if (buttons.full())
      continue;

    const MenuItem &menuItem = (*menu)[i];
    if (!menuItem.IsDefined())
      continue;

    TCHAR buffer[100];
    ButtonLabel::Expanded expanded =
      ButtonLabel::Expand(menuItem.label, buffer, ARRAY_SIZE(buffer));
    if (!expanded.visible)
      continue;

    PixelRect button_rc;
    button_rc.left = 0;
    button_rc.top = 0;
    button_rc.right = 80;
    button_rc.bottom = 30;
    WndButton *button =
      new WndCustomButton(*grid_view, dialog_look, expanded.text,
                          button_rc, buttonStyle, OnButtonClicked);
    button->SetEnabled(expanded.enabled);

    buttons.append(button);
    events.append(menuItem.event);
  }

  grid_view->SetItems(buttons);
  SetFormDefaultFocus();
  SetFormCaption();

  wf->SetKeyDownNotify(FormKeyDown);

  wf->ShowModal();

  for (auto it = buttons.begin(), end = buttons.end(); it != end; ++it)
    delete *it;

  buttons.clear();
  events.clear();

  delete wf;
  delete grid_view;
}