const wchar_t* ON_wString::ToNumber(
  const wchar_t* buffer,
  double value_on_failure,
  double* value
  )
{
  if (nullptr == value)
    return nullptr;
  *value = value_on_failure;
  if (nullptr == buffer)
    return nullptr;

  char local_buffer[512];
  const size_t local_buffer_capacity = sizeof(local_buffer) / sizeof(local_buffer[0]);
  size_t local_buffer_count = 0;

  if ('-' == *buffer || '+' == *buffer)
    local_buffer[local_buffer_count++] = (char)(*buffer++);

  bool bHaveMantissa = false;
  while (buffer[0] >= '0' && buffer[0] <= '9')
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);
    bHaveMantissa = true;
  }

  if ('.' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
      bHaveMantissa = true;
    }
  }

  if (false == bHaveMantissa)
    return nullptr;

  if ('e' == *buffer || 'E' == *buffer)
  {
    if (local_buffer_count >= local_buffer_capacity)
      return nullptr;
    local_buffer[local_buffer_count++] = (char)(*buffer++);

    if ('-' == *buffer || '+' == *buffer)
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }

    while (buffer[0] >= '0' && buffer[0] <= '9')
    {
      if (local_buffer_count >= local_buffer_capacity)
        return nullptr;
      local_buffer[local_buffer_count++] = (char)(*buffer++);
    }
  }

  local_buffer[local_buffer_count++] = 0;

  double x = value_on_failure;
#if defined(ON_COMPILER_CLANG)
#if defined(ON_RUNTIME_ANDROID)
  if (1 == sscanf(local_buffer, "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#else
  if (1 == sscanf_l(local_buffer, ON_Locale::InvariantCulture.NumericLocalePtr(), "%lg", &x))
  {
    *value = x;
    return buffer;
  }
#endif
#else
  if (1 == _sscanf_s_l(local_buffer, "%lg", ON_Locale::InvariantCulture.NumericLocalePtr(), &x))
  {
    *value = x;
    return buffer;
  }
#endif
  *value = value_on_failure;
  return nullptr;
}