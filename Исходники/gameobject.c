void objecttimetolive(void)
  {
  int count;

  count=0;
  while (count<numofobjects)
    {
    if (object[count].timetolive<10000)
      object[count].timetolive--;
    while (count<numofobjects && object[count].timetolive<0)
      {
      deleteobject(count);

      if (object[count].timetolive<10000)
        object[count].timetolive--;
      }
    count++;
    }
  }