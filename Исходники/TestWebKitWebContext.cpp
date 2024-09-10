String generateHTMLContent(unsigned contentLength)
{
    String baseString("abcdefghijklmnopqrstuvwxyz0123457890");
    unsigned baseLength = baseString.length();

    StringBuilder builder;
    builder.append("<html><body>");

    if (contentLength <= baseLength)
        builder.append(baseString, 0, contentLength);
    else {
        unsigned currentLength = 0;
        while (currentLength < contentLength) {
            if ((currentLength + baseLength) <= contentLength)
                builder.append(baseString);
            else
                builder.append(baseString, 0, contentLength - currentLength);

            // Account for the 12 characters of the '<html><body>' prefix.
            currentLength = builder.length() - 12;
        }
    }
    builder.append("</body></html>");

    return builder.toString();
}