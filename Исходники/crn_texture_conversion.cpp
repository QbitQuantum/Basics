      static bool convert_error(const convert_params& params, const wchar_t* pError_msg)
      {
         params.m_status = false;
         params.m_error_message = pError_msg;

         _wremove(params.m_dst_filename.get_ptr());

         return false;
      }