static void
windows_event_logger_log(grn_ctx *ctx, grn_log_level level,
                         const char *timestamp, const char *title,
                         const char *message, const char *location,
                         void *user_data)
{
    grn_windows_event_logger_data *data = user_data;
    WORD type;
    WORD category = 0;
    DWORD event_id = 0;
    PSID user_sid = NULL;
    WORD n_strings = 1;
    DWORD event_data_size = 0;
    const WCHAR *strings[1];
    LPVOID event_data = NULL;
    const char level_marks[] = " EACewnid-";
    grn_obj formatted_buffer;
    UINT code_page;
    DWORD convert_flags = 0;
    int n_converted_chars;

    switch (level) {
    case GRN_LOG_NONE :
        return;
        break;
    case GRN_LOG_EMERG :
    case GRN_LOG_ALERT :
    case GRN_LOG_CRIT :
    case GRN_LOG_ERROR :
        type = EVENTLOG_ERROR_TYPE;
        break;
    case GRN_LOG_WARNING :
        type = EVENTLOG_WARNING_TYPE;
        break;
    case GRN_LOG_NOTICE :
    case GRN_LOG_INFO :
    case GRN_LOG_DEBUG :
    case GRN_LOG_DUMP :
        type = EVENTLOG_INFORMATION_TYPE;
        break;
    default :
        type = EVENTLOG_ERROR_TYPE;
        break;
    }

    if (data->event_source == INVALID_HANDLE_VALUE) {
        data->event_source = RegisterEventSourceA(NULL, data->event_source_name);
        if (data->event_source == INVALID_HANDLE_VALUE) {
            return;
        }
    }

    GRN_TEXT_INIT(&formatted_buffer, 0);
    if (location && location[0]) {
        grn_text_printf(ctx, &formatted_buffer, "%s|%c|%s %s %s",
                        timestamp, level_marks[level], title, message, location);
    } else {
        grn_text_printf(ctx, &formatted_buffer, "%s|%c|%s %s",
                        timestamp, level_marks[level], title, message);
    }

    code_page = grn_windows_encoding_to_code_page(ctx->encoding);

    n_converted_chars = MultiByteToWideChar(code_page,
                                            convert_flags,
                                            GRN_TEXT_VALUE(&formatted_buffer),
                                            GRN_TEXT_LEN(&formatted_buffer),
                                            NULL,
                                            0);
#define CONVERTED_BUFFER_SIZE 512
    if (n_converted_chars < CONVERTED_BUFFER_SIZE) {
        WCHAR converted_buffer[CONVERTED_BUFFER_SIZE];
        n_converted_chars = MultiByteToWideChar(code_page,
                                                convert_flags,
                                                GRN_TEXT_VALUE(&formatted_buffer),
                                                GRN_TEXT_LEN(&formatted_buffer),
                                                converted_buffer,
                                                CONVERTED_BUFFER_SIZE);
        converted_buffer[n_converted_chars] = L'\0';
        strings[0] = converted_buffer;
        ReportEventW(data->event_source, type, category, event_id, user_sid,
                     n_strings, event_data_size,
                     strings, event_data);
#undef CONVERTED_BUFFER_SIZE
    } else {
        WCHAR *converted;
        converted = GRN_MALLOCN(WCHAR, n_converted_chars);
        n_converted_chars = MultiByteToWideChar(code_page,
                                                convert_flags,
                                                GRN_TEXT_VALUE(&formatted_buffer),
                                                GRN_TEXT_LEN(&formatted_buffer),
                                                converted,
                                                n_converted_chars);
        converted[n_converted_chars] = L'\0';
        strings[0] = converted;
        ReportEventW(data->event_source, type, category, event_id, user_sid,
                     n_strings, event_data_size,
                     strings, event_data);
        GRN_FREE(converted);
    }
    GRN_OBJ_FIN(ctx, &formatted_buffer);
}