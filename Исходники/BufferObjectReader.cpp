double BufferObjectReader::readDouble()
{
   // We are reading the double as a 8 byte value
   BOOST_STATIC_ASSERT(sizeof(double) == 8);
   union
   {
     double      doubleVal;
     vpr::Uint64 intVal;
   } data;

   std::memcpy(&data.intVal, readRaw(8), 8);
   data.intVal = vpr::System::Ntohll(data.intVal);

   return data.doubleVal;
}