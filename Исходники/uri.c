static int
unify_uri_authority_components(term_t components,
			       size_t len, const pl_wchar_t *s)
{ const pl_wchar_t *end = &s[len];
  const pl_wchar_t *e;
  range user   = {0};
  range passwd = {0};
  range host   = {0};
  range port   = {0};
  term_t t = PL_new_term_refs(5);
  term_t av = t+1;

  if ( (e=skip_not(s, end, L"@")) && e<end )
  { user.start = s;
    user.end = e;
    s = e+1;
    if ( (e=skip_not(user.start, user.end, L":")) && e<user.end )
    { passwd.start = e+1;
      passwd.end   = user.end;
      user.end     = e;
    }
  }
  host.start = s;
  host.end = skip_not(s, end, L":");
  if ( host.end < end )
  { port.start = host.end+1;
    port.end = end;
  }

  if ( user.start )
    unify_decoded_atom(av+0, &user, ESC_USER);
  if ( passwd.start )
    unify_decoded_atom(av+1, &passwd, ESC_PASSWD);
  unify_decoded_atom(av+2, &host, ESC_HOST);
  if ( port.start )
  { wchar_t *ep;
    long pn = wcstol(port.start, &ep, 10);

    if ( ep == port.end )
    { if ( !PL_put_integer(av+3, pn) )
	return FALSE;
    } else
    { unify_decoded_atom(av+3, &port, ESC_PORT);
    }
  }

  return (PL_cons_functor_v(t, FUNCTOR_uri_authority4, av) &&
	  PL_unify(components, t));
}