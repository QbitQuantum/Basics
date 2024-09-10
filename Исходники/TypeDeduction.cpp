void TypeDeduction::Visit(CallExpression* node)
{
    node->GetTarget()->Accept(this);
    std::vector<Expression *> *arguments = node->GetArgumentList();
    for (std::vector<Expression *>::iterator it = arguments->begin(); it != arguments->end(); ++it)
    {
        Expression *arg = *it;
        arg->Accept(this);
        //TODO: Check the parameter types, and do implicit conversion if needed
    }

    FunctionType *funcType = dynamic_cast<FunctionType *>(node->GetTarget()->GetTag<Type>("Type"));
    if (funcType == NULL)
    {
        
        CompilationContext::GetInstance()->ReportError(node->SourceLocation, false, "Requires a function type.");
    }

    node->SetTag<Type>("Type", funcType->GetReturnType());
}