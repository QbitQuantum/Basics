AttributePtr gen_text(const RuleTable& print_rules, NodePtr root,
      BindingsPtr bindings) {
   const Rules& rules(bindings->get_rules());
   std::ostringstream os;
   if (rules.operator_rules_defined()) {
      NodePtr cloned_root = clone_including_attributes(root);
      /*
	 the parentheses operator can be configured through
	 the operator set named "parentheses";
	 Op::LPAREN is taken by default
      */
      OperatorSetPtr parenthesesSet = rules.get_opset("parentheses");
      Operator parentheses;
      if (parenthesesSet && parenthesesSet->get_card() == 1) {
	 OperatorSet::Iterator it = parenthesesSet->begin();
	 parentheses = Operator(*it);
      } else {
	 parentheses = Op::LPAREN;
      }
      parenthesize(cloned_root, rules.get_operator_table(), parentheses);
      root = cloned_root;
   }
   if (print(os, root, print_rules, bindings)) {
      return std::make_shared<Attribute>(os.str());
   } else {
      return AttributePtr(nullptr);
   }
}