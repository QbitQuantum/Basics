// Returns a desugared version of the QualType, and marks ShouldAKA as true
// whenever we remove significant sugar from the type.
static QualType Desugar(ASTContext &Context, QualType QT, bool &ShouldAKA) {
  QualifierCollector QC;

  while (true) {
    const Type *Ty = QC.strip(QT);

    // Don't aka just because we saw an elaborated type...
    if (const ElaboratedType *ET = dyn_cast<ElaboratedType>(Ty)) {
      QT = ET->desugar();
      continue;
    }
    // ... or a paren type ...
    if (const ParenType *PT = dyn_cast<ParenType>(Ty)) {
      QT = PT->desugar();
      continue;
    }
    // ...or a substituted template type parameter ...
    if (const SubstTemplateTypeParmType *ST =
          dyn_cast<SubstTemplateTypeParmType>(Ty)) {
      QT = ST->desugar();
      continue;
    }
    // ...or an attributed type...
    if (const AttributedType *AT = dyn_cast<AttributedType>(Ty)) {
      QT = AT->desugar();
      continue;
    }
    // ... or an auto type.
    if (const AutoType *AT = dyn_cast<AutoType>(Ty)) {
      if (!AT->isSugared())
        break;
      QT = AT->desugar();
      continue;
    }

    // Don't desugar template specializations. 
    if (isa<TemplateSpecializationType>(Ty))
      break;

    // Don't desugar magic Objective-C types.
    if (QualType(Ty,0) == Context.getObjCIdType() ||
        QualType(Ty,0) == Context.getObjCClassType() ||
        QualType(Ty,0) == Context.getObjCSelType() ||
        QualType(Ty,0) == Context.getObjCProtoType())
      break;

    // Don't desugar va_list.
    if (QualType(Ty,0) == Context.getBuiltinVaListType())
      break;

    // Otherwise, do a single-step desugar.
    QualType Underlying;
    bool IsSugar = false;
    switch (Ty->getTypeClass()) {
#define ABSTRACT_TYPE(Class, Base)
#define TYPE(Class, Base) \
case Type::Class: { \
const Class##Type *CTy = cast<Class##Type>(Ty); \
if (CTy->isSugared()) { \
IsSugar = true; \
Underlying = CTy->desugar(); \
} \
break; \
}
#include "clang/AST/TypeNodes.def"
    }

    // If it wasn't sugared, we're done.
    if (!IsSugar)
      break;

    // If the desugared type is a vector type, we don't want to expand
    // it, it will turn into an attribute mess. People want their "vec4".
    if (isa<VectorType>(Underlying))
      break;

    // Don't desugar through the primary typedef of an anonymous type.
    if (const TagType *UTT = Underlying->getAs<TagType>())
      if (const TypedefType *QTT = dyn_cast<TypedefType>(QT))
        if (UTT->getDecl()->getTypedefForAnonDecl() == QTT->getDecl())
          break;

    // Record that we actually looked through an opaque type here.
    ShouldAKA = true;
    QT = Underlying;
  }

  // If we have a pointer-like type, desugar the pointee as well.
  // FIXME: Handle other pointer-like types.
  if (const PointerType *Ty = QT->getAs<PointerType>()) {
    QT = Context.getPointerType(Desugar(Context, Ty->getPointeeType(),
                                        ShouldAKA));
  } else if (const LValueReferenceType *Ty = QT->getAs<LValueReferenceType>()) {
    QT = Context.getLValueReferenceType(Desugar(Context, Ty->getPointeeType(),
                                                ShouldAKA));
  } else if (const RValueReferenceType *Ty = QT->getAs<RValueReferenceType>()) {
    QT = Context.getRValueReferenceType(Desugar(Context, Ty->getPointeeType(),
                                                ShouldAKA));
  }

  return QC.apply(Context, QT);
}