int main() {

	string input;

	while(true) {
		cout << "Evaluate >> ";
		getline(cin, input);

		if(input == "exit") break;
		else {
			Parser * p = new Parser(input);
			SExpr se;

			Expr * root = p->E();

			// Evaluates S-Expr with visitor
			root->accept(se);
			cout << endl;

			delete p;
		}
	}

	return 0;

}