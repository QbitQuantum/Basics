void RenderMenuList::adjustInnerStyle()
{
    RenderStyle* innerStyle = m_innerBlock->style();
    innerStyle->setFlexGrow(1);
    innerStyle->setFlexShrink(1);
    // min-width: 0; is needed for correct shrinking.
    // FIXME: Remove this line when https://bugs.webkit.org/show_bug.cgi?id=111790 is fixed.
    innerStyle->setMinWidth(Length(0, Fixed));
    // Use margin:auto instead of align-items:center to get safe centering, i.e.
    // when the content overflows, treat it the same as align-items: flex-start.
    // But we only do that for the cases where html.css would otherwise use center.
    if (style()->alignItems() == AlignCenter) {
        innerStyle->setMarginTop(Length());
        innerStyle->setMarginBottom(Length());
        innerStyle->setAlignSelf(AlignFlexStart);
    }

    innerStyle->setPaddingLeft(Length(theme()->popupInternalPaddingLeft(style()), Fixed));
    innerStyle->setPaddingRight(Length(theme()->popupInternalPaddingRight(style()), Fixed));
    innerStyle->setPaddingTop(Length(theme()->popupInternalPaddingTop(style()), Fixed));
    innerStyle->setPaddingBottom(Length(theme()->popupInternalPaddingBottom(style()), Fixed));

    if (document()->page()->chrome().selectItemWritingDirectionIsNatural()) {
        // Items in the popup will not respect the CSS text-align and direction properties,
        // so we must adjust our own style to match.
        innerStyle->setTextAlign(LEFT);
        TextDirection direction = (m_buttonText && m_buttonText->text()->defaultWritingDirection() == WTF::Unicode::RightToLeft) ? RTL : LTR;
        innerStyle->setDirection(direction);
    } else if (m_optionStyle && document()->page()->chrome().selectItemAlignmentFollowsMenuWritingDirection()) {
        if ((m_optionStyle->direction() != innerStyle->direction() || m_optionStyle->unicodeBidi() != innerStyle->unicodeBidi()))
            m_innerBlock->setNeedsLayoutAndPrefWidthsRecalc();
        innerStyle->setTextAlign(style()->isLeftToRightDirection() ? LEFT : RIGHT);
        innerStyle->setDirection(m_optionStyle->direction());
        innerStyle->setUnicodeBidi(m_optionStyle->unicodeBidi());
    }
}