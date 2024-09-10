uintptr_t *MJC_allocObject(size_t size) {

#ifdef DEBUG_ALLOC
  printf("MJC alloc object size %zu bytes (%zu words)\n", size, WORDSIZE(size));
#endif

  // size request was # bytes - convert to words
  size = WORDSIZE(size);

  uintptr_t *obj = heapalloc(size + OBJ_HEADER_SIZE) + OBJ_HEADER_SIZE;

  // store a class type into the header for later use
  obj[-OBJ_HEADER_TYPE_OFFSET] = (uintptr_t)(OBJECT_HEADER_TYPE);
  obj[-OBJ_HEADER_SIZE_OFFSET] = size;

  // initialize remaining alloc space to 0
  memset(obj, 0, size * sizeof(uintptr_t));

  return obj;
}