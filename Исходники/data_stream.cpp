size_t DataStream::getPosition()const
{
    return distance(this->beg, this->iter);
}