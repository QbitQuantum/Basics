bool RenderImageScaleObserver::shouldImagePaintAtLowQuality(RenderImage* image, const IntSize& size)
{
    // If the image is not a bitmap image, then none of this is relevant and we just paint at high
    // quality.
    if (!image->image() || !image->image()->isBitmapImage())
        return false;

    // Make sure to use the unzoomed image size, since if a full page zoom is in effect, the image
    // is actually being scaled.
    IntSize imageSize(image->image()->width(), image->image()->height());

    // Look ourselves up in the hashtable.
    RenderImageScaleData* data = 0;
    if (gImages)
        data = gImages->get(image);

    if (imageSize == size) {
        // There is no scale in effect.  If we had a scale in effect before, we can just delete this data.
        if (data) {
            gImages->remove(image);
            delete data;
        }
        return false;
    }

    // There is no need to hash scaled images that always use low quality mode when the page demands it.  This is the iChat case.
    if (image->document()->page()->inLowQualityImageInterpolationMode()) {
        double totalPixels = static_cast<double>(image->image()->width()) * static_cast<double>(image->image()->height());
        if (totalPixels > cInterpolationCutoff)
            return true;
    }

    // If there is no data yet, we will paint the first scale at high quality and record the paint time in case a second scale happens
    // very soon.
    if (!data) {
        data = new RenderImageScaleData(image, size, currentTime(), false);
        if (!gImages)
            gImages = new HashMap<RenderImage*, RenderImageScaleData*>;
        gImages->set(image, data);
        return false;
    }

    // We are scaled, but we painted already at this size, so just keep using whatever mode we last painted with.
    if (data->size() == size)
        return data->useLowQualityScale();

    // We have data and our size just changed.  If this change happened quickly, go into low quality mode and then set a repaint
    // timer to paint in high quality mode.  Otherwise it is ok to just paint in high quality mode.
    double newTime = currentTime();
    data->setUseLowQualityScale(newTime - data->time() < cLowQualityTimeThreshold);
    data->setTime(newTime);
    data->setSize(size);
    return data->useLowQualityScale();
}