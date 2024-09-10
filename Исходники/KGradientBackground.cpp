bool KGradientBackground::loadStyle(KOdfLoadingContext &context, const QSizeF &shapeSize)
{
    Q_D(KGradientBackground);
    KOdfStyleStack &styleStack = context.styleStack();
    if (! styleStack.hasProperty(KOdfXmlNS::draw, "fill"))
        return false;

    QString fillStyle = styleStack.property(KOdfXmlNS::draw, "fill");
    if (fillStyle == "gradient") {
        QBrush brush = KOdf::loadOdfGradientStyle(styleStack, context.stylesReader(), shapeSize);
        const QGradient * gradient = brush.gradient();
        if (gradient) {
            d->gradient = KFlake::cloneGradient(gradient);
            d->matrix = brush.transform();
            return true;
        }
    }
    return false;
}