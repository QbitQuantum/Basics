_dnode *_scan_vols_tree(
		vol_inf *vol,
		int     *count
	)
{
	list_entry *del;
	list_entry *node;
	list_entry *sub;	

	for ( node = __drives.flink;
		  node != &__drives
		  ;
		) 
	{
		_dnode *root = contain_record(node, _dnode, list);
		if ( count )
		{
			*count += 1;
		}
		for ( sub = root->root.vols.flink;
			  sub != &root->root.vols
			  ; 
			) 
		{
			_dnode *mnt = contain_record(sub, _dnode, list);
			if ( count ) 
			{
				*count += 1;
			}				
			if (! vol )
			{
				if (! mnt->exists )
				{
					del = sub;
					sub = sub->flink;

					_remove_entry_list(del);
					free(del);

					continue;
				}
			} else {
				if ( ( wcscmp(mnt->mnt.info.device, vol->device) == 0 ) && (! mnt->exists) ) 
				{
					return mnt;
				}
			}
			sub = sub->flink;
		}
		if (_is_list_empty(sub)) 
		{
			del = node;
			node = node->flink;

			_remove_entry_list(del);
			free(del);

			continue;
		}
		node = node->flink;
	}
	return NULL;

}