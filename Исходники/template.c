void destructed(int clone) {
  int i, n;
  if(SYSTEM() && clone) {
    if(children) {
      for(i = 0, n = sizeof(children); i < n; i++)
        destruct_object(children[i]);
    }
  }
}