/// Sets the position at \p index to (\p x, \p y).
void DiagramCoordinates::setPosition(size_t index, float x, float y)
{
    setPosition(index, Point2f(x, y));
}