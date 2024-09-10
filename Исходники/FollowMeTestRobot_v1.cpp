double MyController::onAction(ActionEvent &evt)
{  
  if(first == false){
    std::string msg = "start";  
    broadcastMsg(msg);
    first = true; 
  }

    int count=0;
    double r=0.0; //2点間の直線距離
    double angle;

    if(end==false){
        if(start==true){

            Vector3d pos;
            Vector3d npos;

            if(first==false){
                FILE* fp;           
                x=0;
                y=0;
                z=0;
                w=0; //チェックポイント
      
                dx=0;
                dy=0;
                dz=0;

                if((fp = fopen("node.txt", "r")) == NULL) {
	             printf("File do not exist.\n");
	             exit(0);
                }
                while(fscanf(fp, "%lf,%lf,%lf,%lf", &x, &y, &z,&w) != EOF) {
                    temp.x[i]=x;
                    temp.y[i]=y;
                    temp.z[i]=z;
                    temp.w[i]=w;
                    i++;
                }
                fclose(fp);
                first = true;
                i=0;
            }

            if(stop==false){
                my->getPosition(pos);

                npos.x(temp.x[i]); 
                npos.y(temp.y[i]); 
                npos.z(temp.z[i]); 

                angle = rotateTowardObj(npos);   

                if(angle < 0.0){
                    angle = -1.0 * angle;
                }
 		/*ここに相当する部分を書く*/
                //my->setAxisAndAngle(0, 1.0, 0, -angle);
   	        // 回転すべき円周距離
                double distance = m_distance*PI*fabs(targetAngle)/(2*PI);
                if(targetAngle > 0.0){
                    m_my->setWheelVelocity(velocity, -velocity);
                }
                else{
                    m_my->setWheelVelocity(-velocity, velocity);
                }
                // 車輪の半径から移動速度を得る
                double vel = m_radius*velocity;
    
                // 回転時間(u秒)
                double time = (distance / vel) + evt.time();
    
                if(evt.time>=time){
		    m_my->setWheelVelocity(0, 0);
                }

                dx=(temp.x[i]-pos.x());
                dy=(temp.y[i]-pos.y());
                dz=(temp.z[i]-pos.z());

                r=sqrt(pow(dx,2)+pow(dz,2));
                //ここまでが現在地から次の座標までの距離と角度の計算

                double vel = m_radius*velocity;

                // 移動開始
                m_my->setWheelVelocity(velocity, velocity);

                // 到着時間取得
                double time2 = r / vel;

                count = 0;
                count2= 0;
                i++;
            }


            if(temp.w[i-1] == 1.0){
                std::string msg = "point1";  
                //"robot_000"にメッセージを送信します  
                sendMsg("man_001", msg); 

            }else if(temp.w[i-1] == 2.0){

                stop=true;
                broadcastMsgToSrv("elevator");

                if(elevator==true){
                   stop=false;
                }
            }
        }
    }

/***************************************************************************/
  
/*
      if(strstr(myname() , "robot_004")!= NULL){    
        m_my->setWheelVelocity(m_vel*2, m_vel*2);
      }
*/
  return 0.1;      
}  