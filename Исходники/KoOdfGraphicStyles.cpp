QString KoOdfGraphicStyles::saveOdfGradientStyle(KoGenStyles &mainStyles, const QBrush &brush)
{
    KoGenStyle gradientStyle;
    if (brush.style() == Qt::RadialGradientPattern) {
        const QRadialGradient *gradient = static_cast<const QRadialGradient*>(brush.gradient());
        gradientStyle = KoGenStyle(KoGenStyle::RadialGradientStyle /*no family name*/);
        gradientStyle.addAttributePercent("svg:cx", gradient->center().x() * 100);
        gradientStyle.addAttributePercent("svg:cy", gradient->center().y() * 100);
        gradientStyle.addAttributePercent("svg:r",  gradient->radius() * 100);
        gradientStyle.addAttributePercent("svg:fx", gradient->focalPoint().x() * 100);
        gradientStyle.addAttributePercent("svg:fy", gradient->focalPoint().y() * 100);
    } else if (brush.style() == Qt::LinearGradientPattern) {
        const QLinearGradient *gradient = static_cast<const QLinearGradient*>(brush.gradient());
        gradientStyle = KoGenStyle(KoGenStyle::LinearGradientStyle /*no family name*/);
        gradientStyle.addAttributePercent("svg:x1", gradient->start().x() * 100);
        gradientStyle.addAttributePercent("svg:y1", gradient->start().y() * 100);
        gradientStyle.addAttributePercent("svg:x2", gradient->finalStop().x() * 100);
        gradientStyle.addAttributePercent("svg:y2", gradient->finalStop().y() * 100);
    } else if (brush.style() == Qt::ConicalGradientPattern) {
        const QConicalGradient * gradient = static_cast<const QConicalGradient*>(brush.gradient());
        gradientStyle = KoGenStyle(KoGenStyle::ConicalGradientStyle /*no family name*/);
        gradientStyle.addAttributePercent("svg:cx", gradient->center().x() * 100);
        gradientStyle.addAttributePercent("svg:cy", gradient->center().y() * 100);
        gradientStyle.addAttribute("draw:angle", QString("%1").arg(gradient->angle()));
    }
    const QGradient * gradient = brush.gradient();
    if (gradient->spread() == QGradient::RepeatSpread)
        gradientStyle.addAttribute("svg:spreadMethod", "repeat");
    else if (gradient->spread() == QGradient::ReflectSpread)
        gradientStyle.addAttribute("svg:spreadMethod", "reflect");
    else
        gradientStyle.addAttribute("svg:spreadMethod", "pad");

    if (! brush.transform().isIdentity()) {
        gradientStyle.addAttribute("svg:gradientTransform", saveTransformation(brush.transform()));
    }

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    KoXmlWriter elementWriter(&buffer);    // TODO pass indentation level

    // save stops
    QGradientStops stops = gradient->stops();
    Q_FOREACH (const QGradientStop & stop, stops) {
        elementWriter.startElement("svg:stop");
        elementWriter.addAttribute("svg:offset", QString("%1").arg(stop.first));
        elementWriter.addAttribute("svg:stop-color", stop.second.name());
        if (stop.second.alphaF() < 1.0)
            elementWriter.addAttribute("svg:stop-opacity", QString("%1").arg(stop.second.alphaF()));
        elementWriter.endElement();
    }