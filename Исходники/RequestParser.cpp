boost::tribool
RequestParser::consume(Request &req, char input, http::CompressionType *compressionType)
{
    switch (state_)
    {
    case method_start:
        if (!isChar(input) || isCTL(input) || isTSpecial(input))
        {
            return false;
        }
        state_ = method;
        return boost::indeterminate;
    case method:
        if (input == ' ')
        {
            state_ = uri;
            return boost::indeterminate;
        }
        if (!isChar(input) || isCTL(input) || isTSpecial(input))
        {
            return false;
        }
        return boost::indeterminate;
    case uri_start:
        if (isCTL(input))
        {
            return false;
        }
        state_ = uri;
        req.uri.push_back(input);
        return boost::indeterminate;
    case uri:
        if (input == ' ')
        {
            state_ = http_version_h;
            return boost::indeterminate;
        }
        if (isCTL(input))
        {
            return false;
        }
        req.uri.push_back(input);
        return boost::indeterminate;
    case http_version_h:
        if (input == 'H')
        {
            state_ = http_version_t_1;
            return boost::indeterminate;
        }
        return false;
    case http_version_t_1:
        if (input == 'T')
        {
            state_ = http_version_t_2;
            return boost::indeterminate;
        }
        return false;
    case http_version_t_2:
        if (input == 'T')
        {
            state_ = http_version_p;
            return boost::indeterminate;
        }
        return false;
    case http_version_p:
        if (input == 'P')
        {
            state_ = http_version_slash;
            return boost::indeterminate;
        }
        return false;
    case http_version_slash:
        if (input == '/')
        {
            state_ = http_version_major_start;
            return boost::indeterminate;
        }
        return false;
    case http_version_major_start:
        if (isDigit(input))
        {
            state_ = http_version_major;
            return boost::indeterminate;
        }
        return false;
    case http_version_major:
        if (input == '.')
        {
            state_ = http_version_minor_start;
            return boost::indeterminate;
        }
        if (isDigit(input))
        {
            return boost::indeterminate;
        }
        return false;
    case http_version_minor_start:
        if (isDigit(input))
        {
            state_ = http_version_minor;
            return boost::indeterminate;
        }
        return false;
    case http_version_minor:
        if (input == '\r')
        {
            state_ = expecting_newline_1;
            return boost::indeterminate;
        }
        if (isDigit(input))
        {
            return boost::indeterminate;
        }
        return false;
    case expecting_newline_1:
        if (input == '\n')
        {
            state_ = header_line_start;
            return boost::indeterminate;
        }
        return false;
    case header_line_start:
        if (header.name == "Accept-Encoding")
        {
            /* giving gzip precedence over deflate */
            if (header.value.find("deflate") != std::string::npos)
            {
                *compressionType = deflateRFC1951;
            }
            if (header.value.find("gzip") != std::string::npos)
            {
                *compressionType = gzipRFC1952;
            }
        }

        if ("Referer" == header.name)
        {
            req.referrer = header.value;
        }

        if ("User-Agent" == header.name)
        {
            req.agent = header.value;
        }

        if (input == '\r')
        {
            state_ = expecting_newline_3;
            return boost::indeterminate;
        }
        if (!isChar(input) || isCTL(input) || isTSpecial(input))
        {
            return false;
        }
        state_ = header_name;
        header.Clear();
        header.name.push_back(input);
        return boost::indeterminate;
    case header_lws:
        if (input == '\r')
        {
            state_ = expecting_newline_2;
            return boost::indeterminate;
        }
        if (input == ' ' || input == '\t')
        {
            return boost::indeterminate;
        }
        if (isCTL(input))
        {
            return false;
        }
        state_ = header_value;
        return boost::indeterminate;
    case header_name:
        if (input == ':')
        {
            state_ = space_before_header_value;
            return boost::indeterminate;
        }
        if (!isChar(input) || isCTL(input) || isTSpecial(input))
        {
            return false;
        }
        header.name.push_back(input);
        return boost::indeterminate;
    case space_before_header_value:
        if (input == ' ')
        {
            state_ = header_value;
            return boost::indeterminate;
        }
        return false;
    case header_value:
        if (input == '\r')
        {
            state_ = expecting_newline_2;
            return boost::indeterminate;
        }
        if (isCTL(input))
        {
            return false;
        }
        header.value.push_back(input);
        return boost::indeterminate;
    case expecting_newline_2:
        if (input == '\n')
        {
            state_ = header_line_start;
            return boost::indeterminate;
        }
        return false;
    case expecting_newline_3:
        return (input == '\n');
    default:
        return false;
    }
}