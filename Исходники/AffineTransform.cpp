void AffineTransform::blend(const AffineTransform& from, double progress)
{
    DecomposedType srA, srB;

    from.decompose(srA);
    this->decompose(srB);

    // If x-axis of one is flipped, and y-axis of the other, convert to an unflipped rotation.
    if ((srA.scaleX < 0 && srB.scaleY < 0) || (srA.scaleY < 0 &&  srB.scaleX < 0)) {
        srA.scaleX = -srA.scaleX;
        srA.scaleY = -srA.scaleY;
        srA.angle += srA.angle < 0 ? piDouble : -piDouble;
    }

    // Don't rotate the long way around.
    srA.angle = fmod(srA.angle, 2 * piDouble);
    srB.angle = fmod(srB.angle, 2 * piDouble);

    if (fabs(srA.angle - srB.angle) > piDouble) {
        if (srA.angle > srB.angle)
            srA.angle -= piDouble * 2;
        else
            srB.angle -= piDouble * 2;
    }

    srA.scaleX += progress * (srB.scaleX - srA.scaleX);
    srA.scaleY += progress * (srB.scaleY - srA.scaleY);
    srA.angle += progress * (srB.angle - srA.angle);
    srA.remainderA += progress * (srB.remainderA - srA.remainderA);
    srA.remainderB += progress * (srB.remainderB - srA.remainderB);
    srA.remainderC += progress * (srB.remainderC - srA.remainderC);
    srA.remainderD += progress * (srB.remainderD - srA.remainderD);
    srA.translateX += progress * (srB.translateX - srA.translateX);
    srA.translateY += progress * (srB.translateY - srA.translateY);

    this->recompose(srA);
}