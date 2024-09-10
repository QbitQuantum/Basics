void FieldAsset::drawPath(
    const Vec2& from, const Vec2& to, bool isLast, const Color4F& fromColor, 
    const Color4F& toColor
) {
    Vec2 control = (from + to)/2 + Vec2(0, from.distance(to) / 4);
    float t = 0;
    Vec2 lastVertex;
    Vec2 vertex;    
    float drawUpperLimit = 1;
    if(isLast) drawUpperLimit = _fieldModel->birdJumpProgress;
    while(t < drawUpperLimit) {
	// TODO: compute this value somewhere else
        float x = powf(1 - t, 2) * from.x + 2.0f * (1 - t) * t * control.x + t * t * to.x;
        float y = powf(1 - t, 2) * from.y + 2.0f * (1 - t) * t * control.y + t * t * to.y;
        vertex = Vec2(x, y);
	if(lastVertex.distance(vertex) >= 6) {
	    auto colorBorder = Color4F::GRAY;
	    auto colorInnder = mixColors(fromColor, toColor, 1-t);
	    _errorPathDrawer->drawDot(vertex, 2.5, colorBorder);
	    _errorPathDrawer->drawDot(vertex, 2, colorInnder);
	    lastVertex = vertex;
	}
        t += 0.005;
    }
    
}