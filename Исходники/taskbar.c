void cmenulaunch(void * self,MenuData *item) {

  switch(item->command) {
    case LAUNCHIT:
      spawnlp(0,item->data,NULL);
    break;
  }
}