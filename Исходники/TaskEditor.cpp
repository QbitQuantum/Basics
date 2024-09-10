Task TaskEditor::getTask() const
{
    Task newTask = m_task;
    newTask.setName( m_ui->lineEditName->text() );
    newTask.setTrackable( m_ui->checkBoxTrackable->isChecked() );
    if( m_ui->checkBoxTopLevel->isChecked() ) {
        newTask.setParent( 0 );
    }
    if( m_ui->checkBoxFrom->isChecked() ) {
        newTask.setValidFrom( QDateTime() );
    } else {
        newTask.setValidFrom( m_ui->dateEditFrom->dateTime() );
    }
    if( m_ui->checkBoxUntil->isChecked() ) {
        newTask.setValidUntil( QDateTime() );
    } else {
        newTask.setValidUntil( m_ui->dateEditTo->dateTime() );
    }
    return newTask;
}