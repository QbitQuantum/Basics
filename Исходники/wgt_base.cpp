void wgt_base::connect_to_signal_mapper(QPushButton *button, int i, QSignalMapper *signalMapper)
{
	signalMapper->setMapping(button, i);
	connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
}