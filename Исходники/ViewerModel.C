// The following selection functions interact directly with the selection model.
void ViewerModel::invertSelection()
{
   QItemSelection select;
   QItemSelection deselect;
   
   GLObjectList::iterator iter;
   for (iter = m_visibleObjects.begin(); iter != m_visibleObjects.end(); ++iter) {
       if ((*iter)->isSelected()) {
          deselect.select((*iter)->index(), (*iter)->index());
       }else {
          select.select((*iter)->index(), (*iter)->index());
       }
   }

   selectionChanged(deselect, QItemSelectionModel::Deselect);
   selectionChanged(select, QItemSelectionModel::Select);
}