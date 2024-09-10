String D2StatData::processRBF(Array<D2ItemStat>& list)
{
  int stat1 = -1, stat2 = -1;
  String text;
  if (findStat(list, &stats[197], 59) >= 0)
    text = "cold die ", stat1 = 335, stat2 = 331;
  else if (findStat(list, &stats[197], 56) >= 0)
    text = "fire die ", stat1 = 333, stat2 = 329;
  else if (findStat(list, &stats[197], 53) >= 0)
    text = "light die ", stat1 = 334, stat2 = 330;
  else if (findStat(list, &stats[197], 92) >= 0)
    text = "psn die ", stat1 = 336, stat2 = 332;
  else if (findStat(list, &stats[199], 44) >= 0)
    text = "cold up ", stat1 = 335, stat2 = 331;
  else if (findStat(list, &stats[199], 46) >= 0)
    text = "fire up ", stat1 = 333, stat2 = 329;
  else if (findStat(list, &stats[199], 48) >= 0)
    text = "light up ", stat1 = 334, stat2 = 330;
  else if (findStat(list, &stats[199], 278) >= 0)
    text = "psn up ", stat1 = 336, stat2 = 332;
  if (stat1 >= 0) stat1 = findStat(list, &stats[stat1]);
  if (stat2 >= 0) stat2 = findStat(list, &stats[stat2]);
  if (stat1 < 0 || stat2 < 0)
    return "";
  text.printf(" -%d/+%d", list[stat1].value1, list[stat2].value2);
  return text;
}