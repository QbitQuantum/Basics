ossimAnnotationObject* ossimAnnotationFontObject::getNewClippedObject(const ossimDrect& rect)const
{
   if(intersects(rect))
   {
      return (ossimAnnotationObject*)dup();
   }
   
   return (ossimAnnotationObject*)NULL;
}