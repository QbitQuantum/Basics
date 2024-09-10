/*===========================================================================
 *
 * Class CSrResourceInstance Method - int64 GetFilesize (void);
 *
 *=========================================================================*/
int64 CSrResourceInstance::GetFilesize (void) {
  int64 Size;

  if (GetFilesize(Size)) return (Size);
  return (-1);
}