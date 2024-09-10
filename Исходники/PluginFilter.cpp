bool CPluginFilter::IsElementHidden(const std::wstring& tag, IHTMLElement* pEl, const std::wstring& domain, const std::wstring& indent) const
{
  std::wstring id;
  CComBSTR idBstr;
  if (SUCCEEDED(pEl->get_id(&idBstr)) && idBstr)
  {
    id = ToWstring(idBstr);
  }
  std::wstring classNames;
  CComBSTR classNamesBstr;
  if (SUCCEEDED(pEl->get_className(&classNamesBstr)) && classNamesBstr)
  {
    classNames = ToWstring(classNamesBstr);
  }

  CriticalSection::Lock filterEngineLock(s_criticalSectionFilterMap);
  {
    // Search tag/id filters
    if (!id.empty())
    {
      auto idItEnum = m_elementHideTagsId.equal_range(std::make_pair(tag, id));
      for (auto idIt = idItEnum.first; idIt != idItEnum.second; ++idIt)
      {
        if (idIt->second.IsMatchFilterElementHide(pEl))
        {
#ifdef ENABLE_DEBUG_RESULT
          DEBUG_HIDE_EL(indent + L"HideEl::Found (tag/id) filter:" + idIt->second.m_filterText);
          CPluginDebug::DebugResultHiding(tag, L"id:" + id, idIt->second.m_filterText);
#endif
          return true;
        }
      }

      // Search general id
      idItEnum = m_elementHideTagsId.equal_range(std::make_pair(L"", id));
      for (auto idIt = idItEnum.first; idIt != idItEnum.second; ++idIt)
      {
        if (idIt->second.IsMatchFilterElementHide(pEl))
        {
#ifdef ENABLE_DEBUG_RESULT
          DEBUG_HIDE_EL(indent + L"HideEl::Found (?/id) filter:" + idIt->second.m_filterText);
          CPluginDebug::DebugResultHiding(tag, L"id:" + id, idIt->second.m_filterText);
#endif
          return true;
        }
      }
    }

    // Search tag/className filters
    if (!classNames.empty())
    {
      wchar_t* nextToken = nullptr;
      const wchar_t* token = wcstok_s(&classNames[0], L" \t\n\r", &nextToken);
      while (token != nullptr)
      {
        std::wstring className(token);
        auto classItEnum = m_elementHideTagsClass.equal_range(std::make_pair(tag, className));
        for (auto classIt = classItEnum.first; classIt != classItEnum.second; ++classIt)
        {
          if (classIt->second.IsMatchFilterElementHide(pEl))
          {
#ifdef ENABLE_DEBUG_RESULT
            DEBUG_HIDE_EL(indent + L"HideEl::Found (tag/class) filter:" + classIt->second.m_filterText);
            CPluginDebug::DebugResultHiding(tag, L"class:" + className, classIt->second.m_filterText);
#endif
            return true;
          }
        }

        // Search general class name
        classItEnum = m_elementHideTagsClass.equal_range(std::make_pair(L"", className));
        for (auto classIt = classItEnum.first; classIt != classItEnum.second; ++ classIt)
        {
          if (classIt->second.IsMatchFilterElementHide(pEl))
          {
#ifdef ENABLE_DEBUG_RESULT
            DEBUG_HIDE_EL(indent + L"HideEl::Found (?/class) filter:" + classIt->second.m_filterText);
            CPluginDebug::DebugResultHiding(tag, L"class:" + className, classIt->second.m_filterText);
#endif
            return true;
          }
        }
        token = wcstok_s(nullptr, L" \t\n\r", &nextToken);
      }
    }

    // Search tag filters
    auto tagItEnum = m_elementHideTags.equal_range(tag);
    for (auto tagIt = tagItEnum.first; tagIt != tagItEnum.second; ++tagIt)
    {
      if (tagIt->second.IsMatchFilterElementHide(pEl))
      {
#ifdef ENABLE_DEBUG_RESULT
        DEBUG_HIDE_EL(indent + L"HideEl::Found (tag) filter:" + tagIt->second.m_filterText);
        CPluginDebug::DebugResultHiding(tag, L"-", tagIt->second.m_filterText);
#endif
        return true;
      }
    }
  }

  return false;
}