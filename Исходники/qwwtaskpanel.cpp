void QwwTaskPanel::removeTask(int index) {
    if (index < 0 || index>=m_tasks.count()) return;
    Task *tsk = static_cast<Task*>(m_tasks.at(index));
    m_tasks.removeAt(index);
    if (m_tasks.count()<=index) {
        setCurrentIndex(m_tasks.count()-1);
    }
    QWidget *body = tsk->body();
    body->setParent(this);
    delete tsk;
}