	void PlayerBehavior::MovePlayer() {
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 Angle = GetMoveVector();
		//Rigidbodyを取り出す
		auto PtrRedit = GetGameObject()->GetComponent<Rigidbody>();
		auto Velo = PtrRedit->GetVelocity();
		if (Angle.length() <= 0.0f && Velo.y == 0.0f) {
			//コントローラを離したとき対策
			Velo *= GetDecel();
			PtrRedit->SetVelocity(Velo);
			return;
		}
		//Transform
		auto PtrTransform = GetGameObject()->GetComponent<Transform>();
		//現在の速度を取り出す
		//目的地を最高速度を掛けて求める
		auto Target = Angle * GetMaxSpeed();
		//目的地に向かうために力のかける方向を計算する
		//Forceはフォースである
		auto Force = Target - Velo;
		//yは0にする
		Force.y = 0;
		//加速度を求める
		auto Accel = Force / GetMass();
		//ターン時間を掛けたものを速度に加算する
		Velo += (Accel * ElapsedTime);
		//速度を設定する
		PtrRedit->SetVelocity(Velo);
		//回転の計算
		if (Angle.length() > 0.0f) {
			auto UtilPtr = GetGameObject()->GetBehavior<UtilBehavior>();
			UtilPtr->RotToHead(Angle, 1.0f);
		}
	}