static void readLock(skipList list) {

  mLock(&list->read);

  if(list->block)
    cWait(&list->resume, &list->read);

  list->readers++;

  mUnlock(&list->read);

  return;
}