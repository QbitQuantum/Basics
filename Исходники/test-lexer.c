void test4()
{
  const char* msg = "ERROR :Closing link: ([email protected]) [Ping "
                    "timeout: 121 seconds]\r\n";

  yi_buffer_t* buf = yi_buffer_create(msg, strlen(msg));

  // textual command
  ASSERT(yi_lex_command(buf), "");
  ASSERT(buf->token->type == YI_T_COMMAND, "");
  STRNCMP(buf->token->buf, "ERROR");

  // trailing parameter w/ space and colon
  ASSERT(yi_lex_param_trailing(buf), "");
  ASSERT(buf->token->type == YI_T_PARAM, "");
  STRNCMP(buf->token->buf,
          "Closing link: ([email protected]) [Ping timeout: 121 seconds]");

  // crlf
  ASSERT(yi_lex_terminal(buf, "\r\n", 2), "tokenize crlf");
  ASSERT(buf->token->type == YI_T_TERMINAL, "it's a terminal!");

  yi_buffer_destroy(buf);
}