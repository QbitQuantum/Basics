void Info::GetPrefferedNames(std::string & primaryName, std::string & secondaryName) const
{
  auto const mwmInfo = GetID().m_mwmId.GetInfo();
  if (mwmInfo)
  {
    auto const deviceLang = StringUtf8Multilang::GetLangIndex(languages::GetCurrentNorm());
    feature::GetPreferredNames(mwmInfo->GetRegionData(), m_name, deviceLang,
                               true /* allowTranslit */, primaryName, secondaryName);
  }
}