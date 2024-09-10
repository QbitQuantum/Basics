int CheckCredit(NETADDR *dest, PMAH pmah)
{
  NFIND *nf;
  int cost;

  if (! (pmah->ma.attribs & MA_NET))
    return 0;
  
  if ((nf=NodeFindOpen(dest))==NULL)
  {
    if (! GEPriv(usr.priv, prm.unlisted_priv))
    {
      Puts(unlisteddest);
      Press_ENTER();
      return -1;
    }

    cost=prm.unlisted_cost;
  }
  else
  {
    cost=nf->found.cost;
    NodeFindClose(nf);
  }

  if (mailflag(CFLAGM_NETFREE))
    cost=0;

  if (usr.debit+cost > usr.credit)
  {
    Puts(ncredit);
    Press_ENTER();
    return -1;
  }

  return 0;
}