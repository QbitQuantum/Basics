// Remove attributes
bool wxTextAttr::RemoveStyle(wxTextAttr& destStyle, const wxTextAttr& style)
{
    int flags = style.GetFlags();
    int destFlags = destStyle.GetFlags();

    // We must treat text effects specially, since we must remove only some.
    if (style.HasTextEffects() && (style.GetTextEffectFlags() != 0))
    {
        int newTextEffectFlags = destStyle.GetTextEffectFlags() & ~style.GetTextEffectFlags();
        int newTextEffects = destStyle.GetTextEffects() & ~style.GetTextEffectFlags();
        destStyle.SetTextEffects(newTextEffects);
        destStyle.SetTextEffectFlags(newTextEffectFlags);

        // Don't remove wxTEXT_ATTR_EFFECTS unless the resulting flags are zero
        if (newTextEffectFlags != 0)
            flags &= ~wxTEXT_ATTR_EFFECTS;
    }

    destStyle.SetFlags(destFlags & ~flags);

    return true;
}