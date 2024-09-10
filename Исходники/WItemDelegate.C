WWidget *WItemDelegate::createEditor(const WModelIndex& index,
				     WFlags<ViewItemRenderFlag> flags) const
{
  IndexContainerWidget *const result =
      new IndexContainerWidget(index);
  result->setSelectable(true);

  WLineEdit *lineEdit = new WLineEdit();
  lineEdit->setText(asString(index.data(EditRole), textFormat_));
  lineEdit->enterPressed().connect
    (boost::bind(&WItemDelegate::doCloseEditor, this, result, true));
  lineEdit->escapePressed().connect
    (boost::bind(&WItemDelegate::doCloseEditor, this, result, false));
  lineEdit->escapePressed().preventPropagation();

  if (flags & RenderFocused)
    lineEdit->setFocus(true);

  // We use a layout so that the line edit fills the entire cell.
  // Somehow, this does not work with konqueror, but it does respond
  // properly to width, height being set to 100% !
  WApplication *app = WApplication::instance();
  if (app->environment().agent() != WEnvironment::Konqueror) {
    result->setLayout(new WHBoxLayout());
    result->layout()->setContentsMargins(1, 1, 1, 1);
    result->layout()->addWidget(lineEdit);
  } else {
    lineEdit->resize(WLength(100, WLength::Percentage),
		     WLength(100, WLength::Percentage));
    result->addWidget(lineEdit);
  }

  return result;
}