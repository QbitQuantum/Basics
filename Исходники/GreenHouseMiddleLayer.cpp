boolean GreenHouseMiddleLayer::updateDataAndCheckIfFull(LinkedList<Message>& list,Message& lastMessage,int fullSize){
	if (list.size() == 0) {					//for the first time
		list.add(lastMessage);
	}
	else {
		// update data
		int i;
		for (i = 0; i < list.size(); ++i) {
			if (list.get(i).source == lastMessage.source) {	//if arduino id exsist, overwrite the data
				list.remove(i);
				list.add(lastMessage);
				break;
			}
		}
		if(list.size() == i) // if we didnt find id that maches last message id
			list.add(lastMessage);			//add the message (it has a new id)
		//check if full
		if (fullSize == list.size()) {
			return true;
		}
		return false;
	}
		

	if (list.size() == CommonValues::lowerLayerRegisteredNum)
		return true;
	else
		return false;
}