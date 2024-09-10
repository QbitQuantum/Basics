/**
 * The function evalAST(ASTNode_t) evaluates the formula of an
 * Abstract Syntax Tree by simple recursion and returns the result
 * as a double value.
 *
 * If variables (ASTNodeType_t AST_NAME) occur in the formula the user is
 * asked to provide a numerical value.  When evaluating ASTs within an SBML
 * document or simulating an SBML model this node type includes parameters
 * and variables of the model.  Parameters should be retrieved from the
 * SBML file, time and variables from current values of the simulation.
 *
 * Not implemented:
 *
 *  - PIECEWISE, LAMBDA, and the SBML model specific functions DELAY and
 *    TIME and user-defined functions.
 *
 *  - Complex numbers and/or checking for domains of trigonometric and root
 *    functions.
 *
 *  - Checking for precision and rounding errors.
 *
 * The Nodetypes AST_TIME, AST_DELAY and AST_PIECEWISE default to 0.  The
 * SBML DELAY function and unknown functions (SBML user-defined functions)
 * use the value of the left child (first argument to function) or 0 if the
 * node has no children.
 */
double
evalAST(ASTNode_t *n)
{
  int    i;
  double result;
  
  int       childnum = ASTNode_getNumChildren(n);
  ASTNode_t  **child = (ASTNode_t **) malloc(childnum * sizeof(ASTNode_t*));


  for (i = 0; i < childnum; i++)
  {
    child[i] = ASTNode_getChild(n, i);
  }

  switch (ASTNode_getType(n))
  {
  case AST_INTEGER:
    result = (double) ASTNode_getInteger(n);
    break;

  case AST_REAL:
    result = ASTNode_getReal(n);
    break;

  case AST_REAL_E:
    result = ASTNode_getReal(n);
    break;

  case AST_RATIONAL:
    result = ASTNode_getReal(n);
    break;
  
  case AST_NAME:
    {
      char *l;
      double var;
      printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
      printf("Please enter a number for the variable!\n");
      printf("If you do not enter a valid number (empty or characters), the \n");
      printf("evaluation will proceed with a current internal value and the \n");
      printf("result will make no sense.\n");
      printf("%s=",ASTNode_getName(n));
      l = get_line(stdin);
      sscanf(l, "%lf", &var);
      free(l);
      printf("%s = %f\n", ASTNode_getName(n), var);
      printf("-----------------------END MESSAGE--------------------------\n\n");
      result = var;
    }
    break;

  case AST_FUNCTION_DELAY:
    printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
    printf("Delays can only be evaluated during a time series simulation.\n");
    printf("The value of the first child (ie. the first argument to the function)\n");
    printf("is used for this evaluation. If the function node has no children the\n");
    printf("value defaults to 0.\n");
    printf("-----------------------END MESSAGE--------------------------\n\n");
    if(i>0)
      result = evalAST(child[0]);
    else
      result = 0.0;
    break;

  case AST_NAME_TIME:
    printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
    printf("The time can only be evaluated during a time series simulation.\n");
    printf("The value of defaults to 0\n");
    printf("-----------------------END MESSAGE--------------------------\n\n");
    result = 0.0;
    break;

  case AST_CONSTANT_E:
    /* exp(1) is used to adjust exponentiale to machine precision */
    result = exp(1);
    break;

  case AST_CONSTANT_FALSE:
    result = 0.0;
    break;

  case AST_CONSTANT_PI:
    /* pi = 4 * atan 1  is used to adjust Pi to machine precision */
    result = 4.*atan(1.);
    break;

  case AST_CONSTANT_TRUE:
    result = 1.0;
    break;

  case AST_PLUS:
    result = evalAST(child[0]) + evalAST(child[1]);
    break;

  case AST_MINUS:
    if(childnum==1)
      result = - (evalAST(child[0]));
    else
      result = evalAST(child[0]) - evalAST(child[1]);
    break;

  case AST_TIMES:
    result = evalAST(child[0]) * evalAST(child[1]) ;
    break;

  case AST_DIVIDE:
    result = evalAST(child[0]) / evalAST(child[1]);
    break;

  case AST_POWER:
    result = pow(evalAST(child[0]),evalAST(child[1]));
    break;

  case AST_LAMBDA:
    printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
    printf("This function is not implemented yet.\n");
    printf("The value defaults to 0.\n");
    printf("-----------------------END MESSAGE--------------------------\n\n");
    result = 0.0;
    break;

  case AST_FUNCTION:
    printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
    printf("This function is not known.\n");
    printf("Within an SBML document new functions can be defined by the user or \n");
    printf("application. The value of the first child (ie. the first argument to \n");
    printf("the function) is used for this evaluation. If the function node has\n");
    printf("no children the value defaults to 0.\n");
    printf("-----------------------END MESSAGE--------------------------\n\n");
    if(childnum>0)
      result = evalAST(child[0]);
    else
      result = 0.0;
    break;

  case AST_FUNCTION_ABS:
    result = (double) fabs(evalAST(child[0]));
    break;

  case AST_FUNCTION_ARCCOS:
    result = acos(evalAST(child[0])) ;
    break;

  case AST_FUNCTION_ARCCOSH:
#ifndef WIN32
    result = acosh(evalAST(child[0]));
#else
	result = log(evalAST(child[0]) + SQR(evalAST(child[0]) * evalAST(child[0]) - 1.));
#endif
    break;
  case AST_FUNCTION_ARCCOT:
    /* arccot x =  arctan (1 / x) */
    result = atan(1./ evalAST(child[0]));
    break;

  case AST_FUNCTION_ARCCOTH:
    /* arccoth x = 1/2 * ln((x+1)/(x-1)) */
    result = ((1./2.)*log((evalAST(child[0])+1.)/(evalAST(child[0])-1.)) );
    break;

  case AST_FUNCTION_ARCCSC:
    /* arccsc(x) = Arctan(1 / sqrt((x - 1)(x + 1))) */
    result = atan( 1. / SQRT( (evalAST(child[0])-1.)*(evalAST(child[0])+1.) ) );
    break;

  case AST_FUNCTION_ARCCSCH:
    /* arccsch(x) = ln((1 + sqrt(1 + x^2)) / x) */
    result = log((1.+SQRT((1+SQR(evalAST(child[0]))))) /evalAST(child[0]));
    break;

  case AST_FUNCTION_ARCSEC:
    /* arcsec(x) = arctan(sqrt((x - 1)(x + 1))) */
    result = atan( SQRT( (evalAST(child[0])-1.)*(evalAST(child[0])+1.) ) );
    break;

  case AST_FUNCTION_ARCSECH:
    /* arcsech(x) = ln((1 + sqrt(1 - x^2)) / x) */
    result = log((1.+pow((1-SQR(evalAST(child[0]))),0.5))/evalAST(child[0]));
    break;

  case AST_FUNCTION_ARCSIN:
    result = asin(evalAST(child[0]));
    break;
  case AST_FUNCTION_ARCSINH:
#ifndef WIN32
    result = asinh(evalAST(child[0]));
#else
	result = log(evalAST(child[0]) + SQR(evalAST(child[0]) * evalAST(child[0]) + 1.));
#endif
    break;

  case AST_FUNCTION_ARCTAN:
    result = atan(evalAST(child[0]));
    break;
  case AST_FUNCTION_ARCTANH:
#ifndef WIN32
    result = atanh(evalAST(child[0]));
#else
	result = log((1. / evalAST(child[0]) + 1.) / (1. / evalAST(child[0]) - 1.)) / 2.;
#endif
    break;

  case AST_FUNCTION_CEILING:
    result = ceil(evalAST(child[0]));
    break;

  case AST_FUNCTION_COS:
    result = cos(evalAST(child[0]));
    break;
  case AST_FUNCTION_COSH:
    result = cosh(evalAST(child[0]));
    break;

  case AST_FUNCTION_COT:
    /* cot x = 1 / tan x */
    result = (1./tan(evalAST(child[0])));
    break;
  case AST_FUNCTION_COTH:
    /* coth x = cosh x / sinh x */
    result = cosh(evalAST(child[0])) / sinh(evalAST(child[0]));
    break;
  case AST_FUNCTION_CSC:
    /* csc x = 1 / sin x */
    result = (1./sin(evalAST(child[0])));
    break;

  case AST_FUNCTION_CSCH:
    /* csch x = 1 / cosh x  */
    result = (1./cosh(evalAST(child[0])));
    break;

  case AST_FUNCTION_EXP:
    result = exp(evalAST(child[0]));
    break;

  case AST_FUNCTION_FACTORIAL:
    {
      printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
      printf("The factorial is only implemented for integer values. If a floating\n");
      printf("point number is passed, the floor value is used for calculation!\n");
      printf("-----------------------END MESSAGE--------------------------\n\n");
      i = (int)floor(evalAST(child[0]));
      for(result=1;i>1;--i)
        result *= i;
    }
    break;

  case AST_FUNCTION_FLOOR:
    result = floor(evalAST(child[0]));
    break;

  case AST_FUNCTION_LN:
    result = log(evalAST(child[0]));
    break;

  case AST_FUNCTION_LOG:
    result = log10(evalAST(child[0]));
    break;

  case AST_FUNCTION_PIECEWISE:
    printf("\n-------------MESSAGE FROM EVALUATION FUNCTION-------------\n");
    printf("This function is not implemented yet.\n");
    printf("The value defaults to 0.\n");
    printf("-----------------------END MESSAGE--------------------------\n\n");
    result = 0.0;
    break;

  case AST_FUNCTION_POWER:
    result = pow(evalAST(child[0]),evalAST(child[1]));
    break;

  case AST_FUNCTION_ROOT:
    result = pow(evalAST(child[1]),(1./evalAST(child[0])));
    break;

  case AST_FUNCTION_SEC:
    /* sec x = 1 / cos x */
    result = 1./cos(evalAST(child[0]));
    break;

  case AST_FUNCTION_SECH:
    /* sech x = 1 / sinh x */
    result = 1./sinh(evalAST(child[0]));
    break;

  case AST_FUNCTION_SIN:
    result = sin(evalAST(child[0]));
    break;

  case AST_FUNCTION_SINH:
    result = sinh(evalAST(child[0]));
    break;

  case AST_FUNCTION_TAN:
    result = tan(evalAST(child[0]));
    break;

  case AST_FUNCTION_TANH:
    result = tanh(evalAST(child[0]));
    break;

  case AST_LOGICAL_AND:
    result = (double) ((evalAST(child[0])) && (evalAST(child[1])));
    break;

  case AST_LOGICAL_NOT:
    result = (double) (!(evalAST(child[0])));
    break;

  case AST_LOGICAL_OR:
    result = (double) ((evalAST(child[0])) || (evalAST(child[1])));
    break;

  case AST_LOGICAL_XOR:
    result = (double) ((!(evalAST(child[0])) && (evalAST(child[1])))
                       || ((evalAST(child[0])) &&  !(evalAST(child[1]))));
    break;

  case AST_RELATIONAL_EQ :
    result = (double) ((evalAST(child[0])) == (evalAST(child[1])));
    break;

  case AST_RELATIONAL_GEQ:
    result = (double) ((evalAST(child[0])) >= (evalAST(child[1])));
    break;

  case AST_RELATIONAL_GT:
    result = (double) ((evalAST(child[0])) > (evalAST(child[1])));
    break;

  case AST_RELATIONAL_LEQ:
    result = (double) ((evalAST(child[0])) <= (evalAST(child[1])));
    break;

  case AST_RELATIONAL_LT :
    result = (double) ((evalAST(child[0])) < (evalAST(child[1])));
    break;

  default:
    result = 0;
    break;
  }

  free(child);

  return result;
}