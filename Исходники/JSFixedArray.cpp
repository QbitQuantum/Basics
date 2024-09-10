void JSFixedArray::dumpToStream(const JSCell* cell, PrintStream& out)
{
    VM& vm = *cell->vm();
    const auto* thisObject = jsCast<const JSFixedArray*>(cell);
    out.printf("<%p, %s, [%u], [", thisObject, thisObject->className(vm), thisObject->length());
    CommaPrinter comma;
    for (unsigned index = 0; index < thisObject->length(); ++index)
        out.print(comma, thisObject->get(index));
    out.print("]>");
}