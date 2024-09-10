FUNCTION int Q4WZ(obj Q5AO, obj Q4H5, obj user)
{
  transferAllResources(Q5AO, Q4H5);
  Q59B(Q5AO);
  obj Q5AB = NULL();
  if(hasObjVar(Q5AO, "myhousedoor"))
  {
    Q5AB = getobjvar_obj(Q5AO, "myhousedoor");
  }
  obj Q5AP = NULL();
  if(hasObjVar(Q5AO, "myhousesign"))
  {
    Q5AP = getobjvar_obj(Q5AO, "myhousesign");
  }
  string Q4F8 = getName(user);
  if(Q5AP != NULL())
  {
    setObjVar(Q5AP, "creatorId", user);
    setObjVar(Q5AP, "creatorName", Q4F8);
  }
  else
  {
    setObjVar(Q5AO, "creatorId", user);
    setObjVar(Q5AO, "creatorName", Q4F8);
  }
  int Q5NC = Q4WT(user, Q5AO, Q5AB, Q5AP, 0x00);
  Q5NC = Q4WT(user, Q5AO, Q5AB, Q5AP, 0x01);
  if(Q5AO != NULL())
  {
    deleteObject(Q4H5);
  }
  return(0x01);
}