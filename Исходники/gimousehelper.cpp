bool GiMouseHelper::onMouseMove(float x, float y, bool ldown, bool)
{
    bool ret = false;

    if (ldown && _ldown) {
        if (!_moved && _hypotf(x - _startX, y - _startY) > 5.f) {
            _moved = _coreView->onGesture(_view, kGiGesturePan, 
                kGiGestureBegan, _startX, _startY);
        }
        if (_moved) {
            ret = _coreView->onGesture(_view, kGiGesturePan, 
                kGiGestureMoved, x, y);
        }
    }

    return ret;
}