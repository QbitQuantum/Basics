void TextureTestApp::draw()
{
	gl::clear(Color(0.2f, 0.2f, 0.2f));

  // カメラの状態から行列を作成
  // 視点座標変換用と正規化デバイス座標変換用の２つを用意する
  gl::setMatrices(camera);

  // ライティング開始
  light->enable();

  // ローカル→ワールド変換行列を用意
  gl::scale(100.0, 100.0, 100.0);
  gl::rotate(Vec3f(rx, ry, rz));

  // テクスチャを拘束
  image.bind();

  // ポリゴンを描画
  gl::draw(mesh);

  // 拘束を解除
  image.unbind();
}