bool DrawableFactory::addTextFromCSV(const std::string& filename, Resources& res, Scene* scene)
{
    // Fontリソースの読み込み
    FontResourceManager& fr = res.fonts();

    // CSVデータ読み込み
    CSVData data;
    DrawableFactory::loadCSV(filename, data);

    // データを読み出して登録する
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        auto b = (*it);
        // エラー処理
        if (b.size() != 11) {
            printf("Text: ファイルフォーマットエラー\n");
            return false;
        }
        // データの格納
        std::string drawKey(b[0]);
        std::string text(b[2]);
        std::string fontKey(b[8]);
        int layer = std::atoi(b[1].c_str());
        int x =     std::atoi(b[3].c_str());
        int y =     std::atoi(b[4].c_str());
        int red =   std::atoi(b[5].c_str());
        int green = std::atoi(b[6].c_str());
        int blue =  std::atoi(b[7].c_str());
        int alpha = std::atoi(b[9].c_str());
        bool isVisible = (b[10] == "true") ? true : false;

        // エラー処理
        if (b[0] == "" ||
            b[1] == "" ||
            b[8] == "") {
            printf("Text: 未入力が存在します。\n");
            return false;
        }

        // 初期値の処理
        if (b[9] == "") alpha = 255;

        // 生成
        DrawableText* d = new DrawableText();
        d->setFontHandle(fr.get(fontKey));
        d->setPosition(x, y);
        d->setText(text);
        d->setTextColor(red, green, blue);
        d->setAlpha(alpha);
        d->setIsVisible(isVisible);
        scene->addDrawable(drawKey, d, layer);
    
        printf("$$$ Text loaded: %s\n", drawKey.c_str());
    }
    return true;
}