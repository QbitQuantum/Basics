// 初始化语音识别
HRESULT ThisApp::init_speech_recognizer(){
    HRESULT hr = S_OK;
    // 创建语音输入流
    if (SUCCEEDED(hr)){
        hr = CoCreateInstance(CLSID_SpStream, nullptr, CLSCTX_INPROC_SERVER, __uuidof(ISpStream), (void**)&m_pSpeechStream);;
    }
    // 与我们的Kinect语音输入相连接
    if (SUCCEEDED(hr)){
        WAVEFORMATEX wft = {
            WAVE_FORMAT_PCM, // PCM编码
            1, // 单声道
            16000,  // 采样率为16KHz
            32000, // 每分钟数据流 = 采样率 * 对齐
            2, // 对齐 : 单声道 * 样本深度 = 2byte
            16, // 样本深度 16BIT
            0 // 额外数据
        };
        // 设置状态
        hr = m_pSpeechStream->SetBaseStream(m_p16BitPCMAudioStream, SPDFID_WaveFormatEx, &wft);
    }
    // 创建语音识别对象
    if (SUCCEEDED(hr)){
        ISpObjectToken *pEngineToken = nullptr;
        // 创建语言识别器
        hr = CoCreateInstance(CLSID_SpInprocRecognizer, nullptr, CLSCTX_INPROC_SERVER, __uuidof(ISpRecognizer), (void**)&m_pSpeechRecognizer);
        if (SUCCEEDED(hr)) {
            // 连接我们创建的语音输入流对象
            m_pSpeechRecognizer->SetInput(m_pSpeechStream, TRUE);
            // 创建待识别语言 这里选择大陆汉语(zh-cn) 
            // 目前没有Kinect的汉语语音识别包 有的话可以设置"language=804;Kinect=Ture"
            hr = SpFindBestToken(SPCAT_RECOGNIZERS, L"Language=804", nullptr, &pEngineToken);
            if (SUCCEEDED(hr)) {
                // 设置待识别语言
                m_pSpeechRecognizer->SetRecognizer(pEngineToken);
                // 创建语音识别上下文
                hr = m_pSpeechRecognizer->CreateRecoContext(&m_pSpeechContext);
                // 适应性 ON! 防止因长时间的处理而导致识别能力的退化
                if (SUCCEEDED(hr))  {
                    hr = m_pSpeechRecognizer->SetPropertyNum(L"AdaptationOn", 0);
                }
            }
        }
        SafeRelease(pEngineToken);
    }
    // 创建语法
    if (SUCCEEDED(hr)){
        hr = m_pSpeechContext->CreateGrammar(1, &m_pSpeechGrammar);
    }
    // 加载静态SRGS语法文件
    if (SUCCEEDED(hr)){
        hr = m_pSpeechGrammar->LoadCmdFromFile(s_GrammarFileName, SPLO_STATIC);
    }
    // 激活语法规则
    if (SUCCEEDED(hr)){
        hr = m_pSpeechGrammar->SetRuleState(nullptr, nullptr, SPRS_ACTIVE);
    }
    // 设置识别器一直读取数据
    if (SUCCEEDED(hr)){
        hr = m_pSpeechRecognizer->SetRecoState(SPRST_ACTIVE_ALWAYS);
    }
    // 设置对识别事件感兴趣
    if (SUCCEEDED(hr)){
        hr = m_pSpeechContext->SetInterest(SPFEI(SPEI_RECOGNITION), SPFEI(SPEI_RECOGNITION));
    }
    // 保证语音识别处于激活状态
    if (SUCCEEDED(hr)){
        hr = m_pSpeechContext->Resume(0);
    }
    // 获取识别事件
    if (SUCCEEDED(hr)){
        m_p16BitPCMAudioStream->SetSpeechState(TRUE);
        m_hSpeechEvent = m_pSpeechContext->GetNotifyEventHandle();
		printf_s("init_speech_recognizer succeeded\n");
    }
#ifdef _DEBUG
    else
        printf_s("init_speech_recognizer failed\n");
#endif
    return hr;
}