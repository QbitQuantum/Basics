FUNCTION void Q64G(obj Q4F0, obj Q62D, int Q571)
{
  int Q63U;
  list metal;
  clearList(metal);
  Q4S8(metal, Q62D);
  for(int num = numInList(metal); num > 0x00; num --)
  {
    int Q56Z;
    obj Q5UD = metal[0x00];
    int Q4Q1 = getResource(Q56Z, Q5UD, "metal", 0x03, 0x02);
    if(Q571 >= Q56Z)
    {
      transferResources(Q4F0, Q5UD, Q56Z, "metal");
      deleteObject(Q5UD);
      removeItem(metal, 0x00);
      Q571 = Q571 - Q56Z;
    }
    else
    {
      transferResources(Q4F0, Q5UD, Q571, "metal");
      Q4Q1 = getResource(Q56Z, Q5UD, "metal", 0x03, 0x02);
      if(Q56Z < 0x01)
      {
        deleteObject(Q5UD);
      }
      break;
    }
  }
  clearList(metal);
  return;
}