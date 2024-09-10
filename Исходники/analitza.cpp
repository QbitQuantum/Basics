Object* Analitza::eval(Object* branch)
{
	Q_ASSERT(branch && branch->type()!=Object::none);
	//Won't calc so would be a good idea to have it simplified 
	if(branch->isContainer()) {
		Container* c = (Container*) branch;
		Operator op = c->firstOperator();
		switch(op.operatorType()) {
			case Object::diff:
				branch = derivative("x", c->m_params[1]);
				break;
			case Object::onone:
				branch = eval(c->m_params[0]);
				break;
			default:
				break;
		}
	}
	return branch;
}