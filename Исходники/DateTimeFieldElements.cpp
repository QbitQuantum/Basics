RawPtr<DateTimeHour11FieldElement> DateTimeHour11FieldElement::create(Document& document, FieldOwner& fieldOwner, const Range& hour23Range, const Step& step)
{
    ASSERT(hour23Range.minimum >= 0);
    ASSERT(hour23Range.maximum <= 23);
    ASSERT(hour23Range.minimum <= hour23Range.maximum);
    Range range(0, 11);
    if (hour23Range.maximum < 12)
        range = hour23Range;
    else if (hour23Range.minimum >= 12) {
        range.minimum = hour23Range.minimum - 12;
        range.maximum = hour23Range.maximum - 12;
    }

    RawPtr<DateTimeHour11FieldElement> field = new DateTimeHour11FieldElement(document, fieldOwner, range, step);
    field->initialize();
    return field.release();
}