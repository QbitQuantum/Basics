static status
unlinkMenuItem(MenuItem mi)
{ if ( notNil(mi->menu) )
    deleteMenu(mi->menu, mi);

  succeed;
}