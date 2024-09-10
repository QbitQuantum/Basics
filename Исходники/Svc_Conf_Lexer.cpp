int
ACE_Svc_Conf_Lexer::yylex (YYSTYPE* ace_yylval,
                           ACE_Svc_Conf_Param* param)
{
#if defined (ACE_USES_WCHAR)
  bool look_for_bom = false;
  ACE_Encoding_Converter_Factory::Encoding_Hint hint =
                ACE_Encoding_Converter_Factory::ACE_NONE;
#endif /* ACE_USES_WCHAR */
  if (param->buffer == 0)
    {
#if defined (ACE_USES_WCHAR)
      look_for_bom = true;
#endif /* ACE_USES_WCHAR */
      ACE_NEW_RETURN (param->buffer,
                      ace_yy_buffer_state,
                      -1);
    }

  int token = ACE_NO_STATE;
  do {
    if (param->buffer->need_more_)
      {
#if defined (ACE_USES_WCHAR)
        size_t skip_bytes = 0;
#endif /* ACE_USES_WCHAR */
        param->buffer->need_more_ = false;
        size_t amount =
               input (param,
                      param->buffer->input_ + param->buffer->size_,
                      normalize (ACE_YY_BUF_SIZE -
                                 param->buffer->size_));
        if (amount == 0)
          {
            param->buffer->eof_ = true;
#if defined (ACE_USES_WCHAR)
            skip_bytes = param->buffer->size_;
#endif /* ACE_USES_WCHAR */
          }
        else
          {
#if defined (ACE_USES_WCHAR)
            if (look_for_bom)
              {
                size_t read_more = 0;

                look_for_bom = false;
                hint = locate_bom (param->buffer->input_, amount, read_more);

                if (read_more != 0)
                  {
                    input (param,
                           param->buffer->input_ + amount,
                           read_more);
                    ACE_OS::memmove (param->buffer->input_,
                                     param->buffer->input_ + read_more,
                                     amount);
                  }
              }
            skip_bytes = param->buffer->size_;
#endif /* ACE_USES_WCHAR */
            param->buffer->size_ += amount;
          }

#if defined (ACE_USES_WCHAR)
        if (!convert_to_utf8 (param, skip_bytes, hint))
          {
            ace_yyerror (++param->yyerrno,
                         param->yylineno,
                         ACE_TEXT ("Unable to convert input stream to UTF-8"));
            return ACE_NO_STATE;
          }
#endif /* ACE_USES_WCHAR */
      }

    token = scan (ace_yylval, param);
  } while (token == ACE_NO_STATE && param->buffer->need_more_);

  return token;
}