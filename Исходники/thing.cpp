Cylinder* Thing::getTopParent()
{
	//tile
	if(getParent() == NULL)
		return dynamic_cast<Cylinder*>(this);

	Cylinder* aux = getParent();
	Cylinder* prevaux = dynamic_cast<Cylinder*>(this);

	while(aux->getParent() != NULL){
		prevaux = aux;
		aux = aux->getParent();
	}

	if(dynamic_cast<Cylinder*>(prevaux)){
		return prevaux;
	}

	return aux;
}