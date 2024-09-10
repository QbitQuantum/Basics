void _cleanup(Tptr p) {
  if (p) {
    _cleanup(p->lokid);
    if (p->splitchar) {
      _cleanup(p->eqkid);
    } else {
      free(p->eqkid); /* It's just a string, free the memory */
    }
    _cleanup(p->hikid);
    free(p);  
  }
}