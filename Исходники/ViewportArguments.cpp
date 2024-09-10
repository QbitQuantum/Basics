ViewportAttributes computeViewportAttributes(ViewportArguments args, int desktopWidth, int deviceWidth, int deviceHeight, int deviceDPI, IntSize visibleViewport)
{
    ViewportAttributes result;

    float availableWidth = visibleViewport.width();
    float availableHeight = visibleViewport.height();

#if !OS(ANDROID) // FIXME: Enable this assert http://b/5633905.
    ASSERT(availableWidth > 0 && availableHeight > 0);
#endif

    float autoDPI = deviceDPI;

    switch (args.type) {
    case ViewportArguments::Implicit:
        autoDPI = deviceDPI;
        break;
    case ViewportArguments::ViewportMeta:
        autoDPI = 160;
        break;
    }

#if OS(ANDROID)
    bool isAutoDPI = args.targetDensityDpi == ViewportArguments::ValueAuto;
#endif

    switch (int(args.targetDensityDpi)) {
    case ViewportArguments::ValueDeviceDPI:
        args.targetDensityDpi = deviceDPI;
        break;
    case ViewportArguments::ValueLowDPI:
        args.targetDensityDpi = 120;
        break;
    case ViewportArguments::ValueAuto:
        args.targetDensityDpi = autoDPI;
        break;
    case ViewportArguments::ValueMediumDPI:
        args.targetDensityDpi = 160;
        break;
    case ViewportArguments::ValueHighDPI:
        args.targetDensityDpi = 240;
        break;
    }

    result.devicePixelRatio = float(deviceDPI / args.targetDensityDpi);
#if OS(ANDROID)
    // Snap the devicePixelRatio so that it converts the device width from
    // integer to integer.  Since we're currently applying it with page scale,
    // effectively this will happen later in the pipeline anyway, so we should
    // do it in advance to make all calculations match that.
    int deviceWidthInLayoutPixels = static_cast<int>(deviceWidth / result.devicePixelRatio);
    result.devicePixelRatio = deviceWidth / static_cast<float>(deviceWidthInLayoutPixels);
#endif

    // Resolve non-'auto' width and height to pixel values.
    if (result.devicePixelRatio != 1.0) {
        availableWidth /= result.devicePixelRatio;
        availableHeight /= result.devicePixelRatio;
        deviceWidth /= result.devicePixelRatio;
        deviceHeight /= result.devicePixelRatio;
    }

#if OS(ANDROID)
    result.devicePixelRatioForDeviceDimensions = isAutoDPI ? (deviceDPI / 160.0f) : result.devicePixelRatio;
#endif

    switch (int(args.width)) {
    case ViewportArguments::ValueDesktopWidth:
        args.width = desktopWidth;
        break;
    case ViewportArguments::ValueDeviceWidth:
        args.width = deviceWidth;
        break;
    case ViewportArguments::ValueDeviceHeight:
        args.width = deviceHeight;
        break;
    }

    switch (int(args.height)) {
    case ViewportArguments::ValueDesktopWidth:
        args.height = desktopWidth;
        break;
    case ViewportArguments::ValueDeviceWidth:
        args.height = deviceWidth;
        break;
    case ViewportArguments::ValueDeviceHeight:
        args.height = deviceHeight;
        break;
    }

    // Clamp values to range defined by spec and resolve minimum-scale and maximum-scale values
    if (args.width != ViewportArguments::ValueAuto)
        args.width = min(float(10000), max(args.width, float(1)));
    if (args.height != ViewportArguments::ValueAuto)
        args.height = min(float(10000), max(args.height, float(1)));

    if (args.initialScale != ViewportArguments::ValueAuto)
        args.initialScale = min(float(10), max(args.initialScale, float(0.1)));
    if (args.minimumScale != ViewportArguments::ValueAuto)
        args.minimumScale = min(float(10), max(args.minimumScale, float(0.1)));
    if (args.maximumScale != ViewportArguments::ValueAuto)
        args.maximumScale = min(float(10), max(args.maximumScale, float(0.1)));

    // Resolve minimum-scale and maximum-scale values according to spec.
    if (args.minimumScale == ViewportArguments::ValueAuto)
        result.minimumScale = float(0.25);
    else
        result.minimumScale = args.minimumScale;

    if (args.maximumScale == ViewportArguments::ValueAuto) {
        result.maximumScale = float(5.0);
        result.minimumScale = min(float(5.0), result.minimumScale);
    } else
        result.maximumScale = args.maximumScale;
    result.maximumScale = max(result.minimumScale, result.maximumScale);

    // Resolve initial-scale value.
    result.initialScale = args.initialScale;
    if (result.initialScale == ViewportArguments::ValueAuto) {
        result.initialScale = availableWidth / desktopWidth;
        if (args.width != ViewportArguments::ValueAuto)
            result.initialScale = availableWidth / args.width;
        if (args.height != ViewportArguments::ValueAuto) {
            // if 'auto', the initial-scale will be negative here and thus ignored.
            result.initialScale = max<float>(result.initialScale, availableHeight / args.height);
        }
    }

    // Constrain initial-scale value to minimum-scale/maximum-scale range.
    result.initialScale = min(result.maximumScale, max(result.minimumScale, result.initialScale));

    // Resolve width value.
    float width;
    if (args.width != ViewportArguments::ValueAuto)
        width = args.width;
    else {
        if (args.initialScale == ViewportArguments::ValueAuto)
            width = desktopWidth;
        else if (args.height != ViewportArguments::ValueAuto)
            width = args.height * (availableWidth / availableHeight);
        else
            width = availableWidth / result.initialScale;
    }

    // Resolve height value.
    float height;
    if (args.height != ViewportArguments::ValueAuto)
        height = args.height;
    else
        height = width * availableHeight / availableWidth;

    // Extend width and height to fill the visual viewport for the resolved initial-scale.
    width = max<float>(width, availableWidth / result.initialScale);
    height = max<float>(height, availableHeight / result.initialScale);
    result.layoutSize.setWidth(static_cast<int>(roundf(width)));
    result.layoutSize.setHeight(static_cast<int>(roundf(height)));

    result.userScalable = args.userScalable;

    return result;
}