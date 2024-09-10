StatsRenderer::StatsRenderer(MPEVRCustomPresenter* presenter, IDirect3DDevice9* device):
  m_pPresenter(presenter),
  m_pD3DDev(device),
  m_pD3DXCreateLine(NULL),
  m_pD3DXCreateFont(NULL),
  m_pD3DXCreateSprite(NULL),
  m_hD3DX9Dll(NULL),
  m_pFont(NULL),
  m_pSprite(NULL),
  m_pLine(NULL)
{
  HINSTANCE hDll;
  hDll = GetD3X9Dll();
  if(hDll)
  {
    (FARPROC&)m_pD3DXCreateLine    = GetProcAddress(hDll, "D3DXCreateLine");
    (FARPROC&)m_pD3DXCreateFont    = GetProcAddress(hDll, "D3DXCreateFontW");
    (FARPROC&)m_pD3DXCreateSprite = GetProcAddress(hDll, "D3DXCreateSprite");    
  }

  if (m_pD3DXCreateSprite)
  {
    m_pD3DXCreateSprite( m_pD3DDev, &m_pSprite);
  }

  if (m_pD3DXCreateLine)
  {
    m_pD3DXCreateLine(m_pD3DDev, &m_pLine);
  }

	PDH_STATUS pdhStatus;

	PdhOpenQuery(NULL, NULL, &m_cpuQuery);
	pdhStatus = PdhAddEnglishCounter(m_cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &m_cpuTotal);
	if (pdhStatus == ERROR_SUCCESS)
	{
		PdhCollectQueryData(m_cpuQuery);
	}

	m_counter = 20;
}