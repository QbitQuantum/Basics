XERCES_CPP_NAMESPACE_USE

PlotSetImp::PlotSetImp(const string& id, const string& plotSetName, QWidget* pParent) :
   QTabWidget(pParent),
   SessionItemImp(id, plotSetName),
   mpExplorer(Service<SessionExplorer>().get(), SIGNAL_NAME(SessionExplorer, AboutToShowSessionItemContextMenu),
      Slot(this, &PlotSetImp::updateContextMenu)),
   mpAssociatedView(SIGNAL_NAME(View, Renamed), Slot(this, &PlotSetImp::viewRenamed)),
   mpSelector(NULL)
{
   // Initialization
   setTabPosition(QTabWidget::South);
   setTabShape(QTabWidget::Triangular);

   // Make this a little taller than default, as combobox and pushbutton was not fully vertically displayed otherwise.
   this->setStyleSheet("QTabBar::tab { height: 5ex;}");

   QPushButton* pSelectorButton = new QPushButton(QIcon(":/icons/PlotSelection"),"", this);
   VERIFYNRV(NULL != pSelectorButton);
   this->setCornerWidget(pSelectorButton, Qt::BottomLeftCorner);

   // Get rid of extra horizontal border.
   pSelectorButton->setMaximumWidth(20);

   // Add menu to be displayed when button pressed.
   mpSelector = new QMenu(pSelectorButton);
   VERIFYNR(connect(mpSelector, SIGNAL(triggered(QAction*)), this, SLOT(handlePlotSelected(QAction*))));
   pSelectorButton->setMenu(mpSelector);

   // Connections
   VERIFYNR(connect(this, SIGNAL(currentChanged(int)), this, SLOT(activatePlot(int))));
   VERIFYNR(Service<DesktopServices>()->attach(SIGNAL_NAME(DesktopServices, AboutToShowContextMenu),
      Slot(this, &PlotSetImp::updateContextMenu)));
}