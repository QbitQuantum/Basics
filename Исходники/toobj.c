        void visit(ClassDeclaration *cd)
        {
            //printf("ClassDeclaration::toObjFile('%s')\n", cd->toChars());

            if (cd->type->ty == Terror)
            {
                cd->error("had semantic errors when compiling");
                return;
            }

            if (!cd->members)
                return;

            if (multiobj && !cd->hasStaticCtorOrDtor())
            {
                obj_append(cd);
                return;
            }

            if (global.params.symdebug)
                toDebug(cd);

            assert(!cd->scope);     // semantic() should have been run to completion

            enum_SC scclass = SCglobal;
            if (cd->isInstantiated())
                scclass = SCcomdat;

            // Put out the members
            for (size_t i = 0; i < cd->members->dim; i++)
            {
                Dsymbol *member = (*cd->members)[i];
                /* There might be static ctors in the members, and they cannot
                 * be put in separate obj files.
                 */
                member->accept(this);
            }

            // Generate C symbols
            toSymbol(cd);
            toVtblSymbol(cd);
            Symbol *sinit = toInitializer(cd);

            //////////////////////////////////////////////

            // Generate static initializer
            sinit->Sclass = scclass;
            sinit->Sfl = FLdata;
            ClassDeclaration_toDt(cd, &sinit->Sdt);
            out_readonly(sinit);
            outdata(sinit);

            //////////////////////////////////////////////

            // Put out the TypeInfo
            genTypeInfo(cd->type, NULL);
            //toObjFile(cd->type->vtinfo, multiobj);

            //////////////////////////////////////////////

            // Put out the ClassInfo
            cd->csym->Sclass = scclass;
            cd->csym->Sfl = FLdata;

            /* The layout is:
               {
                    void **vptr;
                    monitor_t monitor;
                    byte[] initializer;         // static initialization data
                    char[] name;                // class name
                    void *[] vtbl;
                    Interface[] interfaces;
                    ClassInfo *base;            // base class
                    void *destructor;
                    void *invariant;            // class invariant
                    ClassFlags flags;
                    void *deallocator;
                    OffsetTypeInfo[] offTi;
                    void *defaultConstructor;
                    //const(MemberInfo[]) function(string) xgetMembers;   // module getMembers() function
                    void *xgetRTInfo;
                    //TypeInfo typeinfo;
               }
             */
            dt_t *dt = NULL;
            unsigned offset = Target::classinfosize;    // must be ClassInfo.size
            if (Type::typeinfoclass)
            {
                if (Type::typeinfoclass->structsize != Target::classinfosize)
                {
        #ifdef DEBUG
                    printf("Target::classinfosize = x%x, Type::typeinfoclass->structsize = x%x\n", offset, Type::typeinfoclass->structsize);
        #endif
                    cd->error("mismatch between dmd and object.d or object.di found. Check installation and import paths with -v compiler switch.");
                    fatal();
                }
            }

            if (Type::typeinfoclass)
                dtxoff(&dt, toVtblSymbol(Type::typeinfoclass), 0, TYnptr); // vtbl for ClassInfo
            else
                dtsize_t(&dt, 0);                // BUG: should be an assert()
            dtsize_t(&dt, 0);                    // monitor

            // initializer[]
            assert(cd->structsize >= 8 || (cd->cpp && cd->structsize >= 4));
            dtsize_t(&dt, cd->structsize);           // size
            dtxoff(&dt, sinit, 0, TYnptr);      // initializer

            // name[]
            const char *name = cd->ident->toChars();
            size_t namelen = strlen(name);
            if (!(namelen > 9 && memcmp(name, "TypeInfo_", 9) == 0))
            {
                name = cd->toPrettyChars();
                namelen = strlen(name);
            }
            dtsize_t(&dt, namelen);
            dtabytes(&dt, TYnptr, 0, namelen + 1, name);

            // vtbl[]
            dtsize_t(&dt, cd->vtbl.dim);
            dtxoff(&dt, cd->vtblsym, 0, TYnptr);

            // interfaces[]
            dtsize_t(&dt, cd->vtblInterfaces->dim);
            if (cd->vtblInterfaces->dim)
                dtxoff(&dt, cd->csym, offset, TYnptr);      // (*)
            else
                dtsize_t(&dt, 0);

            // base
            if (cd->baseClass)
                dtxoff(&dt, toSymbol(cd->baseClass), 0, TYnptr);
            else
                dtsize_t(&dt, 0);

            // destructor
            if (cd->dtor)
                dtxoff(&dt, toSymbol(cd->dtor), 0, TYnptr);
            else
                dtsize_t(&dt, 0);

            // invariant
            if (cd->inv)
                dtxoff(&dt, toSymbol(cd->inv), 0, TYnptr);
            else
                dtsize_t(&dt, 0);

            // flags
            ClassFlags::Type flags = ClassFlags::hasOffTi;
            if (cd->isCOMclass()) flags |= ClassFlags::isCOMclass;
            if (cd->isCPPclass()) flags |= ClassFlags::isCPPclass;
            flags |= ClassFlags::hasGetMembers;
            flags |= ClassFlags::hasTypeInfo;
            if (cd->ctor)
                flags |= ClassFlags::hasCtor;
            for (ClassDeclaration *pc = cd; pc; pc = pc->baseClass)
            {
                if (pc->dtor)
                {
                    flags |= ClassFlags::hasDtor;
                    break;
                }
            }
            if (cd->isabstract)
                flags |= ClassFlags::isAbstract;
            for (ClassDeclaration *pc = cd; pc; pc = pc->baseClass)
            {
                if (pc->members)
                {
                    for (size_t i = 0; i < pc->members->dim; i++)
                    {
                        Dsymbol *sm = (*pc->members)[i];
                        //printf("sm = %s %s\n", sm->kind(), sm->toChars());
                        if (sm->hasPointers())
                            goto L2;
                    }
                }
            }
            flags |= ClassFlags::noPointers;
          L2:
            dtsize_t(&dt, flags);


            // deallocator
            if (cd->aggDelete)
                dtxoff(&dt, toSymbol(cd->aggDelete), 0, TYnptr);
            else
                dtsize_t(&dt, 0);

            // offTi[]
            dtsize_t(&dt, 0);
            dtsize_t(&dt, 0);            // null for now, fix later

            // defaultConstructor
            if (cd->defaultCtor && !(cd->defaultCtor->storage_class & STCdisable))
                dtxoff(&dt, toSymbol(cd->defaultCtor), 0, TYnptr);
            else
                dtsize_t(&dt, 0);

            // xgetRTInfo
            if (cd->getRTInfo)
                Expression_toDt(cd->getRTInfo, &dt);
            else if (flags & ClassFlags::noPointers)
                dtsize_t(&dt, 0);
            else
                dtsize_t(&dt, 1);

            //dtxoff(&dt, toSymbol(type->vtinfo), 0, TYnptr); // typeinfo

            //////////////////////////////////////////////

            // Put out (*vtblInterfaces)[]. Must immediately follow csym, because
            // of the fixup (*)

            offset += cd->vtblInterfaces->dim * (4 * Target::ptrsize);
            for (size_t i = 0; i < cd->vtblInterfaces->dim; i++)
            {
                BaseClass *b = (*cd->vtblInterfaces)[i];
                ClassDeclaration *id = b->sym;

                /* The layout is:
                 *  struct Interface
                 *  {
                 *      ClassInfo *interface;
                 *      void *[] vtbl;
                 *      size_t offset;
                 *  }
                 */

                // Fill in vtbl[]
                b->fillVtbl(cd, &b->vtbl, 1);

                dtxoff(&dt, toSymbol(id), 0, TYnptr);         // ClassInfo

                // vtbl[]
                dtsize_t(&dt, id->vtbl.dim);
                dtxoff(&dt, cd->csym, offset, TYnptr);

                dtsize_t(&dt, b->offset);                        // this offset

                offset += id->vtbl.dim * Target::ptrsize;
            }

            // Put out the (*vtblInterfaces)[].vtbl[]
            // This must be mirrored with ClassDeclaration::baseVtblOffset()
            //printf("putting out %d interface vtbl[]s for '%s'\n", vtblInterfaces->dim, toChars());
            for (size_t i = 0; i < cd->vtblInterfaces->dim; i++)
            {
                BaseClass *b = (*cd->vtblInterfaces)[i];
                ClassDeclaration *id = b->sym;

                //printf("    interface[%d] is '%s'\n", i, id->toChars());
                size_t j = 0;
                if (id->vtblOffset())
                {
                    // First entry is ClassInfo reference
                    //dtxoff(&dt, toSymbol(id), 0, TYnptr);

                    // First entry is struct Interface reference
                    dtxoff(&dt, cd->csym, Target::classinfosize + i * (4 * Target::ptrsize), TYnptr);
                    j = 1;
                }
                assert(id->vtbl.dim == b->vtbl.dim);
                for (; j < id->vtbl.dim; j++)
                {
                    assert(j < b->vtbl.dim);
        #if 0
                    RootObject *o = b->vtbl[j];
                    if (o)
                    {
                        printf("o = %p\n", o);
                        assert(o->dyncast() == DYNCAST_DSYMBOL);
                        Dsymbol *s = (Dsymbol *)o;
                        printf("s->kind() = '%s'\n", s->kind());
                    }
        #endif
                    FuncDeclaration *fd = b->vtbl[j];
                    if (fd)
                        dtxoff(&dt, toThunkSymbol(fd, b->offset), 0, TYnptr);
                    else
                        dtsize_t(&dt, 0);
                }
            }

            // Put out the overriding interface vtbl[]s.
            // This must be mirrored with ClassDeclaration::baseVtblOffset()
            //printf("putting out overriding interface vtbl[]s for '%s' at offset x%x\n", toChars(), offset);
            ClassDeclaration *pc;
            for (pc = cd->baseClass; pc; pc = pc->baseClass)
            {
                for (size_t k = 0; k < pc->vtblInterfaces->dim; k++)
                {
                    BaseClass *bs = (*pc->vtblInterfaces)[k];
                    FuncDeclarations bvtbl;
                    if (bs->fillVtbl(cd, &bvtbl, 0))
                    {
                        //printf("\toverriding vtbl[] for %s\n", bs->sym->toChars());
                        ClassDeclaration *id = bs->sym;

                        size_t j = 0;
                        if (id->vtblOffset())
                        {
                            // First entry is ClassInfo reference
                            //dtxoff(&dt, toSymbol(id), 0, TYnptr);

                            // First entry is struct Interface reference
                            dtxoff(&dt, toSymbol(pc), Target::classinfosize + k * (4 * Target::ptrsize), TYnptr);
                            j = 1;
                        }

                        for (; j < id->vtbl.dim; j++)
                        {
                            assert(j < bvtbl.dim);
                            FuncDeclaration *fd = bvtbl[j];
                            if (fd)
                                dtxoff(&dt, toThunkSymbol(fd, bs->offset), 0, TYnptr);
                            else
                                dtsize_t(&dt, 0);
                        }
                    }
                }
            }

            cd->csym->Sdt = dt;
            // ClassInfo cannot be const data, because we use the monitor on it
            outdata(cd->csym);
            if (cd->isExport())
                objmod->export_symbol(cd->csym, 0);

            //////////////////////////////////////////////

            // Put out the vtbl[]
            //printf("putting out %s.vtbl[]\n", toChars());
            dt = NULL;
            if (cd->vtblOffset())
                dtxoff(&dt, cd->csym, 0, TYnptr);           // first entry is ClassInfo reference
            for (size_t i = cd->vtblOffset(); i < cd->vtbl.dim; i++)
            {
                FuncDeclaration *fd = cd->vtbl[i]->isFuncDeclaration();

                //printf("\tvtbl[%d] = %p\n", i, fd);
                if (fd && (fd->fbody || !cd->isAbstract()))
                {
                    // Ensure function has a return value (Bugzilla 4869)
                    fd->functionSemantic();

                    Symbol *s = toSymbol(fd);

                    if (cd->isFuncHidden(fd))
                    {
                        /* fd is hidden from the view of this class.
                         * If fd overlaps with any function in the vtbl[], then
                         * issue 'hidden' error.
                         */
                        for (size_t j = 1; j < cd->vtbl.dim; j++)
                        {
                            if (j == i)
                                continue;
                            FuncDeclaration *fd2 = cd->vtbl[j]->isFuncDeclaration();
                            if (!fd2->ident->equals(fd->ident))
                                continue;
                            if (fd->leastAsSpecialized(fd2) || fd2->leastAsSpecialized(fd))
                            {
                                TypeFunction *tf = (TypeFunction *)fd->type;
                                if (tf->ty == Tfunction)
                                    cd->error("use of %s%s is hidden by %s; use 'alias %s = %s.%s;' to introduce base class overload set",
                                        fd->toPrettyChars(),
                                        parametersTypeToChars(tf->parameters, tf->varargs),
                                        cd->toChars(),

                                        fd->toChars(),
                                        fd->parent->toChars(),
                                        fd->toChars());
                                else
                                    cd->error("use of %s is hidden by %s", fd->toPrettyChars(), cd->toChars());
                                break;
                            }
                        }
                    }

                    dtxoff(&dt, s, 0, TYnptr);
                }
                else
                    dtsize_t(&dt, 0);
            }
            cd->vtblsym->Sdt = dt;
            cd->vtblsym->Sclass = scclass;
            cd->vtblsym->Sfl = FLdata;
            out_readonly(cd->vtblsym);
            outdata(cd->vtblsym);
            if (cd->isExport())
                objmod->export_symbol(cd->vtblsym,0);
        }