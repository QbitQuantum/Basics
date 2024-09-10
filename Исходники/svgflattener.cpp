void SvgFlattener::flattenChildren(QDomElement &element){

    // recurse the children
    QDomNodeList childList = element.childNodes();

    for(uint i = 0; i < childList.length(); i++){
        QDomElement child = childList.item(i).toElement();
        flattenChildren(child);
    }

    //do translate
    if(hasTranslate(element)){
		QList<double> params = TextUtils::getTransformFloats(element);
		if (params.size() == 2) {
            shiftChild(element, params.at(0), params.at(1), false);
			//DebugDialog::debug(QString("translating %1 %2").arg(params.at(0)).arg(params.at(1)));
		}
		else if (params.size() == 6) {
            shiftChild(element, params.at(4), params.at(5), false);
		}
		else if (params.size() == 1) {
            shiftChild(element, params.at(0), 0, false);
			//DebugDialog::debug(QString("translating %1").arg(params.at(0)));
		}
		else {
			DebugDialog::debug("weird transform found");
		}
    }
    else if(hasOtherTransform(element)) {
        QMatrix transform = TextUtils::transformStringToMatrix(element.attribute("transform"));

        //DebugDialog::debug(QString("rotating %1 %2 %3 %4 %5 %6").arg(params.at(0)).arg(params.at(1)).arg(params.at(2)).arg(params.at(3)).arg(params.at(4)).arg(params.at(5)));
        unRotateChild(element, transform);
    }

    // remove transform
    element.removeAttribute("transform");
}