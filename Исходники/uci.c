int go(char *input, ENGINE_STATE *stat)
{  
  stat->control->max_depth = MAXDEPTH;
  stat->control->max_time = INFINITE;
  stat->control->wish_time = INFINITE;
  stat->control->stop = 1;
  stat->control->ponder = 0;
  ResetTimes(stat);
  int movestogo = 20;
  char manage_times = 1;
  char *str_param = strtok(input, " \n\t");
  for (str_param = strtok(NULL, " \n\t"); str_param; str_param = strtok(NULL, " \n\t")) {
    if (!strcmp("depth",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->max_depth = atoi(str_param);
        manage_times = 0;
      }
      break;
    } else if (!strcmp("time",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->wish_time = INFINITE;
        stat->control->max_time = atol(str_param);
        manage_times = 0;
      }
    } else if (!strcmp("infinite",  str_param)) {
      manage_times = 0;
      break;
    } else if (!strcmp("ponder", str_param)) {
      stat->control->ponder = 1;
    } else if (!strcmp("btime",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->btime = atoi(str_param);
      }
    } else if (!strcmp("wtime",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->wtime = atoi(str_param);
      }
    } else if (!strcmp("binc",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->btime_inc = atoi(str_param);
      }
    } else if (!strcmp("winc",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        stat->control->wtime_inc = atoi(str_param);
      }
    } else if (!strcmp("movestogo",  str_param)) {
      str_param = strtok(NULL, " \n\t");
      if (str_param) {
        movestogo = atoi(str_param);
      }
    } else break;
  }

  if (stat->control->stop) {
    if (manage_times) {
      ManageTimes(movestogo, stat);
    }
    stat->control->stop = 0;
    stat->control->init_time = clock();
#ifdef __linux__
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);

    pthread_t thread_id;
    pthread_create(&thread_id, &tattr, (void *)(think), stat);
#elif defined _WIN32
    _beginthread(think, 0, stat);
#endif
  }
  return 1;
}