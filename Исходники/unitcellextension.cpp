  QUndoCommand* UnitCellExtension::performAction(QAction *, GLWidget *widget)
  {
    // FIXME: this is bad mmmkay
    m_widget = widget;

    if (m_molecule == NULL)
      return NULL; // nothing we can do

    OBUnitCell *uc = m_molecule->OBUnitCell();

    if (uc == NULL) {
      // show warning and ask if the user wants to create a unit cell
      // (otherwise this extension isn't very useful)

      QMessageBox::StandardButton ret;
      ret = QMessageBox::warning(qobject_cast<QWidget*>(parent()),
                                 tr("Avogadro"),
                                 tr("This document is currently an isolated molecule.\n\n"
                                    "Do you want to create a crystal unit cell?"),
                                 QMessageBox::Yes
                                 | QMessageBox::No);
      if (ret == QMessageBox::Yes) {
        // Set some initial data (e.g., a box about the size of the molecule)
        // and one unit cell in each direction
        uc = new OBUnitCell;
        double estimatedSize = widget->radius() + 2.0;
        uc->SetData(estimatedSize, estimatedSize, estimatedSize,
                    90.0, 90.0, 90.0);
        m_molecule->setOBUnitCell(uc);

        widget->setUnitCells(1, 1, 1);
        widget->setUnitCellColor(m_color);
      } else { // do nothing -- user picked "Cancel"
        return NULL;
      }

    } // end if (existing unit cell or create a new one)

    // Don't emit signals while we update these
    disconnect(m_dialog, SIGNAL(unitCellDisplayChanged(int, int, int)),
            this, SLOT(unitCellDisplayChanged(int, int, int)));
    disconnect(m_dialog, SIGNAL(unitCellParametersChanged(double, double, double, double, double, double)),
            this, SLOT(unitCellParametersChanged(double, double, double, double, double, double)));

    m_dialog->aCells(widget->aCells());
    m_dialog->bCells(widget->bCells());
    m_dialog->cCells(widget->cCells());

    m_dialog->aLength(uc->GetA());
    m_dialog->bLength(uc->GetB());
    m_dialog->cLength(uc->GetC());

    m_dialog->alpha(uc->GetAlpha());
    m_dialog->beta(uc->GetBeta());
    m_dialog->gamma(uc->GetGamma());

    // OK, now we can handle signal/slots
    connect(m_dialog, SIGNAL(unitCellDisplayChanged(int, int, int)),
            this, SLOT(unitCellDisplayChanged(int, int, int)));
    connect(m_dialog, SIGNAL(unitCellParametersChanged(double, double, double, double, double, double)),
            this, SLOT(unitCellParametersChanged(double, double, double, double, double, double)));

    m_dialog->show();

    return NULL;
  }