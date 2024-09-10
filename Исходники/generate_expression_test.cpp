TEST(generateExpression, integrate_ode) {
  static const bool user_facing = true;
  std::stringstream msgs;

  stan::lang::integrate_ode so; // null ctor should work and not raise error

  std::string integration_function_name = "bar";
  std::string system_function_name = "foo";
  stan::lang::variable y0("y0_var_name");
  y0.set_type(stan::lang::bare_array_type(stan::lang::double_type()));
  stan::lang::variable t0("t0_var_name");
  t0.set_type(stan::lang::double_type());
  stan::lang::variable ts("ts_var_name");
  ts.set_type(stan::lang::bare_array_type(stan::lang::double_type()));
  stan::lang::variable theta("theta_var_name");
  theta.set_type(stan::lang::bare_array_type(stan::lang::double_type()));
  stan::lang::variable x("x_var_name");
  x.set_type(stan::lang::bare_array_type(stan::lang::double_type()));
  stan::lang::variable x_int("x_int_var_name");
  x.set_type(stan::lang::bare_array_type(stan::lang::int_type()));
  stan::lang::integrate_ode so2(integration_function_name, system_function_name,
                    y0, t0, ts, theta, x, x_int);
  stan::lang::expression e1(so2);

  generate_expression(e1, user_facing, msgs);
  EXPECT_EQ(msgs.str(),
            "bar(foo_functor__(), y0_var_name, t0_var_name, ts_var_name, "
            "theta_var_name, x_var_name, x_int_var_name, pstream__)");

}