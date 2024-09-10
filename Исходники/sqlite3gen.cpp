static void generateSqlite3ForMember(sqlite3*db,MemberDef *md,Definition *def)
{
  // + declaration/definition arg lists
  // + reimplements
  // + reimplementedBy
  // + exceptions
  // + const/volatile specifiers
  // - examples
  // + source definition
  // + source references
  // + source referenced by
  // - body code
  // + template arguments
  //     (templateArguments(), definitionTemplateParameterLists())
  // - call graph

  // enum values are written as part of the enum
  if (md->memberType()==MemberType_EnumValue) return;
  if (md->isHidden()) return;
  //if (md->name().at(0)=='@') return; // anonymous member

  // group members are only visible in their group
  //if (def->definitionType()!=Definition::TypeGroup && md->getGroupDef()) return;
  QCString memType;
  // memberdef
  bindTextParameter(i_s_memberdef,":refid",md->anchor().data(),FALSE);
  bindIntParameter(i_s_memberdef,":kind",md->memberType());
  bindIntParameter(i_s_memberdef,":prot",md->protection());
  bindIntParameter(i_s_memberdef,":static",md->isStatic());

  bool isFunc=FALSE;
  switch (md->memberType())
  {
    case MemberType_Function: // fall through
    case MemberType_Signal:   // fall through
    case MemberType_Friend:   // fall through
    case MemberType_DCOP:     // fall through
    case MemberType_Slot:
      isFunc=TRUE;
      break;
    default:
      break;
  }
  if (isFunc)
  {
    ArgumentList *al = md->argumentList();
    if (al!=0 && al->constSpecifier)
    {
      bindIntParameter(i_s_memberdef,":const",al->constSpecifier);
    }

    bindIntParameter(i_s_memberdef,":explicit",md->isExplicit());
    bindIntParameter(i_s_memberdef,":inline",md->isInline());
    bindIntParameter(i_s_memberdef,":final",md->isFinal());
    bindIntParameter(i_s_memberdef,":sealed",md->isSealed());
    bindIntParameter(i_s_memberdef,":new",md->isNew());
    bindIntParameter(i_s_memberdef,":optional",md->isOptional());
    bindIntParameter(i_s_memberdef,":required",md->isRequired());
    bindIntParameter(i_s_memberdef,":virt",md->virtualness());
  }
  // place in the arguments and linkify the arguments

  if (md->memberType() == MemberType_Variable)
  {
    bindIntParameter(i_s_memberdef,":mutable",md->isMutable());
    bindIntParameter(i_s_memberdef,":initonly",md->isInitonly());
  }
  else if (md->memberType() == MemberType_Property)
  {
    bindIntParameter(i_s_memberdef,":readable",md->isReadable());
    bindIntParameter(i_s_memberdef,":writable",md->isWritable());
    bindIntParameter(i_s_memberdef,":gettable",md->isGettable());
    bindIntParameter(i_s_memberdef,":settable",md->isSettable());

    if (md->isAssign() || md->isCopy() || md->isRetain())
    {
      int accessor = md->isAssign() ? md->isAssign() :
          (md->isCopy() ? md->isCopy() : md->isRetain()) ;

      bindIntParameter(i_s_memberdef,":accessor",accessor);
    }
  }
  else if (md->memberType() == MemberType_Event)
  {
    bindIntParameter(i_s_memberdef,":addable",md->isAddable());
    bindIntParameter(i_s_memberdef,":removable",md->isRemovable());
    bindIntParameter(i_s_memberdef,":raisable",md->isRaisable());
  }

  // + declaration/definition arg lists
  if (md->memberType()!=MemberType_Define &&
      md->memberType()!=MemberType_Enumeration
     )
  {
    QCString typeStr = md->typeString();
    stripQualifiers(typeStr);
    StringList l;
    linkifyText(TextGeneratorSqlite3Impl(l),def,md->getBodyDef(),md,typeStr);
    if (typeStr.data())
    {
      bindTextParameter(i_s_memberdef,":type",typeStr.data(),FALSE);
    }

    if (md->definition())
    {
      bindTextParameter(i_s_memberdef,":definition",md->definition());
    }

    if (md->argsString())
    {
      bindTextParameter(i_s_memberdef,":argsstring",md->argsString());
    }
  }

  bindTextParameter(i_s_memberdef,":name",md->name());

  if (md->memberType() == MemberType_Property)
  {
    if (md->isReadable())
    {
      DBG_CTX(("<read>\n"));
    }
    if (md->isWritable())
    {
      DBG_CTX(("<write>\n"));
    }
  }
  if (isFunc) //function
  {
    ArgumentList *declAl = md->declArgumentList();
    ArgumentList *defAl = md->argumentList();
    if (declAl!=0 && declAl->count()>0)
    {
      ArgumentListIterator declAli(*declAl);
      ArgumentListIterator defAli(*defAl);
      Argument *a;
      for (declAli.toFirst();(a=declAli.current());++declAli)
      {
        Argument *defArg = defAli.current();
        DBG_CTX(("<param>\n"));
        if (!a->attrib.isEmpty())
        {
          DBG_CTX(("<attributes>:%s\n",a->attrib.data()));
        }
        if (!a->type.isEmpty())
        {
          StringList l;
          linkifyText(TextGeneratorSqlite3Impl(l),def,md->getBodyDef(),md,a->type);

          StringListIterator li(l);
          QCString *s;
          while ((s=li.current()))
          {
            insertMemberReference(db,md->anchor().data(),s->data(),def->getDefFileName().data(),md->getDefLine(),1);
            ++li;
          }
        }
        if (!a->name.isEmpty())
        {
          DBG_CTX(("<declname>%s\n",a->name.data()));
        }
        if (defArg && !defArg->name.isEmpty() && defArg->name!=a->name)
        {
          DBG_CTX(("<defname>%s\n",defArg->name.data()));
        }
        if (!a->array.isEmpty())
        {
          DBG_CTX(("<array>%s",a->array.data()));
        }
        if (!a->defval.isEmpty())
        {
          StringList l;
          linkifyText(TextGeneratorSqlite3Impl(l),def,md->getBodyDef(),md,a->defval);
        }
        if (defArg) ++defAli;
      }
    }
  }
  else if (md->memberType()==MemberType_Define &&
          md->argsString()) // define
  {
    if (md->argumentList()->count()==0) // special case for "foo()" to
                                        // disguish it from "foo".
    {
      DBG_CTX(("no params\n"));
    }
    else
    {
      ArgumentListIterator ali(*md->argumentList());
      Argument *a;
      for (ali.toFirst();(a=ali.current());++ali)
      {
        DBG_CTX(("<param><defname>%s\n",a->type.data()));
      }
    }
  }


  // Extract references from initializer
  // avoid that extremely large tables are written to the output.
  // todo: it's better to adhere to MAX_INITIALIZER_LINES.
  // drm_mod_register_buffer,
  if (!md->initializer().isEmpty() && md->initializer().length()<2000)
  {
    bindTextParameter(i_s_memberdef,":initializer",md->initializer().data());

    StringList l;
    linkifyText(TextGeneratorSqlite3Impl(l),def,md->getBodyDef(),md,md->initializer());
    StringListIterator li(l);
    QCString *s;
    while ((s=li.current()))
    {
      if (md->getBodyDef())
      {
        DBG_CTX(("initializer:%s %s %s %d\n",
              md->anchor().data(),
              s->data(),
              md->getBodyDef()->getDefFileName().data(),
              md->getStartBodyLine()));
        insertMemberReference(db,md->anchor().data(),s->data(),md->getBodyDef()->getDefFileName().data(),md->getStartBodyLine(),1);
      }
      ++li;
    }
  }

  if ( md->getScopeString() )
  {
    bindTextParameter(i_s_memberdef,":scope",md->getScopeString().data(),FALSE);
  }

  // Brief and detail description

  bindTextParameter(i_s_memberdef,":briefdescription",md->briefDescription(),FALSE);
  bindTextParameter(i_s_memberdef,":detaileddescription",md->documentation(),FALSE);
  bindTextParameter(i_s_memberdef,":inbodydescription",md->inbodyDocumentation(),FALSE);

  // File location
  if (md->getDefLine() != -1)
  {
    int id_file = insertFile(db,md->getDefFileName());
    if (id_file!=-1)
    {
      bindIntParameter(i_s_memberdef,":id_file",id_file);
      bindIntParameter(i_s_memberdef,":line",md->getDefLine());
      bindIntParameter(i_s_memberdef,":column",md->getDefColumn());

      if (md->getStartBodyLine()!=-1)
      {
        int id_bodyfile = insertFile(db,md->getBodyDef()->absFilePath());
        if (id_bodyfile == -1)
        {
            sqlite3_clear_bindings(i_s_memberdef);
        }
        else
        {
            bindIntParameter(i_s_memberdef,":id_bodyfile",id_bodyfile);
            bindIntParameter(i_s_memberdef,":bodystart",md->getStartBodyLine());
            bindIntParameter(i_s_memberdef,":bodyend",md->getEndBodyLine());
        }
      }
    }
  }

  if (-1==step(db,i_s_memberdef))
  {
      sqlite3_clear_bindings(i_s_memberdef);
  }
  sqlite3_last_insert_rowid(db);

  // + source references
  // The cross-references in initializers only work when both the src and dst
  // are defined.
  MemberSDict *mdict = md->getReferencesMembers();
  if (mdict!=0)
  {
    MemberSDict::IteratorDict mdi(*mdict);
    MemberDef *rmd;
    for (mdi.toFirst();(rmd=mdi.current());++mdi)
    {
      insertMemberReference(db,md,rmd,mdi.currentKey());
    }
  }

  // + source referenced by
  mdict = md->getReferencedByMembers();
  if (mdict!=0)
  {
    MemberSDict::IteratorDict mdi(*mdict);
    MemberDef *rmd;
    for (mdi.toFirst();(rmd=mdi.current());++mdi)
    {
      insertMemberReference(db,rmd,md,mdi.currentKey());
    }
  }
}