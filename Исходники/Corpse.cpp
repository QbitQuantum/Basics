		void Corpse::Update(float dt) {
			SPADES_MARK_FUNCTION();
			float damp = 1.f;
            float damp2 = 1.f;
			if(dt > 0.f){
				damp = powf(.9f, dt);
				damp2 = powf(.371f, dt);
            }
			//dt *= 0.1f;
			
			for(int i = 0; i <NodeCount; i++){
				Node& node = nodes[i];
				Vector3 oldPos = node.lastPos;
				node.pos += node.vel * dt;
				
				SPAssert(!isnan(node.pos.x));
				SPAssert(!isnan(node.pos.y));
				SPAssert(!isnan(node.pos.z));
				
				if(node.pos.z > 63.f){
					node.vel.z -= dt * 6.f; // buoyancy
					node.vel *= damp;
				}else{
                    node.vel.z += dt * 32.f; // gravity
                    node.vel.z *= damp2;
                }
				
				//node.vel *= damp;
				
				if(!map->ClipBox(oldPos.x, oldPos.y, oldPos.z)){
					
					if(map->ClipBox(node.pos.x,
									oldPos.y,
									oldPos.z)){
						node.vel.x = -node.vel.x * .2f;
						if(fabsf(node.vel.x) < .3f)
							node.vel.x = 0.f;
						node.pos.x = oldPos.x;
						
						node.vel.y *= .5f;
						node.vel.z *= .5f;
					}
					
					if(map->ClipBox(node.pos.x,
									node.pos.y,
									oldPos.z)){
						node.vel.y = -node.vel.y * .2f;
						if(fabsf(node.vel.y) < .3f)
							node.vel.y = 0.f;
						node.pos.y = oldPos.y;
						
						node.vel.x *= .5f;
						node.vel.z *= .5f;
					}
					
					if(map->ClipBox(node.pos.x,
									node.pos.y,
									node.pos.z)){
						node.vel.z = -node.vel.z * .2f;
						if(fabsf(node.vel.z) < .3f)
							node.vel.z = 0.f;
						node.pos.z = oldPos.z;
						
						node.vel.x *= .5f;
						node.vel.y *= .5f;
					}
					
					if(map->ClipBox(node.pos.x, node.pos.y, node.pos.z)){
						// TODO: getting out block
						//node.pos = oldPos;
						//node.vel *= .5f;
					}
				}
				
				/*
				if(map->ClipBox(node.pos.x,
								node.pos.y,
								node.pos.z)){
					if(!map->ClipBox(node.pos.x,
									node.pos.y,
									oldPos.z)){
						node.vel.z = -node.vel.z * .2f;
						if(fabsf(node.vel.z) < .3f)
							node.vel.z = 0.f;
						node.pos.z = oldPos.z;
					}
					if(!map->ClipBox(node.pos.x,
									 oldPos.y,
									 node.pos.z)){
						node.vel.y = -node.vel.y * .2f;
						if(fabsf(node.vel.y) < .3f)
							node.vel.y = 0.f;
						node.pos.y = oldPos.y;
					}
					if(!map->ClipBox(oldPos.x,
									 node.pos.y,
									 node.pos.z)){
						node.vel.x = -node.vel.x * .2f;
						if(fabsf(node.vel.x) < .3f)
							node.vel.x = 0.f;
						node.pos.x = oldPos.x;
					}
					node.vel *= .8f;
					//node.pos = oldPos;
					
					if(node.vel.GetLength() < .02f){
						node.vel *= 0.f;
					}
				}*/
				
				node.lastPos = node.pos;
				node.lastForce = node.vel;
			}
			ApplyConstraint(dt);
			
			for(int i = 0; i <NodeCount; i++){
				nodes[i].lastForce = nodes[i].vel - nodes[i].lastForce;
			}
			
		}