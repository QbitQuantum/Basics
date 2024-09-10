void ExtractViewResource( tag_file* tf, XGHandle& data, int off, int end )
{
	unsigned int id = data.GetLong(off+4);
	if( id != 'VRes' )
		return;
	
	c_block_size = 0;
	memset( string_block, 0, sizeof(string_block) );
	
	// skip the view resource.
	int str_len = (unsigned char)data.GetChar(off+10);
	char name[256];
	data.GetMemory( off+11, str_len, name );
	name[str_len] = 0;
	
	str_len += 5;//4+(str_len&1);
	
	off = off + 10 + str_len; // extra 4 there because i don't know why, but it's off.
	//int end = data.GetLong(off)+data.GetLong(off+4);
	id = data.GetLong(off+8);
	assert( id == 'wind' );
	int num_controls = 0;
	dialog_t dlog;
	unsigned int dlog_id = 0;//data.GetLong(off+16);
	
	if( dlog_id == 0 )
		dlog_id = new_tag_id_from_string( name, 0x62696e61, NULL );
		
	dlog.bounds.left = data.GetLong(off+22);
	dlog.bounds.top = data.GetLong(off+26);
	dlog.bounds.right = dlog.bounds.left+data.GetLong(off+46);
	dlog.bounds.bottom = dlog.bounds.top+data.GetLong(off+50);
	
	/* skip dlog */
	str_len = data.GetChar(off+70)+1;
	str_len += 5;//4+2-(str_len&1);
	//end += off + str_len;
	
	off = off + 70 + str_len;
	control_t* ctrl;
	control_loader_t* ldr;
	int len;
	
	//end += off;
	
	while( off < end && num_controls < MAX_CONTROLS )
	{
		len = data.GetLong(off);
		id = data.GetLong(off+12);
		ldr = FindControlLoader(id);
		if(!ldr)
			return;
			
		ctrl = &control_set[num_controls++];
		ctrl->tag = ldr->tag;
		ctrl->item_id = data.GetLong(off+16);
		ctrl->flags = 0;
		ctrl->state = 0;
		
		ctrl->bounds.left = data.GetLong(off+32);
		ctrl->bounds.top = data.GetLong(off+36);
		ctrl->bounds.right = data.GetLong(off+40);
		ctrl->bounds.bottom = data.GetLong(off+44);
		
		/*
		myth3 wants the bottom corners.
		*/
		int height = 0;//(ctrl->bounds.bottom-ctrl->bounds.top)/2;
		ctrl->bounds.top += height;
		ctrl->bounds.bottom += height;
		
		ctrl->bitmap_ids[0] = 
		ctrl->bitmap_ids[1] = 0;
		
		if( ldr->load_proc )
			off += ldr->load_proc( ctrl, data, off+54 );
		if( len == 0 )
			break;
		//off += len;
		off += 54;
	}
	
	dlog.control_count = num_controls;
	WriteMythDialog( tf, dlog_id, &dlog, name );
}