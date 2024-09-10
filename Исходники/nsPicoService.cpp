already_AddRefed<nsPicoService>
nsPicoService::GetInstanceForService()
{
  nsRefPtr<nsPicoService> picoService = GetInstance();
  return picoService.forget();
}