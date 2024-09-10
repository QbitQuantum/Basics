void *
realloc(void *Object, size_t Size)
{
  void *NewObject;
  size_t CopySize;

  NewObject = EngAllocMem(0, sizeof(size_t) + Size, TAG_FREETYPE);
  if (NULL != NewObject)
    {
    *((size_t *) NewObject) = Size;
    NewObject = (void *)((size_t *) NewObject + 1);
    CopySize = *((size_t *) Object - 1);
    if (Size < CopySize)
      {
      CopySize = Size;
      }
    memcpy(NewObject, Object, CopySize);
    EngFreeMem((size_t *) Object - 1);
    }

  return NewObject;
}