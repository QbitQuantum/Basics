//! Get the information from resource in a resource list specified
//  by its position in the list.
void ResourceList::getResourceInfoAt(size_t at,
                                     UtlString& uri,
                                     UtlString& nameXml,
                                     UtlString& display_name)
{
   uri.remove(0);
   nameXml.remove(0);
   display_name.remove(0);

   ResourceReference* resource =
      dynamic_cast <ResourceReference*> (mResourcesList.at(at));
   if (resource)
   {
      uri = *resource->getUri();
      nameXml = *resource->getNameXml();
      display_name = *resource->getDisplayName();
   }
}