	//グラフィックハンドルを削除する
	static void Delete(std::string FileName){DeleteGraph(getInstance().GrHwnd[FileName]);getInstance().GrHwnd.erase(FileName);};