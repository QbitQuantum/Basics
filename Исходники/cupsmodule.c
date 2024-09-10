static int
do_model_compare (const wchar_t *a, const wchar_t *b)
{
  const wchar_t *digits = L"0123456789";
  wchar_t quick_a, quick_b;
  while ((quick_a = *a) != L'\0' && (quick_b = *b) != L'\0') {
    int end_a = wcsspn (a, digits);
    int end_b = wcsspn (b, digits);
    int min;
    int a_is_digit = 1;
    int cmp;

    if (quick_a != quick_b && !iswdigit (quick_a) && !iswdigit (quick_b)) {
      if (quick_a < quick_b) return -1;
      else return 1;
    }

    if (!end_a) {
      end_a = wcscspn (a, digits);
      a_is_digit = 0;
    }

    if (!end_b) {
      if (a_is_digit)
	return -1;
      end_b = wcscspn (b, digits);
    } else if (!a_is_digit)
      return 1;

    if (a_is_digit) {
      unsigned long n_a, n_b;
      n_a = wcstoul (a, NULL, 10);
      n_b = wcstoul (b, NULL, 10);
      if (n_a < n_b) cmp = -1;
      else if (n_a == n_b) cmp = 0;
      else cmp = 1;
    } else {
      min = end_a < end_b ? end_a : end_b;
      cmp = wcsncmp (a, b, min);
    }

    if (!cmp) {
      if (end_a != end_b)
	return end_a < end_b ? -1 : 1;

      a += end_a;
      b += end_b;
      continue;
    }

    return cmp;
  }

  if (quick_a == L'\0') {
    if (*b == L'\0')
      return 0;

    return -1;
  }

  return 1;
}