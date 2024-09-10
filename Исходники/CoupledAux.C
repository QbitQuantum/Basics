InputParameters validParams<CoupledAux>()
{
  InputParameters params = validParams<AuxKernel>();

  MooseEnum operators("+ - * /", "+");

  params.addRequiredCoupledVar("coupled", "Coupled Value for Calculation");

  params.addParam<Real>("value", 0.0, "A value to use in the binary arithmetic operation of this coupled auxkernel");
  params.addParam<MooseEnum>("operator", operators, "The binary operator to use in the calculation");
  return params;
}