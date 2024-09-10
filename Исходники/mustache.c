static bool IsTagStandalone(const char *start, const char *tag_start, const char *tag_end, const char **line_begin, const char **line_end)
{
    assert(start <= tag_start);

    *line_begin = start;
    for (const char *cur = tag_start - 1; cur >= start; cur--)
    {
        if (IsSpace(*cur))
        {
            *line_begin = cur;
            if (cur == start)
            {
                break;
            }
            continue;
        }
        else if (*cur == '\n')
        {
            *line_begin = cur + 1;
            break;
        }
        else
        {
            return false;
        }
    }

    *line_end = NULL;
    for (const char *cur = tag_end; true; cur++)
    {
        if (IsSpace(*cur))
        {
            continue;
        }
        else if (*cur == '\n')
        {
            *line_end = cur + 1;
            break;
        }
        else if (*cur == '\r')
        {
            if (*(cur + 1) == '\n')
            {
                *line_end = cur + 2;
                break;
            }
            continue;
        }
        else if (*cur == '\0')
        {
            *line_end = cur;
            break;
        }
        else
        {
            return false;
        }
    }

    assert(*line_end);

    return true;
}