NTSTATUS AndroidUsbFileObject::Initialize() {
  ASSERT_IRQL_LOW();
  ASSERT(NULL != wdf_file());
  if (NULL == wdf_file())
    return STATUS_INTERNAL_ERROR;
  
  // Register context for this file object
  return InitializeContext();
}