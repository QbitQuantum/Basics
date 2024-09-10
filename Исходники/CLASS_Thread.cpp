void* Thread::threadProc(void* p)
{
  Thread* thread = reinterpret_cast<Thread*>(p);
  if (!thread)
    return 0;
  
  thread->setActive(true);
  int result = 0;
  if (thread->init())
  {
    result = thread->run();
    thread->exit();
  }
  thread->done();
  thread->setActive(false);

  return (void*)result;
}