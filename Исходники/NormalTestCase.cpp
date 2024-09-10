void NormalRepNode::clientOperations()
{
	XmlTransaction txn = getManager().createTransaction();
	try {
		// Save the new node state.
		docNum_ = getContainer().getNumDocuments(txn);
		txn.commit();
	} catch (XmlException &xe) {
		txn.abort();
		throwIfUnExpected(xe);
	}
}