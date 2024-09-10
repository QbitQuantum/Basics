// **************************************************************************
// HTTPヘッダを受信して解析する。
//
// 処理するのはGETのみ。GET以外のメソッドが来たらエラー
// 今のところ、URIとuser_agent、Range、Hostを解析。
// URIは、URIデコードもやる。
//
//	return: 0 		正常終了
//	return: 0以外 	エラー
// **************************************************************************
static int http_header_receive(int accept_socket, HTTP_RECV_INFO *http_recv_info_p)
{
    int result = 0;
    int	recv_len;
    char	line_buf[1024];	// 大きめに。
    char 	work_buf[1024];
    char 	work_buf2[1024];
    char 	split1[1024];
    char 	split2[1024];
    int		ret;
    int		i;
    // ================================
    // １行づつ HTTPヘッダを受信
    // ================================
    for (i=0;;i++){
        // 1行受信 実行。
        recv_len = line_receive(accept_socket, line_buf, sizeof(line_buf));
        // 受信した内容をチェック。
        if ( recv_len == 0 ){ // 空行検知。ヘッダ受信終了。
            break;
        }else if ( recv_len < 0 ){ // 受信失敗
            return ( -1 );
        }
        // debug. 受信したヘッダ表示
        debug_log_output("'%s'(%d byte)\n", line_buf, recv_len );
        // --------------------------
        // GETメッセージチェック
        // --------------------------
        if ( i == 0 ){ // １行目のみチェック
            debug_log_output("%d:URI Check start.'%s'\n", accept_socket,line_buf);
            // GETある？
            if       ( strstr(line_buf, "GET") != NULL ){
                http_recv_info_p->isGet = 1;
            }else if ( strstr(line_buf, "HEAD") != NULL ){
                http_recv_info_p->isGet = 2;
            }else if ( strstr(line_buf, "POST") != NULL ){
                http_recv_info_p->isGet = 3;
            }else{
                debug_log_output("'GET' not found. error.%d",accept_socket);
                return ( -1 );
            }
            // 最初のスペースまでを削除。
            cut_before_character(line_buf, ' ');
            // 次にスペースが出てきたところの後ろまでを削除。
            cut_after_character(line_buf, ' ');
            // ===========================
            // GETオプション部解析
            // ===========================
            // REQUEST_URI用・Proxy用に値を保存
            strncpy(http_recv_info_p->request_uri, line_buf, sizeof(http_recv_info_p->request_uri));
            // '?'が存在するかチェック。
            if ( strchr(line_buf, '?') != NULL ){
                strncpy(work_buf, line_buf, sizeof(work_buf));
                // '?'より前をカット
                cut_before_character(work_buf, '?' );
                while ( 1 ){
                    memset(split1, 0, sizeof(split1));
                    memset(split2, 0, sizeof(split2));
                    // 最初に登場する'&'で分割
                    ret = sentence_split(work_buf, '&', split1, split2 );
                    if ( ret == 0 ){ // 分割成功
                        strncpy(work_buf, split2, sizeof(work_buf));
                    }else if (strlen(work_buf) > 0){ // まだwork_bufに中身ある？
                        strncpy( split1, work_buf, sizeof(split1));
                        strncpy( work_buf, "", sizeof(work_buf));
                    }else{ // 処理終了
                        break;
                    }
                    // -------------------------------------
                    // GETした内容 解析開始
                    // 超安直。いいのかこんな比較で。
                    // -------------------------------------
                    // URIデコード
                    uri_decode(work_buf2, sizeof(work_buf2), split1, sizeof(split1) );
                    // "action="あるか調査。
                    if (strncasecmp( work_buf2, "action=", strlen("action=") ) == 0 ){
                        // = より前を削除
                        cut_before_character(work_buf2, '=');
                        // 構造体に値を保存。
                        strncpy(http_recv_info_p->action, work_buf2, sizeof(http_recv_info_p->action));
                        continue;
                    }
                }
            }
            debug_log_output("http_recv_info_p->action = '%s'", http_recv_info_p->action);
            // URIデコード
            cut_after_character(line_buf, '?');
            uri_decode(work_buf, sizeof(work_buf), line_buf, sizeof(line_buf) );
            strncpy(line_buf, work_buf, sizeof(line_buf));
            debug_log_output("URI(decoded):'%s'\n", line_buf);
            convert_language_code(line_buf, work_buf, sizeof(work_buf), CODE_AUTO, CODE_EUC);
            debug_log_output("URI(decoded,euc,FYI):'%s'\n", work_buf);
            // 構造体に保存
            strncpy(http_recv_info_p->recv_uri, line_buf, sizeof(http_recv_info_p->recv_uri));
            //httpから始まってる場合には、http://以降の最初の'/'の前でカット
            if( strncmp(http_recv_info_p->recv_uri,"http://",7)==0){
                char* ptr = strstr(http_recv_info_p->recv_uri+7,"/");
                if( ptr ){
                    strcpy(http_recv_info_p->recv_uri,ptr);
                }
            }
            continue;
        }
        // User-agent切り出し
        if ( strncasecmp(line_buf, HTTP_USER_AGENT, strlen(HTTP_USER_AGENT) ) == 0 ){
            debug_log_output("User-agent: Detect.\n");
            // ':'より前を切る
            cut_before_character(line_buf, ':');
            cut_first_character(line_buf, ' ');
            // 構造体に保存
            strncpy( http_recv_info_p->user_agent, line_buf, sizeof(http_recv_info_p->user_agent));
            continue;
        }
        // Rangeあるかチェック
        if ( strncasecmp(line_buf, HTTP_RANGE,	strlen(HTTP_RANGE) ) == 0 ){
            debug_log_output("%s Detect.\n", HTTP_RANGE);
            // ':' より前を切る。
            cut_before_character(line_buf, ':');
            cut_first_character(line_buf, ' ');
            // recv_range にRangeの中身保存
            strncpy(http_recv_info_p->recv_range, line_buf, sizeof(http_recv_info_p->recv_range));
            // '=' より前を切る
            cut_before_character(line_buf, '=');
            // '-'で前後に分割。
            sentence_split(line_buf, '-', work_buf, work_buf2);
            debug_log_output("wrok_buf='%s'\n", work_buf);
            debug_log_output("wrok_buf2='%s'\n", work_buf2);
            // 値を文字列→数値変換
            http_recv_info_p->range_start_pos  = strtoull(work_buf, NULL, 10);
            if ( strlen(work_buf2) > 0 ){
                http_recv_info_p->range_end_pos = strtoull(work_buf2, NULL, 10);
            }
            debug_log_output("range_start_pos=%d\n", http_recv_info_p->range_start_pos);
            debug_log_output("range_end_pos=%d\n", http_recv_info_p->range_end_pos);
            continue;
        }
        // Hostあるかチェック
        if ( strncasecmp(line_buf, HTTP_HOST,	strlen(HTTP_HOST) ) == 0 ){
            // ':' より前を切る。
            cut_before_character(line_buf, ':');
            cut_first_character(line_buf, ' ');
            strncpy(http_recv_info_p->recv_host, line_buf, sizeof(http_recv_info_p->recv_host));
            debug_log_output("%s Detect. %s '%s'", HTTP_HOST, HTTP_HOST, http_recv_info_p->recv_host);
            continue;
        }
        // Content-Lengthあるかチェック
        if ( strncasecmp(line_buf, HTTP_CONTENT_LENGTH1, strlen(HTTP_CONTENT_LENGTH1) ) == 0 ){
            // ':' より前を切る。
            cut_before_character(line_buf, ':');
            cut_first_character(line_buf, ' ');
            strncpy(http_recv_info_p->content_length, line_buf, sizeof(http_recv_info_p->content_length));
            debug_log_output("%s Detect. %s '%s'", HTTP_CONTENT_LENGTH1, HTTP_CONTENT_LENGTH1, http_recv_info_p->content_length);
            continue;
        }
        // Content-TYPEあるかチェック
        if ( strncasecmp(line_buf, HTTP_CONTENT_TYPE1, strlen(HTTP_CONTENT_TYPE1) ) == 0 ){
            // ':' より前を切る。
            cut_before_character(line_buf, ':');
            cut_first_character(line_buf, ' ');
            strncpy(http_recv_info_p->content_type, line_buf, sizeof(http_recv_info_p->content_type));
            debug_log_output("%s Detect. %s '%s'", HTTP_CONTENT_TYPE1, HTTP_CONTENT_TYPE1, http_recv_info_p->content_type);
            continue;
        }
    }
    return result;
}