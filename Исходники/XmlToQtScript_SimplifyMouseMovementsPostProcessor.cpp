void XmlToQtScript::SimplifyMouseMovementsPostProcessor::process(Item* iterator, QList<Item>* in)
{
	if(iterator->method == "moveMouse")
	{
		const QVariant target = iterator->target;
		const QString targetClass = iterator->targetClass;
		QVariantMap parameters = iterator->parameters.toMap();
		const QPoint origin = QPoint(
			parameters.value("x").toInt(),
			parameters.value("y").toInt()
		);
		int duration = 0;
		while(!in->isEmpty())
		{
			Item msec;
			msec = in->takeFirst(); // msec << pointing at
			duration += msec.parameters.toInt();

			if(in->isEmpty())
			{
				*iterator = msec;
				break;
			}

			*iterator = in->takeFirst(); // ? Unknown
			if(iterator->method != "moveMouse" || iterator->target != target)
			{
				in->prepend(*iterator);
				*iterator = msec;
				break;
			}
			parameters = iterator->parameters.toMap();
		}
		const QPoint destination = QPoint(
			parameters.value("x").toInt(),
			parameters.value("y").toInt()
		);
		parameters.remove("x");
		parameters.remove("y");
		parameters.insert("originX", origin.x());
		parameters.insert("originY", origin.y());
		parameters.insert("destinationX", destination.x());
		parameters.insert("destinationY", destination.y());
		parameters.insert("duration", duration);
		insertItem(
			Item(
				target,
				targetClass,
				"moveMouse",
				parameters
			),
			BeforeCurrentItem
		);
	}
}