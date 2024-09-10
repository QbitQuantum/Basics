bool ReferenceSystem::linkTo(ReferenceSystem *rs)
{
	if(rs!=base)//if it is not currently dependant
	{   //it si posible to link if this is not parent grand parent ...etc) of rs	
		if(isAncestorOf(rs)==false){
			unLink();
			base=rs;//rs es el padre de *this
			if(rs)rs->dependentSystem.push_back(this);//set *this as dependant of 
			setNeedToUpdate();
			return true;
			}
		return false;
	}
	return true;

}