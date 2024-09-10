QcepObject::~QcepObject()
{
#ifndef QT_NO_DEBUG
  QThread *currTh = QThread::currentThread();
  QThread *objTh  = thread();

  if (objTh && currTh != objTh) {
    printf("Deleting object from different thread %s (%s, %s)\n",
           qPrintable(objectName()),
           qPrintable(currTh ? currTh->objectName() : "null"),
           qPrintable(objTh ? objTh->objectName() : "null"));
  }
#endif

  s_ObjectDeleteCount.fetchAndAddOrdered(1);

#ifndef QT_NO_DEBUG
  s_Allocated.remove(this);
#endif
}