    virtual wxDirTraverseResult OnFile(const wxString& filename) {
        wxFileName temp = filename;
        wxString shastr = wxT("0");
        unsigned long ovlversion = 0;
        int modtime = temp.GetModificationTime().GetTicks();
        wxFileOffset size = 0;

        if (wxFile::Access(filename.c_str(), wxFile::read)) {
            m_sha.Reset();
            /*
            wxFile f(filename, wxFile::read);
            counted_array_ptr<unsigned char> buf(new unsigned char[f.Length()]);
            size = f.Length();
            f.Read(buf.get(), f.Length());
            m_sha.Input(buf.get(), f.Length());
            */
            size = m_sha.Input(filename);
            shastr = m_sha.Result();

            if (filename.Lower().EndsWith(wxT(".common.ovl"))) {
                cOVLDump dovl;
                dovl.Load(filename.mb_str(wxConvFile));
                ovlversion = dovl.GetVersion();
            }
        }

        temp.MakeRelativeTo(m_root.GetPath(wxPATH_GET_SEPARATOR | wxPATH_GET_VOLUME));
        m_buf.Format("insert into vanilla values ('%q', '%q', %d, %lld, %ld);", temp.GetFullPath().mb_str(wxConvUTF8).data(), shastr.mb_str(wxConvUTF8).data(), modtime, size, ovlversion);
        m_db->ExecuteUpdate(m_buf);
        m_pd.Pulse(temp.GetFullPath());
        return wxDIR_CONTINUE;
    }