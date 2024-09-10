void* mem_alloc(size_t size_alloc) {

  if(DEBUG) { printf("=============== mem_alloc =============\n"); }
  
  if (size_alloc == 0) {
    printf("opération invalide (size=0)\n");
    return NULL;
  }

  fb* ptr_alloc = ptr_init;

  //calcul de l'espace mémoire réel à réserver

  //1) métadonnées
  size_alloc += METASIZE;
  //2) alignement
  size_alloc = align(size_alloc);
  if(DEBUG) { printf("step1 : size_alloc=%d\n", (int) size_alloc); }
  //recherche d'une zone libre selon la stratégie d'allocation choisie
  ptr_alloc = (*active_fit_fonction)(ptr_alloc, size_alloc);
  if (ptr_alloc == NULL) {
    printf("Allocation impossible\n");
    return NULL;
  }
  if(DEBUG) { printf("step2\n"); }
  //3) padding
  if (size_alloc + align(1) + METASIZE >= ptr_alloc->size) {
    size_alloc = ptr_alloc->size;
  }
  if(DEBUG) { printf("step3\n"); }

  //récupère le pointeur de zone libre précédant la zone libre choisie
  fb* ptr_prec = ptr_init;
  if (ptr_prec->next != NULL) {
    while (ptr_prec->next < ptr_alloc) {
      ptr_prec = ptr_prec->next;
    }
  }

  if(DEBUG) { printf("step4\n"); }
  //met à jour le chainage des zones libres restantes
  if(DEBUG){ printf("if (%d == %d) {\n", (int) ptr_prec->size, (int) size_alloc); }
  if (ptr_alloc->size == size_alloc) {
    //1er cas : la zone libre choisie est totalement remplie
    if (ptr_alloc == ptr_init) {
      // la zone allouée est la première du chainage
      // on remplace le chainage (ptr_alloc---->ptr_alloc.next---->...) par (ptr_alloc.next---->...)
      if(DEBUG) { printf("1\n"); }
      ptr_init = ptr_init->next;
    } else {
      // on remplace le chainage (ptr_prec---->ptr_alloc---->ptr_alloc.next) par (ptr_prec---->ptr_alloc.next)
      if(DEBUG) { printf("2\n"); }
      ptr_prec->next = (fb*) ptr_alloc->next;
    }
  } else {
    //2e cas : la zone libre choisie est partiellement remplie
    //=> on décale le pointeur de zone libre
    if ((fb*) ptr_alloc == ptr_init) {
      //décale les métadonnées de la zone libre :
      //1) buffer
      if(DEBUG) { printf("3\n"); }
      fb* ptr_tmp = ptr_init;
      //2) décale le pointeur
      ptr_init = (fb*) ((void*) ptr_init + size_alloc);
      //3) met à jour la taille
      ptr_tmp->size = ptr_tmp->size - size_alloc;
      //4) écrit les métadonnées
      ptr_init->size = ptr_tmp->size;
      ptr_init->next = ptr_tmp->next;
    } else {
      if(DEBUG) { printf("4\n"); }
      //décale les métadonnées de la zone libre :
      //1) buffer
      fb* ptr_tmp = ptr_prec->next;
      //2) décale le pointeur
      ptr_prec->next = (fb*) ((void*) ptr_prec->next + size_alloc);
      //3) met à jour la taille
      ptr_tmp->size = ptr_tmp->size - size_alloc;
      //4) écrit les métadonnées
      ptr_prec->next->size = ptr_tmp->size;
      ptr_prec->next->next = ptr_tmp->next;
    }
  }

  //écrit la taille de l'espace mémoire réservé avant celui-ci
  *((size_t*) ptr_alloc) = size_alloc;
  //décale ptr_alloc sur la premiere case de l'espace réservé (=valeur de retour)
  ptr_alloc = (fb*) ((void*) ptr_alloc + METASIZE);

  if(DEBUG) { printf("=======================================\n"); }

  return ptr_alloc;
}