TypeIdent* TratadorVariableDef::getType(Node* typeNode){
	int escopo = this->escopoAtual;
	Node* typeSymbol;
	TypeIdent* resultType=NULL;
	
	typeNode->firstChild();
	
	if(typeNode->getChild()->getHandle()->getHandleName()=="typeSymbol"){	
        typeNode->getChild()->getChild()->firstChild();
		typeSymbol = typeNode->getChild()->getChild()->getChild();
		
		while((escopo>=0)&&(resultType==NULL)){
			resultType = (TypeIdent*) (*this->typeList)[escopo]->getIdentByName(typeSymbol->getToken()->getLexema());
		
			escopo--;
		}
		
		return resultType;
	}else{
		//TRATAR TUPLETYPE
	}
}