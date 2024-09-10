bool TextFieldInputType::isEmptyValue() const
{
    TextControlInnerTextElement* innerText = innerTextElement();
    ASSERT(innerText);

    for (Text* text = TextNodeTraversal::firstWithin(*innerText); text; text = TextNodeTraversal::next(*text, innerText)) {
        if (text->length())
            return false;
    }
    return true;
}