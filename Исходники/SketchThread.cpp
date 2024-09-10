void* SketchThread::sketch_thread_main(void*)
{
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

  Clock().delay(50); // Experimenting with some delay
  setup();

  while(1)
    loop();

  return NULL;
}