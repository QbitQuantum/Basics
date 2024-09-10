TEST_F(SymbolTest, testClassSymbol) {
  DataType* data_type = class_->getDataType();
  ASSERT_NE(nullptr, data_type);
  ASSERT_EQ(DataType::DATA_TYPE_CLASS, data_type->getType());
  ClassType* type = dynamic_cast<ClassType*>(data_type);
  ASSERT_NE(nullptr, type);
  EXPECT_EQ(class_.get(), type->getClassSymbol());

  VariableSymbol* v1 = new VariableSymbol("v1");
  v1->setDataType(DataTypeFactory::getInt32Type());
  class_->addVariable(v1);

  VariableSymbol* v2 = new VariableSymbol("v2");
  v2->setDataType(DataTypeFactory::getStringType());
  class_->addVariable(v2);
  const auto& actual_vars = class_->getVariables();
  std::vector<VariableSymbol*> expected_vars {v1, v2};
  EXPECT_EQ(expected_vars, actual_vars);

  FunctionSymbol* f = new FunctionSymbol("f");
  f->setReturnType(DataTypeFactory::getCharType());
  class_->addFunction(f);
  const auto& actual_funcs = class_->getFunctions();
  std::vector<FunctionSymbol*> expected_funcs {f};
  EXPECT_EQ(expected_funcs, actual_funcs);

  Scope* scope = class_->getScope();
  ASSERT_NE(nullptr, scope);
  EXPECT_FALSE(scope->isOwnedBySymbolTable());
  EXPECT_EQ(class_->getName(), scope->getName());

  EXPECT_EQ(4, scope->getSize());
  EXPECT_EQ(v1, scope->lookup(v1->getName()));
  EXPECT_EQ(v2, scope->lookup(v2->getName()));
  EXPECT_EQ(f, scope->lookup(f->getName()));
  EXPECT_EQ(class_.get(), scope->lookup(class_->getName()));

  ClassSymbol super_class("super");
  class_->setSuperClass(&super_class);
  EXPECT_EQ(super_class.getScope(), scope->getParent());
  EXPECT_EQ(&super_class, scope->lookup(super_class.getName()));
}