void KPrShapeManagerAnimationStrategy::paint( KoShape * shape, QPainter &painter, const KoViewConverter &converter, bool forPrint )
{
    if ( ! dynamic_cast<KPrPlaceholderShape *>( shape ) && m_strategy->page()->displayShape( shape ) ) {
        if ( m_animationCache->value(shape, "visibility", true).toBool() ) {
            painter.save();
            QTransform animationTransform = m_animationCache->value(shape, "transform", QTransform()).value<QTransform>();;
            QTransform transform(painter.transform() * shape->absoluteTransformation(&converter));
            if (animationTransform.isScaling()) {
                transform = animationTransform * transform;
            } else {
                transform = transform * animationTransform;
            }

            painter.setTransform(transform);
            // paint shape
            shapeManager()->paintShape( shape, painter, converter, forPrint );
            painter.restore();  // for the transform
        }
    }
}