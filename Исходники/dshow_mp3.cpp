void  main()
{
	// DirectShowのインスタンス宣言
	IGraphBuilder *p_graph=NULL;
	IMediaControl *p_control=NULL;
	IMediaEvent   *p_event=NULL;

	HRESULT hr;   // 処理結果

	long event_code;   // イベントコード

	// COMライブラリの初期化
	hr=CoInitialize(NULL);

	// フィルタグラフのインスタンスを生成
	hr=CoCreateInstance(
			CLSID_FilterGraph,	  // フィルタグラフのクラスID
			NULL,				// 非アグリゲートオブジェクト
			CLSCTX_INPROC_SERVER,   // 呼び出し側と同じプロセスで実行
			IID_IGraphBuilder,	  // グラフビルダでオブジェクト間通信する
			(void **)&p_graph);	 // インスタンスを入れるポインタ

	// フィルタグラフからIMediaControlを取得する
	hr=p_graph->QueryInterface(
			IID_IMediaControl,	  //IMediaControlのインターフェース指定
			(void **)&p_control);   //IMediaControlを入れるポインタ

	// フィルタグラフからIMediaEventを取得する
	hr=p_graph->QueryInterface(
			IID_IMediaEvent,		//IMediaEventのインターフェース指定
			(void **)&p_event);	 //IMediaEventを入れるポインタ

	// 再生するファイルを指定する
	hr=p_graph->RenderFile(
			L"C:\\workdir\\testh.mp3",  // メディアファイル名
			NULL);								// 予約(NULL固定)

	// ファイルのレンダリングに成功したらグラフを実行する
	if(SUCCEEDED(hr))
	{
	  // グラフを実行する
	  hr=p_control->Run();

	 if( hr == S_OK )
	  {
		// グラフの実行に成功したら完了するまでイベントを待つ
		p_event->WaitForCompletion(
			INFINITE,				 // イベントタイマー(無期限)
			&event_code);			 // イベント結果コード
	  }
	}

	// IMediaControlを開放する
	p_control->Release();

	// IMediaEventを開放する
	p_event->Release();

	// フィルタグラフを開放する
	p_graph->Release();

	// COMライブラリを開放する
	CoUninitialize();
}