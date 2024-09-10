bool RegistryUtilities::GetRegistryValue(const HKEY root_key,
                                         const std::wstring& subkey,
                                         const std::wstring& value_name,
                                         std::wstring *value) {
  std::string root_key_description = "HKEY_CURRENT_USER";
  if (root_key == HKEY_CLASSES_ROOT) {
    root_key_description = "HKEY_CLASSES_ROOT";
  } else if (root_key == HKEY_LOCAL_MACHINE) {
    root_key_description = "HKEY_LOCAL_MACHINE";
  }

  bool value_retrieved = false;
  DWORD required_buffer_size;
  DWORD value_type;
  HKEY key_handle;
  long registry_call_result = ::RegOpenKeyEx(root_key,
                                             subkey.c_str(),
                                             0,
                                             KEY_QUERY_VALUE,
                                             &key_handle);
  if (ERROR_SUCCESS == registry_call_result) {
    registry_call_result = ::RegQueryValueEx(key_handle,
                                             value_name.c_str(),
                                             NULL,
                                             &value_type,
                                             NULL,
                                             &required_buffer_size);
    if (ERROR_SUCCESS == registry_call_result) {
      if (value_type == REG_SZ || value_type == REG_EXPAND_SZ || value_type == REG_MULTI_SZ) {
        std::vector<wchar_t> value_buffer(required_buffer_size);
        registry_call_result = ::RegQueryValueEx(key_handle,
                                                value_name.c_str(),
                                                NULL,
                                                &value_type,
                                                reinterpret_cast<LPBYTE>(&value_buffer[0]),
                                                &required_buffer_size);
        if (ERROR_SUCCESS == registry_call_result) {
          *value = &value_buffer[0];
          value_retrieved = true;
        }
      } else if (value_type == REG_DWORD) {
        DWORD numeric_value = 0;
        registry_call_result = ::RegQueryValueEx(key_handle,
                                                 value_name.c_str(),
                                                 NULL,
                                                 &value_type,
                                                 reinterpret_cast<LPBYTE>(&numeric_value),
                                                 &required_buffer_size);
        if (ERROR_SUCCESS == registry_call_result) {
          // Coerce the numeric value to a string to return back.
          // Assume 10 characters will be enough to hold the size
          // of the value.
          std::vector<wchar_t> numeric_value_buffer(10);
          _ltow_s(numeric_value, &numeric_value_buffer[0], numeric_value_buffer.size(), 10);
          *value = &numeric_value_buffer[0];
          value_retrieved = true;
        }
      } else {
        LOG(WARN) << "Unexpected value type of " << value_type
                  << " for RegQueryValueEx was found for value with name "
                  << LOGWSTRING(value_name) << " in subkey "
                  << LOGWSTRING(subkey) << " in hive "
                  << root_key_description;
      }
      if (ERROR_SUCCESS != registry_call_result) {
        LOG(WARN) << "RegQueryValueEx failed with error code "
                  << registry_call_result << " retrieving value with name "
                  << LOGWSTRING(value_name) << " in subkey "
                  << LOGWSTRING(subkey) << "in hive "
                  << root_key_description;
      }
    } else {
      LOG(WARN) << "RegQueryValueEx failed with error code "
                << registry_call_result
                << " retrieving required buffer size for value with name "
                << LOGWSTRING(value_name) << " in subkey "
                << LOGWSTRING(subkey) << " in hive "
                << root_key_description;
    }
    ::RegCloseKey(key_handle);
  } else {
    LOG(WARN) << "RegOpenKeyEx failed with error code "
              << registry_call_result <<  " attempting to open subkey "
              << LOGWSTRING(subkey) << " in hive "
              << root_key_description;

  }
  return value_retrieved;
}