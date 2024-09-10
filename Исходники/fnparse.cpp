_Use_decl_annotations_ EXTERN_C IMAGE_RUNTIME_FUNCTION_ENTRY *
FnparseLookupFunctionEntry(FARPROC FunctionAddress, PVOID *ImageBase) {
  PAGED_CODE();

  return RtlLookupFunctionEntry(FunctionAddress, ImageBase, nullptr);
}