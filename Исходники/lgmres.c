hypre_LGMRESFunctions *
hypre_LGMRESFunctionsCreate(
   char *       (*CAlloc)        ( size_t count, size_t elt_size ),
   HYPRE_Int    (*Free)          ( char *ptr ),
   HYPRE_Int    (*CommInfo)      ( void  *A, HYPRE_Int   *my_id,
                                   HYPRE_Int   *num_procs ),
   void *       (*CreateVector)  ( void *vector ),
   void *       (*CreateVectorArray)  ( HYPRE_Int size, void *vectors ),
   HYPRE_Int    (*DestroyVector) ( void *vector ),
   void *       (*MatvecCreate)  ( void *A, void *x ),
   HYPRE_Int    (*Matvec)        ( void *matvec_data, HYPRE_Complex alpha, void *A,
                                   void *x, HYPRE_Complex beta, void *y ),
   HYPRE_Int    (*MatvecDestroy) ( void *matvec_data ),
   HYPRE_Real   (*InnerProd)     ( void *x, void *y ),
   HYPRE_Int    (*CopyVector)    ( void *x, void *y ),
   HYPRE_Int    (*ClearVector)   ( void *x ),
   HYPRE_Int    (*ScaleVector)   ( HYPRE_Complex alpha, void *x ),
   HYPRE_Int    (*Axpy)          ( HYPRE_Complex alpha, void *x, void *y ),
   HYPRE_Int    (*PrecondSetup)  ( void *vdata, void *A, void *b, void *x ),
   HYPRE_Int    (*Precond)       ( void *vdata, void *A, void *b, void *x )
   )
{
   hypre_LGMRESFunctions * lgmres_functions;
   lgmres_functions = (hypre_LGMRESFunctions *)
      CAlloc( 1, sizeof(hypre_LGMRESFunctions) );

   lgmres_functions->CAlloc = CAlloc;
   lgmres_functions->Free = Free;
   lgmres_functions->CommInfo = CommInfo; /* not in PCGFunctionsCreate */
   lgmres_functions->CreateVector = CreateVector;
   lgmres_functions->CreateVectorArray = CreateVectorArray; /* not in PCGFunctionsCreate */
   lgmres_functions->DestroyVector = DestroyVector;
   lgmres_functions->MatvecCreate = MatvecCreate;
   lgmres_functions->Matvec = Matvec;
   lgmres_functions->MatvecDestroy = MatvecDestroy;
   lgmres_functions->InnerProd = InnerProd;
   lgmres_functions->CopyVector = CopyVector;
   lgmres_functions->ClearVector = ClearVector;
   lgmres_functions->ScaleVector = ScaleVector;
   lgmres_functions->Axpy = Axpy;
/* default preconditioner must be set here but can be changed later... */
   lgmres_functions->precond_setup = PrecondSetup;
   lgmres_functions->precond       = Precond;

   return lgmres_functions;
}