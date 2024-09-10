static Object *
apply_primitive( Primitive *p, Array *spine, unsigned int nargs, Manager *m )
{
    unsigned int i;
    Object *ap, *arg;
    void *args[PRIM__MAX_PARAMS];
    void *result;
    Type *t;

    if ( DEBUG__SAFE && ( !p || !spine || !m || p->arity > PRIM__MAX_PARAMS ) )
        abort();

    if ( PRIM__ALLOW_NULLARY )
    {
        /* Not supported. */
    }

    else
        /* Make the compiler happy. */
        ap = 0;

    /* Apply the primitive, provided that there are enough arguments, and that
       they reduce to objects of the expected types. */
    if ( nargs >= p->arity )
    {
        /* For each argument... */
        for ( i = 0; i < p->arity; i++ )
        {
            ap = array__pop( spine );
            arg = reduce__graph_lazy( OPERAND( ap ), spine, m );

            /* Argument reduced to a non-null object. */
            if ( arg )
            {
                t = p->parameters[i].type;

                /* Check for type agreement. */
                if ( PRIM__CHECKS__PARAM_TYPE )
                {
                    if ( t != arg->type
                    && ( !PRIM__ALLOW_GENERIC_PARAMS || t != BOXED_TYPE ) )
                    {
                        ERROR( "prim_reduce: argument type mismatch" );

                        goto bad_arg;
                    }
                }

                /* Argument type is boxed. */
                if ( PRIM__ALLOW_GENERIC_PARAMS && t == BOXED_TYPE )
                    args[i] = arg;

                /* Argument type is unboxed. */
                else
                    args[i] = arg->value;
            }

            /* Argument reduced to null. */
            else
                goto bad_arg;
        }

        /* Caution: there is no exception handling at this level. */
        result = p->cstub( args );

        /* Return value is an existing typed object. */
        if ( PRIM__ALLOW_GENERIC_RESULTS && p->return_type == BOXED_TYPE )
            substitute_boxed( ap, result );

        /* Return type is a raw data reference which needs to be bound to a type ("boxed"). */
        else
        {
            if ( result )
                substitute_unboxed( ap, p->return_type, result );

            else if ( FIRST_CLASS_NULL )
                substitute_boxed( ap, 0 );

            else
                abort();
        }

        return ap;
    }

    else
        return 0;

bad_arg:

/* FIXME: OBJECT__IRREDUCIBLE property is not used */
    if ( COMPILER__ALLOW_NONREDUX )
        ap->flags |= OBJECT__IRREDUCIBLE;

    /* f 0 --> 0 */
    substitute_boxed( ap, 0 );

    return ap;
}