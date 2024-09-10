TransformationMatrix SVGLocatable::getTransformToElement(SVGElement* target, ExceptionCode& ec) const
{
    TransformationMatrix ctm = getCTM();

    if (target && target->isStyledLocatable()) {
        TransformationMatrix targetCTM = static_cast<SVGStyledLocatableElement*>(target)->getCTM();
        if (!targetCTM.isInvertible()) {
            ec = SVGException::SVG_MATRIX_NOT_INVERTABLE;
            return ctm;
        }
        ctm *= targetCTM.inverse();
    }

    return ctm;
}