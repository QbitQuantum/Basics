BOOL
MFCArrangeView::OnDrop(
			COleDataObject* object,
			DROPEFFECT dropEffect,
			CPoint point 
		)
{
	cerr << "MFCArrangeView::on drop"<<endl;
	point += GetScrollPosition();
	switch (dragon.type) {
		case QuaDrop::FILES:
		case QuaDrop::AUDIOFILES:
		case QuaDrop::MIDIFILES: {
			Time	at_time;
			short	at_channel;
			Pix2Time(point.x, at_time);
			at_channel = Pix2Channel(point.y);
			std::cerr << "file drop " << at_channel << " chan " << at_time.StringValue() << endl;
			//			int		bar, barbeat, beattick;
//			at_time.GetBBQValue(bar, barbeat, beattick);
//			fprintf(stderr, "drag files is dropped: on point %d %d, channel %d, ticks %d t %d:%d.%d\n", point.x, point.y, at_channel, at_time.ticks, bar, barbeat, beattick);
			short	i;
			bool	drop_sample_file=false;
			bool	drop_midi_file=false;
			bool	drop_qua_file=false;
			for (i=0; ((unsigned)i)<dragon.data.filePathList->size(); i++) {
				string	mime_t = Qua::identifyFile(dragon.data.filePathList->at(i));
				if (mime_t.size() > 0) {
					std::cout << "drop " << dragon.data.filePathList->at(i) << ", " << mime_t << endl;
					if (mime_t == "audio/x-midi") {
						drop_midi_file = true;
						break;
					} else if (mime_t == "audio/x-wav" ||
								mime_t == "audio/x-raw" ||
								mime_t == "audio/x-aiff") {
						drop_sample_file = true;
						break;
					} else if (mime_t == "audio/x-quascript") {
						drop_qua_file = true;
						break;
					}
				} else {
//					fprintf(stderr, "dragged file %d unidentifiable\n", i);
				}
			}
			if (i == dragon.count) { // didn't find something useable in the drop
				return FALSE;
			}
			if (drop_sample_file) {
				StabEnt *s = quaLink->CreateSample("", *dragon.data.filePathList);
				quaLink->CreateInstance(s, at_channel, at_time, Time());
			} else if (drop_midi_file) {
				;
			} else if (drop_qua_file) {
				;
			} else {
				return FALSE;
			}
			return TRUE;
		}

		case QuaDrop::VSTPLUGIN: 
		case QuaDrop::VOICE: 
		case QuaDrop::SAMPLE: 
		case QuaDrop::SCHEDULABLE: {
			Time	at_time;
			short	at_channel;
			Pix2Time(point.x, at_time);
			at_channel = Pix2Channel(point.y);
			cerr << "schedulable drop " << at_channel << " chan " << at_time.StringValue() << endl;
//			int		bar, barbeat, beattick;
//			at_time.GetBBQValue(bar, barbeat, beattick);
//			fprintf(stderr, "drop schedulable %s: on point %d %d, channel %d, ticks %d t %d:%d.%d\n", dragon.data.symbol->name, point.x, point.y, at_channel, at_time.ticks, bar, barbeat, beattick);

			quaLink->CreateInstance(dragon.data.symbol, at_channel, at_time, Time::zero);
			return TRUE;
		}
			
		case QuaDrop::INSTANCE: {
			Time	at_time;
			short	at_channel;
			Pix2Time(point.x, at_time);
			at_channel = Pix2Channel(point.y);
			std::cerr << "instance drop " << at_channel << " chan " << at_time.StringValue() << endl;
			//			int		bar, barbeat, beattick;
//			at_time.GetBBQValue(bar, barbeat, beattick);
//			fprintf(stderr, "drop instance %s: on point %d %d, channel %d, ticks %d t %d:%d.%d\n", dragon.data.symbol->name, point.x, point.y, at_channel, at_time.ticks, bar, barbeat, beattick);
			Instance *i = dragon.data.symbol->InstanceValue();
			if (i != nullptr) {
				quaLink->MoveInstance(dragon.data.symbol, at_channel, at_time, i->duration);
			} else {
				std::cout << "oops bad drop ... expected an instance" << endl;
			}
			return TRUE;
		}
		case QuaDrop::APPLICATION:
		case QuaDrop::PORT:
		case QuaDrop::BUILTIN:
		case QuaDrop::TEMPLATE:
			switch (dropEffect) {
				case DROPEFFECT_COPY:
					fprintf(stderr, "left click drag: on drop copy %d %d\n", point.x, point.y);
					break;
				case DROPEFFECT_MOVE:
					fprintf(stderr, "left click drag: on drop move %d %d\n", point.x, point.y);
					break;
				case DROPEFFECT_LINK:
					fprintf(stderr, "left click drag: on drop link %d %d\n", point.x, point.y);
					break;
			}
			break;
	}
	return FALSE;
}