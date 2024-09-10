// ---------------------------------------------------------------------------
// Pop and destroy a dir entry from a dir entry queue
// ---------------------------------------------------------------------------
//
void CMPXFolderScanner::CDirQueueEntry::PopAndDestroy(
                                  RPointerArray< CDirQueueEntry >& aDirQueue )
    {
    CDirQueueEntry* entry = aDirQueue[ 0 ];
    delete entry;
    aDirQueue.Remove( 0 );
    }