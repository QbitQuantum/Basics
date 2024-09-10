size_t http_parser_execute (http_parser *parser,
                            const http_parser_settings *settings,
                            const char *data,
                            size_t len)
{
  char c, ch;
  int8_t unhex_val;
  const char *p = data, *pe;
  int64_t to_read;
  enum state state;
  enum header_states header_state;
  uint64_t index = parser->index;
  uint64_t nread = parser->nread;

  /* technically we could combine all of these (except for url_mark) into one
     variable, saving stack space, but it seems more clear to have them
     separated. */
  const char *header_field_mark = 0;
  const char *header_value_mark = 0;
  const char *url_mark = 0;

  /* We're in an error state. Don't bother doing anything. */
  if (HTTP_PARSER_ERRNO(parser) != HPE_OK) {
    return 0;
  }

  state = (enum state) parser->state;
  header_state = (enum header_states) parser->header_state;

  if (len == 0) {
    switch (state) {
      case s_body_identity_eof:
        CALLBACK2(message_complete);
        return 0;

      case s_dead:
      case s_start_req_or_res:
      case s_start_res:
      case s_start_req:
        return 0;

      default:
        SET_ERRNO(HPE_INVALID_EOF_STATE);
        return 1;
    }
  }


  if (state == s_header_field)
    header_field_mark = data;
  if (state == s_header_value)
    header_value_mark = data;
  if (state == s_req_path || state == s_req_schema || state == s_req_schema_slash
      || state == s_req_schema_slash_slash || state == s_req_port
      || state == s_req_query_string_start || state == s_req_query_string
      || state == s_req_host
      || state == s_req_fragment_start || state == s_req_fragment)
    url_mark = data;

  for (p=data, pe=data+len; p != pe; p++) {
    ch = *p;

    if (PARSING_HEADER(state)) {
      ++nread;
      /* Buffer overflow attack */
      if (nread > HTTP_MAX_HEADER_SIZE) {
        SET_ERRNO(HPE_HEADER_OVERFLOW);
        goto error;
      }
    }

    switch (state) {

      case s_dead:
        /* this state is used after a 'Connection: close' message
         * the parser will error out if it reads another message
         */
        SET_ERRNO(HPE_CLOSED_CONNECTION);
        goto error;

      case s_start_req_or_res:
      {
        if (ch == CR || ch == LF)
          break;
        parser->flags = 0;
        parser->content_length = -1;

        CALLBACK2(message_begin);

        if (ch == 'H')
          state = s_res_or_resp_H;
        else {
          parser->type = HTTP_REQUEST;
          goto start_req_method_assign;
        }
        break;
      }

      case s_res_or_resp_H:
        if (ch == 'T') {
          parser->type = HTTP_RESPONSE;
          state = s_res_HT;
        } else {
          if (ch != 'E') {
            SET_ERRNO(HPE_INVALID_CONSTANT);
            goto error;
          }

          parser->type = HTTP_REQUEST;
          parser->method = HTTP_HEAD;
          index = 2;
          state = s_req_method;
        }
        break;

      case s_start_res:
      {
        parser->flags = 0;
        parser->content_length = -1;

        CALLBACK2(message_begin);

        switch (ch) {
          case 'H':
            state = s_res_H;
            break;

          case CR:
          case LF:
            break;

          default:
            SET_ERRNO(HPE_INVALID_CONSTANT);
            goto error;
        }
        break;
      }

      case s_res_H:
        STRICT_CHECK(ch != 'T');
        state = s_res_HT;
        break;

      case s_res_HT:
        STRICT_CHECK(ch != 'T');
        state = s_res_HTT;
        break;

      case s_res_HTT:
        STRICT_CHECK(ch != 'P');
        state = s_res_HTTP;
        break;

      case s_res_HTTP:
        STRICT_CHECK(ch != '/');
        state = s_res_first_http_major;
        break;

      case s_res_first_http_major:
        if (ch < '0' || ch > '9') {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_major = ch - '0';
        state = s_res_http_major;
        break;

      /* major HTTP version or dot */
      case s_res_http_major:
      {
        if (ch == '.') {
          state = s_res_first_http_minor;
          break;
        }

        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_major *= 10;
        parser->http_major += ch - '0';

        if (parser->http_major > 999) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        break;
      }

      /* first digit of minor HTTP version */
      case s_res_first_http_minor:
        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_minor = ch - '0';
        state = s_res_http_minor;
        break;

      /* minor HTTP version or end of request line */
      case s_res_http_minor:
      {
        if (ch == ' ') {
          state = s_res_first_status_code;
          break;
        }

        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_minor *= 10;
        parser->http_minor += ch - '0';

        if (parser->http_minor > 999) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        break;
      }

      case s_res_first_status_code:
      {
        if (!IS_NUM(ch)) {
          if (ch == ' ') {
            break;
          }

          SET_ERRNO(HPE_INVALID_STATUS);
          goto error;
        }
        parser->status_code = ch - '0';
        state = s_res_status_code;
        break;
      }

      case s_res_status_code:
      {
        if (!IS_NUM(ch)) {
          switch (ch) {
            case ' ':
              state = s_res_status;
              break;
            case CR:
              state = s_res_line_almost_done;
              break;
            case LF:
              state = s_header_field_start;
              break;
            default:
              SET_ERRNO(HPE_INVALID_STATUS);
              goto error;
          }
          break;
        }

        parser->status_code *= 10;
        parser->status_code += ch - '0';

        if (parser->status_code > 999) {
          SET_ERRNO(HPE_INVALID_STATUS);
          goto error;
        }

        break;
      }

      case s_res_status:
        /* the human readable status. e.g. "NOT FOUND"
         * we are not humans so just ignore this */
        if (ch == CR) {
          state = s_res_line_almost_done;
          break;
        }

        if (ch == LF) {
          state = s_header_field_start;
          break;
        }
        break;

      case s_res_line_almost_done:
        STRICT_CHECK(ch != LF);
        state = s_header_field_start;
        break;

      case s_start_req:
      {
        if (ch == CR || ch == LF)
          break;
        parser->flags = 0;
        parser->content_length = -1;

        CALLBACK2(message_begin);

        if (!IS_ALPHA(ch)) {
          SET_ERRNO(HPE_INVALID_METHOD);
          goto error;
        }

      start_req_method_assign:
        parser->method = (enum http_method) 0;
        index = 1;
        switch (ch) {
          case 'C': parser->method = HTTP_CONNECT; /* or COPY, CHECKOUT */ break;
          case 'D': parser->method = HTTP_DELETE; break;
          case 'G': parser->method = HTTP_GET; break;
          case 'H': parser->method = HTTP_HEAD; break;
          case 'L': parser->method = HTTP_LOCK; break;
          case 'M': parser->method = HTTP_MKCOL; /* or MOVE, MKACTIVITY, MERGE, M-SEARCH */ break;
          case 'N': parser->method = HTTP_NOTIFY; break;
          case 'O': parser->method = HTTP_OPTIONS; break;
          case 'P': parser->method = HTTP_POST;
            /* or PROPFIND or PROPPATCH or PUT or PATCH */
            break;
          case 'R': parser->method = HTTP_REPORT; break;
          case 'S': parser->method = HTTP_SUBSCRIBE; break;
          case 'T': parser->method = HTTP_TRACE; break;
          case 'U': parser->method = HTTP_UNLOCK; /* or UNSUBSCRIBE */ break;
          default:
            SET_ERRNO(HPE_INVALID_METHOD);
            goto error;
        }
        state = s_req_method;
        break;
      }

      case s_req_method:
      {
        const char *matcher;
        if (ch == '\0') {
          SET_ERRNO(HPE_INVALID_METHOD);
          goto error;
        }

        matcher = method_strings[parser->method];
        if (ch == ' ' && matcher[index] == '\0') {
          state = s_req_spaces_before_url;
        } else if (ch == matcher[index]) {
          ; /* nada */
        } else if (parser->method == HTTP_CONNECT) {
          if (index == 1 && ch == 'H') {
            parser->method = HTTP_CHECKOUT;
          } else if (index == 2  && ch == 'P') {
            parser->method = HTTP_COPY;
          } else {
            goto error;
          }
        } else if (parser->method == HTTP_MKCOL) {
          if (index == 1 && ch == 'O') {
            parser->method = HTTP_MOVE;
          } else if (index == 1 && ch == 'E') {
            parser->method = HTTP_MERGE;
          } else if (index == 1 && ch == '-') {
            parser->method = HTTP_MSEARCH;
          } else if (index == 2 && ch == 'A') {
            parser->method = HTTP_MKACTIVITY;
          } else {
            goto error;
          }
        } else if (index == 1 && parser->method == HTTP_POST) {
          if (ch == 'R') {
            parser->method = HTTP_PROPFIND; /* or HTTP_PROPPATCH */
          } else if (ch == 'U') {
            parser->method = HTTP_PUT;
          } else if (ch == 'A') {
            parser->method = HTTP_PATCH;
          } else {
            goto error;
          }
        } else if (index == 2 && parser->method == HTTP_UNLOCK && ch == 'S') {
          parser->method = HTTP_UNSUBSCRIBE;
        } else if (index == 4 && parser->method == HTTP_PROPFIND && ch == 'P') {
          parser->method = HTTP_PROPPATCH;
        } else {
          SET_ERRNO(HPE_INVALID_METHOD);
          goto error;
        }

        ++index;
        break;
      }
      case s_req_spaces_before_url:
      {
        if (ch == ' ') break;

        if (ch == '/' || ch == '*') {
          MARK(url);
          state = s_req_path;
          break;
        }

        /* Proxied requests are followed by scheme of an absolute URI (alpha).
         * CONNECT is followed by a hostname, which begins with alphanum.
         * All other methods are followed by '/' or '*' (handled above).
         */
        if (IS_ALPHA(ch) || (parser->method == HTTP_CONNECT && IS_NUM(ch))) {
          MARK(url);
          state = (parser->method == HTTP_CONNECT) ? s_req_host : s_req_schema;
          break;
        }

        SET_ERRNO(HPE_INVALID_URL);
        goto error;
      }

      case s_req_schema:
      {
        if (IS_ALPHA(ch)) break;

        if (ch == ':') {
          state = s_req_schema_slash;
          break;
        }

        SET_ERRNO(HPE_INVALID_URL);
        goto error;
      }

      case s_req_schema_slash:
        STRICT_CHECK(ch != '/');
        state = s_req_schema_slash_slash;
        break;

      case s_req_schema_slash_slash:
        STRICT_CHECK(ch != '/');
        state = s_req_host;
        break;

      case s_req_host:
      {
        if (IS_HOST_CHAR(ch)) break;
        switch (ch) {
          case ':':
            state = s_req_port;
            break;
          case '/':
            state = s_req_path;
            break;
          case ' ':
            /* The request line looks like:
             *   "GET http://foo.bar.com HTTP/1.1"
             * That is, there is no path.
             */
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case '?':
            state = s_req_query_string_start;
            break;
          default:
            SET_ERRNO(HPE_INVALID_HOST);
            goto error;
        }
        break;
      }

      case s_req_port:
      {
        if (IS_NUM(ch)) break;
        switch (ch) {
          case '/':
            state = s_req_path;
            break;
          case ' ':
            /* The request line looks like:
             *   "GET http://foo.bar.com:1234 HTTP/1.1"
             * That is, there is no path.
             */
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case '?':
            state = s_req_query_string_start;
            break;
          default:
            SET_ERRNO(HPE_INVALID_PORT);
            goto error;
        }
        break;
      }

      case s_req_path:
      {
        if (IS_URL_CHAR(ch)) break;

        switch (ch) {
          case ' ':
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case CR:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_req_line_almost_done;
            break;
          case LF:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_header_field_start;
            break;
          case '?':
            state = s_req_query_string_start;
            break;
          case '#':
            state = s_req_fragment_start;
            break;
          default:
            SET_ERRNO(HPE_INVALID_PATH);
            goto error;
        }
        break;
      }

      case s_req_query_string_start:
      {
        if (IS_URL_CHAR(ch)) {
          state = s_req_query_string;
          break;
        }

        switch (ch) {
          case '?':
            break; /* XXX ignore extra '?' ... is this right? */
          case ' ':
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case CR:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_req_line_almost_done;
            break;
          case LF:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_header_field_start;
            break;
          case '#':
            state = s_req_fragment_start;
            break;
          default:
            SET_ERRNO(HPE_INVALID_QUERY_STRING);
            goto error;
        }
        break;
      }

      case s_req_query_string:
      {
        if (IS_URL_CHAR(ch)) break;

        switch (ch) {
          case '?':
            /* allow extra '?' in query string */
            break;
          case ' ':
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case CR:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_req_line_almost_done;
            break;
          case LF:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_header_field_start;
            break;
          case '#':
            state = s_req_fragment_start;
            break;
          default:
            SET_ERRNO(HPE_INVALID_QUERY_STRING);
            goto error;
        }
        break;
      }

      case s_req_fragment_start:
      {
        if (IS_URL_CHAR(ch)) {
          state = s_req_fragment;
          break;
        }

        switch (ch) {
          case ' ':
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case CR:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_req_line_almost_done;
            break;
          case LF:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_header_field_start;
            break;
          case '?':
            state = s_req_fragment;
            break;
          case '#':
            break;
          default:
            SET_ERRNO(HPE_INVALID_FRAGMENT);
            goto error;
        }
        break;
      }

      case s_req_fragment:
      {
        if (IS_URL_CHAR(ch)) break;

        switch (ch) {
          case ' ':
            CALLBACK(url);
            state = s_req_http_start;
            break;
          case CR:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_req_line_almost_done;
            break;
          case LF:
            CALLBACK(url);
            parser->http_major = 0;
            parser->http_minor = 9;
            state = s_header_field_start;
            break;
          case '?':
          case '#':
            break;
          default:
            SET_ERRNO(HPE_INVALID_FRAGMENT);
            goto error;
        }
        break;
      }

      case s_req_http_start:
        switch (ch) {
          case 'H':
            state = s_req_http_H;
            break;
          case ' ':
            break;
          default:
            SET_ERRNO(HPE_INVALID_CONSTANT);
            goto error;
        }
        break;

      case s_req_http_H:
        STRICT_CHECK(ch != 'T');
        state = s_req_http_HT;
        break;

      case s_req_http_HT:
        STRICT_CHECK(ch != 'T');
        state = s_req_http_HTT;
        break;

      case s_req_http_HTT:
        STRICT_CHECK(ch != 'P');
        state = s_req_http_HTTP;
        break;

      case s_req_http_HTTP:
        STRICT_CHECK(ch != '/');
        state = s_req_first_http_major;
        break;

      /* first digit of major HTTP version */
      case s_req_first_http_major:
        if (ch < '1' || ch > '9') {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_major = ch - '0';
        state = s_req_http_major;
        break;

      /* major HTTP version or dot */
      case s_req_http_major:
      {
        if (ch == '.') {
          state = s_req_first_http_minor;
          break;
        }

        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_major *= 10;
        parser->http_major += ch - '0';

        if (parser->http_major > 999) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        break;
      }

      /* first digit of minor HTTP version */
      case s_req_first_http_minor:
        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_minor = ch - '0';
        state = s_req_http_minor;
        break;

      /* minor HTTP version or end of request line */
      case s_req_http_minor:
      {
        if (ch == CR) {
          state = s_req_line_almost_done;
          break;
        }

        if (ch == LF) {
          state = s_header_field_start;
          break;
        }

        /* XXX allow spaces after digit? */

        if (!IS_NUM(ch)) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        parser->http_minor *= 10;
        parser->http_minor += ch - '0';

        if (parser->http_minor > 999) {
          SET_ERRNO(HPE_INVALID_VERSION);
          goto error;
        }

        break;
      }

      /* end of request line */
      case s_req_line_almost_done:
      {
        if (ch != LF) {
          SET_ERRNO(HPE_LF_EXPECTED);
          goto error;
        }

        state = s_header_field_start;
        break;
      }

      case s_header_field_start:
      header_field_start:
      {
        if (ch == CR) {
          state = s_headers_almost_done;
          break;
        }

        if (ch == LF) {
          /* they might be just sending \n instead of \r\n so this would be
           * the second \n to denote the end of headers*/
          state = s_headers_almost_done;
          goto headers_almost_done;
        }

        c = TOKEN(ch);

        if (!c) {
          SET_ERRNO(HPE_INVALID_HEADER_TOKEN);
          goto error;
        }

        MARK(header_field);

        index = 0;
        state = s_header_field;

        switch (c) {
          case 'c':
            header_state = h_C;
            break;

          case 'p':
            header_state = h_matching_proxy_connection;
            break;

          case 't':
            header_state = h_matching_transfer_encoding;
            break;

          case 'u':
            header_state = h_matching_upgrade;
            break;

          default:
            header_state = h_general;
            break;
        }
        break;
      }

      case s_header_field:
      {
        c = TOKEN(ch);

        if (c) {
          switch (header_state) {
            case h_general:
              break;

            case h_C:
              index++;
              header_state = (c == 'o' ? h_CO : h_general);
              break;

            case h_CO:
              index++;
              header_state = (c == 'n' ? h_CON : h_general);
              break;

            case h_CON:
              index++;
              switch (c) {
                case 'n':
                  header_state = h_matching_connection;
                  break;
                case 't':
                  header_state = h_matching_content_length;
                  break;
                default:
                  header_state = h_general;
                  break;
              }
              break;

            /* connection */

            case h_matching_connection:
              index++;
              if (index > sizeof(CONNECTION)-1
                  || c != CONNECTION[index]) {
                header_state = h_general;
              } else if (index == sizeof(CONNECTION)-2) {
                header_state = h_connection;
              }
              break;

            /* proxy-connection */

            case h_matching_proxy_connection:
              index++;
              if (index > sizeof(PROXY_CONNECTION)-1
                  || c != PROXY_CONNECTION[index]) {
                header_state = h_general;
              } else if (index == sizeof(PROXY_CONNECTION)-2) {
                header_state = h_connection;
              }
              break;

            /* content-length */

            case h_matching_content_length:
              index++;
              if (index > sizeof(CONTENT_LENGTH)-1
                  || c != CONTENT_LENGTH[index]) {
                header_state = h_general;
              } else if (index == sizeof(CONTENT_LENGTH)-2) {
                header_state = h_content_length;
              }
              break;

            /* transfer-encoding */

            case h_matching_transfer_encoding:
              index++;
              if (index > sizeof(TRANSFER_ENCODING)-1
                  || c != TRANSFER_ENCODING[index]) {
                header_state = h_general;
              } else if (index == sizeof(TRANSFER_ENCODING)-2) {
                header_state = h_transfer_encoding;
              }
              break;

            /* upgrade */

            case h_matching_upgrade:
              index++;
              if (index > sizeof(UPGRADE)-1
                  || c != UPGRADE[index]) {
                header_state = h_general;
              } else if (index == sizeof(UPGRADE)-2) {
                header_state = h_upgrade;
              }
              break;

            case h_connection:
            case h_content_length:
            case h_transfer_encoding:
            case h_upgrade:
              if (ch != ' ') header_state = h_general;
              break;

            default:
              assert(0 && "Unknown header_state");
              break;
          }
          break;
        }

        if (ch == ':') {
          CALLBACK(header_field);
          state = s_header_value_start;
          break;
        }

        if (ch == CR) {
          state = s_header_almost_done;
          CALLBACK(header_field);
          break;
        }

        if (ch == LF) {
          CALLBACK(header_field);
          state = s_header_field_start;
          break;
        }

        SET_ERRNO(HPE_INVALID_HEADER_TOKEN);
        goto error;
      }

      case s_header_value_start:
      {
        if (ch == ' ' || ch == '\t') break;

        MARK(header_value);

        state = s_header_value;
        index = 0;

        if (ch == CR) {
          CALLBACK(header_value);
          header_state = h_general;
          state = s_header_almost_done;
          break;
        }

        if (ch == LF) {
          CALLBACK(header_value);
          state = s_header_field_start;
          break;
        }

        c = LOWER(ch);

        switch (header_state) {
          case h_upgrade:
            parser->flags |= F_UPGRADE;
            header_state = h_general;
            break;

          case h_transfer_encoding:
            /* looking for 'Transfer-Encoding: chunked' */
            if ('c' == c) {
              header_state = h_matching_transfer_encoding_chunked;
            } else {
              header_state = h_general;
            }
            break;

          case h_content_length:
            if (!IS_NUM(ch)) {
              SET_ERRNO(HPE_INVALID_CONTENT_LENGTH);
              goto error;
            }

            parser->content_length = ch - '0';
            break;

          case h_connection:
            /* looking for 'Connection: keep-alive' */
            if (c == 'k') {
              header_state = h_matching_connection_keep_alive;
            /* looking for 'Connection: close' */
            } else if (c == 'c') {
              header_state = h_matching_connection_close;
            } else {
              header_state = h_general;
            }
            break;

          default:
            header_state = h_general;
            break;
        }
        break;
      }

      case s_header_value:
      {

        if (ch == CR) {
          CALLBACK(header_value);
          state = s_header_almost_done;
          break;
        }

        if (ch == LF) {
          CALLBACK(header_value);
          goto header_almost_done;
        }

        c = LOWER(ch);

        switch (header_state) {
          case h_general:
            break;

          case h_connection:
          case h_transfer_encoding:
            assert(0 && "Shouldn't get here.");
            break;

          case h_content_length:
            if (ch == ' ') break;
            if (!IS_NUM(ch)) {
              SET_ERRNO(HPE_INVALID_CONTENT_LENGTH);
              goto error;
            }

            parser->content_length *= 10;
            parser->content_length += ch - '0';
            break;

          /* Transfer-Encoding: chunked */
          case h_matching_transfer_encoding_chunked:
            index++;
            if (index > sizeof(CHUNKED)-1
                || c != CHUNKED[index]) {
              header_state = h_general;
            } else if (index == sizeof(CHUNKED)-2) {
              header_state = h_transfer_encoding_chunked;
            }
            break;

          /* looking for 'Connection: keep-alive' */
          case h_matching_connection_keep_alive:
            index++;
            if (index > sizeof(KEEP_ALIVE)-1
                || c != KEEP_ALIVE[index]) {
              header_state = h_general;
            } else if (index == sizeof(KEEP_ALIVE)-2) {
              header_state = h_connection_keep_alive;
            }
            break;

          /* looking for 'Connection: close' */
          case h_matching_connection_close:
            index++;
            if (index > sizeof(CLOSE)-1 || c != CLOSE[index]) {
              header_state = h_general;
            } else if (index == sizeof(CLOSE)-2) {
              header_state = h_connection_close;
            }
            break;

          case h_transfer_encoding_chunked:
          case h_connection_keep_alive:
          case h_connection_close:
            if (ch != ' ') header_state = h_general;
            break;

          default:
            state = s_header_value;
            header_state = h_general;
            break;
        }
        break;
      }

      case s_header_almost_done:
      header_almost_done:
      {
        STRICT_CHECK(ch != LF);

        state = s_header_value_lws;

        switch (header_state) {
          case h_connection_keep_alive:
            parser->flags |= F_CONNECTION_KEEP_ALIVE;
            break;
          case h_connection_close:
            parser->flags |= F_CONNECTION_CLOSE;
            break;
          case h_transfer_encoding_chunked:
            parser->flags |= F_CHUNKED;
            break;
          default:
            break;
        }
        break;
      }

      case s_header_value_lws:
      {
        if (ch == ' ' || ch == '\t')
          state = s_header_value_start;
        else
        {
          state = s_header_field_start;
          goto header_field_start;
        }
        break;
      }

      case s_headers_almost_done:
      headers_almost_done:
      {
        STRICT_CHECK(ch != LF);

        if (parser->flags & F_TRAILING) {
          /* End of a chunked request */
          CALLBACK2(message_complete);
          state = NEW_MESSAGE();
          break;
        }

        nread = 0;

        if (parser->flags & F_UPGRADE || parser->method == HTTP_CONNECT) {
          parser->upgrade = 1;
        }

        /* Here we call the headers_complete callback. This is somewhat
         * different than other callbacks because if the user returns 1, we
         * will interpret that as saying that this message has no body. This
         * is needed for the annoying case of recieving a response to a HEAD
         * request.
         */
        if (settings->on_headers_complete) {
          switch (settings->on_headers_complete(parser)) {
            case 0:
              break;

            case 1:
              parser->flags |= F_SKIPBODY;
              break;

            default:
              parser->state = state;
              SET_ERRNO(HPE_CB_headers_complete);
              return p - data; /* Error */
          }
        }

        /* Exit, the rest of the connect is in a different protocol. */
        if (parser->upgrade) {
          CALLBACK2(message_complete);
          return (p - data) + 1;
        }

        if (parser->flags & F_SKIPBODY) {
          CALLBACK2(message_complete);
          state = NEW_MESSAGE();
        } else if (parser->flags & F_CHUNKED) {
          /* chunked encoding - ignore Content-Length header */
          state = s_chunk_size_start;
        } else {
          if (parser->content_length == 0) {
            /* Content-Length header given but zero: Content-Length: 0\r\n */
            CALLBACK2(message_complete);
            state = NEW_MESSAGE();
          } else if (parser->content_length > 0) {
            /* Content-Length header given and non-zero */
            state = s_body_identity;
          } else {
            if (parser->type == HTTP_REQUEST || http_should_keep_alive(parser)) {
              /* Assume content-length 0 - read the next */
              CALLBACK2(message_complete);
              state = NEW_MESSAGE();
            } else {
              /* Read body until EOF */
              state = s_body_identity_eof;
            }
          }
        }

        break;
      }

      case s_body_identity:
        to_read = MIN(pe - p, (int64_t)parser->content_length);
        if (to_read > 0) {
          if (settings->on_body) settings->on_body(parser, p, to_read);
          p += to_read - 1;
          parser->content_length -= to_read;
          if (parser->content_length == 0) {
            CALLBACK2(message_complete);
            state = NEW_MESSAGE();
          }
        }
        break;

      /* read until EOF */
      case s_body_identity_eof:
        to_read = pe - p;
        if (to_read > 0) {
          if (settings->on_body) settings->on_body(parser, p, to_read);
          p += to_read - 1;
        }
        break;

      case s_chunk_size_start:
      {
        assert(nread == 1);
        assert(parser->flags & F_CHUNKED);

        unhex_val = unhex[(unsigned char)ch];
        if (unhex_val == -1) {
          SET_ERRNO(HPE_INVALID_CHUNK_SIZE);
          goto error;
        }

        parser->content_length = unhex_val;
        state = s_chunk_size;
        break;
      }

      case s_chunk_size:
      {
        assert(parser->flags & F_CHUNKED);

        if (ch == CR) {
          state = s_chunk_size_almost_done;
          break;
        }

        unhex_val = unhex[(unsigned char)ch];

        if (unhex_val == -1) {
          if (ch == ';' || ch == ' ') {
            state = s_chunk_parameters;
            break;
          }

          SET_ERRNO(HPE_INVALID_CHUNK_SIZE);
          goto error;
        }

        parser->content_length *= 16;
        parser->content_length += unhex_val;
        break;
      }

      case s_chunk_parameters:
      {
        assert(parser->flags & F_CHUNKED);
        /* just ignore this shit. TODO check for overflow */
        if (ch == CR) {
          state = s_chunk_size_almost_done;
          break;
        }
        break;
      }

      case s_chunk_size_almost_done:
      {
        assert(parser->flags & F_CHUNKED);
        STRICT_CHECK(ch != LF);

        nread = 0;

        if (parser->content_length == 0) {
          parser->flags |= F_TRAILING;
          state = s_header_field_start;
        } else {
          state = s_chunk_data;
        }
        break;
      }

      case s_chunk_data:
      {
        assert(parser->flags & F_CHUNKED);

        to_read = MIN(pe - p, (int64_t)(parser->content_length));

        if (to_read > 0) {
          if (settings->on_body) settings->on_body(parser, p, to_read);
          p += to_read - 1;
        }

        if (to_read == parser->content_length) {
          state = s_chunk_data_almost_done;
        }

        parser->content_length -= to_read;
        break;
      }

      case s_chunk_data_almost_done:
        assert(parser->flags & F_CHUNKED);
        STRICT_CHECK(ch != CR);
        state = s_chunk_data_done;
        break;

      case s_chunk_data_done:
        assert(parser->flags & F_CHUNKED);
        STRICT_CHECK(ch != LF);
        state = s_chunk_size_start;
        break;

      default:
        assert(0 && "unhandled state");
        SET_ERRNO(HPE_INVALID_INTERNAL_STATE);
        goto error;
    }
  }

#if defined(HTTP_PARSER_USE_RESTART)
  if (url_mark) return (url_mark - data);
  if (header_field_mark) return (header_field_mark - data);
  if (header_value_mark) return (header_value_mark - data);
#else
  CALLBACK(header_field);
  CALLBACK(header_value);
  CALLBACK(url);
#endif

  parser->state = state;
  parser->header_state = header_state;
  parser->index = index;
  parser->nread = nread;

  return len;

error:
  if (HTTP_PARSER_ERRNO(parser) == HPE_OK) {
    SET_ERRNO(HPE_UNKNOWN);
  }

  return (p - data);
}