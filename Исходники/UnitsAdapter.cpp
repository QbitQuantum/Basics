bool UnitsAdapter::isKindOf(const std::string& className) const
{
   if ((className == getObjectType()) || (className == "Units"))
   {
      return true;
   }

   return UnitsImp::isKindOf(className);
}