static void removeMarkupPrefix(String& markup)
{
    // The markup prefix is not harmful, but we remove it from the string anyway, so that
    // we can have consistent results with other ports during the layout tests.
    if (markup.startsWith(gMarkupPrefix))
        markup.remove(0, gMarkupPrefix.length());
}