void AreaError(int err)
{
  Puts(err_entering_msg_area);

  switch (err)
  {
    case MERR_NOENT:  Puts(areadoesntexist); break;
    case MERR_NOMEM:  Puts(merr_nomem);   break;
    case MERR_NODS:   Puts(merr_nods);    break;
    case MERR_NOLOCK: Puts(merr_nolock);  break;
    case MERR_SHARE:  Puts(merr_share);   break;
    case MERR_BADH:
    case MERR_BADF:
    case MERR_BADA:
    case MERR_EOPEN:  Puts(merr_corrupt); break;
    default:
    case MERR_NONE:   Printf(merr_unknown, err);  break;
  }

  Putc('\n');
  Press_ENTER();
}