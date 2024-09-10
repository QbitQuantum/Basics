/**
 * get an array of size_t values that indicate possible pointer words in memory 
 *  if interpreted as the type given as argument
 * the first array element is the size of the type for independent interpretation
 *  of the array
 * following elements bits represent one word (4/8 bytes depending on the target 
 *  architecture). If set the corresponding memory might contain a pointer/reference.
 *
 *  [T.sizeof, pointerbit0-31/63, pointerbit32/64-63/128, ...]
 */
Expression *pointerBitmap(TraitsExp *e)
{
    int result = 0;
    if (!e->args || e->args->dim != 1)
    {
        error(e->loc, "a single type expected for trait pointerBitmap");
        return new ErrorExp();
    }
    Type *t = getType((*e->args)[0]);
    if (!t)
    {
        error(e->loc, "%s is not a type", (*e->args)[0]->toChars());
        return new ErrorExp();
    }
    d_uns64 sz = t->size(e->loc);
    if (t->ty == Tclass && !((TypeClass*)t)->sym->isInterfaceDeclaration())
        sz = ((TypeClass*)t)->sym->AggregateDeclaration::size(e->loc);

    d_uns64 sz_size_t = Type::tsize_t->size(e->loc);
    d_uns64 bitsPerWord = sz_size_t * 8;
    d_uns64 cntptr = (sz + sz_size_t - 1) / sz_size_t;
    d_uns64 cntdata = (cntptr + bitsPerWord - 1) / bitsPerWord;
    Array<d_uns64> data;
    data.setDim((size_t)cntdata);
    data.zero();

    class PointerBitmapVisitor : public Visitor
    {
    public:
        PointerBitmapVisitor(Array<d_uns64>* _data, d_uns64 _sz_size_t)
            : data(_data), offset(0), sz_size_t(_sz_size_t) 
        {}
        
        void setpointer(d_uns64 off)
        {
            d_uns64 ptroff = off / sz_size_t;
            (*data)[(size_t)(ptroff / (8 * sz_size_t))] |= 1LL << (ptroff % (8 * sz_size_t));
        }
        virtual void visit(Type *t) 
        {
            Type *tb = t->toBasetype();
            if (tb != t)
                tb->accept(this);
        }
        virtual void visit(TypeError *t) { visit((Type *)t); }
        virtual void visit(TypeNext *t) { assert(0); }
        virtual void visit(TypeBasic *t)
        {
            if (t->ty == Tvoid)
                setpointer(offset);
        }
        virtual void visit(TypeVector *t) { }
        virtual void visit(TypeArray *t) { assert(0); }
        virtual void visit(TypeSArray *t)
        {
            d_uns64 arrayoff = offset;
            d_uns64 nextsize = t->next->size();
            d_uns64 dim = t->dim->toInteger();
            for (d_uns64 i = 0; i < dim; i++)
            {
                offset = arrayoff + i * nextsize;
                t->next->accept(this);
            }
            offset = arrayoff;
        }
        virtual void visit(TypeDArray *t) { setpointer(offset + sz_size_t); } // dynamic array is {length,ptr}
        virtual void visit(TypeAArray *t) { setpointer(offset); }
        virtual void visit(TypePointer *t) 
        {
            if (t->nextOf()->ty != Tfunction) // don't mark function pointers
                setpointer(offset);
        }
        virtual void visit(TypeReference *t) { setpointer(offset); }
        virtual void visit(TypeClass *t) { setpointer(offset); }
        virtual void visit(TypeFunction *t) { }
        virtual void visit(TypeDelegate *t) { setpointer(offset); } // delegate is {context, function}
        virtual void visit(TypeQualified *t) { assert(0); } // assume resolved
        virtual void visit(TypeIdentifier *t) { assert(0); }
        virtual void visit(TypeInstance *t) { assert(0); }
        virtual void visit(TypeTypeof *t) { assert(0); }
        virtual void visit(TypeReturn *t) { assert(0); }
        virtual void visit(TypeEnum *t) { visit((Type *)t); }
        virtual void visit(TypeTuple *t) { visit((Type *)t); }
        virtual void visit(TypeSlice *t) { assert(0); }
        virtual void visit(TypeNull *t) { assert(0); }

        virtual void visit(TypeStruct *t)
        {
            d_uns64 structoff = offset;
            for (size_t i = 0; i < t->sym->fields.dim; i++)
            {
                VarDeclaration *v = t->sym->fields[i];
                offset = structoff + v->offset;
                if (v->type->ty == Tclass)
                    setpointer(offset);
                else
                    v->type->accept(this);
            }
            offset = structoff;
        }

        // a "toplevel" class is treated as an instance, while TypeClass fields are treated as references
        void visitClass(TypeClass* t)
        {
            d_uns64 classoff = offset;

            // skip vtable-ptr and monitor
            if (t->sym->baseClass)
                visitClass((TypeClass*)t->sym->baseClass->type);

            for (size_t i = 0; i < t->sym->fields.dim; i++)
            {
                VarDeclaration *v = t->sym->fields[i];
                offset = classoff + v->offset;
                v->type->accept(this);
            }
            offset = classoff;
        }

        Array<d_uns64>* data;
        d_uns64 offset;
        d_uns64 sz_size_t;
    };

    PointerBitmapVisitor pbv(&data, sz_size_t);
    if (t->ty == Tclass)
        pbv.visitClass((TypeClass*)t);
    else
        t->accept(&pbv);

    Expressions* exps = new Expressions;
    exps->push(new IntegerExp(e->loc, sz, Type::tsize_t));
    for (d_uns64 i = 0; i < cntdata; i++)
        exps->push(new IntegerExp(e->loc, data[(size_t)i], Type::tsize_t));

    ArrayLiteralExp* ale = new ArrayLiteralExp(e->loc, exps);
    ale->type = Type::tsize_t->sarrayOf(cntdata + 1);
    return ale;
}