D2Data::D2Data()
  : itemTypes(DictionaryMap::alNum)
  , baseItems(DictionaryMap::alNum)
  , images(DictionaryMap::pathName)
  , fonts(DictionaryMap::pathName)
{
  WideString path = cfg.getwstr("d2path");
  if (path.empty()) path = getAppPath();
  int loaded = !!loader.loadArchive(WideString::buildFullName(path, L"resources.mpq"));
  loaded += !!loader.loadArchive(WideString::buildFullName(path, L"d2data.mpq"));
  loaded += !!loader.loadArchive(WideString::buildFullName(path, L"d2exp.mpq"));
  loaded += !!loader.loadArchive(WideString::buildFullName(path, L"patch_d2.mpq"));
  if (!loaded)
  {
    path = getAppPath();
    loaded = !!loader.loadArchive(WideString::buildFullName(path, L"resources.mpq"));
  }
  if (!loaded) return;
  cfg.setwstr("d2path", path);

  for (int f = 0; f < 10; f++)
    for (int t = 0; t < 21; t++)
      for (int i = 0; i < 256; i++)
        tints[f][t][i] = i;
  TempFile(loader.load("data\\global\\items\\Palette\\grey.dat"))->read(tints[1], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\grey2.dat"))->read(tints[2], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\gold.dat"))->read(tints[3], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\brown.dat"))->read(tints[4], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\greybrown.dat"))->read(tints[5], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\invgrey.dat"))->read(tints[6], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\invgrey2.dat"))->read(tints[7], 256 * 21);
  TempFile(loader.load("data\\global\\items\\Palette\\invgreybrown.dat"))->read(tints[8], 256 * 21);
  LocalPtr<File> pal = loader.load("data\\global\\palette\\ACT1\\pal.dat");
  for (int i = 0; i < 256; i++)
  {
    int b = pal->getc(), g = pal->getc(), r = pal->getc();//, a = pal->getc();
    palette[i] = Image::clr(r, g, b);
  }

  memset(textColor, 0xFF, sizeof textColor);
  {
    LocalPtr<File> pl2 = loader.load("data\\global\\palette\\ACT1\\Pal.PL2");
    pl2->seek(1024 + 49 * 256, SEEK_SET);
    pl2->read(blendTable, sizeof blendTable);
    pl2->seek(1024 + 1714 * 256, SEEK_SET);
    for (int i = 0; i < 13; i++)
    {
      int r = pl2->getc(), g = pl2->getc(), b = pl2->getc();
      textColor[i] = Image::clr(r, g, b);
    }
    pl2->seek(256, SEEK_CUR);
    for (int i = 1; i < 13; i++)
      pl2->read(tints[9][i], 256);
  }

  strings.load(TempFile(loader.load("data\\local\\lng\\eng\\string.tbl")), 0);
  strings.load(TempFile(loader.load("data\\local\\lng\\eng\\expansionstring.tbl")), 20000);
  strings.load(TempFile(loader.load("data\\local\\lng\\eng\\patchstring.tbl")), 10000);

  rootType.name = "All Items";
  loadTypes(TempFile(loader.load("data\\global\\excel\\ItemTypes.txt")));
  loadBase(TempFile(loader.load("data\\global\\excel\\weapons.txt")));
  loadBase(TempFile(loader.load("data\\global\\excel\\armor.txt")));
  loadBase(TempFile(loader.load("data\\global\\excel\\misc.txt")));
  baseMatch.build();

  itemTypes.get("h2h2").bases = 0;
  itemTypes.get("mcha").name = strings.byIndex(20436);
  itemTypes.get("lcha").name = strings.byIndex(20437);
  itemTypes.get("ques").setType(D2Item::tMisc, 0, 0);
  itemTypes.get("key").setType(D2Item::tMisc, 0, 0);
  itemTypes.get("weap").setType(D2Item::tAuto, 0);
  itemTypes.get("armo").setType(D2Item::tAuto, 1);
  itemTypes.get("ring").setType(D2Item::tAuto, 2);
  itemTypes.get("amul").setType(D2Item::tAuto, 2);
  itemTypes.get("char").setType(D2Item::tCharm, 0);
  itemTypes.get("gem").setType(D2Item::tSocket, 0, 0);
  itemTypes.get("rune").setType(D2Item::tSocket, 1, 0);
  itemTypes.get("jewl").setType(D2Item::tSocket, 2);
  for (uint32 cur = baseItems.enumStart(); cur; cur = baseItems.enumNext(cur))
  {
    D2BaseItem* base = &baseItems.enumGetValue(cur);
    while (base->type && base->type->bases == 0)
      base->type = base->type->parent;
  }
  mergeType(&rootType);

  {
    D2Excel table(TempFile(loader.load("data\\global\\excel\\PlayerClass.txt")));
    int id = 0;
    for (int i = 0; i < table.rows(); i++)
    {
      if (!*table.value(i, 1))
        continue;
      charClass.set(table.value(i, 1), id);
      classNames[id] = strings.byName(table.value(i, 0));
      id++;
    }
  }
  statData = new D2StatData(this);

  loadUnique();
  loadGems();

  loadBackground();

  LocalPtr<mpq::ListFile> list = loader.buildListFile();
  list->sort();
  for (uint32 cur = baseItems.enumStart(); cur; cur = baseItems.enumNext(cur))
    unpack(&loader, list, baseItems.enumGetValue(cur).invfile);
  for (uint32 cur = itemTypes.enumStart(); cur; cur = itemTypes.enumNext(cur))
  {
    D2ItemType& type = itemTypes.enumGetValue(cur);
    for (int i = 0; i < type.invgfx.length(); i++)
      unpack(&loader, list, type.invgfx[i]);
  }
  for (int i = 0; i < uniqueItems.length(); i++)
    unpack(&loader, list, uniqueItems[i]->invfile);
}