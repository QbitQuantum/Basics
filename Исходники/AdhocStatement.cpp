BasicStatementTask::~BasicStatementTask()
{
    free((void*)m_sql);
}