void objectWalker(const Object* root, int ind)
{
	Container *c; Cn *num; Operator *op; Ci *var;
	QString s;
	if(!root) {
		qDebug() << "This is an null object";
		return;
	}
	if(ind>100) return;
	
	for(int i=0; i<ind; i++)
		s += " |_____";
	
	switch(root->type()) { //TODO: include the function into a module and use toString
		case Object::container:
			c= (Container*) root;
			qDebug() << qPrintable(s) << "| cont: " << c->toMathML();
			for(int i=0; i<c->m_params.count(); i++)
				objectWalker(c->m_params[i], ind+1);
			
			break;
		case Object::value:
			num= (Cn*) root;
			qDebug() << qPrintable(s) << "| num: " << num->value();
			break;
		case Object::oper:
			op= (Operator*) root;
			qDebug() << qPrintable(s) << "| operator: " << op->toString();
			break;
		case Object::variable:
			var = (Ci*) root;
			qDebug() << qPrintable(s) << "| variable: " << var->name() << "Func:" << var->isFunction();
			break;
		default:			qDebug() << qPrintable(s) << "| dunno: " << (int) root->type();
			break;
	}
}