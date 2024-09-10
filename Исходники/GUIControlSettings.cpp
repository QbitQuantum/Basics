bool CGUIControlListSetting::GetIntegerItems(const CSetting *setting, CFileItemList &items)
{
  const CSettingInt *pSettingInt = NULL;
  std::set<int> values;
  if (setting->GetType() == SettingTypeInteger)
  {
    pSettingInt = static_cast<const CSettingInt*>(setting);
    values.insert(pSettingInt->GetValue());
  }
  else if (setting->GetType() == SettingTypeList)
  {
    const CSettingList *settingList = static_cast<const CSettingList*>(setting);
    if (settingList->GetElementType() != SettingTypeInteger)
      return false;

    pSettingInt = static_cast<const CSettingInt*>(settingList->GetDefinition());
    std::vector<CVariant> list = CSettingUtils::GetList(settingList);
    for (std::vector<CVariant>::const_iterator itValue = list.begin(); itValue != list.end(); ++itValue)
    {
      if (!itValue->isInteger())
        return false;
      values.insert((int)itValue->asInteger());
    }
  }
  else
    return false;

  switch (pSettingInt->GetOptionsType())
  {
    case SettingOptionsTypeStatic:
    {
      const StaticIntegerSettingOptions& options = pSettingInt->GetOptions();
      for (StaticIntegerSettingOptions::const_iterator it = options.begin(); it != options.end(); ++it)
      {
        CFileItemPtr pItem = GetItem(g_localizeStrings.Get(it->first), it->second);

        if (values.find(it->second) != values.end())
          pItem->Select(true);

        items.Add(pItem);
      }
      break;
    }

    case SettingOptionsTypeDynamic:
    {
      DynamicIntegerSettingOptions options = const_cast<CSettingInt*>(pSettingInt)->UpdateDynamicOptions();
      for (DynamicIntegerSettingOptions::const_iterator option = options.begin(); option != options.end(); ++option)
      {
        CFileItemPtr pItem = GetItem(option->first, option->second);

        if (values.find(option->second) != values.end())
          pItem->Select(true);

        items.Add(pItem);
      }
      break;
    }

    case SettingOptionsTypeNone:
    default:
      return false;
  }

  return true;
}