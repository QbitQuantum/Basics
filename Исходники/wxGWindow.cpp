void wxGWindow::setDimensions (const Rect2D &dims) {
    window->SetSize(dims.x0(), dims.y0(), dims.width(), dims.height());
}