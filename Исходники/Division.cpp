Operator* Division::Simplified(
    Context* nctx,
    TypeCorrespondanceTable& table )
{
    Operator* fp = mySubOps[0]->Simplified(nctx, table);
    Operator* fs = mySubOps[1]->Simplified(nctx, table);
    
    if( fp->IsNull() )
        return new Constant( nctx, 0.0, table[GetType()] );
    else if( fp->IsOne() )
        return new Inverse( nctx, fs );
    else if( fp->IsConstant() && fs->IsConstant() )
    {
        Constant* cfp = reinterpret_cast<Constant*>(fp);
        Constant* cfs = reinterpret_cast<Constant*>(fs);
        
        return new Constant( nctx, cfp->GetValue() / cfs->GetValue(), table[GetType()] );
    }
    else
        return new Division( nctx, fp, fs );
}