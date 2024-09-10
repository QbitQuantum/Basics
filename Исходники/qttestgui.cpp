QtTestGui::QtTestGui(QWidget *parent)
	: QMainWindow(parent), trayIcon(this), stopD3d(false){
	ui.setupUi(this);

	this->trayIcon.setToolTip("Click me!");

	Qt::WindowFlags flags = this->windowFlags();
	this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
	this->setAttribute(Qt::WidgetAttribute::WA_PaintOnScreen);

	connect(&this->trayIcon, &QSystemTrayIcon::activated, this, &QtTestGui::TrayActivated);


	HRESULT hr = S_OK;
	D3D_FEATURE_LEVEL levels[] = {
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_9_1
	};

	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevTmp;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dCtxTmp;

	uint32_t dxDevFlags = D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	dxDevFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::lock_guard<std::mutex> lk(this->d3dMtx);

	hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr, dxDevFlags,
		levels, sizeof(levels) / sizeof(levels[0]),
		D3D11_SDK_VERSION,
		d3dDevTmp.GetAddressOf(), &this->d3dLevel, d3dCtxTmp.GetAddressOf());

	hr = d3dDevTmp.As(&this->d3dDev);
	hr = d3dCtxTmp.As(&this->d3dCtx);

	this->TestTextureTypes();
	this->CreateGeometry();
	this->CreateShaders();
	this->CreateSampler();

	this->UpdateProjection();

	this->d3dThread = std::thread([=](){
		this->RenderD3d();
	});
}