 void destroyDictionary() {
    for ( unsigned int reg_id = 1; reg_id < _object->getRegionNodeCount()+1; reg_id += 1 ) {
       NewNewDirectoryEntryData *entry = ( NewNewDirectoryEntryData * ) _object->getRegionData( reg_id );
       delete entry;
    }
    delete _object;
    _object = NULL;
 }