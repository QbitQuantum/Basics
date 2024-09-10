	void Unload(){
		
		HOOK_CALL( 0x004018A0, 0x00401C8A ); // ReferencedPortraits
		HOOK_CALL( 0x004018A0, 0x00401E21 ); // ReferencedPortraits
		HOOK_CALL( 0x0041EC00, 0x0042A3C6 ); // PortraitShutdown
		HOOK_CALL( 0x0041EB40, 0x00428A1F ); // PortraitInit
		*((BYTE*)0x0041EE08) = 0x3F; // max head_db entries
		*((BYTE*)0x0041EC9B) = 0x3F; // max head_db entries

		memcpy( (void*)0x004184B0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x004184D0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x004184F0, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x00418510, "\x56\x57\x66\x33\xF6", 5 ); 
		memcpy( (void*)0x00418540, "\x8B\x44\x24\x04\x8D", 5 );
		memcpy( (void*)0x0042B510, "\x81\xEC\x00\x01\x00", 5 ); 
		memcpy( (void*)0x0042B600, "\xB8\x78\xEB\x4C\x00", 5 ); 
		memcpy( (void*)0x0042B9E0, "\x81\xEC\x00\x01\x00", 5 );
		*((DWORD*)0x004018DF) = 0x004CFBD0; // Portrait_First
		*((DWORD*)0x00401910) = 0x004D09E8; // Portrait_Last
		*((DWORD*)0x0041D3A5) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042459C) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042BD81) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042BEDD) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042E238) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0042B705) = 0x004CEB78; // &(SpriteTable[0].loaded_index)
		*((DWORD*)0x0047FE01) = 0x004EBC88; // offset_table
		*((DWORD*)0x00526D24) = 0; // Loaded_Sprite_Array 	
		*((DWORD*)0x00526D2C) = 0; // Loaded_Banner_Array
		*((DWORD*)0x00409F11) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x00409F52) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x0040C0CC) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x0040C108) = 0x004C0940; // troop_book_unit_pic
		*((DWORD*)0x00409DE3) = 0x004C0A80; // troop_book_leader_pic
		*((DWORD*)0x0040BD24) = 0x004C0A80; // troop_book_leader_pic
		*((DWORD*)0x00409EC2) = 0x004E2640; // unit name
		*((DWORD*)0x0040B876) = 0x004E2640; // unit name
		*((DWORD*)0x0040BE4A) = 0x004E2640; // unit name
		*((DWORD*)0x0040C20F) = 0x004E2640; // unit name
		*((DWORD*)0x0040C461) = 0x004E2640; // unit name
		*((DWORD*)0x0040D213) = 0x004E2640; // unit name
		*((DWORD*)0x0040D9C3) = 0x004E2640; // unit name
		*((DWORD*)0x0041985C) = 0x004E2640; // unit name
		*((DWORD*)0x0041A5E4) = 0x004E2640; // unit name
		*((DWORD*)0x0041B1B0) = 0x004E2640; // unit name
		*((DWORD*)0x0041B4CA) = 0x004E2640; // unit name
		*((DWORD*)0x0042671A) = 0x004E2640; // unit name
		*((DWORD*)0x004286E1) = 0x004E2640; // unit name
		*((DWORD*)0x00409E63) = 0x004E2780; // unit_desc
		*((DWORD*)0x0040BDE0) = 0x004E2780; // unit_desc
		*((DWORD*)0x004099B5) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00409DAD) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040B83D) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040BCE0) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040C1D5) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040C413) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040D97C) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0040E1E9) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x004192A4) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041981E) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041A39E) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041A5A6) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041B172) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x0041B48C) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00425B26) = 0x004C0BC0; // small_banner_index
		*((DWORD*)0x00426DEB) = 0x004C0BC0; // small_banner_index

		for( int i = 80; i < 180; i++ ){
			if( troop_book_leader_pic[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_leader_pic[i] );
				troop_book_leader_pic[i] = NULL;
			}
			if( troop_book_unit_pic[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_unit_pic[i] );
				troop_book_unit_pic[i] = NULL; 
			}
			if( troop_book_unit_desc[i] != NULL ){ 
				HeapFree( GetProcessHeap(), 0, troop_book_unit_desc[i] );
				troop_book_unit_desc[i] = NULL;
			}
		}

	}