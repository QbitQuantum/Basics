/*
 * Construct a call object for the given bindings.  If this is a call object
 * for a function invocation, callee should be the function being called.
 * Otherwise it must be a call object for eval of strict mode code, and callee
 * must be null.
 */
CallObject *
CallObject::create(JSContext *cx, JSScript *script, JSObject &enclosing, JSObject *callee)
{
    RootedVarShape shape(cx);
    shape = script->bindings.callObjectShape(cx);
    if (shape == NULL)
        return NULL;

    gc::AllocKind kind = gc::GetGCObjectKind(shape->numFixedSlots() + 1);

    RootedVarTypeObject type(cx);

    type = cx->compartment->getEmptyType(cx);
    if (!type)
        return NULL;

    HeapSlot *slots;
    if (!PreallocateObjectDynamicSlots(cx, shape, &slots))
        return NULL;

    JSObject *obj = JSObject::create(cx, kind, shape, type, slots);
    if (!obj)
        return NULL;

    /*
     * Update the parent for bindings associated with non-compileAndGo scripts,
     * whose call objects do not have a consistent global variable and need
     * to be updated dynamically.
     */
    JSObject &global = enclosing.global();
    if (&global != obj->getParent()) {
        JS_ASSERT(obj->getParent() == NULL);
        if (!obj->setParent(cx, &global))
            return NULL;
    }

#ifdef DEBUG
    JS_ASSERT(!obj->inDictionaryMode());
    for (Shape::Range r = obj->lastProperty(); !r.empty(); r.popFront()) {
        const Shape &s = r.front();
        if (s.hasSlot()) {
            JS_ASSERT(s.slot() + 1 == obj->slotSpan());
            break;
        }
    }
#endif

    if (!obj->asScope().setEnclosingScope(cx, enclosing))
        return NULL;

    JS_ASSERT_IF(callee, callee->isFunction());
    obj->initFixedSlot(CALLEE_SLOT, ObjectOrNullValue(callee));
    obj->initFixedSlot(ARGUMENTS_SLOT, MagicValue(JS_UNASSIGNED_ARGUMENTS));

    /*
     * If |bindings| is for a function that has extensible parents, that means
     * its Call should have its own shape; see BaseShape::extensibleParents.
     */
    if (obj->lastProperty()->extensibleParents() && !obj->generateOwnShape(cx))
        return NULL;

    return &obj->asCall();
}