/// returns if given object is a NPC object
inline bool IsNpcObject(const ObjectPtr& ptr)
{
   return ptr->GetObjectType() == objectNpc;
}