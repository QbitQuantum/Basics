void VehicleSelectionView::drawBar(Surface &dest, const iXY &pos, int length, float percent)
{
    iXY size(int(float(length) * percent), Surface::getFontHeight());

    dest.fillRect(iRect(pos.x, pos.y, size.x, size.y), Color::red);
}