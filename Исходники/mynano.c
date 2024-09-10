void do_right()
{
  if (curline->pdata_x<
      curline->data+strlen(curline->data))
  {
     int bytelen=mblen(curline->pdata_x,MB_CUR_MAX);
     curline->pdata_x+=bytelen;
     curline->win_x+=  (bytelen>1)?2:1;
  } 
}