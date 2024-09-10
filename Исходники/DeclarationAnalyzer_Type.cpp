TypePtr DeclarationAnalyzer::defineType(const std::shared_ptr<TypeDeclaration>& node)
{
    TypeIdentifierPtr id = node->getIdentifier();
    SymbolScope* scope = NULL;
    TypePtr type;

    //Analyze the type's category
    Type::Category category;
    switch(node->getNodeType())
    {
        case NodeType::Enum:
            category = Type::Enum;
            break;
        case NodeType::Class:
            category = Type::Class;
            break;
        case NodeType::Struct:
            category = Type::Struct;
            break;
        case NodeType::Protocol:
            category = Type::Protocol;
            break;
        default:
            assert(0 && "Impossible to execute here.");
    }

    //it's inside the type's scope, so need to access parent scope;
    SymbolScope* typeScope = symbolRegistry->getCurrentScope();
    SymbolScope* currentScope = typeScope->getParentScope();

    //check if this type is already defined
    symbolRegistry->lookupType(id->getName(), &scope, &type);
    if(type && scope == currentScope)
    {
        //invalid redeclaration of type T
        error(node, Errors::E_INVALID_REDECLARATION_1, id->getName());
        return nullptr;
    }
    //prepare for generic types
    GenericDefinitionPtr generic;
    GenericParametersDefPtr genericParams = node->getGenericParametersDef();

    //check if it's defined as a nested type
    if(ctx->currentType)
    {
        if(genericParams)
        {
            error(node, Errors::E_GENERIC_TYPE_A_NESTED_IN_TYPE_B_IS_NOT_ALLOWED_2, id->getName(), ctx->currentType->getName());
            return nullptr;
        }
        if(ctx->currentType->isGenericType())
        {
            error(node, Errors::E_TYPE_A_NESTED_IN_GENERIC_TYPE_B_IS_NOT_ALLOWED_2, id->getName(), ctx->currentType->getName());
            return nullptr;
        }
    }

    if(genericParams)
    {
        generic = prepareGenericTypes(genericParams);
        generic->registerTo(typeScope);
    }

    //check inheritance clause
    TypePtr parent = nullptr;
    std::vector<TypePtr> protocols;
    bool first = true;

    for(const TypeIdentifierPtr& parentType : node->getParents())
    {
        parentType->accept(semanticAnalyzer);
        TypePtr ptr = this->lookupType(parentType);
        if(ptr->getCategory() == Type::Class && category == Type::Class)
        {
            if(!first)
            {
                //only the first type can be class type
                error(parentType, Errors::E_SUPERCLASS_MUST_APPEAR_FIRST_IN_INHERITANCE_CLAUSE_1, toString(parentType));
                return nullptr;
            }
            parent = ptr;
            if(parent->hasFlags(SymbolFlagFinal))
            {
                error(parentType, Errors::E_INHERITANCE_FROM_A_FINAL_CLASS_A_1, parentType->getName());
                return nullptr;
            }
        }
        else if(category == Type::Enum && ptr->getCategory() != Type::Protocol)
        {

            if(parent)//already has a raw type
            {
                error(parentType, Errors::E_MULTIPLE_ENUM_RAW_TYPES_A_AND_B_2, parent->toString(), ptr->toString());
                return nullptr;
            }
            if(!first)
            {
                error(parentType, Errors::E_RAW_TYPE_A_MUST_APPEAR_FIRST_IN_THE_ENUM_INHERITANCE_CLAUSE_1, ptr->toString());
                return nullptr;
            }
            //check if the raw type is literal convertible
            if(!isLiteralTypeForEnum(symbolRegistry->getGlobalScope(), ptr))
            {
                error(parentType, Errors::E_RAW_TYPE_A_IS_NOT_CONVERTIBLE_FROM_ANY_LITERAL_1, ptr->toString());
                return nullptr;
            }
            if(!ptr->canAssignTo(symbolRegistry->getGlobalScope()->Equatable()))
            {
                error(parentType, Errors::E_RAWREPRESENTABLE_INIT_CANNOT_BE_SYNTHESIZED_BECAUSE_RAW_TYPE_A_IS_NOT_EQUATABLE_1, ptr->toString());
                return nullptr;
            }
            parent = ptr;
        }
        else if(ptr->getCategory() == Type::Protocol)
        {
            protocols.push_back(ptr);
        }
        else
        {
            if(category == Type::Class)
                error(parentType, Errors::E_INHERITANCE_FROM_NONE_PROTOCOL_NON_CLASS_TYPE_1, toString(parentType));
            else
                error(parentType, Errors::E_INHERITANCE_FROM_NONE_PROTOCOL_TYPE_1, toString(parentType));
            return nullptr;
        }
        first = false;
    }

    //register this type
    type = Type::newType(node->getIdentifier()->getName(), category, node, parent, protocols, generic);
    node->setType(type);
    if(parent && parent->getAccessLevel() == AccessLevelPublic && (node->getModifiers() & DeclarationModifiers::AccessModifiers) == 0)
        type->setAccessLevel(AccessLevelPublic);//when access level is undefined, try to inherit base's access level
    else
        type->setAccessLevel(parseAccessLevel(node->getModifiers()));
    currentScope->addSymbol(type);
    if(node->hasModifier(DeclarationModifiers::Final))
        type->setFlags(SymbolFlagFinal, true);

    declarationFinished(type->getName(), type, node);
    return type;
}