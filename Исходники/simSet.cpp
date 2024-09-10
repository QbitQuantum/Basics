SimSet* SimSet::clone()
{
   // Clone the set object.
   
   SimObject* object = Parent::clone();
   SimSet* set = dynamic_cast< SimSet* >( object );
   if( !set )
   {
      object->deleteObject();
      return NULL;
   }
   
   // Add all object in the set.
   
   for( iterator iter = begin(); iter != end(); ++ iter )
      set->addObject( *iter );
   
   return set;
}