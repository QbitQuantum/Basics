const VirtualFunctionTableEntry* VirtualClass::getDefaultConstructor() const
{
   String name = mName;
   std::size_t pos = mName.lastIndexOf('.');
   if ( pos != String::npos )
   {
      name.remove(0, pos + 1);
   }

   return mVTable.findByName(name);
}