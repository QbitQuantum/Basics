static int
do_test (void)
{
  int size = sysconf (_SC_PAGESIZE);
  int nchars = size / sizeof (CHAR);
  CHAR *adr;
  CHAR *dest;
  int result = 0;

  adr = (CHAR *) mmap (NULL, 3 * size, PROT_READ | PROT_WRITE,
		       MAP_PRIVATE | MAP_ANON, -1, 0);
  dest = (CHAR *) mmap (NULL, 3 * size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANON, -1, 0);
  if (adr == MAP_FAILED || dest == MAP_FAILED)
    {
      if (errno == ENOSYS)
	puts ("No test, mmap not available.");
      else
	{
	  printf ("mmap failed: %m");
	  result = 1;
	}
    }
  else
    {
      int inner, middle, outer;

      mprotect (adr, size, PROT_NONE);
      mprotect (adr + 2 * nchars, size, PROT_NONE);
      adr += nchars;

      mprotect (dest, size, PROT_NONE);
      mprotect (dest + 2 * nchars, size, PROT_NONE);
      dest += nchars;

      MEMSET (adr, L('T'), nchars);

      /* strlen/wcslen test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      if (STRLEN (&adr[outer]) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %d, inner = %d\n",
			  STRINGIFY (STRLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	}

      /* strnlen/wcsnlen test */
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      if (STRNLEN (&adr[outer], inner - outer + 1)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %d, inner = %d\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	}
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner <= nchars; ++inner)
	    {
	      if (STRNLEN (&adr[outer], inner - outer)
		  != (size_t) (inner - outer))
		{
		  printf ("%s flunked bounded for outer = %d, inner = %d\n",
			  STRINGIFY (STRNLEN), outer, inner);
		  result = 1;
		}
	    }
	}

      /* strchr/wcschr test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      for (inner = middle; inner < nchars; ++inner)
		{
		  adr[middle] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRCHR (&adr[outer], L('V'));

		  if ((inner == middle && cp != NULL)
		      || (inner != middle
			  && (cp - &adr[outer]) != middle - outer))
		    {
		      printf ("%s flunked for outer = %d, middle = %d, "
			      "inner = %d\n",
			      STRINGIFY (STRCHR), outer, middle, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[middle] = L('T');
		}
	    }
	}

      /* Special test.  */
      adr[nchars - 1] = L('\0');
      if (STRCHR (&adr[nchars - 1], L('\n')) != NULL)
	{
	  printf ("%s flunked test of empty string at end of page\n",
		  STRINGIFY (STRCHR));
	  result = 1;
	}

      /* strrchr/wcsrchr test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      for (inner = middle; inner < nchars; ++inner)
		{
		  adr[middle] = L('V');
		  adr[inner] = L('\0');

		  CHAR *cp = STRRCHR (&adr[outer], L('V'));

		  if ((inner == middle && cp != NULL)
		      || (inner != middle
			  && (cp - &adr[outer]) != middle - outer))
		    {
		      printf ("%s flunked for outer = %d, middle = %d, "
			      "inner = %d\n",
			      STRINGIFY (STRRCHR), outer, middle, inner);
		      result = 1;
		    }

		  adr[inner] = L('T');
		  adr[middle] = L('T');
		}
	    }
	}

      /* memchr test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = MEMCHR (&adr[outer], L('V'), 3 * size);

	      if (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %d, middle = %d\n",
			  STRINGIFY (MEMCHR), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	}
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  CHAR *cp = MEMCHR (&adr[outer], L('V'), nchars - outer);

	  if (cp != NULL)
	    {
	      printf ("%s flunked for outer = %d\n",
		      STRINGIFY (MEMCHR), outer);
	      result = 1;
	    }
	}

      /* These functions only exist for single-byte characters.  */
#ifndef WCSTEST
      /* rawmemchr test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = rawmemchr (&adr[outer], L('V'));

	      if (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %d, middle = %d\n",
			  STRINGIFY (rawmemchr), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	}

      /* memrchr test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('V');

	      CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	      if (cp - &adr[outer] != middle - outer)
		{
		  printf ("%s flunked for outer = %d, middle = %d\n",
			  STRINGIFY (memrchr), outer, middle);
		  result = 1;
		}

	      adr[middle] = L('T');
	    }
	}
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  CHAR *cp = memrchr (&adr[outer], L('V'), nchars - outer);

	  if (cp != NULL)
	    {
	      printf ("%s flunked for outer = %d\n",
		      STRINGIFY (memrchr), outer);
	      result = 1;
	    }
	}
#endif

      /* strcpy/wcscpy test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      if (STRCPY (dest, &adr[outer]) != dest
		  || STRLEN (dest) != (size_t) (inner - outer))
		{
		  printf ("%s flunked for outer = %d, inner = %d\n",
			  STRINGIFY (STRCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	}

      /* strcmp/wcscmp tests */
      for (outer = 1; outer < 32; ++outer)
	for (middle = 0; middle < 16; ++middle)
	  {
	    MEMSET (adr + middle, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('\0');

	    if (STRCMP (adr + middle, dest + nchars - outer) <= 0)
	      {
		printf ("%s 1 flunked for outer = %d, middle = %d\n",
			STRINGIFY (STRCMP), outer, middle);
		result = 1;
	      }

	    if (STRCMP (dest + nchars - outer, adr + middle) >= 0)
	      {
		printf ("%s 2 flunked for outer = %d, middle = %d\n",
			STRINGIFY (STRCMP), outer, middle);
		result = 1;
	      }
	  }

      /* strncmp/wcsncmp tests */
      for (outer = 1; outer < 32; ++outer)
	for (middle = 0; middle < 16; ++middle)
	  {
	    MEMSET (adr + middle, L('T'), 256);
	    adr[256] = L('\0');
	    MEMSET (dest + nchars - outer, L('T'), outer - 1);
	    dest[nchars - 1] = L('U');

	    for (inner = 0; inner < outer; ++inner)
	      {
		if (STRNCMP (adr + middle, dest + nchars - outer, inner) != 0)
		  {
		    printf ("%s 1 flunked for outer = %d, middle = %d, "
			    "inner = %d\n",
			    STRINGIFY (STRNCMP), outer, middle, inner);
		    result = 1;
		  }

		if (STRNCMP (dest + nchars - outer, adr + middle, inner) != 0)
		  {
		    printf ("%s 2 flunked for outer = %d, middle = %d, "
			    "inner = %d\n",
			    STRINGIFY (STRNCMP), outer, middle, inner);
		    result = 1;
		  }
	      }

	    if (STRNCMP (adr + middle, dest + nchars - outer, outer) >= 0)
	      {
		printf ("%s 1 flunked for outer = %d, middle = %d, full\n",
			STRINGIFY (STRNCMP), outer, middle);
		result = 1;
	      }

	    if (STRNCMP (dest + nchars - outer, adr + middle, outer) <= 0)
	      {
		printf ("%s 2 flunked for outer = %d, middle = %d, full\n",
			STRINGIFY (STRNCMP), outer, middle);
		result = 1;
	      }
	  }

      /* strncpy/wcsncpy tests */
      adr[nchars - 1] = L('T');
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  size_t len;

	  for (len = 0; len < nchars - outer; ++len)
	    {
	      if (STRNCPY (dest, &adr[outer], len) != dest
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %d, len = %Zd\n",
			  STRINGIFY (STRNCPY), outer, len);
		  result = 1;
		}
	    }
	}
      adr[nchars - 1] = L('\0');

      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner < nchars; ++inner)
	    {
	      size_t len;

	      adr[inner] = L('\0');

	      for (len = 0; len < nchars - outer + 64; ++len)
		{
		  if (STRNCPY (dest, &adr[outer], len) != dest
		      || MEMCMP (dest, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest) != (inner - outer)))
		    {
		      printf ("%s flunked for outer = %d, inner = %d, "
			      "len = %Zd\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		  if (STRNCPY (dest + 1, &adr[outer], len) != dest + 1
		      || MEMCMP (dest + 1, &adr[outer],
				 MIN (inner - outer, len)) != 0
		      || (inner - outer < len
			  && STRLEN (dest + 1) != (inner - outer)))
		    {
		      printf ("%s+1 flunked for outer = %d, inner = %d, "
			      "len = %Zd\n",
			      STRINGIFY (STRNCPY), outer, inner, len);
		      result = 1;
		    }
		}

	      adr[inner] = L('T');
	    }
	}

      /* stpcpy/wcpcpy test */
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (inner = MAX (outer, nchars - 64); inner < nchars; ++inner)
	    {
	      adr[inner] = L('\0');

	      if ((STPCPY (dest, &adr[outer]) - dest) != inner - outer)
		{
		  printf ("%s flunked for outer = %d, inner = %d\n",
			  STRINGIFY (STPCPY), outer, inner);
		  result = 1;
		}

	      adr[inner] = L('T');
	    }
	}

      /* stpncpy/wcpncpy test */
      adr[nchars - 1] = L('T');
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	{
	  size_t len;

	  for (len = 0; len < nchars - outer; ++len)
	    {
	      if (STPNCPY (dest, &adr[outer], len) != dest + len
		  || MEMCMP (dest, &adr[outer], len) != 0)
		{
		  printf ("outer %s flunked for outer = %d, len = %Zd\n",
			  STRINGIFY (STPNCPY), outer, len);
		  result = 1;
		}
	    }
	}
      adr[nchars - 1] = L('\0');

      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	{
	  for (middle = MAX (outer, nchars - 64); middle < nchars; ++middle)
	    {
	      adr[middle] = L('\0');

	      for (inner = 0; inner < nchars - outer; ++ inner)
		{
		  if ((STPNCPY (dest, &adr[outer], inner) - dest)
		      != MIN (inner, middle - outer))
		    {
		      printf ("%s flunked for outer = %d, middle = %d, "
			      "inner = %d\n",
			      STRINGIFY (STPNCPY), outer, middle, inner);
		      result = 1;
		    }
		}

	      adr[middle] = L('T');
	    }
	}

      /* memcpy/wmemcpy test */
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	for (inner = 0; inner < nchars - outer; ++inner)
	  if (MEMCPY (dest, &adr[outer], inner) !=  dest)
	    {
	      printf ("%s flunked for outer = %d, inner = %d\n",
		      STRINGIFY (MEMCPY), outer, inner);
	      result = 1;
	    }

      /* mempcpy/wmempcpy test */
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	for (inner = 0; inner < nchars - outer; ++inner)
	  if (MEMPCPY (dest, &adr[outer], inner) !=  dest + inner)
	    {
	      printf ("%s flunked for outer = %d, inner = %d\n",
		      STRINGIFY (MEMPCPY), outer, inner);
	      result = 1;
	    }

      /* This function only exists for single-byte characters.  */
#ifndef WCSTEST
      /* memccpy test */
      memset (adr, '\0', nchars);
      for (outer = nchars; outer >= MAX (0, nchars - 128); --outer)
	for (inner = 0; inner < nchars - outer; ++inner)
	  if (memccpy (dest, &adr[outer], L('\1'), inner) != NULL)
	    {
	      printf ("memccpy flunked full copy for outer = %d, inner = %d\n",
		      outer, inner);
	      result = 1;
	    }
      for (outer = nchars - 1; outer >= MAX (0, nchars - 128); --outer)
	for (middle = 0; middle < nchars - outer; ++middle)
	  {
	    memset (dest, L('\2'), middle + 1);
	    for (inner = 0; inner < middle; ++inner)
	      {
		adr[outer + inner] = L('\1');

		if (memccpy (dest, &adr[outer], '\1', middle + 128)
		    !=  dest + inner + 1)
		  {
		    printf ("\
memccpy flunked partial copy for outer = %d, middle = %d, inner = %d\n",
			    outer, middle, inner);
		    result = 1;
		  }
		else if (dest[inner + 1] != L('\2'))
		  {
		    printf ("\
memccpy copied too much for outer = %d, middle = %d, inner = %d\n",
			    outer, middle, inner);
		    result = 1;
		  }
		adr[outer + inner] = L('\0');
	      }