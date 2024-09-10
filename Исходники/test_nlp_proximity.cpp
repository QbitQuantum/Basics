 vect<double,3> operator()() {
   vect_n<double> x(0.0,0.0,0.0,0.0);
   vect<double,3> c1 = mShape1->getPose().transformToGlobal(vect<double,3>(0.0,0.0,0.0));
   vect<double,3> c2 = mShape2->getPose().transformToGlobal(vect<double,3>(0.0,0.0,0.0));
   
   // pick the middle between centers as the starting guess at the solution.
   x[1] = (c1[0] + c2[0]) * 0.5;
   x[2] = (c1[1] + c2[1]) * 0.5;
   x[3] = (c1[2] + c2[2]) * 0.5;
   
   if(mShape1->getObjectType() == geom::box::getStaticObjectType()) {
     shared_ptr< geom::box > bx1 = rtti::rk_dynamic_ptr_cast< geom::box >(mShape1);
     double min_dim = 0.5 * bx1->getDimensions()[0];
     if(min_dim > 0.5 * bx1->getDimensions()[1])
       min_dim = 0.5 * bx1->getDimensions()[1];
     if(min_dim > 0.5 * bx1->getDimensions()[2])
       min_dim = 0.5 * bx1->getDimensions()[2];
     if(mShape2->getObjectType() == geom::box::getStaticObjectType()) {
       // box-box case.
       shared_ptr< geom::box > bx2 = rtti::rk_dynamic_ptr_cast< geom::box >(mShape2);
       if(min_dim > 0.5 * bx2->getDimensions()[0])
         min_dim = 0.5 * bx2->getDimensions()[0];
       if(min_dim > 0.5 * bx2->getDimensions()[1])
         min_dim = 0.5 * bx2->getDimensions()[1];
       if(min_dim > 0.5 * bx2->getDimensions()[2])
         min_dim = 0.5 * bx2->getDimensions()[2];
       
       x[0] = norm_2(c2 - c1) / min_dim;
       
       std::cout << "Checking proximity between Box '" << bx1->getName() << "' and Box '" << bx2->getName() << "'..." << std::endl;
       
       try {
       optim::make_nlip_newton_tr(geom::slack_minimize_func(),geom::slack_minimize_grad(),geom::slack_minimize_hess(),min_dim,0.1,300,1e-4,1e-3,0.9)
         .set_ineq_constraints(
           geom::dual_boundary_func<geom::box_boundary_func, geom::box_boundary_func>(
             geom::box_boundary_func(bx1), geom::box_boundary_func(bx2)),
           geom::dual_boundary_jac<geom::box_boundary_jac, geom::box_boundary_jac>(
             geom::box_boundary_jac(bx1), geom::box_boundary_jac(bx2)))
         (x);
       } catch(...) { };
       
       std::cout << "  -- The raw solution obtained was: " << x << std::endl;
       std::cout << "  -- The shape1 boundary functions give: " << geom::box_boundary_func(bx1)(x) << std::endl;
       std::cout << "  -- The shape2 boundary functions give: " << geom::box_boundary_func(bx2)(x) << std::endl;
       
     } else {
       // box-cylinder case.
       shared_ptr< geom::cylinder > cy2 = rtti::rk_dynamic_ptr_cast< geom::cylinder >(mShape2);
       if(min_dim > 0.5 * cy2->getLength())
         min_dim = 0.5 * cy2->getLength();
       if(min_dim > cy2->getRadius())
         min_dim = cy2->getRadius();
       
       x[0] = norm_2(c2 - c1) / min_dim;
       
       std::cout << "Checking proximity between Box '" << bx1->getName() << "' and Cylinder '" << cy2->getName() << "'..." << std::endl;
       
       try {
       optim::make_nlip_newton_tr(geom::slack_minimize_func(),geom::slack_minimize_grad(),geom::slack_minimize_hess(),min_dim,0.1,300,1e-4,1e-3,0.9)
         .set_ineq_constraints(
           geom::dual_boundary_func<geom::box_boundary_func, geom::cylinder_boundary_func>(
             geom::box_boundary_func(bx1), geom::cylinder_boundary_func(cy2)),
           geom::dual_boundary_jac<geom::box_boundary_jac, geom::cylinder_boundary_jac>(
             geom::box_boundary_jac(bx1), geom::cylinder_boundary_jac(cy2)))
         (x);
       } catch(...) { };
       
       std::cout << "  -- The raw solution obtained was: " << x << std::endl;
       std::cout << "  -- The shape1 boundary functions give: " << geom::box_boundary_func(bx1)(x) << std::endl;
       std::cout << "  -- The shape2 boundary functions give: " << geom::cylinder_boundary_func(cy2)(x) << std::endl;
       
     };
   } else {
     shared_ptr< geom::cylinder > cy1 = rtti::rk_dynamic_ptr_cast< geom::cylinder >(mShape1);
     double min_dim = 0.5 * cy1->getLength();
     if(min_dim > cy1->getRadius())
       min_dim = cy1->getRadius();
     if(mShape2->getObjectType() == geom::box::getStaticObjectType()) {
       // cylinder-box case.
       shared_ptr< geom::box > bx2 = rtti::rk_dynamic_ptr_cast< geom::box >(mShape2);
       if(min_dim > 0.5 * bx2->getDimensions()[0])
         min_dim = 0.5 * bx2->getDimensions()[0];
       if(min_dim > 0.5 * bx2->getDimensions()[1])
         min_dim = 0.5 * bx2->getDimensions()[1];
       if(min_dim > 0.5 * bx2->getDimensions()[2])
         min_dim = 0.5 * bx2->getDimensions()[2];
       
       x[0] = norm_2(c2 - c1) / min_dim;
       
       std::cout << "Checking proximity between Cylinder '" << cy1->getName() << "' and Box '" << bx2->getName() << "'..." << std::endl;
       
       try {
       optim::make_nlip_newton_tr(geom::slack_minimize_func(),geom::slack_minimize_grad(),geom::slack_minimize_hess(),min_dim,0.1,300,1e-4,1e-3,0.9)
         .set_ineq_constraints(
           geom::dual_boundary_func<geom::cylinder_boundary_func, geom::box_boundary_func>(
             geom::cylinder_boundary_func(cy1), geom::box_boundary_func(bx2)),
           geom::dual_boundary_jac<geom::cylinder_boundary_jac, geom::box_boundary_jac>(
             geom::cylinder_boundary_jac(cy1), geom::box_boundary_jac(bx2)))
         (x);
       } catch(...) { };
       
       std::cout << "  -- The raw solution obtained was: " << x << std::endl;
       std::cout << "  -- The shape1 boundary functions give: " << geom::cylinder_boundary_func(cy1)(x) << std::endl;
       std::cout << "  -- The shape2 boundary functions give: " << geom::box_boundary_func(bx2)(x) << std::endl;
       
     } else {
       // cylinder-cylinder case.
       shared_ptr< geom::cylinder > cy2 = rtti::rk_dynamic_ptr_cast< geom::cylinder >(mShape2);
       if(min_dim > 0.5 * cy2->getLength())
         min_dim = 0.5 * cy2->getLength();
       if(min_dim > cy2->getRadius())
         min_dim = cy2->getRadius();
       
       x[0] = norm_2(c2 - c1) / min_dim;
       
       std::cout << "Checking proximity between Cylinder '" << cy1->getName() << "' and Cylinder '" << cy2->getName() << "'..." << std::endl;
       
       try {
       optim::make_nlip_newton_tr(geom::slack_minimize_func(),geom::slack_minimize_grad(),geom::slack_minimize_hess(),min_dim,0.1,300,1e-4,1e-3,0.9)
         .set_ineq_constraints(
           geom::dual_boundary_func<geom::cylinder_boundary_func, geom::cylinder_boundary_func>(
             geom::cylinder_boundary_func(cy1), geom::cylinder_boundary_func(cy2)),
           geom::dual_boundary_jac<geom::cylinder_boundary_jac, geom::cylinder_boundary_jac>(
             geom::cylinder_boundary_jac(cy1), geom::cylinder_boundary_jac(cy2)))
         (x);
       } catch(...) { };
       
       std::cout << "  -- The raw solution obtained was: " << x << std::endl;
       std::cout << "  -- The shape1 boundary functions give: " << geom::cylinder_boundary_func(cy1)(x) << std::endl;
       std::cout << "  -- The shape2 boundary functions give: " << geom::cylinder_boundary_func(cy2)(x) << std::endl;
       
     };
   };
   
   vect<double,3> result(x[1],x[2],x[3]);
   vect<double,3> x1_rel = mShape1->getPose().transformFromGlobal(vect<double,3>(x[1],x[2],x[3]));
   vect<double,3> x2_rel = mShape2->getPose().transformFromGlobal(vect<double,3>(x[1],x[2],x[3]));
   
   if(x[0] > 1e-6) {
     x1_rel *= (1.0 / x[0]);
     x2_rel *= (1.0 / x[0]);
     vect<double,3> x1 = mShape1->getPose().transformToGlobal(x1_rel);
     vect<double,3> x2 = mShape2->getPose().transformToGlobal(x2_rel);
     std::cout << "  -- The point on Shape1 is " << x1 << std::endl;
     std::cout << "  -- The point on Shape2 is " << x2 << std::endl;
     std::cout << "  -- The distance is " <<  (norm_2(x2 - x1) * (x[0] < 1.0 ? -1.0 : 1.0)) << std::endl;
   } else {
     std::cout << "  -- The center points of the shapes are coincident! At " << vect<double,3>(x[1],x[2],x[3]) << std::endl;
   };
   
   return result;
 };