void expand_variable_error(parser_t &parser, const wchar_t *token, size_t token_pos, int error_pos)
{
    size_t stop_pos = token_pos+1;

    switch (token[stop_pos])
    {
        case BRACKET_BEGIN:
        {
            wchar_t *cpy = wcsdup(token);
            *(cpy+token_pos)=0;
            wchar_t *name = &cpy[stop_pos+1];
            wchar_t *end = wcschr(name, BRACKET_END);
            wchar_t *post;
            int is_var=0;
            if (end)
            {
                post = end+1;
                *end = 0;

                if (!wcsvarname(name))
                {
                    is_var = 1;
                }
            }

            if (is_var)
            {
                parser.error(SYNTAX_ERROR,
                             error_pos,
                             COMPLETE_VAR_BRACKET_DESC,
                             cpy,
                             name,
                             post);
            }
            else
            {
                parser.error(SYNTAX_ERROR,
                             error_pos,
                             COMPLETE_VAR_BRACKET_DESC,
                             L"",
                             L"VARIABLE",
                             L"");
            }
            free(cpy);

            break;
        }

        case INTERNAL_SEPARATOR:
        {
            parser.error(SYNTAX_ERROR,
                         error_pos,
                         COMPLETE_VAR_PARAN_DESC);
            break;
        }

        case 0:
        {
            parser.error(SYNTAX_ERROR,
                         error_pos,
                         COMPLETE_VAR_NULL_DESC);
            break;
        }

        default:
        {
            wchar_t token_stop_char = token[stop_pos];
            // Unescape (see http://github.com/fish-shell/fish-shell/issues/50)
            if (token_stop_char == ANY_CHAR)
                token_stop_char = L'?';
            else if (token_stop_char == ANY_STRING || token_stop_char == ANY_STRING_RECURSIVE)
                token_stop_char = L'*';

            parser.error(SYNTAX_ERROR,
                         error_pos,
                         (token_stop_char == L'?' ? COMPLETE_YOU_WANT_STATUS : COMPLETE_VAR_DESC),
                         token_stop_char);
            break;
        }
    }
}