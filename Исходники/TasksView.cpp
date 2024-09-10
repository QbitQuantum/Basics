void TasksView::addTaskHelper( const Task& parent )
{
    ViewFilter* filter = Application::instance().model().taskModel();
    Task task;
    int suggestedId = parent.isValid() ? parent.id() : 1;
    if ( parent.isValid() ) {
        task.setParent( parent.id() );
        // subscribe if the parent is subscribed:
        task.setSubscribed( parent.subscribed()
                            || CONFIGURATION.taskPrefilteringMode == Configuration::TaskPrefilter_SubscribedOnly
                            || CONFIGURATION.taskPrefilteringMode == Configuration::TaskPrefilter_SubscribedAndCurrentOnly );
    }
    // yeah, daredevil!
    while ( filter->taskIdExists( suggestedId ) ) ++suggestedId;
    TaskIdDialog dialog( filter, this );
    dialog.setSuggestedId( suggestedId );
    if ( dialog.exec() ) {
        task.setId( dialog.selectedId() );
        task.setName( dialog.taskName() );
        CommandAddTask* cmd = new CommandAddTask( task, this );
        emit emitCommand( cmd );
        if ( parent.isValid() ) {
            const QModelIndex parentIdx = filter->indexForTaskId( parent.id() );
            m_treeView->setExpanded( parentIdx, true );
        }
    }
}