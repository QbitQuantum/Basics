static void   read_heap   (
    //        =========
    //
    Inbuf*       bp,
    Heap_Header* header,
    Task*        task,
    Val*         externs
){
    Heap*		heap =  task->heap;

    Sib_Header*	sib_headers;
    Sib_Header*	p;
    Sib_Header*	q;

    int			sib_headers_bytesize;
    int			i, j, k;

    long		prevSzB[MAX_PLAIN_ILKS], size;
    Sibid*		oldBOOK2SIBID;
    Punt		addrOffset[MAX_AGEGROUPS][MAX_PLAIN_ILKS];

    Hugechunk_Region_Relocation_Info*	boRelocInfo;

    Addresstable*	boRegionTable;

    // Allocate a book_to_sibid__global for the imported
    // heap image's address space:
    //
    #ifdef TWO_LEVEL_MAP
        #error two level map not supported
    #else
	oldBOOK2SIBID = MALLOC_VEC (Sibid, BOOK2SIBID_TABLE_SIZE_IN_SLOTS);
    #endif

    // Read in the hugechunk region descriptors
    // for the old address space:
    //
    {
	int		  size;
	Hugechunk_Region_Header* boRgnHdr;

	boRegionTable = make_address_hashtable(LOG2_BOOK_BYTESIZE+1, header->hugechunk_ramregion_count);

	size = header->hugechunk_ramregion_count * sizeof(Hugechunk_Region_Header);

	boRgnHdr = (Hugechunk_Region_Header*) MALLOC (size);

	heapio__read_block( bp, boRgnHdr, size );

	boRelocInfo = MALLOC_VEC(Hugechunk_Region_Relocation_Info, header->hugechunk_ramregion_count);

	for (i = 0;  i < header->hugechunk_ramregion_count;  i++) {

	    set_book2sibid_entries_for_range(oldBOOK2SIBID,
		(Val*)(boRgnHdr[i].base_address),
		BOOKROUNDED_BYTESIZE(boRgnHdr[i].bytesize),
		HUGECHUNK_DATA_SIBID(1)
            );

	    oldBOOK2SIBID[GET_BOOK_CONTAINING_POINTEE(boRgnHdr[i].base_address)] = HUGECHUNK_RECORD_SIBID(MAX_AGEGROUPS);

	    boRelocInfo[i].first_ram_quantum = boRgnHdr[i].first_ram_quantum;

	    boRelocInfo[i].page_count
                =
                (boRgnHdr[i].bytesize - (boRgnHdr[i].first_ram_quantum - boRgnHdr[i].base_address))
                >>
                LOG2_HUGECHUNK_RAM_QUANTUM_IN_BYTES;

	    boRelocInfo[i].hugechunk_page_to_hugechunk = MALLOC_VEC(Hugechunk_Relocation_Info*, boRelocInfo[i].page_count);

	    for (j = 0;  j < boRelocInfo[i].page_count;  j++) {
	        //
		boRelocInfo[i].hugechunk_page_to_hugechunk[j] = NULL;
            } 
	    addresstable_insert (boRegionTable, boRgnHdr[i].base_address, &(boRelocInfo[i]));
	}
	FREE (boRgnHdr);
    }

    // Read the sib headers:
    //
    sib_headers_bytesize = header->active_agegroups * TOTAL_ILKS * sizeof( Sib_Header );
    //
    sib_headers = (Sib_Header*) MALLOC( sib_headers_bytesize );
    //
    heapio__read_block( bp, sib_headers, sib_headers_bytesize );

    for (i = 0;  i < MAX_PLAIN_ILKS;  i++) {
	prevSzB[i] = heap->agegroup0_buffer_bytesize;
    }

    // Allocate the sib buffers and read in the heap image:
    //
    for (p = sib_headers, i = 0;  i < header->active_agegroups;  i++) {
        //
	Agegroup*  age =  heap->agegroup[ i ];

	// Compute the space required for this agegroup,
	// and mark the oldBOOK2SIBID to reflect the old address space:
	//
	for (q = p, j = 0;  j < MAX_PLAIN_ILKS;  j++) {

	    set_book2sibid_entries_for_range (
		//
		oldBOOK2SIBID,

		(Val*) q->info.o.base_address,

		BOOKROUNDED_BYTESIZE( q->info.o.bytesize ),

		age->sib[ j ]->id
	    );

	    size = q->info.o.bytesize + prevSzB[j];

	    if (j == PAIR_ILK
            &&  size > 0
            ){
		size += 2*WORD_BYTESIZE;
	    }

	    age->sib[ j ]->tospace_bytesize
		=
		BOOKROUNDED_BYTESIZE( size );

	    prevSzB[ j ] =  q->info.o.bytesize;

	    q++;
	}

	if (allocate_and_partition_an_agegroup(age) == FAILURE) {
	    die ("unable to allocated space for agegroup %d\n", i+1);
        } 
	if (sib_is_active( age->sib[ VECTOR_ILK ] )) {							// sib_is_active	def in    src/c/h/heap.h
	    //
	    make_new_coarse_inter_agegroup_pointers_map_for_agegroup (age);
        }

	// Read in the sib buffers for this agegroup
	// and initialize the address offset table:
	//
	for (int j = 0;  j < MAX_PLAIN_ILKS;  j++) {
	    //
	    Sib* ap = age->sib[ j ];

	    if (p->info.o.bytesize > 0) {

		addrOffset[i][j] = (Punt)(ap->tospace) - (Punt)(p->info.o.base_address);

		heapio__seek( bp, (long) p->offset );

		heapio__read_block( bp, (ap->tospace), p->info.o.bytesize );

		ap->next_tospace_word_to_allocate  = (Val *)((Punt)(ap->tospace) + p->info.o.bytesize);
		ap->end_of_fromspace_oldstuff = ap->tospace;

	    } else if (sib_is_active(ap)) {

		ap->end_of_fromspace_oldstuff =  ap->tospace;
	    }

	    if (verbosity > 0)   say(".");

	    p++;
	}

        // Read in the hugechunk sib buffers (currently just codechunks):
        //
	for (int ilk = 0;  ilk < MAX_HUGE_ILKS;  ilk++) {			// MAX_HUGE_ILKS		def in    src/c/h/sibid.h
	    //	
	    Punt	 totSizeB;

	    Hugechunk* freeChunk;
	    Hugechunk* bdp = NULL;		// Without this initialization, gcc -Wall gives a 'possible uninitialized use' warning.

	    Hugechunk_Region*	 free_region;
	    Hugechunk_Header*	 boHdrs;

	    int			 boHdrSizeB;
	    int			 index;

	    Hugechunk_Region_Relocation_Info*  region;

	    if (p->info.bo.hugechunk_quanta_count > 0) {
		//
		totSizeB = p->info.bo.hugechunk_quanta_count << LOG2_HUGECHUNK_RAM_QUANTUM_IN_BYTES;

		freeChunk = allocate_hugechunk_region( heap, totSizeB );

		free_region = freeChunk->region;

		free_region->age_of_youngest_live_chunk_in_region
		    =
                    i;

		set_book2sibid_entries_for_range (
		    //
		    book_to_sibid__global,
                    (Val*) free_region,
		    BYTESIZE_OF_MULTIPAGE_RAM_REGION( free_region->ram_region ),
		    HUGECHUNK_DATA_SIBID( i )
		);

		book_to_sibid__global[ GET_BOOK_CONTAINING_POINTEE( free_region ) ]
		    =
		    HUGECHUNK_RECORD_SIBID( i );

	        // Read in the hugechunk headers:
                //
		boHdrSizeB = p->info.bo.hugechunk_count * sizeof(Hugechunk_Header);
		//
		boHdrs = (Hugechunk_Header*) MALLOC (boHdrSizeB);
		//
		heapio__read_block (bp, boHdrs, boHdrSizeB);

	        // Read in the hugechunks:
                //
		heapio__read_block( bp, (void *)(freeChunk->chunk), totSizeB );
		//
		if (ilk == CODE__HUGE_ILK) {					// ilk = 0 == CODE__HUGE_ILK	def in    src/c/h/sibid.h
		    //
		    flush_instruction_cache ((void *)(freeChunk->chunk), totSizeB);
		}

	        // Set up the hugechunk descriptors 
                // and per-chunk relocation info:
                //
		for (k = 0;  k < p->info.bo.hugechunk_count;  k++) {
		    //
		    // Find the region relocation info for the
		    // chunk's region in the exported heap:
		    //
		    for (index = GET_BOOK_CONTAINING_POINTEE(boHdrs[k].base_address);
			!SIBID_ID_IS_BIGCHUNK_RECORD(oldBOOK2SIBID[index]);
			index--)
			continue;

		    region = LOOK_UP_HUGECHUNK_REGION (boRegionTable, index);

		    // Allocate the hugechunk record for
		    // the chunk and link it into the list
                    // of hugechunks for its agegroup.
		    //
		    bdp = allocate_a_hugechunk( freeChunk, &(boHdrs[k]), region );

		    bdp->next = age->hugechunks[ ilk ];

		    age->hugechunks[ ilk ] = bdp;

		    ASSERT( bdp->gen == i+1 );

		    if (codechunk_comment_display_is_enabled__global
                    &&  ilk == CODE__HUGE_ILK
                    ){
		        // Dump the comment string of the code chunk.

			Unt8* namestring;
			//
			if ((namestring = get_codechunk_comment_string_else_null( bdp ))) {
			    debug_say ("[%6d bytes] %s\n", bdp->bytesize, (char*)namestring);
                        }
		    }
		}

		if (freeChunk != bdp) {					// if p->info.bo.hugechunk_count can be zero, 'bdp' value here may be bogus. XXX BUGGO FIXME.
		    //
		    // There was some extra space left in the region:
		    //
		    insert_hugechunk_in_doubly_linked_list( heap->hugechunk_freelist, freeChunk);						// insert_hugechunk_in_doubly_linked_list	def in   src/c/h/heap.h
		}

		FREE (boHdrs);
	    }

	    if (verbosity > 0)   say(".");

	    p++;
	}
    }

    repair_heap (heap, oldBOOK2SIBID, addrOffset, boRegionTable, externs);

    // Adjust the run-time globals
    // that point into the heap:
    //
    *PTR_CAST( Val*, PERVASIVE_PACKAGE_PICKLE_LIST_REFCELL__GLOBAL )
        =
        repair_word(
            *PTR_CAST( Val*, PERVASIVE_PACKAGE_PICKLE_LIST_REFCELL__GLOBAL ),
	    oldBOOK2SIBID,
            addrOffset,
            boRegionTable,
            externs
        );

    runtime_package__global = repair_word( runtime_package__global, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

#ifdef ASM_MATH
    mathvec__global = repair_word (mathvec__global, oldBOOK2SIBID, addrOffset, boRegionTable, externs);
#endif

    // Adjust the Mythryl registers
    // to the new address space:
    //
    ASSIGN(
        POSIX_INTERPROCESS_SIGNAL_HANDLER_REFCELL__GLOBAL,
	//
        repair_word (
	    //
	    DEREF( POSIX_INTERPROCESS_SIGNAL_HANDLER_REFCELL__GLOBAL ),
	    oldBOOK2SIBID,
	    addrOffset,
	    boRegionTable,
            externs
	)
    );

    task->argument
	=
	repair_word( task->argument, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->fate
	=
	repair_word( task->fate, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->current_closure
	=
	repair_word( task->current_closure, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->program_counter
	=
	repair_word(  task->program_counter, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->link_register
	=
	repair_word (task->link_register, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->exception_fate
	=
	repair_word( task->exception_fate, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->current_thread
	=
	repair_word( task->current_thread, oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->callee_saved_registers[0]
	=
	repair_word( task->callee_saved_registers[0], oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->callee_saved_registers[1]
	=
	repair_word( task->callee_saved_registers[1], oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    task->callee_saved_registers[2]
	=
	repair_word( task->callee_saved_registers[2], oldBOOK2SIBID, addrOffset, boRegionTable, externs );

    // Release storage:
    //
    for (i = 0; i < header->hugechunk_ramregion_count;  i++) {
      //
	Hugechunk_Relocation_Info*	p;
	for (p = NULL, j = 0;  j < boRelocInfo[i].page_count;  j++) {
	    if ((boRelocInfo[i].hugechunk_page_to_hugechunk[j] != NULL)
	    && (boRelocInfo[i].hugechunk_page_to_hugechunk[j] != p)) {
		FREE (boRelocInfo[i].hugechunk_page_to_hugechunk[j]);
		p = boRelocInfo[i].hugechunk_page_to_hugechunk[j];
	    }
	}
    }

    free_address_table( boRegionTable, FALSE );

    FREE( boRelocInfo    );
    FREE( sib_headers  );
    FREE( oldBOOK2SIBID       );

    // Reset the next_word_to_sweep_in_tospace pointers:
    //
    for (int i = 0;  i < heap->active_agegroups;  i++) {
        //
	Agegroup*	age =  heap->agegroup[i];
        //
	for (int j = 0;  j < MAX_PLAIN_ILKS;  j++) {
	    //
	    Sib* ap =  age->sib[ j ];
	    //
	    if (sib_is_active(ap)) {							// sib_is_active	def in    src/c/h/heap.h
		//
		ap->next_word_to_sweep_in_tospace
		    =
		    ap->next_tospace_word_to_allocate;
	    }
	}
    }
}                                                       // fun read_heap