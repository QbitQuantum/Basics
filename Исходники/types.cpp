AString
sp::BuildTypeName(Type *aType, Atom *name, TypeDiagFlags flags)
{
  if (ArrayType *type = aType->asArray()) {
    Vector<ArrayType *> stack;

    Type *cursor = type;
    Type *innermost = nullptr;
    for (;;) {
      if (!cursor->isArray()) {
        innermost = cursor;
        break;
      }
      stack.append(cursor->toArray());
      cursor = cursor->toArray()->contained();
    }

    AutoString builder;
    if (aType->isConst() || !!(flags & TypeDiagFlags::IsConst))
      builder = "const ";

    builder = builder + BuildTypeName(innermost, nullptr, flags & kDiagFlagsInnerMask);

    bool hasFixedLengths = false;
    AutoString brackets;
    for (size_t i = 0; i < stack.length(); i++) {
      if (!stack[i]->hasFixedLength()) {
        brackets = brackets + "[]";
        continue;
      }

      hasFixedLengths = true;
      brackets = brackets + "[" + AutoString(stack[i]->fixedLength()) + "]";
    }

    if (name) {
      if (hasFixedLengths)
        builder = builder + " " + name->chars() + brackets;
      else
        builder = builder + brackets + " " + name->chars();
    } else {
      builder = builder + brackets;
    }
    return AString(builder.ptr());
  }

  AutoString builder;
  if (FunctionType *type = aType->asFunction())
    builder = BuildTypeFromSignature(type->signature(), flags & kDiagFlagsInnerMask);
  else
    builder = GetBaseTypeName(aType);
  if (!!(flags & TypeDiagFlags::IsByRef)) {
    builder = builder + "&";
  }
  if (name)
    builder = builder + " " + name->chars();
  return AString(builder.ptr());
}