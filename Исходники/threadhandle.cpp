ThreadHandle::~ThreadHandle() //停止所有线程，并释放资源
{
    QThread * tmp;
    for (auto it = threadSize.begin(); it != threadSize.end(); ++it)
    {
        tmp = it.key();
        tmp->exit();
        tmp->wait(3000);
        delete tmp;
    }
}