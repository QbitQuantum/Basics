void CComposeFrame::OnSelectAddresses()
{
    CAddrDialog AddressDialog(this);
    GetComposeBar()->OnAddressTab();
    GetComposeBar()->UpdateWindow();
    CWnd * pWnd = GetFocus();
    AddressDialog.DoModal();
    pWnd->SetFocus();
}