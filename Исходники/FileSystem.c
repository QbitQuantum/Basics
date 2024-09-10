// copy what dir_p points to (dir_t) to what attr_p points to (attr_t)
void Dir2Attr( dir_t *dir_p, attr_t *attr_p ) {
   attr_p->dev = GetPid();            // FileSystem() manages this i-node

   attr_p->inode = dir_p->inode;
   attr_p->mode = dir_p->mode;
   attr_p->nlink = ( A_ISDIR( attr_p->mode ) ) + 1;
   attr_p->size = dir_p->size;
   attr_p->data = dir_p->data;
  }