   void console::vprintf(eConsoleMessageType type, const wchar_t* p, va_list args)
   {
      init();

      scoped_mutex lock(*m_pMutex);

      m_num_messages[type]++;

      wchar_t buf[cConsoleBufSize];
#ifdef _MSC_VER
      vswprintf_s(buf, cConsoleBufSize, p, args);
#else
      vswprintf(buf, p, args);
#endif

      bool handled = false;

      if (m_output_funcs.size())
      {
         for (uint i = 0; i < m_output_funcs.size(); i++)
            if (m_output_funcs[i].m_func(type, buf, m_output_funcs[i].m_pData))
               handled = true;
      }

      const wchar_t* pPrefix = NULL;
      if (m_prefixes)
      {
         switch (type)
         {
            case cDebugConsoleMessage:    pPrefix = L"Debug: ";   break;
            case cWarningConsoleMessage:  pPrefix = L"Warning: "; break;
            case cErrorConsoleMessage:    pPrefix = L"Error: ";   break;
            default: break;
         }
      }

      if ((!m_output_disabled) && (!handled))
      {
#ifdef _XBOX
         if (pPrefix)
            OutputDebugStringW(pPrefix);
         OutputDebugStringW(buf);
         if (m_crlf)
            OutputDebugStringW(L"\n");
#else
         if (pPrefix)
            ::wprintf(pPrefix);
         ::wprintf(m_crlf ? L"%s\n" : L"%s", buf);
#endif
      }

      if ((type != cProgressConsoleMessage) && (m_pLog_stream))
      {
         // Yes this is bad.
         dynamic_wstring utf16_buf(buf);

         dynamic_string ansi_buf;
         utf16_buf.as_ansi(ansi_buf);
         ansi_buf.translate_lf_to_crlf();

         m_pLog_stream->printf(m_crlf ? "%s\r\n" : "%s", ansi_buf.get_ptr());
         m_pLog_stream->flush();
      }
   }