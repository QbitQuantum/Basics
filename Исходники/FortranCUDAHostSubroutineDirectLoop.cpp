void
FortranCUDAHostSubroutineDirectLoop::createCUDAKernelInitialisationStatements ()
{
  using namespace SageBuilder;
  using namespace SageInterface;
  using namespace OP2VariableNames;
  using namespace OP2::Macros;
  using boost::lexical_cast;
  using std::string;
  using std::max;

  Debug::getInstance ()->debugMessage (
      "Creating CUDA kernel initialisation statements", Debug::FUNCTION_LEVEL,
      __FILE__, __LINE__);

  /*
   * ======================================================
   * The following values are copied from Mike Giles'
   * implementation and may be subject to future changes
   * ======================================================
   */
  int const nblocks = 200;
  int const nthreads = 128;

  SgExprStatement * assignmentStatement1 = buildAssignStatement (
      variableDeclarations->getReference (CUDA::blocksPerGrid), buildIntVal (
          nblocks));

  appendStatement (assignmentStatement1, subroutineScope);

  SgExprStatement * assignmentStatement2 = buildAssignStatement (
      variableDeclarations->getReference (CUDA::threadsPerBlock), buildIntVal (
          nthreads));

  appendStatement (assignmentStatement2, subroutineScope);

  SgExprStatement * assignmentStatement3 = buildAssignStatement (
      variableDeclarations->getReference (warpSize), buildOpaqueVarRefExp (
          warpSizeMacro, subroutineScope));

  appendStatement (assignmentStatement3, subroutineScope);

  /*
   * ======================================================
   * Compute the value of shared memory passed at CUDA kernel
   * launch.
   *
   * An OP_DAT is only copied into shared memory if its
   * dimension exceeds 1 and it is not an OP_GBL. To
   * compute the value, therefore, we need to get the maximum
   * of (dimension * size of primitive type) across all
   * OP_DATs
   * ======================================================
   */

  unsigned int sharedOpDatMemorySize = 0;
  unsigned int sharedReductionMemorySize = 0;

  for (unsigned int i = 1; i <= parallelLoop->getNumberOfOpDatArgumentGroups (); ++i)
  {
    if (parallelLoop->isDuplicateOpDat (i) == false)
    {
      if (parallelLoop->isGlobal (i) == false)
      {
        unsigned int opDatMemoryRequirements = parallelLoop->getOpDatDimension (
            i) * parallelLoop->getSizeOfOpDat (i);

        if (opDatMemoryRequirements > sharedOpDatMemorySize)
        {
          sharedOpDatMemorySize = opDatMemoryRequirements;
        }
      }
      else if (parallelLoop->isReductionRequired (i))
      {
        unsigned int reductionMemoryRequirements =
            parallelLoop->getOpDatDimension (i) * parallelLoop->getSizeOfOpDat (
                i);

        if (reductionMemoryRequirements > sharedReductionMemorySize)
        {
          sharedReductionMemorySize = reductionMemoryRequirements;
        }
      }
    }
  }

  if (sharedOpDatMemorySize == 0 && sharedReductionMemorySize == 0)
  {
    throw Exceptions::CUDA::SharedMemorySizeException (
        "The shared memory size will be set to zero during kernel launch");
  }
  else
  {
    Debug::getInstance ()->debugMessage (
        "The shared memory size will be set to " + lexical_cast <string> (max (
            sharedOpDatMemorySize, sharedReductionMemorySize))
            + " during kernel launch", Debug::OUTER_LOOP_LEVEL, __FILE__,
        __LINE__);
  }

  SgExprStatement * assignmentStatement4 = buildAssignStatement (
      variableDeclarations->getReference (CUDA::sharedMemorySize), buildIntVal (
          max (sharedOpDatMemorySize, sharedReductionMemorySize)));

  appendStatement (assignmentStatement4, subroutineScope);

  /*
   * ======================================================
   * Initialise the offset into shared memory to <shared
   * memory size> * <warp size>
   * ======================================================
   */

  SgMultiplyOp * multiplyExpression5 = buildMultiplyOp (
      variableDeclarations->getReference (CUDA::sharedMemorySize),
      buildOpaqueVarRefExp (warpSizeMacro, subroutineScope));

  SgExprStatement * assignmentStatement5 = buildAssignStatement (
      variableDeclarations->getReference (sharedMemoryOffset),
      multiplyExpression5);

  appendStatement (assignmentStatement5, subroutineScope);

  SgMultiplyOp * multiplyExpression6 = buildMultiplyOp (
      variableDeclarations->getReference (CUDA::sharedMemorySize),
      variableDeclarations->getReference (CUDA::threadsPerBlock));

  SgExprStatement * assignmentStatement6 = buildAssignStatement (
      variableDeclarations->getReference (CUDA::sharedMemorySize),
      multiplyExpression6);

  appendStatement (assignmentStatement6, subroutineScope);
}