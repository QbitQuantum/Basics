void Rect::grow(float amount) {

    setX(getX() - amount);
    setY(getY() - amount);
    setW(getW() + amount * 2);
    setH(getH() + amount * 2);
}