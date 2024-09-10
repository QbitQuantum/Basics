//--------------------------------------------------------------------------------------------------
/// 
//--------------------------------------------------------------------------------------------------
QItemSelection PdmUiTableViewModel::modelIndexFromPdmObject(PdmObjectHandle* pdmObject)
{
    QItemSelection itemSelection;

    for (int i = 0; i < this->rowCount(); i++)
    {
        PdmObjectHandle* obj = this->pdmObjectForRow(i);
        if (obj == pdmObject)
        {
            // Currently selection only on model index, can be exteded to select whole row
            itemSelection.select(this->createIndex(i, 0), this->createIndex(i, 0));
        }
    }

    return itemSelection;
}