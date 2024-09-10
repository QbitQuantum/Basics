bool SignatureFileDescriptorAdapter::isKindOf(const std::string& className) const
{
   if ((className == getObjectType()) || (className == "SignatureFileDescriptor"))
   {
      return true;
   }

   return SignatureFileDescriptorImp::isKindOf(className);
}