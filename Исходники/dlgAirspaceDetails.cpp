void
AirspaceDetailsWidget::Prepare(ContainerWindow &parent, const PixelRect &rc)
{
  const NMEAInfo &basic = CommonInterface::Basic();
  TCHAR buffer[64];

  AddMultiLine(airspace.GetName());

  if (!airspace.GetRadioText().empty())
    AddReadOnly(_("Radio"), nullptr, airspace.GetRadioText().c_str());

  AddReadOnly(_("Type"), nullptr, AirspaceFormatter::GetClass(airspace));

  AirspaceFormatter::FormatAltitude(buffer, airspace.GetTop());
  AddReadOnly(_("Top"), nullptr, buffer);

  AirspaceFormatter::FormatAltitude(buffer, airspace.GetBase());
  AddReadOnly(_("Base"), nullptr, buffer);

  if (warnings != nullptr) {
    const GeoPoint closest =
      airspace.ClosestPoint(basic.location, warnings->GetProjection());
    const fixed distance = closest.Distance(basic.location);

    FormatUserDistance(distance, buffer);
    AddReadOnly(_("Range"), nullptr, buffer);
  }
}