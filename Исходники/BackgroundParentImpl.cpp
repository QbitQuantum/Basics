dom::PFileSystemRequestParent*
BackgroundParentImpl::AllocPFileSystemRequestParent(
                                                const FileSystemParams& aParams)
{
  AssertIsInMainProcess();
  AssertIsOnBackgroundThread();

  RefPtr<FileSystemRequestParent> result = new FileSystemRequestParent();

  if (NS_WARN_IF(!result->Initialize(aParams))) {
    return nullptr;
  }

  return result.forget().take();
}