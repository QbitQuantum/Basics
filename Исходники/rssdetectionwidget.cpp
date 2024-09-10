RSSDetectionWidget::RSSDetectionWidget(WebView* view, QWidget* parent)
  : QFrame(parent, Qt::Popup)
  , view_(view)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
  setLineWidth(1);
  setMidLineWidth(2);

  gridLayout_ = new QGridLayout(this);
  gridLayout_->setMargin(5);
  gridLayout_->setSpacing(5);

  QWebFrame* frame = view_->page()->mainFrame();
  QWebElementCollection links = frame->findAllElements("link[type=\"application/rss+xml\"]");

  int cols = links.count() / 10 == 0 ? 1 : links.count() / 10;
  int row = 0;

  for (int i = 0; i < links.count(); i++) {
    QWebElement element = links.at(i);
    QString title = element.attribute("title");
    const QUrl url = QUrl::fromEncoded(element.attribute("href").toUtf8());
    if (url.isEmpty()) {
      continue;
    }

    if (title.isEmpty()) {
      title = tr("Untitled feed");
    }

    QPushButton* button = new QPushButton(this);
    button->setStyleSheet("QPushButton {text-align:left; border: none; padding: 0px;}"
                          "QPushButton:hover {color: #1155CC;}");
    button->setCursor(Qt::PointingHandCursor);
    button->setText(title);
    button->setToolTip(url.toString());
    button->setProperty("rss-url", url);
    button->setProperty("rss-title", title);

    int pos = i % cols > 0 ? (i % cols) * 2 : 0;

    gridLayout_->addWidget(button, row, pos);
    connect(button, SIGNAL(clicked()), this, SLOT(addRss()));

    if (i % cols == cols - 1) {
      row++;
    }
  }
}