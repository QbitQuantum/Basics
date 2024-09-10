/** Creates a StandardItemModel with the queried drugs. Items userData are DrugID. */
QStandardItemModel *DrugInteractionQuery::toStandardModel() const
{
    if (!m_StandardModel) {
        m_StandardModel = new QStandardItemModel;
    }

    // for all drugs
    QFont bold;
    bold.setBold(true);
    QVector<IDrug *> insertedDrugs;
    for(int i=0; i < m_Drugs.count(); ++i) {
        IDrug *drug = m_Drugs.at(i);
        if (insertedDrugs.contains(drug))
            continue;
        insertedDrugs.append(drug);
        // add a root item
        QStandardItem *root = new QStandardItem(drug->brandName());
        root->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        root->setData(drug->drugId());
        m_StandardModel->appendRow(root);
        // TODO: foreach component of the drug, append total daily dose
    }
    return m_StandardModel;
}