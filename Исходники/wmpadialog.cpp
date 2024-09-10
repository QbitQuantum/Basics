void CWMPADialog::UpdateSongList()
{
   char buffer[32];
   CString name;
   CString artist;
   CString title;
   CString album;
   CString bitrate;
   CString duration;
   CString song;
   long index;
   long count;

   m_SongListBox.ResetContent();
   CWMPPlaylist playlist = m_WMP.GetCurrentPlaylist();
   count = playlist.GetCount();
   m_SongListBox.ResetContent();
   for (index = 0; index < count; index++) {
      name         = playlist.GetItem(index).GetName();
      artist       = playlist.GetItem(index).getItemInfo("Artist");
      title        = playlist.GetItem(index).getItemInfo("Title");
      album        = playlist.GetItem(index).getItemInfo("Album");
      bitrate      = playlist.GetItem(index).getItemInfo("Bitrate");
      duration     = playlist.GetItem(index).GetDurationString();

      long krate = strtoul((LPCTSTR) bitrate, NULL, 10) / 1000;
      _ultoa(krate, buffer, 10);
      bitrate = CString(buffer);

      if (album.IsEmpty()) {
         playlist.removeItem(playlist.GetItem(index));
         count = playlist.GetCount();
      }
      else {
         song = "";
         song += artist;
         if (song.IsEmpty()) song = "Various";
         song += " - ";
         song += title;
         song += " (";
         song += album;
         song += ") [";
         song += duration;
         song += "/";
         song += bitrate;
         song += "Kbps]";
         m_SongListBox.AddString((LPCTSTR) song);
      }

   }
   m_SongListBox.SetCurSel(0);
}