void QgsFieldModel::updateModel()
{
  if ( mLayer )
  {
    QgsFields newFields = mLayer->fields();
    if ( mFields.toList() != newFields.toList() )
    {
      // Try to handle two special cases: addition of a new field and removal of a field.
      // It would be better to listen directly to attributeAdded/attributeDeleted
      // so we would not have to check for addition/removal here.

      if ( mFields.count() == newFields.count() - 1 )
      {
        QgsFields tmpNewFields = newFields;
        tmpNewFields.remove( tmpNewFields.count() - 1 );
        if ( mFields.toList() == tmpNewFields.toList() )
        {
          // the only change is a new field at the end
          beginInsertRows( QModelIndex(), mFields.count(), mFields.count() );
          mFields = newFields;
          endInsertRows();
          return;
        }
      }

      if ( mFields.count() == newFields.count() + 1 )
      {
        QgsFields tmpOldFields = mFields;
        tmpOldFields.remove( tmpOldFields.count() - 1 );
        if ( tmpOldFields.toList() == newFields.toList() )
        {
          // the only change is a field removed at the end
          beginRemoveRows( QModelIndex(), mFields.count() - 1, mFields.count() - 1 );
          mFields = newFields;
          endRemoveRows();
          return;
        }

        for ( int i = 0; i < newFields.count(); ++i )
        {
          if ( mFields.at( i ) != newFields.at( i ) )
          {
            QgsFields tmpOldFields = mFields;
            tmpOldFields.remove( i );
            if ( tmpOldFields.toList() != newFields.toList() )
              break; // the change is more complex - go with general case

            // the only change is a field removed at index i
            beginRemoveRows( QModelIndex(), i, i );
            mFields = newFields;
            endRemoveRows();
            return;
          }
        }
      }

      // general case with reset - not good - resets selections
      beginResetModel();
      mFields = mLayer->fields();
      endResetModel();
    }
    else
      emit dataChanged( index( 0, 0 ), index( rowCount(), 0 ) );
  }
  else
  {
    beginResetModel();
    mFields = QgsFields();
    endResetModel();
  }
}