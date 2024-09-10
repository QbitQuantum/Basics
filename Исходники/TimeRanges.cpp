void TimeRanges::intersectWith(const TimeRanges* other)
{
    ASSERT(other);

    if (other == this)
        return;

    RefPtr<TimeRanges> invertedOther = other->copy();
    invertedOther->invert();

    invert();
    unionWith(invertedOther.get());
    invert();
}