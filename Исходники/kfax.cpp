void TopLevel::faxOpen( const KURL & url )
{
  if (!url.isValid())
    return;

  faxClose();
  faxAdd( url );

  fileURL = url;

  updateActions();
}