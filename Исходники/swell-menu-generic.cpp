bool DeleteMenu(HMENU hMenu, int idx, int flag)
{
  if (!hMenu) return false;
  if (flag&MF_BYPOSITION)
  {
    if (hMenu->items.Get(idx))
    {
      hMenu->items.Delete(idx,true,HMENU__::freeMenuItem);
      return true;
    }
    return false;
  }
  else
  {
    int x;
    int cnt=0;
    for (x=0;x<hMenu->items.GetSize(); x ++)
    {
      if (!hMenu->items.Get(x)->hSubMenu && hMenu->items.Get(x)->wID == idx)
      {
        hMenu->items.Delete(x--,true,HMENU__::freeMenuItem);
        cnt++;
      }
    }
    if (!cnt)
    {
      for (x=0;x<hMenu->items.GetSize(); x ++)
      {
        if (hMenu->items.Get(x)->hSubMenu) cnt += DeleteMenu(hMenu->items.Get(x)->hSubMenu,idx,flag)?1:0;
      }
    }
    return !!cnt;
  }
}