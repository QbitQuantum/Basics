void create_updated_save(QuickSave& save)
{
	// read data from existing save file
	struct wad_header header;
	struct wad_data *game_wad, *orig_meta_wad, *new_meta_wad;
	int32 game_wad_length;
	std::string imagedata;
	
	OpenedFile currentFile;
	if (save.save_file.Open(currentFile))
	{
		if (read_wad_header(currentFile, &header))
		{
			game_wad = read_indexed_wad_from_file(currentFile, &header, 0, false);
			if (game_wad) game_wad_length = calculate_wad_length(&header, game_wad);

			orig_meta_wad = read_indexed_wad_from_file(currentFile, &header, SAVE_GAME_METADATA_INDEX, true);
			
			if (orig_meta_wad)
			{
				size_t data_length;
				char *raw_imagedata = (char *)extract_type_from_wad(orig_meta_wad, SAVE_IMG_TAG, &data_length);
				imagedata = std::string(raw_imagedata, data_length);
			}
		}
		close_wad_file(currentFile);
	}
	
	// create updated save file
	short err = 0;
	int32 offset, meta_wad_length;
	struct directory_entry entries[2];
	
	FileSpecifier TempFile;
	TempFile.SetTempName(save.save_file);
	
	if (create_wadfile(TempFile, _typecode_savegame))
	{
		OpenedFile SaveFile;
		if(open_wad_file_for_writing(TempFile, SaveFile))
		{
			if (write_wad_header(SaveFile, &header))
			{
				offset = SIZEOF_wad_header;
				
				set_indexed_directory_offset_and_length(&header, entries, 0, offset, game_wad_length, 0);
				
				if (write_wad(SaveFile, &header, game_wad, offset))
				{
					offset += game_wad_length;
					header.directory_offset= offset;
					
					new_meta_wad = build_meta_game_wad(build_save_metadata(save), imagedata, &header, &meta_wad_length);
					if (new_meta_wad)
					{
						set_indexed_directory_offset_and_length(&header, entries, 1, offset, meta_wad_length, SAVE_GAME_METADATA_INDEX);
						
						if (write_wad(SaveFile, &header, new_meta_wad, offset))
						{
							offset += meta_wad_length;
							header.directory_offset= offset;
							
							if (write_wad_header(SaveFile, &header) && write_directorys(SaveFile, &header, entries))
							{
							}
						}
						free_wad(new_meta_wad);
					}
				}
				free_wad(game_wad);
				free_wad(orig_meta_wad);
			}

			err = SaveFile.GetError();
			close_wad_file(SaveFile);
		}
		
		if (!err)
		{
			if (!TempFile.Rename(save.save_file))
			{
				err = 1;
			}
		}
	}
	
	if (err || error_pending())
	{
		if (!err) err = get_game_error(NULL);
		alert_user(infoError, strERRORS, fileError, err);
		clear_game_error();
	}
}