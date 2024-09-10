void
DeviceListWidget::OnPaintItem(Canvas &canvas, const PixelRect rc, unsigned idx)
{
  assert(idx < NUMDEV);

  const DeviceConfig &config =
    CommonInterface::SetSystemSettings().devices[idx];
  const Flags flags(*items[idx]);

  const unsigned margin = Layout::GetTextPadding();

  TCHAR port_name_buffer[128];
  const TCHAR *port_name =
    config.GetPortName(port_name_buffer, ARRAY_SIZE(port_name_buffer));

  StaticString<256> text(_T("A: "));
  text[0u] += idx;

  if (config.UsesDriver()) {
    const TCHAR *driver_name = FindDriverDisplayName(config.driver_name);

    text.AppendFormat(_("%s on %s"), driver_name, port_name);
  } else {
    text.append(port_name);
  }

  canvas.Select(*look.list.font);
  canvas.DrawText(rc.left + margin, rc.top + margin, text);

  /* show a list of features that are available in the second row */

  StaticString<256> buffer;
  const TCHAR *status;
  if (flags.alive) {
    if (flags.location) {
      buffer = _("GPS fix");
    } else if (flags.gps) {
      /* device sends GPGGA, but no valid location */
      buffer = _("Bad GPS");
    } else {
      buffer = _("Connected");
    }

    if (flags.baro) {
      buffer.append(_T("; "));
      buffer.append(_("Baro"));
    }

    if (flags.airspeed) {
      buffer.append(_T("; "));
      buffer.append(_("Airspeed"));
    }

    if (flags.vario) {
      buffer.append(_T("; "));
      buffer.append(_("Vario"));
    }

    if (flags.traffic)
      buffer.append(_T("; FLARM"));

    if (flags.debug) {
      buffer.append(_T("; "));
      buffer.append(_("Debug"));
    }

    status = buffer;
  } else if (config.IsDisabled()) {
    status = _("Disabled");
  } else if (is_simulator() || !config.IsAvailable()) {
    status = _("N/A");
  } else if (flags.open) {
    buffer = _("No data");

    if (flags.debug) {
      buffer.append(_T("; "));
      buffer.append(_("Debug"));
    }

    status = buffer;
#ifdef ANDROID
  } else if ((config.port_type == DeviceConfig::PortType::RFCOMM ||
              config.port_type == DeviceConfig::PortType::RFCOMM_SERVER) &&
             !BluetoothHelper::isEnabled(Java::GetEnv())) {
    status = _("Bluetooth is disabled");
#endif
  } else if (flags.duplicate) {
    status = _("Duplicate");
  } else if (flags.error) {
    if (error_messages[idx].empty())
      status = _("Error");
    else
      status = error_messages[idx].c_str();
  } else {
    status = _("Not connected");
  }

  canvas.Select(look.small_font);
  canvas.DrawText(rc.left + margin, rc.top + 2 * margin + font_height,
                  status);
}