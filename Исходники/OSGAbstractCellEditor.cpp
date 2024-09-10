void AbstractCellEditor::produceEditingStopped(void)
{
    const ChangeEventUnrecPtr TheEvent = ChangeEvent::create(NULL, getSystemTime());
    CellEditorListenerSet CellEditorListenerSet(_CellEditorListeners);
    for(CellEditorListenerSetConstItor SetItor(CellEditorListenerSet.begin()) ; SetItor != CellEditorListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->editingStopped(TheEvent);
    }
    _Producer.produceEvent(EditingStoppedMethodId,TheEvent);
}