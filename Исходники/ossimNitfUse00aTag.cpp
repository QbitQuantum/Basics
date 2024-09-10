void ossimNitfUse00aTag::setAngleToNorth(const ossimString& angleToNorth)
{
   memset(theAngleToNorth, ' ', ANGLE_TO_NORTH_SIZE);
   memcpy(theAngleToNorth, angleToNorth.c_str(), std::min((size_t)ANGLE_TO_NORTH_SIZE, angleToNorth.length()));
}