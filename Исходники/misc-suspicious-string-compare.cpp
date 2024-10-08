int test_implicit_compare_with_functions() {

  if (memcmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'memcmp' is called without explicitly comparing result
  // CHECK-FIXES: memcmp(A, "a", 1) != 0)

  if (wmemcmp(W, L"a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wmemcmp' is called without explicitly comparing result
  // CHECK-FIXES: wmemcmp(W, L"a", 1) != 0)

  if (memicmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'memicmp' is called without explicitly comparing result
  // CHECK-FIXES: memicmp(A, "a", 1) != 0)

  if (_memicmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_memicmp' is called without explicitly comparing result
  // CHECK-FIXES: _memicmp(A, "a", 1) != 0)

  if (_memicmp_l(A, "a", 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_memicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _memicmp_l(A, "a", 1, locale) != 0)

  if (strcmp(A, "a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strcmp' is called without explicitly comparing result
  // CHECK-FIXES: strcmp(A, "a") != 0)

  if (strncmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strncmp' is called without explicitly comparing result
  // CHECK-FIXES: strncmp(A, "a", 1) != 0)

  if (strcasecmp(A, "a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strcasecmp' is called without explicitly comparing result
  // CHECK-FIXES: strcasecmp(A, "a") != 0)

  if (strncasecmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strncasecmp' is called without explicitly comparing result
  // CHECK-FIXES: strncasecmp(A, "a", 1) != 0)

  if (stricmp(A, "a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'stricmp' is called without explicitly comparing result
  // CHECK-FIXES: stricmp(A, "a") != 0)

  if (strcmpi(A, "a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strcmpi' is called without explicitly comparing result
  // CHECK-FIXES: strcmpi(A, "a") != 0)

  if (_stricmp(A, "a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_stricmp' is called without explicitly comparing result
  // CHECK-FIXES: _stricmp(A, "a") != 0)

  if (strnicmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'strnicmp' is called without explicitly comparing result
  // CHECK-FIXES: strnicmp(A, "a", 1) != 0)

  if (_strnicmp(A, "a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_strnicmp' is called without explicitly comparing result
  // CHECK-FIXES: _strnicmp(A, "a", 1) != 0)

  if (_stricmp_l(A, "a", locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_stricmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _stricmp_l(A, "a", locale) != 0)

  if (_strnicmp_l(A, "a", 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_strnicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _strnicmp_l(A, "a", 1, locale) != 0)

  if (wcscmp(W, L"a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wcscmp' is called without explicitly comparing result
  // CHECK-FIXES: wcscmp(W, L"a") != 0)

  if (wcsncmp(W, L"a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wcsncmp' is called without explicitly comparing result
  // CHECK-FIXES: wcsncmp(W, L"a", 1) != 0)

  if (wcscasecmp(W, L"a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wcscasecmp' is called without explicitly comparing result
  // CHECK-FIXES: wcscasecmp(W, L"a") != 0)

  if (wcsicmp(W, L"a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wcsicmp' is called without explicitly comparing result
  // CHECK-FIXES: wcsicmp(W, L"a") != 0)

  if (_wcsicmp(W, L"a"))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_wcsicmp' is called without explicitly comparing result
  // CHECK-FIXES: _wcsicmp(W, L"a") != 0)

  if (_wcsicmp_l(W, L"a", locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_wcsicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _wcsicmp_l(W, L"a", locale) != 0)

  if (wcsnicmp(W, L"a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function 'wcsnicmp' is called without explicitly comparing result
  // CHECK-FIXES: wcsnicmp(W, L"a", 1) != 0)

  if (_wcsnicmp(W, L"a", 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_wcsnicmp' is called without explicitly comparing result
  // CHECK-FIXES: _wcsnicmp(W, L"a", 1) != 0)

  if (_wcsnicmp_l(W, L"a", 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_wcsnicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _wcsnicmp_l(W, L"a", 1, locale) != 0)

  if (_mbscmp(U, V))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbscmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbscmp(U, V) != 0)

  if (_mbsncmp(U, V, 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsncmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbsncmp(U, V, 1) != 0)

  if (_mbsnbcmp(U, V, 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnbcmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnbcmp(U, V, 1) != 0)

  if (_mbsnbicmp(U, V, 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnbicmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnbicmp(U, V, 1) != 0)

  if (_mbsicmp(U, V))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsicmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbsicmp(U, V) != 0)

  if (_mbsnicmp(U, V, 1))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnicmp' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnicmp(U, V, 1) != 0)

  if (_mbscmp_l(U, V, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbscmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbscmp_l(U, V, locale) != 0)

  if (_mbsncmp_l(U, V, 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsncmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbsncmp_l(U, V, 1, locale) != 0)

  if (_mbsicmp_l(U, V, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbsicmp_l(U, V, locale) != 0)

  if (_mbsnicmp_l(U, V, 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnicmp_l(U, V, 1, locale) != 0)

  if (_mbsnbcmp_l(U, V, 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnbcmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnbcmp_l(U, V, 1, locale) != 0)

  if (_mbsnbicmp_l(U, V, 1, locale))
    return 0;
  // CHECK-MESSAGES: [[@LINE-2]]:7: warning: function '_mbsnbicmp_l' is called without explicitly comparing result
  // CHECK-FIXES: _mbsnbicmp_l(U, V, 1, locale) != 0)

  return 1;
}