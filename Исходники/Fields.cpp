void 
GltFields::add(BoundingBox &val,const string &name)
{
	GltFields *root = new GltFields(name);
	_fields.push_back(GltFieldPtr(root));

	root->add(val.defined(),"defined");
	root->add(val.min()    ,"min");
	root->add(val.max()    ,"max");
}