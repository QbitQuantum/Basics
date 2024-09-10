dspOrderActivityByProject::dspOrderActivityByProject(QWidget* parent, const char*, Qt::WindowFlags fl)
  : display(parent, "dspOrderActivityByProject", fl)
{
  setupUi(optionsWidget());
  setWindowTitle(tr("Order Activity by Project"));
  setListLabel(tr("Orders"));
  setReportName("OrderActivityByProject");
  setMetaSQLOptions("orderActivityByProject", "detail");
  setUseAltId(true);

  _run = false;

  list()->addColumn(tr("Name"),        _itemColumn,  Qt::AlignLeft,   true,  "name"   );
  list()->addColumn(tr("Status"),      _orderColumn, Qt::AlignLeft,   true,  "status"   );
  list()->addColumn(tr("Item #"),      _itemColumn,  Qt::AlignLeft,   true,  "item"   );
  list()->addColumn(tr("Description"), -1          , Qt::AlignLeft,   true,  "descrip" );
  list()->addColumn(tr("Account/Customer"), -1          , Qt::AlignLeft,   true,  "customer" );
  list()->addColumn(tr("Contact"), -1          , Qt::AlignLeft,   false,  "contact" );
  list()->addColumn(tr("City"), -1          , Qt::AlignLeft,   false,  "city" );
  list()->addColumn(tr("State"), -1          , Qt::AlignLeft,   false,  "state" );
  list()->addColumn(tr("Qty"),         _qtyColumn,   Qt::AlignRight,  true,  "qty"  );
  list()->addColumn(tr("UOM"),         _uomColumn,   Qt::AlignLeft,   true,  "uom"  );
  list()->addColumn(tr("Value"),      _qtyColumn,   Qt::AlignRight,  true,  "value"  );

  list()->addColumn(tr("Due Date"),      _dateColumn,   Qt::AlignRight,  true,  "due"  );
  list()->addColumn(tr("Assigned"),      _dateColumn,   Qt::AlignRight,  true,  "assigned"  );
  list()->addColumn(tr("Started"),      _dateColumn,   Qt::AlignRight,  true,  "started"  );
  list()->addColumn(tr("Completed"),      _dateColumn,   Qt::AlignRight,  true,  "completed"  );
  list()->addColumn(tr("Hrs. Budget"),      _qtyColumn,   Qt::AlignRight,  true,  "hrs_budget"  );
  list()->addColumn(tr("Hrs. Actual"),      _qtyColumn,   Qt::AlignRight,  true,  "hrs_actual"  );
  list()->addColumn(tr("Hrs. Balance"),      _qtyColumn,   Qt::AlignRight,  true,  "hrs_balance"  );
  list()->addColumn(tr("Exp. Budget"),      _priceColumn,   Qt::AlignRight,  true,  "exp_budget"  );
  list()->addColumn(tr("Exp. Actual"),      _priceColumn,   Qt::AlignRight,  true,  "exp_actual"  );
  list()->addColumn(tr("Exp. Balance"),      _priceColumn,   Qt::AlignRight,  true,  "exp_balance"  );

  list()->setPopulateLinear(true);

  disconnect(newAction(), SIGNAL(triggered()), this, SLOT(sNew()));
  connect(newAction(), SIGNAL(triggered()), this, SLOT(sNewProjectTask()));
  connect(_showSo, SIGNAL(checked()), this, SLOT(sFillList()));
  connect(_showPo, SIGNAL(checked()), this, SLOT(sFillList()));
  connect(_showWo, SIGNAL(checked()), this, SLOT(sFillList()));

  QToolButton * newBtn = (QToolButton*)toolBar()->widgetForAction(newAction());
  newBtn->setPopupMode(QToolButton::MenuButtonPopup);
  QAction *menuItem;
  QMenu * newMenu = new QMenu;
  menuItem = newMenu->addAction(tr("Task"), this, SLOT(sNewProjectTask()));
  menuItem->setEnabled(_privileges->check("MaintainAllProjects"));
  newMenu->addSeparator();
  menuItem = newMenu->addAction(tr("Sales Order"), this, SLOT(sNewSalesOrder()));
  menuItem->setEnabled(_privileges->check("MaintainSalesOrders"));
  menuItem = newMenu->addAction(tr("Purchase Order"),   this, SLOT(sNewPurchaseOrder()));
  menuItem->setEnabled(_privileges->check("MaintainPurchaseOrders"));
  menuItem = newMenu->addAction(tr("Work Order"),   this, SLOT(sNewWorkOrder()));
  menuItem->setEnabled(_privileges->check("MaintainWorkOrders"));
  newBtn->setMenu(newMenu);

}