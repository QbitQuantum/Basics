void RenderTextControl::adjustInnerTextStyle(const RenderStyle* startStyle, RenderStyle& textBlockStyle) const
{
    // The inner block, if present, always has its direction set to LTR,
    // so we need to inherit the direction and unicode-bidi style from the element.
    textBlockStyle.setDirection(style().direction());
    textBlockStyle.setUnicodeBidi(style().unicodeBidi());

    HTMLTextFormControlElement& control = textFormControlElement();
    if (HTMLElement* innerText = control.innerTextElement()) {
        if (const StyleProperties* properties = innerText->presentationAttributeStyle()) {
            RefPtr<CSSValue> value = properties->getPropertyCSSValue(CSSPropertyWebkitUserModify);
            if (is<CSSPrimitiveValue>(value.get()))
                textBlockStyle.setUserModify(downcast<CSSPrimitiveValue>(*value));
        }
    }

    if (control.isDisabledFormControl())
        textBlockStyle.setColor(theme().disabledTextColor(textBlockStyle.visitedDependentColor(CSSPropertyColor), startStyle->visitedDependentColor(CSSPropertyBackgroundColor)));
#if PLATFORM(IOS)
    if (textBlockStyle.textSecurity() != TSNONE && !textBlockStyle.isLeftToRightDirection()) {
        // Preserve the alignment but force the direction to LTR so that the last-typed, unmasked character
        // (which cannot have RTL directionality) will appear to the right of the masked characters. See <rdar://problem/7024375>.
        
        switch (textBlockStyle.textAlign()) {
        case TASTART:
        case JUSTIFY:
            textBlockStyle.setTextAlign(RIGHT);
            break;
        case TAEND:
            textBlockStyle.setTextAlign(LEFT);
            break;
        case LEFT:
        case RIGHT:
        case CENTER:
        case WEBKIT_LEFT:
        case WEBKIT_RIGHT:
        case WEBKIT_CENTER:
            break;
        }

        textBlockStyle.setDirection(LTR);
    }
#endif
}