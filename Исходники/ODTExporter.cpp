void ODTExporter::ODTCreateCommonFiles(wxZipOutputStream &zout)
{
  zout.PutNextEntry(_T("META-INF/manifest.xml"));
  zout.Write(ODTManifestFile, strlen(ODTManifestFile));
  zout.PutNextEntry(_T("meta.xml"));
  zout.Write(ODTMetaFile, strlen(ODTMetaFile));
  zout.PutNextEntry(_T("mimetype"));
  zout.Write(ODTMIMETypeFile, strlen(ODTMIMETypeFile));
  zout.PutNextEntry(_T("settings.xml"));
  zout.Write(ODTSettingsFile, strlen(ODTSettingsFile));
}