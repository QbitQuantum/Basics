// Initialize the dialog widgets and connect the signals/slots
void SatTrajDialog::createDialogContent()
{
  ui->setupUi(dialog);

  SatTrajMgr *module = GETSTELMODULE(SatTrajMgr);
  cButtons.append(new ColorButton(ui->l0colorbutton, module->getMeasTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setMeasTrColor(QColor)));
  cButtons.append(new ColorButton(ui->l1colorbutton, module->getTdTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setTdTrColor(QColor)));
  cButtons.append(new ColorButton(ui->l2colorbutton, module->getRefTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setRefTrColor(QColor)));
  cButtons.append(new ColorButton(ui->l3colorbutton, module->getEstTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setEstTrColor(QColor)));
  cButtons.append(new ColorButton(ui->l4colorbutton, module->getDebTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setDebTrColor(QColor)));
  cButtons.append(new ColorButton(ui->l5colorbutton, module->getAntTrColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setAntTrColor(QColor)));
  cButtons.append(new ColorButton(ui->textcolorbutton, module->getTextColor()));
  connect(cButtons.last(), SIGNAL(newColor(QColor)), module, SLOT(setTextColor(QColor)));

  connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveclose()));
  connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
  connect(ui->az_step_sb, SIGNAL(valueChanged(int)), module,
          SLOT(setAzIncr(int)));
  connect(ui->za_step_sb, SIGNAL(valueChanged(int)), module,
          SLOT(setZaIncr(int)));
  connect(this, SIGNAL(visibleChanged(bool)), this, SLOT(updateGui(bool)));
  connect(ui->tWin, SIGNAL(valueChanged(int)), this, SLOT(setMaxTws(int)));
  connect(ui->ant_extr_chb, SIGNAL(stateChanged(int)), this,
          SLOT(antExtrCheck(int)));
  connect(ui->good_sample_chb, SIGNAL(stateChanged(int)), this,
          SLOT(enableGoodSamp(int)));
  connect(ui->shm_chb, SIGNAL(stateChanged(int)), this, SLOT(enableShm(int)));
  connect(module, SIGNAL(changeEnableShm(bool)), ui->shm_chb, SLOT(setChecked(bool)));

  updateGuiFromSettings();
}