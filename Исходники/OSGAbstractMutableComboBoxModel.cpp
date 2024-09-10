void AbstractMutableComboBoxModel::produceListDataContentsChanged(FieldContainerRefPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventUnrecPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsChanged(e);
    }
    _Producer.produceEvent(ListDataContentsChangedMethodId,e);
}