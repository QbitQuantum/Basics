void ossimNitfSensraTag::setVertVelUnit(ossimString vertVelUnit)
{
   memset(theVertVelUnit, ' ', VERT_VEL_UNIT_SIZE);
   memcpy(theVertVelUnit, vertVelUnit.c_str(), std::min((size_t)VERT_VEL_UNIT_SIZE, vertVelUnit.length()));
}