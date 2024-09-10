void BaseScene::electricBallAreaEffect(){
	auto balls = SceneDesigner::balls;
	for (int i = 0; i < int(balls->size()); i++){
		if (balls->at(i)->type == b_electricballball_small || balls->at(i)->type == b_electricball_mid){
			auto e_ball = balls->at(i);
			for (int j = 0; j < int(balls->size()); j++){
				auto ball = balls->at(j);
				if (e_ball != ball){

					float distanceSquar = e_ball->getSprite()->getPosition().distanceSquared(ball->getSprite()->getPosition());

					float forceValue = e_ball->effectRadius *RTM_RATIO * RTM_RATIO * e_ball->effectRadius / distanceSquar;

					if (forceValue >= 1){ //  进入作用域

						forceValue = forceValue * 0.3; // 作用域最远处，加速度为0.3
						// 吸引的方向
						Vec2 direction = e_ball->getSprite()->getPosition() - ball->getSprite()->getPosition();
						if (direction == Vec2(0, 0)) continue;
						direction = direction / direction.distance(Vec2::ZERO);
						// 吸引电球和铁球
						if (ball->type == b_ironball_mid || ball->type == b_ironball_small ||
							ball->type == b_electricballball_small || ball->type == b_electricball_mid){
							ball->applyForce(forceValue * direction, true);
							e_ball->applyForce(-forceValue * direction, true);
						}
						// 排斥其他球
						else{
							direction *= -1;
							ball->applyForce(forceValue * direction, true);
							e_ball->applyForce(-forceValue * direction, true);
						}
					}
				}
			}
		}
	}
}