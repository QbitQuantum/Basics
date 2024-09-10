char Filters::BT_ThMLHTML::processText(sword::SWBuf& buf, const sword::SWKey* key, const sword::SWModule* module) {
	sword::ThMLHTML::processText(buf, key, module);

	CSwordModuleInfo* m = CPointers::backend()->findModuleByName( module->Name() );

	if (m && !(m->has(CSwordModuleInfo::lemmas) || m->has(CSwordModuleInfo::strongNumbers))) { //only parse if the module has strongs or lemmas
		return 1;
	}

	QString result;

	QString t = QString::fromUtf8(buf.c_str());
	QRegExp tag("([.,;]?<sync[^>]+(type|value)=\"([^\"]+)\"[^>]+(type|value)=\"([^\"]+)\"([^<]*)>)+");

	QStringList list;
	int lastMatchEnd = 0;
	int pos = tag.indexIn(t,0);

	if (pos == -1) { //no strong or morph code found in this text
		return 1; //WARNING: Return alread here
	}

	while (pos != -1) {
		list.append(t.mid(lastMatchEnd, pos+tag.matchedLength()-lastMatchEnd));

		lastMatchEnd = pos+tag.matchedLength();
		pos = tag.indexIn(t,pos+tag.matchedLength());
	}

	if (!t.right(t.length() - lastMatchEnd).isEmpty()) {
		list.append(t.right(t.length() - lastMatchEnd));
	}

	tag = QRegExp("<sync[^>]+(type|value|class)=\"([^\"]+)\"[^>]+(type|value|class)=\"([^\"]+)\"[^>]+((type|value|class)=\"([^\"]+)\")*([^<]*)>");

	for (QStringList::iterator it = list.begin(); it != list.end(); ++it) {
		QString e( *it );

		const bool textPresent = (e.trimmed().remove(QRegExp("[.,;:]")).left(1) != "<");

		if (!textPresent) {
			continue;
		}


		bool hasLemmaAttr = false;
		bool hasMorphAttr = false;

		int pos = tag.indexIn(e, 0);
		bool insertedTag = false;
		QString value;
		QString valueClass;

		while (pos != -1) {
			bool isMorph = false;
			bool isStrongs = false;
			value = QString::null;
			valueClass = QString::null;

			// check 3 attribute/value pairs

			for (int i = 1; i < 6; i += 2) {
				if (i > 4)
					i++;

				if (tag.cap(i) == "type") {
					isMorph   = (tag.cap(i+1) == "morph");
					isStrongs = (tag.cap(i+1) == "Strongs");
				}
				else if (tag.cap(i) == "value") {
					value = tag.cap(i+1);
				}
				else if (tag.cap(i) == "class") {
					valueClass = tag.cap(i+1);
				}
			}

			// prepend the class qualifier to the value
			if (!valueClass.isEmpty()) {
				value = valueClass + ":" + value;
				//     value.append(":").append(value);
			}

			if (value.isEmpty()) {
				break;
			}

			//insert the span
			if (!insertedTag) {
				e.replace(pos, tag.matchedLength(), "</span>");
				pos += 7;

				QString rep = QString("<span lemma=\"").append(value).append("\">");
				int startPos = 0;
				QChar c = e[startPos];

				while ((startPos < pos) && (c.isSpace() || c.isPunct())) {
					++startPos;
					c = e[startPos];
				}

				hasLemmaAttr = isStrongs;
				hasMorphAttr = isMorph;

				e.insert( startPos, rep );
				pos += rep.length();
			}
			else { //add the attribute to the existing tag
				e.remove(pos, tag.matchedLength());

				if ((!isMorph && hasLemmaAttr) || (isMorph && hasMorphAttr)) { //we append another attribute value, e.g. 3000 gets 3000|5000
					//search the existing attribute start
					QRegExp attrRegExp( isMorph ? "morph=\".+(?=\")" : "lemma=\".+(?=\")" );
					attrRegExp.setMinimal(true);
					const int foundAttrPos = e.indexOf(attrRegExp, pos);

					if (foundAttrPos != -1) {
						e.insert(foundAttrPos + attrRegExp.matchedLength(), QString("|").append(value));
						pos += value.length() + 1;

						hasLemmaAttr = !isMorph;
						hasMorphAttr = isMorph;
					}
				}
				else { //attribute was not yet inserted
					const int attrPos = e.indexOf(QRegExp("morph=|lemma="), 0);

					if (attrPos >= 0) {
						QString attr;
						attr.append(isMorph ? "morph" : "lemma").append("=\"").append(value).append("\" ");
						e.insert(attrPos, attr);

						hasMorphAttr = isMorph;
						hasLemmaAttr = !isMorph;

						pos += attr.length();
					}
				}
			}

			insertedTag = true;
			pos = tag.indexIn(e, pos);
		}

		result.append( e );
	}

	if (list.count()) {
		buf = (const char*)result.toUtf8();
	}

	return 1;
}