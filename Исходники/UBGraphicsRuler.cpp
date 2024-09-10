UBItem* UBGraphicsRuler::deepCopy() const
{
    UBGraphicsRuler* copy = new UBGraphicsRuler();

    copy->setPos(this->pos());
    copy->setRect(this->rect());
    copy->setTransform(this->transform());

    // TODO UB 4.7 ... complete all members ?

    return copy;
}