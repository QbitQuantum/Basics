void ConvolveMatrixEffectConfigWidget::editKernel()
{
    if (!m_effect) {
        return;
    }

    QVector<qreal> oldKernel = m_effect->kernel();
    QPoint kernelSize = m_effect->order();
    m_matrixModel->setMatrix(oldKernel, kernelSize.y(), kernelSize.x());
    connect(m_matrixModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(kernelChanged()));

    QPointer<QDialog> dlg = new QDialog(this);
    QTableView *table = new QTableView(dlg);
    table->setModel(m_matrixModel);
    table->horizontalHeader()->hide();
    table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->hide();
    table->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    dlg->setLayout(mainLayout);
    mainLayout->addWidget(table);
    if (dlg->exec() == QDialog::Accepted) {
        m_effect->setKernel(m_matrixModel->matrix());
        emit filterChanged();
    } else {
        m_effect->setKernel(oldKernel);
    }
    delete dlg;

    disconnect(m_matrixModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(kernelChanged()));
}