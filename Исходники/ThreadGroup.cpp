void mt::ThreadGroup::createThread(sys::Runnable *runnable)
{
    createThread(std::auto_ptr<sys::Runnable>(runnable));
}