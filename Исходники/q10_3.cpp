// 布の形状の更新
void updateCloth(void) {
  // ★次の手順で質点の位置を決定する
  // 1. 質点に働く力を求める
  // 2. 質点の加速度を求める
  // 3. 質点の速度を更新する
  // 4. 質点の位置を更新する

  //1-1. 質点に働く力をリセット
  for(int y = 0; y < POINT_NUM; y++) {
    for(int x = 0; x < POINT_NUM; x++) {
      cloth->points[x][y].f.set(0, 0, 0);
    }
  }

  //1-2. バネの両端の質点に力を働かせる
  // 全てのバネについての処理
  for(int i = 0; i < cloth->springs.size(); i++) {
    // clothオブジェクトの i 番目のバネを取得
    Spring *spring = cloth->springs[i];

    // i 番目のバネの自然長（spring->restLength）と、
		// 現在の長さ（計算で求める）の差分を求める
    double d = spring->restLength - spring->length();

    // 上記の値に、バネ定数 Ks を掛けた値がバネが質点に加える力
    // ただし、力には向きがあるので、大きさだけではなく、方向の情報も必要
    Vector3d Fs = (spring->p0->p - spring->p1->p).normalize() * d * Ks;

    // 両端の質点に対して、力ベクトルを加算する
    // バネの一方の質点に働く力(spring->p0->f)に加算（向きに注意）
    // バネのもう一方の質点に加わる力(spring->p1->f)に加算（向きに注意）
    spring->p0->f += Fs;
    spring->p1->f -= Fs;
  }

  //1-3. 重力、空気抵抗による力を加算する
  // 全ての質点に対する処理
  for(int y = 0; y < POINT_NUM; y++) {
    for(int x = 0; x < POINT_NUM; x++) {
      // cloth->points[x][y].f に、重力、空気抵抗による力を加算する
      Point *p = &(cloth->points[x][y]);
      p->f += gravity * Mass - p->v * Dk;
    }
  }

  // 全ての質点に対する処理
  for(int y = 0; y < POINT_NUM; y++) {
    for(int x = 0; x < POINT_NUM; x++) {
      Point *p = &(cloth->points[x][y]);
      // 2. 質点の加速度ベクトルを計算 (力ベクトル cloth->points[x][y].f を質量で割った値)
      // 3. 質点の速度ベクトル(cloth->points[x][y].v) を更新
      p->v += p->f * (dT/Mass);
      // 4. 質点の位置ベクトル (cloth->points[x][y].p) を更新
      if (!p->bFixed) {
        p->p += p->v * dT;
        // オプション. 球体の内部に入るようなら、強制的に外に移動させる
        Vector3d C(0, 0, -POINT_NUM / 2);// 球体の中心
        Vector3d r = p->p - C;
        if (r.length() < 8) {
          p->p = C + r.normalize() * 8.1;
          p->v.set(0,0,0);
        }
      }
    }
  }
}