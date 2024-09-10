Direct3DBlitter::Direct3DBlitter(VideoBufferLocker vbl, QWidget *parent) :
	BlitterWidget(vbl, "Direct3D", 2, parent),
	confWidget(new QWidget),
	adapterSelector(new QComboBox),
	vblankblit_(new QCheckBox("Wait for vertical blank"), "direct3dblitter/vblankblit", false),
	flipping_(new QCheckBox("Exclusive full screen"), "direct3dblitter/flipping", false),
	vblankflip_(new QCheckBox("Flip during vertical blank"), "direct3dblitter/vblankflip", true),
	triplebuf_(new QCheckBox("Triple buffering"), "direct3dblitter/triplebuf", false),
	bf_(new QCheckBox("Bilinear filtering"), "direct3dblitter/bf", true),
	d3d9handle(NULL),
	d3d(NULL),
	device(NULL),
	vertexBuffer(NULL),
	stexture(NULL),
	vtexture(NULL),
	lastblank(0),
	backBufferWidth(1),
	backBufferHeight(1),
	clear(0),
	dhz(600),
	swapInterval(0),
	adapterIndex(0),
	exclusive(false),
	windowed(false),
	drawn(false)
{
	setAttribute(Qt::WA_PaintOnScreen, true);

	if ((d3d9handle = LoadLibraryA("d3d9.dll"))) {
		typedef IDirect3D9* (WINAPI *Direct3DCreate9Ptr)(UINT);

		if (const Direct3DCreate9Ptr direct3DCreate9 = (Direct3DCreate9Ptr) GetProcAddress(d3d9handle, "Direct3DCreate9")) {
			if ((d3d = direct3DCreate9(D3D_SDK_VERSION))) {
				const unsigned adapterCount = d3d->GetAdapterCount();
				D3DADAPTER_IDENTIFIER9 adapterId;

				for (unsigned i = 0; i < adapterCount; ++i) {
					if (FAILED(d3d->GetAdapterIdentifier(i, 0, &adapterId)))
						break;

					adapterSelector->addItem(adapterId.Description);
				}
			}
		}
	}

	if (adapterSelector->count() < 1)
		adapterSelector->addItem(QString());

	QSettings settings;
	settings.beginGroup("direct3dblitter");

	if ((adapterIndex = settings.value("adapterIndex", adapterIndex).toUInt()) >= static_cast<unsigned>(adapterSelector->count()))
		adapterIndex = 0;

	settings.endGroup();

	{
		QVBoxLayout *mainLayout = new QVBoxLayout;
		mainLayout->setMargin(0);

		if (adapterSelector->count() > 1) {
			QHBoxLayout *const hlayout = new QHBoxLayout;
			hlayout->addWidget(new QLabel(QString(tr("Direct3D adapter:"))));
			hlayout->addWidget(adapterSelector);
			mainLayout->addLayout(hlayout);
		}

		mainLayout->addWidget(vblankblit_.checkBox());
		vblankblit_.checkBox()->setToolTip(tr("Prevents tearing. Does not work well on all systems.\n"
		                                      "Ignored when exclusive full screen or DWM composition is active."));
		mainLayout->addWidget(flipping_.checkBox());
		flipping_.checkBox()->setToolTip(tr("Grabs device for better performance when full screen."));

		{
			QHBoxLayout *const l = new QHBoxLayout;
			l->addSpacing(QApplication::style()->pixelMetric(QStyle::PM_LayoutLeftMargin));
			l->addWidget(vblankflip_.checkBox());
			vblankflip_.checkBox()->setToolTip(tr("Prevents tearing. Recommended."));
			mainLayout->addLayout(l);
		}

		mainLayout->addWidget(triplebuf_.checkBox());
		triplebuf_.checkBox()->setToolTip(tr("Attempts to improve video flow at the cost of increased latency."));
		mainLayout->addWidget(bf_.checkBox());
		confWidget->setLayout(mainLayout);
	}

	vblankflip_.checkBox()->setEnabled(flipping_.checkBox()->isChecked());
	connect(flipping_.checkBox(), SIGNAL(toggled(bool)), vblankflip_.checkBox(), SLOT(setEnabled(bool)));
	rejectSettings();
}