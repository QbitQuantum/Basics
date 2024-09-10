int UniscribeHelper::xToCharacter(int x) const
{
    // We iterate in screen order until we find the item with the given pixel
    // position in it. When we find that guy, we ask Uniscribe for the
    // character index.
    HRESULT hr;
    for (size_t screenIndex = 0; screenIndex < m_runs.size(); screenIndex++) {
        int itemIndex = m_screenOrder[screenIndex];
        int itemAdvance = advanceForItem(itemIndex);

        // Note that the run may be empty if shaping failed, so we want to skip
        // over it.
        const Shaping& shaping = m_shapes[itemIndex];
        int itemLength = shaping.charLength();
        if (x <= itemAdvance && itemLength > 0) {
            // The requested offset is within this item.
            const SCRIPT_ITEM& item = m_runs[itemIndex];

            // Account for the leading space we've added to this run that
            // Uniscribe doesn't know about.
            x -= shaping.m_prePadding;

            int charX = 0;
            int trailing;
            hr = ScriptXtoCP(x, itemLength, shaping.glyphLength(),
                             &shaping.m_logs[0], &shaping.m_visualAttributes[0],
                             shaping.effectiveAdvances(), &item.a, &charX,
                             &trailing);

            // The character offset is within the item. We need to add the
            // item's offset to transform it into the space of the TextRun
            return charX + item.iCharPos;
        }

        // The offset is beyond this item, account for its length and move on.
        x -= itemAdvance;
    }

    // Error condition, we don't know what to do if we don't have that X
    // position in any of our items.
    return 0;
}