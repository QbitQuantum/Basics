AffineTransform RenderSVGContainer::getAspectRatio(const FloatRect& logical, const FloatRect& physical) const
{
    AffineTransform temp;

    float logicX = logical.x();
    float logicY = logical.y();
    float logicWidth = logical.width();
    float logicHeight = logical.height();
    float physWidth = physical.width();
    float physHeight = physical.height();

    float vpar = logicWidth / logicHeight;
    float svgar = physWidth / physHeight;

    if (align() == ALIGN_NONE) {
        temp.scale(physWidth / logicWidth, physHeight / logicHeight);
        temp.translate(-logicX, -logicY);
    } else if ((vpar < svgar && !slice()) || (vpar >= svgar && slice())) {
        temp.scale(physHeight / logicHeight, physHeight / logicHeight);

        if (align() == ALIGN_XMINYMIN || align() == ALIGN_XMINYMID || align() == ALIGN_XMINYMAX)
            temp.translate(-logicX, -logicY);
        else if (align() == ALIGN_XMIDYMIN || align() == ALIGN_XMIDYMID || align() == ALIGN_XMIDYMAX)
            temp.translate(-logicX - (logicWidth - physWidth * logicHeight / physHeight) / 2, -logicY);
        else
            temp.translate(-logicX - (logicWidth - physWidth * logicHeight / physHeight), -logicY);
    } else {
        temp.scale(physWidth / logicWidth, physWidth / logicWidth);

        if (align() == ALIGN_XMINYMIN || align() == ALIGN_XMIDYMIN || align() == ALIGN_XMAXYMIN)
            temp.translate(-logicX, -logicY);
        else if (align() == ALIGN_XMINYMID || align() == ALIGN_XMIDYMID || align() == ALIGN_XMAXYMID)
            temp.translate(-logicX, -logicY - (logicHeight - physHeight * logicWidth / physWidth) / 2);
        else
            temp.translate(-logicX, -logicY - (logicHeight - physHeight * logicWidth / physWidth));
    }

    return temp;
}