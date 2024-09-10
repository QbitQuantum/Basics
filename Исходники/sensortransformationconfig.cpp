/** Create a variant editor for a parameter
 * @brief SensorTransformationConfig::createSensorWidget
 * @param parent
 * @param param
 * @param paramIndex
 * @return a widget containing the editor and a description label
 */
QWidget *SensorTransformationConfig::createSensorWidget(QWidget *parent, const TransformationBaseClass::ParameterDescription &param, int paramIndex)
{
    QFrame * frame = new QFrame(parent);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Plain);
    frame->setFrameStyle(1);
    QHBoxLayout *layout = new QHBoxLayout(frame);
    frame->setLayout(layout);
    QLabel *name = new QLabel(param.name + " : ", frame);
    QLabel *description = new QLabel(param.description, frame);
    description->setWordWrap(true);

    QVector<QVariant> trParams;
    if(m_transformationList[m_currentIndex]){
        trParams = m_transformationList[m_currentIndex]->getParameters();
    }

    QWidget *editor;
    if(param.typeAndDefault.type() == QVariant::String){
        QPlainTextEdit *editor2 = new QPlainTextEdit(param.typeAndDefault.toString(), frame);
        connect(editor2, SIGNAL(textChanged()), this, SLOT(on_textEditorChange()));
        editor = editor2;
    }else if(param.typeAndDefault.type() == QVariant::Double){
        QDoubleSpinBox *editor2 = new QDoubleSpinBox(frame);
        editor2->setMaximum(9999999999);
        editor2->setMinimum(-9999999999);
        editor2->setValue(trParams[paramIndex].toDouble());
        connect(editor2, SIGNAL(valueChanged(double)), this, SLOT(on_doubleEditorChange(double)));
        editor = editor2;
    }else if(param.typeAndDefault.type() == QVariant::Int){