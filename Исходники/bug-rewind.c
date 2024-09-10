static int
do_test (void)
{
  FILE *fptr;
  char arg1;
  char arg2;
  int ret1, ret2, result, num;

  ret1 = 0;
  ret2 = 0;

  fptr = fdopen (fd, "w+");
  if (fptr == NULL)
    {
      printf ("Unable to open file.\n");
      return 1;
    }

  if (fwprintf (fptr, L"cderf") <= 0)
    {
      printf ("Unable to write to file with fwprintf().\n");
      fclose (fptr);
      return 2;
    }

  rewind (fptr);
  ret1 = fwscanf (fptr, L"%c%c", &arg1, &arg2);
  if (ret1 != 2)
    {
      printf ("first fwscanf returned %d, expected 2\n", ret1);
      return 3;
    }

  rewind (fptr);
  ret2 = fwscanf (fptr, L"%c%n%c", &arg1, &num, &arg2);
  if (ret2 != 2)
    {
      printf ("second fwscanf returned %d, expected 2\n", ret2);
      return 4;
    }

  if (arg2 != 'd')
    {
      result = FAILED;
      printf ("rewind after first fwscanf failed\n");
    }
  else
    {
      printf ("Passed\n");
      result = PASSED;
    }


  fclose (fptr);
  return result;
}