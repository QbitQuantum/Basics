void
ShowPortMonitor(SingleWindow &parent, const DialogLook &dialog_look,
                const TerminalLook &terminal_look,
                DeviceDescriptor &_device)
{
  device = &_device;

  /* create the dialog */

  WindowStyle dialog_style;
  dialog_style.Hide();
  dialog_style.ControlParent();

  TCHAR buffer[64];
  StaticString<128> caption;
  caption.Format(_T("%s: %s"), _("Port monitor"),
                 device->GetConfig().GetPortName(buffer, ARRAY_SIZE(buffer)));

  dialog = new WndForm(parent, dialog_look, parent.GetClientRect(),
                       caption, dialog_style);

  ContainerWindow &client_area = dialog->GetClientAreaWindow();

  ButtonPanel buttons(client_area, dialog_look);
  buttons.Add(_("Close"), OnCloseClicked);
  buttons.Add(_("Clear"), OnClearClicked);
  buttons.Add(_("Reconnect"), OnReconnectClicked);
  buttons.Add(_("Pause"), OnPauseClicked);

  const PixelRect rc = buttons.UpdateLayout();

  /* create the terminal */

  terminal = new TerminalWindow(terminal_look);
  terminal->set(dialog->GetClientAreaWindow(), rc.left, rc.top,
                rc.right - rc.left, rc.bottom - rc.top);

  bridge = new PortTerminalBridge(*terminal);
  device->SetMonitor(bridge);
  paused = false;

  /* run it */

  dialog->ShowModal();

  device->SetMonitor(NULL);
  delete bridge;
  delete terminal;
  delete dialog;
}