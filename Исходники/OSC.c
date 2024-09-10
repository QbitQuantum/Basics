static int OSC_handler(const char *path, const char *types,
                       lo_arg **argv, int argc, void *data, void *p)
{
    OSC_PORT  *pp = (OSC_PORT*) p;
    OSCLISTEN *o;
    CSOUND *csound = (CSOUND *) pp->csound;
    int       retval = 1;

    pp->csound->LockMutex(pp->mutex_);
    o = (OSCLISTEN*) pp->oplst;
    //printf("opst=%p\n", o);
    while (o != NULL) {
      //printf("Looking at %s/%s against %s/%s\n",
      //       o->saved_path, path,o->saved_types, types);
      if (strcmp(o->saved_path, path) == 0 &&
          strcmp(o->saved_types, types) == 0) {
        /* Message is for this guy */
        int     i;
        OSC_PAT *m;
        //printf("handler found message\n");
        m = get_pattern(o);
        if (m != NULL) {
          /* queue message for being read by OSClisten opcode */
          m->next = NULL;
          if (o->patterns == NULL)
            o->patterns = m;
          else {
            OSC_PAT *mm;
            for (mm = o->patterns; mm->next != NULL; mm = mm->next)
              ;
            mm->next = m;
          }
          /* copy argument list */
          for (i = 0; o->saved_types[i] != '\0'; i++) {
            switch (types[i]) {
            default:              /* Should not happen */
            case 'i':
              m->args[i].number = (MYFLT) argv[i]->i; break;
            case 'h':
              m->args[i].number = (MYFLT) argv[i]->i64; break;
            case 'c':
               m->args[i].number= (MYFLT) argv[i]->c; break;
            case 'f':
               m->args[i].number = (MYFLT) argv[i]->f; break;
            case 'd':
               m->args[i].number= (MYFLT) argv[i]->d; break;
            case 's':
              { // ***NO CHECK THAT m->args[i] IS A STRING
                char  *src = (char*) &(argv[i]->s), *dst = m->args[i].string.data;
                if (m->args[i].string.size <= (int) strlen(src)) {
                  if (dst != NULL) csound->Free(csound, dst);
                  dst = csound->Strdup(csound, src);
                  // who sets m->args[i].string.size ??
                  m->args[i].string.data = dst;
                  m->args[i].string.size = strlen(dst)+1;
                }
                else strcpy(dst, src);
                break;
              }
            case 'b':
              {
                int len =
                  lo_blobsize((lo_blob*)argv[i]);
                m->args[i].blob =
                  csound->Malloc(csound,len);
                memcpy(m->args[i].blob, argv[i], len);
#ifdef JPFF
                {
                  lo_blob *bb = (lo_blob*)m->args[i].blob;
                  int size = lo_blob_datasize(bb);
                  MYFLT *data = lo_blob_dataptr(bb);
                  int   *idata = (int*)data;
                  printf("size=%d data=%.8x %.8x ...\n",size, idata[0], idata[1]);
                }
#endif
              }
            }
          }
          retval = 0;
        }
        break;
      }
      o = (OSCLISTEN*) o->nxt;
    }

    pp->csound->UnlockMutex(pp->mutex_);
    return retval;
}