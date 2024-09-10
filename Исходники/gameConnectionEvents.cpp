void SimDataBlockEvent::unpack(NetConnection *cptr, BitStream *bstream)
{
   if(bstream->readFlag())
   {
      mProcess = true;
      id = bstream->readInt(DataBlockObjectIdBitSize) + DataBlockObjectIdFirst;
      S32 classId = bstream->readClassId(NetClassTypeDataBlock, cptr->getNetClassGroup());
      mIndex = bstream->readInt(DataBlockObjectIdBitSize);
      mTotal = bstream->readInt(DataBlockObjectIdBitSize + 1);
      
      SimObject* ptr;
      if( Sim::findObject( id, ptr ) )
      {
         // An object with the given ID already exists.  Make sure it has the right class.
         
         AbstractClassRep* classRep = AbstractClassRep::findClassRep( cptr->getNetClassGroup(), NetClassTypeDataBlock, classId );
         if( classRep && dStrcmp( classRep->getClassName(), ptr->getClassName() ) != 0 )
         {
            Con::warnf( "A '%s' datablock with id: %d already existed. "
                        "Clobbering it with new '%s' datablock from server.",
                        ptr->getClassName(), id, classRep->getClassName() );
            ptr->deleteObject();
            ptr = NULL;
         }
      }
      
      if( !ptr )
         ptr = ( SimObject* ) ConsoleObject::create( cptr->getNetClassGroup(), NetClassTypeDataBlock, classId );
         
      mObj = dynamic_cast< SimDataBlock* >( ptr );
      if( mObj != NULL )
      {
         #ifdef DEBUG_SPEW
         Con::printf(" - SimDataBlockEvent: unpacking event of type: %s", mObj->getClassName());
         #endif
         
         mObj->unpackData( bstream );
      }
      else
      {
         #ifdef DEBUG_SPEW
         Con::printf(" - SimDataBlockEvent: INVALID PACKET!  Could not create class with classID: %d", classId);
         #endif
         
         delete ptr;
         cptr->setLastError("Invalid packet in SimDataBlockEvent::unpack()");
      }

#ifdef TORQUE_DEBUG_NET
      U32 checksum = bstream->readInt(32);
      AssertISV( (checksum ^ DebugChecksum) == (U32)classId,
         avar("unpack did not match pack for event of class %s.",
            mObj->getClassName()) );
#endif

   }
}