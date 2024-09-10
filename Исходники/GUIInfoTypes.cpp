void CGUIInfoColor::Parse(const CStdString &label, int context)
{
  // Check for the standard $INFO[] block layout, and strip it if present
  CStdString label2 = label;
  if (label.Equals("-", false))
    return;

  if (StringUtils::StartsWithNoCase(label, "$var["))
  {
    label2 = label.substr(5, label.length() - 6);
    m_info = g_infoManager.TranslateSkinVariableString(label2, context);
    if (!m_info)
      m_info = g_infoManager.RegisterSkinVariableString(g_SkinInfo->CreateSkinVariable(label2, context));
    return;
  }

  if (StringUtils::StartsWithNoCase(label, "$info["))
    label2 = label.substr(6, label.length()-7);

  m_info = g_infoManager.TranslateString(label2);
  if (!m_info)
    m_color = g_colorManager.GetColor(label);
}