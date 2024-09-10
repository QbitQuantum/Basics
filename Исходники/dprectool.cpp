bool convertRecording(const QString &inputfilename, const QString &outputfilename, const QString &outputFormat)
{
	// Open input file
	Reader reader(inputfilename);
	Compatibility compat = reader.open();

	switch(compat) {
	case INCOMPATIBLE:
		fprintf(
			stderr,
			"This recording is incompatible (format version %s). It was made with Drawpile version %s.\n",
			qPrintable(reader.formatVersion().asString()),
			qPrintable(reader.writerVersion())
		);
		return false;
	case NOT_DPREC:
		fprintf(stderr, "Input file is not a Drawpile recording!\n");
		return false;
	case CANNOT_READ:
		fprintf(stderr, "Unable to read input file: %s\n", reader.errorString().toLocal8Bit().constData());
		return false;

	case COMPATIBLE:
	case MINOR_INCOMPATIBILITY:
	case UNKNOWN_COMPATIBILITY:
		// OK to proceed
		break;
	}

	// Open output file (stdout if no filename given)
	QScopedPointer<Writer> writer;
	if(outputfilename.isEmpty()) {
		// No output filename given? Write to stdout
		QFile *out = new QFile();
		out->open(stdout, QFile::WriteOnly);
		writer.reset(new Writer(out));
		out->setParent(writer.data());

		writer->setEncoding(Writer::Encoding::Text);

	} else {
		writer.reset(new Writer(outputfilename));
	}

	// Output format override
	if(outputFormat == "text")
		writer->setEncoding(Writer::Encoding::Text);
	else if(outputFormat == "binary")
		writer->setEncoding(Writer::Encoding::Binary);
	else if(!outputFormat.isEmpty()) {
		fprintf(stderr, "Invalid output format: %s\n", qPrintable(outputFormat));
		return false;
	}

	// Convert input to output
	if(!writer->open()) {
		fprintf(stderr, "Couldn't open %s: %s\n",
			outputfilename.toLocal8Bit().constData(),
			writer->errorString().toLocal8Bit().constData()
			);
		return false;
	}
	if(!writer->writeHeader()) {
		fprintf(stderr, "Error while writing header: %s\n",
			writer->errorString().toLocal8Bit().constData()
			);
		return false;
	}

	bool notEof = true;
	do {
		MessageRecord mr = reader.readNext();
		switch(mr.status) {
		case MessageRecord::OK:

			if(!writer->writeMessage(*mr.message)) {
				fprintf(stderr, "Error while writing message: %s\n",
					writer->errorString().toLocal8Bit().constData()
					);
				return false;
			}
			delete mr.message;
			break;

		case MessageRecord::INVALID:
			writer->writeComment(QStringLiteral("WARNING: Unrecognized message type %1 of length %2 at offset 0x%3")
				.arg(int(mr.error.type))
				.arg(mr.error.len)
				.arg(reader.currentPosition())
				);
			break;

		case MessageRecord::END_OF_RECORDING:
			notEof = false;
			break;
		}
	} while(notEof);

	return true;
}