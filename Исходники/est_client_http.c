/*
 * This function parses the HTTP status code
 * in the first header.  Only a handful of codes are
 * handled by EST.  We are not a full HTTP stack.  Any
 * unrecognized codes will result in an error.
 * Note that HTTP 1.1 is expected.
 */
static int est_io_parse_response_status_code (unsigned char *buf)
{
    if (!strncmp((const char *)buf, EST_HTTP_HDR_200,
                        strnlen_s(EST_HTTP_HDR_200, EST_HTTP_HDR_MAX))) {
        return 200;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_202,
                        strnlen_s(EST_HTTP_HDR_202, EST_HTTP_HDR_MAX))) {
        return 202;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_204,
                        strnlen_s(EST_HTTP_HDR_204, EST_HTTP_HDR_MAX))) {
        return 204;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_400,
                        strnlen_s(EST_HTTP_HDR_400, EST_HTTP_HDR_MAX))) {
        return 400;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_401,
                        strnlen_s(EST_HTTP_HDR_401, EST_HTTP_HDR_MAX))) {
        return 401;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_404,
                        strnlen_s(EST_HTTP_HDR_404, EST_HTTP_HDR_MAX))) {
        return 404;
    } else if (!strncmp((const char *)buf, EST_HTTP_HDR_423,
                        strnlen_s(EST_HTTP_HDR_423, EST_HTTP_HDR_MAX))) {
        return 423;
    } else {
        EST_LOG_ERR("Unhandled HTTP response %s", buf);
        return -1;
    }
}