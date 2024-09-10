bool ResourceBundle::LoadLocaleResources(
    const base::FilePath& locale_resource_path)
{
    DCHECK(NULL == locale_resources_data_) << "locale dll already loaded";

    // 纯资源DLL, 没有可执行代码.
    locale_resources_data_ = LoadLibraryExW(locale_resource_path.value(),
        NULL, GetDataDllLoadFlags());

    return locale_resources_data_ != NULL;
}