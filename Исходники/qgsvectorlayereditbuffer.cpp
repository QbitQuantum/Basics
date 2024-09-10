void QgsVectorLayerEditBuffer::updateFields( QgsFields& fields )
{
  // delete attributes from the higher indices to lower indices
  for ( int i = mDeletedAttributeIds.count() - 1; i >= 0; --i )
  {
    fields.remove( mDeletedAttributeIds[i] );
  }
  // add new fields
  for ( int i = 0; i < mAddedAttributes.count(); ++i )
  {
    fields.append( mAddedAttributes[i], QgsFields::OriginEdit, i );
  }
  // rename fields
  QgsFieldNameMap::const_iterator renameIt = mRenamedAttributes.constBegin();
  for ( ; renameIt != mRenamedAttributes.constEnd(); ++renameIt )
  {
    fields[ renameIt.key()].setName( renameIt.value() );
  }
}