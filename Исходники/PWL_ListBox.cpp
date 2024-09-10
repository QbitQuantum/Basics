void CPWL_ListBox::DrawThisAppearance(CFX_RenderDevice* pDevice,
                                      CFX_Matrix* pUser2Device) {
  CPWL_Wnd::DrawThisAppearance(pDevice, pUser2Device);

  if (m_pList) {
    CFX_FloatRect rcPlate = m_pList->GetPlateRect();
    CFX_FloatRect rcList = GetListRect();
    CFX_FloatRect rcClient = GetClientRect();

    for (int32_t i = 0, sz = m_pList->GetCount(); i < sz; i++) {
      CFX_FloatRect rcItem = m_pList->GetItemRect(i);
      if (rcItem.bottom > rcPlate.top || rcItem.top < rcPlate.bottom)
        continue;

      CFX_FloatPoint ptOffset(rcItem.left, (rcItem.top + rcItem.bottom) * 0.5f);
      if (IFX_Edit* pEdit = m_pList->GetItemEdit(i)) {
        CFX_FloatRect rcContent = pEdit->GetContentRect();
        if (rcContent.Width() > rcClient.Width())
          rcItem.Intersect(rcList);
        else
          rcItem.Intersect(rcClient);
      }

      if (m_pList->IsItemSelected(i)) {
        CFX_SystemHandler* pSysHandler = GetSystemHandler();
        if (pSysHandler && pSysHandler->IsSelectionImplemented()) {
          IFX_Edit::DrawEdit(
              pDevice, pUser2Device, m_pList->GetItemEdit(i),
              CPWL_Utils::PWLColorToFXColor(GetTextColor()),
              CPWL_Utils::PWLColorToFXColor(GetTextStrokeColor()), rcList,
              ptOffset, nullptr, pSysHandler, m_pFormFiller);
          pSysHandler->OutputSelectedRect(m_pFormFiller, rcItem);
        } else {
          CPWL_Utils::DrawFillRect(pDevice, pUser2Device, rcItem,
                                   ArgbEncode(255, 0, 51, 113));
          IFX_Edit::DrawEdit(pDevice, pUser2Device, m_pList->GetItemEdit(i),
                             ArgbEncode(255, 255, 255, 255), 0, rcList,
                             ptOffset, nullptr, pSysHandler, m_pFormFiller);
        }
      } else {
        CFX_SystemHandler* pSysHandler = GetSystemHandler();
        IFX_Edit::DrawEdit(pDevice, pUser2Device, m_pList->GetItemEdit(i),
                           CPWL_Utils::PWLColorToFXColor(GetTextColor()),
                           CPWL_Utils::PWLColorToFXColor(GetTextStrokeColor()),
                           rcList, ptOffset, nullptr, pSysHandler, nullptr);
      }
    }
  }
}