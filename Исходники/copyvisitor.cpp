Soprano::Node NG::CopyVisitor::vertexProxy(const Soprano::Node & node) 
{
    if(node.isBlank())
	return node;

    if(node.isLiteral())
	return node;

    Soprano::Node answer;
    QHash< QUrl, QUrl >::const_iterator it =
	d->proxyUrls->find(node.uri());
    if(it == d->proxyUrls->end()) {
	// Create new

	// Create new url
	// FIXME What label should be passed to the generateUniqueUri
	answer = Soprano::Node(
		     d->targetManager->generateUniqueUri("unknown")
		 );
	Q_ASSERT(!answer.uri().isEmpty());

	// Add to table
	//kDebug() << "Adding proxy to " << node.uri() << " : " << answer.uri();
	d->proxyUrls->insert(node.uri(), answer.uri());
    } else {
	answer  = Soprano::Node(it.value());
    }

    return answer;
}