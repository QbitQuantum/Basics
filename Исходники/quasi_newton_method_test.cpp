void QuasiNewtonMethodTest::test_calculate_DFP_inverse_Hessian_approximation(void)
{
   message += "test_calculate_DFP_inverse_Hessian_approximation\n";

   DataSet ds(2, 1, 1);
   ds.randomize_data_normal();
   NeuralNetwork nn(1, 1);
   PerformanceFunctional pf(&nn, &ds);
   QuasiNewtonMethod qnm(&pf);

   // Test 

   nn.initialize_parameters(1.0);

   Vector<double> old_parameters = nn.arrange_parameters();
   Vector<double> old_gradient = pf.calculate_gradient();
//   Matrix<double> old_inverse_Hessian = pf.calculate_inverse_Hessian();

   nn.initialize_parameters(-0.5);

   Vector<double> parameters = nn.arrange_parameters();
   Vector<double> gradient = pf.calculate_gradient();
//   Matrix<double> inverse_Hessian = pf.calculate_inverse_Hessian();

//   Matrix<double> DFP_inverse_Hessian
//   = qnm.calculate_DFP_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian);

//   assert_true(DFP_inverse_Hessian == inverse_Hessian, LOG);

   // Test 

   nn.initialize_parameters(1.0e-3);

   old_parameters = nn.arrange_parameters();
   old_gradient = pf.calculate_gradient();
//   old_inverse_Hessian = pf.calculate_inverse_Hessian();

   nn.initialize_parameters(1.0e-6);

   parameters = nn.arrange_parameters();
   gradient = pf.calculate_gradient();
//   inverse_Hessian = pf.calculate_inverse_Hessian();

//   DFP_inverse_Hessian = qnm.calculate_DFP_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian);

//   assert_true(DFP_inverse_Hessian == inverse_Hessian, LOG);

   // Test 

   nn.initialize_parameters(1.0e-6);

   old_parameters = nn.arrange_parameters();
   old_gradient = pf.calculate_gradient();
//   old_inverse_Hessian = pf.calculate_inverse_Hessian();

   nn.initialize_parameters(1.0e-9);

   parameters = nn.arrange_parameters();
   gradient = pf.calculate_gradient();
//   inverse_Hessian = pf.calculate_inverse_Hessian();

//   DFP_inverse_Hessian = qnm.calculate_DFP_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian);

//   assert_true(DFP_inverse_Hessian == inverse_Hessian, LOG);

   // Test 

   old_parameters.initialize(1.0e-3);
   parameters.initialize(1.0e-6);

   old_gradient.initialize(1.0e-3);
   gradient.initialize(1.0e-6);

//   old_inverse_Hessian(0,0) = 0.75;
//   old_inverse_Hessian(0,1) = -0.25;
//   old_inverse_Hessian(1,0) = -0.25;
//   old_inverse_Hessian(1,1) = 0.75;

//   DFP_inverse_Hessian = qnm.calculate_DFP_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian);

}