Ti::TiValue Ti::TiViewProxy::remove(Ti::TiValue value)
{
	Ti::TiValue val;
	val.setUndefined();

	Ti::TiViewProxy *childProxy = static_cast<Ti::TiViewProxy*>(value.toProxy());
	if(!_childViewsProxies.contains(childProxy)) return val;

	Ti::TiView* childView = childProxy->getView();
	Ti::TiView* thisView = getView();
	childProxy->makeWeak();
	thisView->remove(childView);
	_childViewsProxies.removeOne(childProxy);

	childProxy->_parentProxy = NULL;
    Local<Value> children = _jsObject->Get(String::New("children"));
    if(!children.IsEmpty() && !children->IsUndefined())
    {
    	Local<Array> array = Local<Array>::Cast(children);
    	for(int i = 0, len = array->Length(); i < len; i++) {
    		if(array->Get(i) == value.toJSValue())
    		{
    	    	array->Delete(i);
    	    	break;
    		}
    	}
    }

	return val;
}