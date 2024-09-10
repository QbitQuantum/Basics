void BluetoothDeviceListItem::paintButton(Graphics &g, bool isMouseOverButton, bool isButtonDown) {
  auto bounds = getLocalBounds();
  auto inset = bounds.reduced(6, 4);
  auto w = bounds.getWidth(), h = bounds.getHeight();
  auto iconBounds = Rectangle<float>(w - h, h/5.0, h*0.6, h*0.6);

  auto listOutline = Path();
  listOutline.addRoundedRectangle(inset.toFloat(), 10.0f);
  g.setColour(findColour(ListBox::ColourIds::backgroundColourId));
  g.fillPath(listOutline);

  if (device->connected) {
    icons->checkIcon->setSize(h, h);
    icons->checkIcon->drawWithin(g, iconBounds, RectanglePlacement::fillDestination, 1.0f);
  }

//  icons->arrowIcon->setSize(h, h);
//  icons->arrowIcon->drawWithin(g, Rectangle<float>(w - (h/8), contentHeight + 8, contentHeight, contentHeight),
//                               RectanglePlacement::fillDestination, 1.0f);

  g.setFont(Font(getLookAndFeel().getTypefaceForFont(Font())));
  g.setFont(h * 0.5);
  g.setColour(findColour(ListBox::ColourIds::textColourId));
  g.drawText(getName(), inset.reduced(h * 0.2, 0), Justification::centredLeft, true);
}