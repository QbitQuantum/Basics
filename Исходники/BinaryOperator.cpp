void BinaryOperator::ResolveTypes()
{
    Operator* fst = mySubOps[0];
    fst->ResolveTypes();

    Operator* snd = mySubOps[1];
    snd->ResolveTypes();

    if( fst->GetType() == snd->GetType() )
        myType = fst->GetType();
    else
        myType = new ErrorType(
            reinterpret_cast<GlobalContext*>( myContext->GetGlobalContext() ),
            "Types mismatch" );
}