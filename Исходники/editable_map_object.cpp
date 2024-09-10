void EditableMapObject::SetName(string name, int8_t langCode)
{
  strings::Trim(name);
  if (name.empty())
    return;

  ASSERT_NOT_EQUAL(StringUtf8Multilang::kDefaultCode, langCode,
                   ("Direct editing of default name is deprecated."));

  if (!Editor::Instance().OriginalFeatureHasDefaultName(GetID()))
  {
    const auto mwmInfo = GetID().m_mwmId.GetInfo();

    if (mwmInfo)
    {
      vector<int8_t> mwmLanguages;
      mwmInfo->GetRegionData().GetLanguages(mwmLanguages);

      if (CanUseAsDefaultName(langCode, mwmLanguages))
        m_name.AddString(StringUtf8Multilang::kDefaultCode, name);
    }
  }

  m_name.AddString(langCode, name);
}