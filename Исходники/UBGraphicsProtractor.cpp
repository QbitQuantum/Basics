UBItem* UBGraphicsProtractor::deepCopy() const
{
    UBGraphicsProtractor* copy = new UBGraphicsProtractor();

    copy->setPos(this->pos());
    copy->setRect(this->rect());
    copy->setTransform(this->transform());

    copy->mCurrentAngle = this->mCurrentAngle;
    copy->mSpan = this->mSpan;
    copy->mStartAngle = this->mStartAngle;
    copy->mScaleFactor = this->mScaleFactor;

    // TODO UB 4.7 ... complete all members ?

    return copy;
}