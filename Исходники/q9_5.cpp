Vector3d getRayColor(Vector3d p0, Vector3d ray, int rec) {

  ray.normalize();

  if (rec == 0) {
    return Vector3d(0,0,0);
  }

  // 最小のt
  double tmin = -1;
  Vector3d P, N, color;

  // レイを飛ばして球と交差するか求める
  for(int i = 0; i < sphere_n; i++) {
    double t_sphere = sphere[i].getIntersec(p0, ray);

    if( (t_sphere > 0) && (t_sphere < tmin || tmin == -1) ) { // 球との交点がある
      tmin = t_sphere;
      // ★前回の課題を参考に、球体の表面の色を計算で求め、colorVecに設定する

      double Is = 0; // 鏡面反射光
      double Id = 0; // 拡散反射光

      //
      // 拡散反射光を計算する
      //

      // 球と視点ベクトルの交点座標 P
      P = p0 + ray * t_sphere;
      // 球の中心座標 C
      Vector3d C = sphere[i].center;
      // 法線ベクトル  N = P - C
      N = P - C;
      // Nを正規化する
      N.normalize();
      // Lambertの反射(拡散反射光)
      Id = -Iin * Kd * getCos(N, lightDirection);
      Id = Id > 0 ? Id : 0;

      //
      // 鏡面反射光を計算する
      //

      // 反射光 R=2(L・N)N-L
      Vector3d R = reflect(-lightDirection, N);
      // Phongの反射(鏡面反射光)
      Is = Iin * Ks * pow2(getCos(R, ray), Ns);
      Is = Is > 0 ? Is : 0;

      double I = Id + Is + Ia;
      double r = I * sphere[i].cR;
      double g = I * sphere[i].cG;
      double b = I * sphere[i].cB;
      color.set(r,g,b);
    } 
  }

  // レイを飛ばして床と交差するか求める
  double t_board = board.getIntersec(p0, ray);

  if( (t_board > 0) && (t_board < tmin || tmin == -1) ) { // 床との交点がある
    tmin = t_board;
    // ★床の表面の色を設定する
    P = p0 + ray * t_board;
    color =  board.getColorVec(P.x, P.z);
    // ★球の影になる場合は、RGBの値をそれぞれ0.5倍する
    Vector3d ray2 = -lightDirection;
    for(int i = 0; i < sphere_n; i++) {
      double t = sphere[i].getIntersec(P, ray2);
      if(t>0) {
        color = color * 0.5;
      }
    }
    N.set(0,1,0);
  }

  if (tmin != -1) {
    return color + getRayColor(P, reflect(ray,N), rec-1) * 0.5;
  } else {
    // 何とも交差しない
    return Vector3d(0,0,0);
  }
}