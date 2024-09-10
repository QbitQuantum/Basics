NS_IMETHODIMP
PresentationService::SendSessionMessage(const nsAString& aSessionId,
                                        uint8_t aRole, const nsAString& aData) {
  MOZ_ASSERT(NS_IsMainThread());
  MOZ_ASSERT(!aData.IsEmpty());
  MOZ_ASSERT(!aSessionId.IsEmpty());
  MOZ_ASSERT(aRole == nsIPresentationService::ROLE_CONTROLLER ||
             aRole == nsIPresentationService::ROLE_RECEIVER);

  RefPtr<PresentationSessionInfo> info = GetSessionInfo(aSessionId, aRole);
  if (NS_WARN_IF(!info)) {
    return NS_ERROR_NOT_AVAILABLE;
  }

  return info->Send(aData);
}