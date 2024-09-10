void PMenu::renameLnkFiles(QDir base_dir)
{
  PMenuItem *item;
  for( item = list.first(); item != 0; item = list.next() )
    {
      if( item->old_name.isEmpty() )
	continue;
      if( item->entry_type == submenu )
	{
	  if( item->real_name != item->old_name )
	    if( base_dir.exists( item->old_name ) )
	      {
		base_dir.rename( item->old_name, item->real_name );
		item->old_name = item->real_name;
	      }
	  QDir sub_dir(base_dir);
	  if( !sub_dir.cd(item->old_name) )
	    continue;
	  item->sub_menu->renameLnkFiles( sub_dir );
	}
      if( item->real_name == item->old_name || item->entry_type == separator )
	continue;
      if( base_dir.exists( item->old_name ) )
	{
	  base_dir.rename( item->old_name, item->real_name );
	  item->old_name = item->real_name;
	}
    }  
}