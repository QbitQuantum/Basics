int ofURLFileLoaderImpl::saveAsync(string url, string path){
	ofHttpRequest request(url,path,true);
	requests.send(request);
	start();
	return request.getID();
}