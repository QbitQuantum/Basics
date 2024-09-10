void vlaknoZiju(void *) {

  while (1) {
    Zprava *z = new Zprava;
    z->initZiju();

    if (!z->send()) {
      HoThread::sendEvent((void *) z);
      return;
    }
    delete z;
 
    char posledni;
    bool konec;
    do {
      z = new Zprava;
      konec = !z->recv();
      posledni = z->posledni;
      printf("konec %i posledni %i typ %i\n", konec, posledni, z->typ);
      HoThread::sendEvent((void *) z);
      if (konec) return;
    } while (!posledni);
  }
}