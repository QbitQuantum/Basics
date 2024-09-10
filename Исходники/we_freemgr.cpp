   const int FreeMgr::releaseSubblock( CommBlock &cb, DataBlock* blockZero, const int freemgr_type,  IdxEmptyListEntry* assignPtr ) 
   {
       int         rc;    // return code from file ops
       DataBlock   workBlock;
       DataBlock   extraBlock;
       int          listOffset; // entry in block zero of head pointer
       IdxEmptyListEntry emptyPtr, emptyMap ;
       uint64_t     numBlocks;
       FILE*       indexFile;
               
       indexFile = cb.file.pFile;
       /**
        * Release sub-block - handle de-allocation of only sub-blocks
        * This makes the assign/release code for smaller segments simpler and 
        * separates the tasks of handling the list containers and the list contents
        * When called, we look at the bucket indicated as head of chain and if it full
        * or not present (no room left in chain) then insert the returned SB as a bucket and 
        * move the head pointer
        **/
       
       
       //if( isDebug( DEBUG_1 )) { printf("DBG: releaseSubblock\n"); }
       if( isDebug( DEBUG_2 )) { 
           cout<<"DBG: releasing sb fbo "<<assignPtr->fbo<<" sbid "<<assignPtr->sbid<<" entry "<<assignPtr->entry<<" from "<<((freemgr_type==LIST)?"LIST":"TREE")<<" (type is "<<((assignPtr->type==EMPTY_PTR)?"EMPTY_PTR":"Not EMPTY_PTR")<<")\n";
       }
       if (!assignPtr){
//            printf ("DBG: Bad pointer: assignPtr is zero\n");
           return ERR_INVALID_PARAM;
       }

       if (!blockZero){
           printf ("DBG: Bad pointer: pointer for blockZero is zero\n");
           return ERR_INVALID_PARAM;
       }

       numBlocks = getFileSize( indexFile )/BYTE_PER_BLOCK ;
/*       if (assignPtr->fbo > numBlocks)
       {
       if( isDebug( DEBUG_1 )) { printf("DBG: Weirdness in releaseSubblock.. assignPtr.fbo > numBlocks (%llu %llu)\n", assignPtr->fbo, numBlocks );}
           return ERR_FM_BAD_FBO;
       }*/
       if (assignPtr->type != EMPTY_PTR)
       {
           printf("DBG: Weirdness in releaseSubblock.. tried to return a pointer with type %i (expected %i)\n", (unsigned int)assignPtr->type, EMPTY_PTR );
           return ERR_FM_BAD_TYPE;
       }
       if ( assignPtr->group != ENTRY_32 )
       {
           printf("DBG: Weirdness in releaseSubblock.. tried to return a pointer from group %i to subblock group\n", (unsigned int)assignPtr->group );
           return ERR_INVALID_PARAM;
       }           
       //find the start of the chain
       listOffset = calcPtrOffset( ENTRY_32 );

       getSubBlockEntry( blockZero, 0, listOffset, 8, &emptyPtr );
       if( isDebug( DEBUG_2 )) { 
          cout<<"DBG: EM (sb release 1) sb fbo "<<emptyPtr.fbo<<" sbid "<<emptyPtr.sbid<<" entry "<<emptyPtr.entry<<"\n";
       }

       //sub block is full or chain empty
       if (emptyPtr.entry == ENTRY_PER_SUBBLOCK-1 || emptyPtr.fbo==0)
       { 
       // change type from EMPTY_PTR to EMPTY_LIST 
           assignPtr->type = EMPTY_LIST;
           
           //if( isDebug( DEBUG_1 )) { printf("DBG: No room in subblock chain - need to add a sub-block\n");  }
           if( isDebug( DEBUG_2 )) { 
                   cout<<"DBG: Change head pointer to fbo "<<assignPtr->fbo<<" sbid "<<assignPtr->sbid<<" entry "<<assignPtr->entry<<"\n";
           }
           
           // change head pointer to released segment
           setSubBlockEntry( blockZero, 0, listOffset, 8, assignPtr );
           blockZero->dirty = 1;
           
           // read in released segment to set llp of new block to point to current head of chain
           rc = readDBFile( cb, extraBlock.data, assignPtr->fbo );
           if (rc != NO_ERROR){ 
               if (isDebug( DEBUG_1 )){
                   cout<<"DBG: File error during releaseSegment (2), rc: "<<rc<<" fbo/lbid: "<<assignPtr->fbo<<"\n"; 
               }
               return rc;
           }
           
           if( isDebug( DEBUG_2 )) { 
               cout<<"DBG: Set LLP for fbo "<<assignPtr->fbo<<" sbid "<<assignPtr->sbid<<" entry "<<assignPtr->entry<<"to fbo "<<emptyPtr.fbo<<" sbid "<<emptyPtr.sbid<<" entry "<<emptyPtr.entry<<"\n";
           }
           if( isDebug( DEBUG_3)){
               printf("Before\n");
               printMemSubBlock( &extraBlock, assignPtr->sbid );
           }
           
           emptyPtr.type = EMPTY_LIST;
           //memset( extraBlock.data, 0, BYTE_PER_SUBBLOCK);
           setSubBlockEntry( extraBlock.data, assignPtr->sbid, 0, 8, &emptyPtr );
           rc = writeDBFile( cb, &extraBlock, assignPtr->fbo );
           if (rc != NO_ERROR){ return rc; }
           
           if( isDebug( DEBUG_2 )) { 
               getSubBlockEntry( blockZero, 0, listOffset, 8, &emptyMap );
               cout<<"DBG: EM (sb release 2) sb fbo "<<emptyMap.fbo<<" sbid "<<emptyMap.sbid<<" entry "<<emptyMap.entry<<"\n";
           }
           if( isDebug( DEBUG_3)){
               printf("After\n");
               printMemSubBlock( &extraBlock, assignPtr->sbid );
           }
           
       }
       else 
       { // 
           emptyPtr.entry++;
           rc = readDBFile( cb, workBlock.data, emptyPtr.fbo );
           if (rc != NO_ERROR) { 
               if (isDebug( DEBUG_1 ))
               {
                   printf("DBG: File error during releaseSubblock\n"); 
               }
               return rc;
           }
           
           if( isDebug( DEBUG_3)){
               printf("Before\n");
               printMemSubBlock( &workBlock, emptyPtr.sbid );
           }

           setSubBlockEntry( workBlock.data, emptyPtr.sbid, emptyPtr.entry, 8, assignPtr );
           rc = writeDBFile( cb, &workBlock, emptyPtr.fbo );
           if (rc != NO_ERROR){ return rc; }

           if( isDebug( DEBUG_2 )) { 
               cout<<"DBG: setting emptyPtr sb fbo "<<emptyPtr.fbo<<" sbid "<<emptyPtr.sbid<<" entry "<<emptyPtr.entry<<"\n";
           }
           if( isDebug( DEBUG_3)){
               printf("After\n");
               printMemSubBlock( &workBlock, emptyPtr.sbid );
           }
           
           emptyPtr.type = EMPTY_LIST;
           emptyPtr.group = ENTRY_32;

           setSubBlockEntry( blockZero, 0, listOffset, 8, &emptyPtr );
           blockZero->dirty = 1;

       }
       uint64_t count;
       
       getSubBlockEntry( blockZero, 0, calcStatOffset(ENTRY_32) , 8, &count );
       count++;
       setSubBlockEntry( blockZero, 0, calcStatOffset(ENTRY_32) , 8, &count );
               

       return NO_ERROR;
   }