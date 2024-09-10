/**
 * Judger handler
 * @param arg   should be (JudgerArgs *), passes the socket handler and the oj
 *    name
 * @return NULL
 */
void * judger_handler(void * arg) {
  JudgerArgs * judger_info = (JudgerArgs *) arg;

  LOGGER->addIdentifier(pthread_self(), judger_info->oj);
  JudgerThread * judger = new JudgerThread(judger_info->socket,
                                           judger_info->oj);
  delete judger_info;

  pthread_mutex_lock(&judgers_mutex);
  judgers.push_back(judger);
  pthread_mutex_unlock(&judgers_mutex);

  judger->run();

  pthread_mutex_lock(&judgers_mutex);
  judgers.remove(judger);
  pthread_mutex_unlock(&judgers_mutex);

  // check if there's unfinished submit
  Submit * submit = judger->Getcurrent_submit();
  if (submit) {
    insert_run(submit);
  }

  delete judger;
  LOGGER->eraseIdentifier(pthread_self());
  pthread_exit(NULL);
}