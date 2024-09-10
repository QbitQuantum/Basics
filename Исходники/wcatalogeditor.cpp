void
wCatalogEditor::checkUserFields( QStringList &lst)
{
	aCfgItem item = md->find(catId);
	int fid;
	if(item.isNull()) return;
	item = md->findChild(item,md_element);
	for(int i=0; i< md->count(item,md_field); i++)
  	{
		aCfgItem mdi = md->findChild(item,md_field,i);
		int ind = lst.findIndex(QString("uf%1").arg(md->attr(mdi,mda_id)));
		if(ind!=-1)
		{
			lst.insert(lst.at(i),lst[ind]);
			lst.remove(lst.at(ind+1));
			
		}
		else
		{
			ind = lst.findIndex(QString("text_uf%1").arg(md->attr(mdi,mda_id)));
			if(ind!=-1)
			{
				lst.insert(lst.at(i),lst[ind]);
				lst.remove(lst.at(ind+1));
			
			}
		}
  	}
	
}