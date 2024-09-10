void clSFTP::Read(const wxString& remotePath, wxMemoryBuffer& buffer) throw(clException)
{
    if(!m_sftp) {
        throw clException("SFTP is not initialized");
    }

    sftp_file file = sftp_open(m_sftp, remotePath.mb_str(wxConvUTF8).data(), O_RDONLY, 0);
    if(file == NULL) {
        throw clException(wxString() << _("Failed to open remote file: ") << remotePath << ". "
                                     << ssh_get_error(m_ssh->GetSession()),
                          sftp_get_error(m_sftp));
    }

    SFTPAttribute::Ptr_t fileAttr = Stat(remotePath);
    if(!fileAttr) {
        throw clException(wxString() << _("Could not stat file:") << remotePath << ". "
                                     << ssh_get_error(m_ssh->GetSession()),
                          sftp_get_error(m_sftp));
    }
    wxInt64 fileSize = fileAttr->GetSize();
    if(fileSize == 0) return;

    // Allocate buffer for the file content
    char pBuffer[65536]; // buffer

    // Read the entire file content
    wxInt64 bytesLeft = fileSize;
    wxInt64 bytesRead = 0;
    while(bytesLeft > 0) {
        wxInt64 nbytes = sftp_read(file, pBuffer, sizeof(pBuffer));
        bytesRead += nbytes;
        bytesLeft -= nbytes;
        buffer.AppendData(pBuffer, nbytes);
    }

    if(bytesRead != fileSize) {
        sftp_close(file);
        buffer.Clear();
        throw clException(wxString() << _("Could not read file:") << remotePath << ". "
                                     << ssh_get_error(m_ssh->GetSession()),
                          sftp_get_error(m_sftp));
    }
    sftp_close(file);
}