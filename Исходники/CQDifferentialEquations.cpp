void CQDifferentialEquations::slotUpdateWidget()
{
  bool hasContents = true;
  //std::ostringstream mml;
  mml.str("");

  bool expand, expandAll;

  switch (comboBoxFunctions->currentItem())
    {
      case 0:
        expand = false;
        expandAll = false;
        break;

      case 1:
        expand = true;
        expandAll = false;
        break;

      default:
        expand = true;
        expandAll = true;
        break;
    };

  bool parameterAsNumbers = false;

  if (comboBoxParameters->currentItem() == 0)
    parameterAsNumbers = true;

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CMMLOutput::writeDifferentialEquations(mml, (*CCopasiRootContainer::getDatamodelList())[0]->getModel(), parameterAsNumbers, expand, expandAll);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());

  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mpMMLWidget->setContent(FROM_UTF8(mml.str()));
  mpMMLWidget->setBaseFontPointSize(qApp->font().pointSize());
  mpMMLWidget->setFontName(QtMmlWidget::NormalFont, qApp->font().family());

  mpScrollView->resizeContents(mpMMLWidget->sizeHint().width(), mpMMLWidget->sizeHint().height());

  if (tmp) tmp->unsetCursor();

  mpSaveButton->setEnabled(hasContents);
}