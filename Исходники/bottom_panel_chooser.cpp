BottomPanelChooser::BottomPanelChooser(
    BottomPanel* bottomPanel,
    QWidget *parent)
  : QToolBar(parent)
  , _bottomPanel(bottomPanel)
  , _displayMenu(NULL)
  , _menuAction(NULL)
  , _openMap(new QSignalMapper(this))
  , _displayMap(new QSignalMapper(this))
{
  this->setObjectName("DarkToolBar");

  _bottomPanel->installEventFilter(this);

  _displayMenu = new QMenu;

  QToolButton* toolButton = new QToolButton;
  //toolButton->setIcon(QIcon());
  toolButton->setMenu(_displayMenu);
  toolButton->setPopupMode(QToolButton::InstantPopup);

  _menuAction = this->QToolBar::addWidget(toolButton);
  _menuAction->setVisible(false);

  connect(_openMap, SIGNAL(mapped(QWidget*)), this, SLOT(xOnOpenTriggered(QWidget*)));
  connect(_displayMap, SIGNAL(mapped(QWidget*)), this, SLOT(xOnDisplayTriggered(QWidget*)));
}