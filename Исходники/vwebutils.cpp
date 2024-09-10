bool VWebUtils::alterHtmlByTargetAction(const QUrl &p_baseUrl, QString &p_html, const CopyTargetAction &p_action)
{
    bool altered = false;
    switch (p_action.m_act.toLatin1()) {
    case 's':
        if (!p_html.startsWith("<html>")) {
            p_html = "<html><body>" + p_html + "</body></html>";
            altered = true;
        }

        break;

    case 'e':
        if (!p_html.startsWith("<html>")) {
            p_html = "<html><body><!--StartFragment-->" + p_html + "<!--EndFragment--></body></html>";
            altered = true;
        }

        break;

    case 'b':
        altered = removeBackgroundColor(p_html, p_action.m_args);
        break;

    case 'c':
        altered = translateColors(p_html, p_action.m_args);
        break;

    case 'i':
        altered = fixImageSrc(p_baseUrl, p_html);
        break;

    case 'm':
        altered = removeMarginPadding(p_html, p_action.m_args);
        break;

    case 'x':
        altered = removeStylesToRemoveWhenCopied(p_html, p_action.m_args);
        break;

    case 'r':
        altered = removeAllStyles(p_html, p_action.m_args);
        break;

    case 'a':
        altered = transformMarkToSpan(p_html);
        break;

    case 'p':
        altered = replacePreBackgroundColorWithCode(p_html);
        break;

    case 'n':
        altered = replaceNewLineWithBR(p_html);
        break;

    case 'g':
        altered = replaceLocalImgWithWarningLabel(p_html);
        break;

    case 'd':
        altered = addSpanInsideCode(p_html);
        break;

    case 'f':
        altered = replaceQuoteInFontFamily(p_html);
        break;

    case 'h':
        altered = replaceHeadingWithSpan(p_html);
        break;

    case 'j':
        altered = fixXHtmlTags(p_html);
        break;

    default:
        break;
    }

    return altered;
}