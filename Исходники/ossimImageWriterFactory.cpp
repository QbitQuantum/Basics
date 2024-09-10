ossimObject* ossimImageWriterFactory::createObject(const ossimKeywordlist& kwl,
                                                   const char *prefix)const
{
   return createWriter(kwl, prefix);
}