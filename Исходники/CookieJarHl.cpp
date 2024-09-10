String cookies(const Document* /*document*/, const KURL& url)
{
    String rawCookie = cookieJar.get(url.host());
    String urlPath = url.path();
    String resCookie;
    Vector<String> field;
    const int fieldNum = 7;
    int i, len;

    if (rawCookie.length() == 0)
        return resCookie;

    // --- Parse raw cookie ---
    rawCookie.split('\t', true, field);
    len = field.size();

    for (i = 0; i < len; i += fieldNum)
        if (urlPath.startsWith(field[i + 2], false))
            resCookie += "; " + field[i + 5] + "=" + field[i + 6];

    // --- Trim leading separator ---
    if (!resCookie.isEmpty())
        resCookie.remove(0, 2);

    // printf("%s: %s\n%s\n\n", __func__, url.string().utf8().data(), resCookie.utf8().data());
    return resCookie;
}