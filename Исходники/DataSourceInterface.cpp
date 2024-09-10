bool DataSourceInterface::endSession() {
	if(context!=NULL) {
		destroyContext(context);
		context = NULL;
		return true;
	}
	return false;
}