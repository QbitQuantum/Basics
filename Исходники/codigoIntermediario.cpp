void GeradorCodigoIntermediario::trataAssign(Node* node){
	Node* actual = NULL;
	Node* aux = NULL;
	Atribuicao* comando = new Atribuicao();
	Variavel* cabeca = NULL;
	Variavel* direita1 = NULL;
	Operador* operador = NULL;
	Variavel* direita2 = NULL;
	
	node->firstChild();
	actual = node->getChild(); //variableAccessList
	actual->firstChild();
	actual = actual->getChild(); //variableAcess
	actual->firstChild();
	
	cabeca = new VariavelToken(actual->getChild()->getToken());
	variaveis.addVariavel(cabeca);
	
	comando->setCabeca(cabeca);
	
	node->nextChild();
	node->nextChild();
	
	actual = node->getChild();//expressionlist	
	
	while(actual->getHandle()->getHandleName()!="simpleExpression"){
		actual->firstChild();
		actual = actual->getChild();
	}
	
	actual->firstChild();	
	
	if(actual->getChild()->getHandle()->getHandleName()!="term"){
		actual->nextChild();
	}
	
	actual = actual->getChild(); //term
	actual->firstChild();
	actual = actual->getChild(); //factor
	
	actual = actual->getChild(); //term
	actual->firstChild();
	actual = actual->getChild(); //factor
		
	actual = actual->getChild(); //term
	actual->firstChild();
	actual = actual->getChild(); //factor			
	
	actual->firstChild();
	actual = actual->getChild(); //factor		
	
	actual->firstChild();
	aux = actual->getChild(); //factor			
	
	direita1 = new VariavelNumber(aux->getToken()->getLexema());
	comando->setDireita1(direita1);
	
	this->comandos.addComando(comando);
}