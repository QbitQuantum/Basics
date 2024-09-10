bool GeoreferenceDescriptorAdapter::isKindOf(const std::string& className) const
{
   if ((className == getObjectType()) || (className == "GeoreferenceDescriptor"))
   {
      return true;
   }

   return GeoreferenceDescriptorImp::isKindOf(className);
}