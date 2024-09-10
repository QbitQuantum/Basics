void WaitWidget::setupScene()
{
	// Creamos el objeto efecto
	d->m_effect = new QGraphicsOpacityEffect;
	d->m_effect->setOpacity(0);
	d->m_effect->setEnabled(true);

	// Ahora creamos los proxys para gráficos que nos permita incluirlos en la escena
	QGraphicsProxyWidget *pFrame = d->m_scene.addWidget(d->m_widget);
	pFrame->resize(d->m_widget->width(), d->m_widget->height());

	// Y lo agregamos a un layout gráfico
	QGraphicsLinearLayout *gLayout = new QGraphicsLinearLayout;
	gLayout->setOrientation(Qt::Vertical);
	gLayout->addItem(pFrame);

	// Creamos finalmente un objeto gráfico que lo contiene todo, y lo agregamos a la escena
	QGraphicsWidget *form = new QGraphicsWidget;
	form->setLayout(gLayout);
	form->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	d->m_scene.addItem(form);

	// Agregamos el efecto de opacidad al aparecer
	form->setGraphicsEffect(d->m_effect);
	form->resize(d->m_widget->width(), d->m_widget->height());
}