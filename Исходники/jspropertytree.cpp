void
ShapeGetterSetterRef::mark(JSTracer *trc)
{
    // Update the current shape's entry in the parent KidsHash table if needed.
    // This is necessary as the computed hash includes the getter/setter
    // pointers.

    JSObject *obj = *objp;
    JSObject *prior = obj;
    if (!prior)
        return;

    trc->setTracingLocation(&*prior);
    gc::Mark(trc, &obj, "AccessorShape getter or setter");
    if (obj == *objp)
        return;

    Shape *parent = shape->parent;
    if (shape->inDictionary() || !parent->kids.isHash()) {
        *objp = obj;
        return;
    }

    KidsHash *kh = parent->kids.toHash();
    kh->remove(StackShape(shape));
    *objp = obj;
    MOZ_ALWAYS_TRUE(kh->putNew(StackShape(shape), shape));
}