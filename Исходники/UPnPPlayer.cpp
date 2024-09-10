bool CUPnPPlayer::QueueNextFile(const CFileItem& file)
{
  CFileItem item(file);
  NPT_Reference<CThumbLoader> thumb_loader;
  NPT_Reference<PLT_MediaObject> obj;
  NPT_String path(file.GetPath().c_str());
  NPT_String tmp;

  if (file.IsVideoDb())
    thumb_loader = NPT_Reference<CThumbLoader>(new CVideoThumbLoader());
  else if (item.IsMusicDb())
    thumb_loader = NPT_Reference<CThumbLoader>(new CMusicThumbLoader());


  obj = BuildObject(item, path, 0, thumb_loader, NULL, CUPnP::GetServer(), UPnPPlayer);
  if(!obj.IsNull())
  {
    NPT_CHECK_LABEL_SEVERE(PLT_Didl::ToDidl(*obj, "", tmp), failed);
    tmp.Insert(didl_header, 0);
    tmp.Append(didl_footer);
  }

  NPT_CHECK_LABEL_WARNING(m_control->SetNextAVTransportURI(m_delegate->m_device
                                                         , m_delegate->m_instance
                                                         , file.GetPath().c_str()
                                                         , (const char*)tmp
                                                         , m_delegate), failed);
  if(!m_delegate->m_resevent.WaitMSec(10000)) goto failed;
  NPT_CHECK_LABEL_WARNING(m_delegate->m_resstatus, failed);
  return true;

failed:
  CLog::Log(LOGERROR, "UPNP: CUPnPPlayer::QueueNextFile - unable to queue file %s", file.GetPath().c_str());
  return false;
}