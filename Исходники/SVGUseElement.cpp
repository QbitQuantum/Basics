void SVGUseElement::toClipPath(Path& path)
{
    ASSERT(path.isEmpty());

    auto* targetClone = this->targetClone();
    if (!is<SVGGraphicsElement>(targetClone))
        return;

    if (!isDirectReference(*targetClone)) {
        // Spec: Indirect references are an error (14.3.5)
        document().accessSVGExtensions().reportError(ASCIILiteral("Not allowed to use indirect reference in <clip-path>"));
        return;
    }

    downcast<SVGGraphicsElement>(*targetClone).toClipPath(path);
    SVGLengthContext lengthContext(this);
    // FIXME: Find a way to do this without manual resolution of x/y here. It's potentially incorrect.
    path.translate(FloatSize(x().value(lengthContext), y().value(lengthContext)));
    path.transform(animatedLocalTransform());
}