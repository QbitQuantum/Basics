		return "?";
	return QString::number(width) + "x" + QString::number(height);
}

class QTextEditSmall : public QTextEdit {

public:
	QTextEditSmall(QWidget *parent) : QTextEdit(parent) {}
	QTextEditSmall(const QString& text, QWidget *parent) : QTextEdit(text, parent) {}
	virtual QSize sizeHint() const override { return QSize(-1, 100); }

};

// sound notification sequences
static const std::array<SimpleSynth::Note, 1> SEQUENCE_RECORD_START = {{
	{0    , 500, 10000, 440.0f * exp2f( 3.0f / 12.0f), 0.8f}, // C5
}};
static const std::array<SimpleSynth::Note, 2> SEQUENCE_RECORD_STOP = {{
	{0    , 500, 20000, 440.0f * exp2f( 3.0f / 12.0f), 0.8f}, // C5
	{10000, 500, 20000, 440.0f * exp2f(-2.0f / 12.0f), 0.8f}, // G4
}};
static const std::array<SimpleSynth::Note, 4> SEQUENCE_RECORD_ERROR = {{
	{0    , 500, 20000, 440.0f * exp2f(-2.0f / 12.0f), 0.8f}, // G4
	{10000, 500, 20000, 440.0f * exp2f(-2.0f / 12.0f), 0.8f}, // G4
	{20000, 500, 20000, 440.0f * exp2f(-6.0f / 12.0f), 0.4f}, // D#4
	{20000, 500, 20000, 440.0f * exp2f(-9.0f / 12.0f), 0.6f}, // C4
}};

const int PageRecord::PRIORITY_RECORD = 0;
const int PageRecord::PRIORITY_PREVIEW = -1;
