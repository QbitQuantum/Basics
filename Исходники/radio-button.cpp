void pRadioButton::setImage(const image& image, Orientation orientation) {
  qtRadioButton->setIconSize(QSize(image.width, image.height));
  qtRadioButton->setIcon(CreateIcon(image));
  qtRadioButton->setStyleSheet("text-align: top;");
  switch(orientation) {
  case Orientation::Horizontal: qtRadioButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); break;
  case Orientation::Vertical:   qtRadioButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);  break;
  }
}