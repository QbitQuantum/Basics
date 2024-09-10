void cShoot::MoveUp(vector<cBicho> *caixes, vector< vector<int> > &map, cBicho &terra, cSound &Sound,int &rebots)
{
                double xaux, zaux, yaux;
                float x,y,z;
                //float rot;
                //rot = GetRot();
                GetPosition(&x,&y,&z);
                xaux=x;
                zaux=z;
                yaux=y;
                int tx,ty;
                GetTile(&tx,&ty);
                //x-=iner*sin(rot*PI/180);
                //z-=iner*cos(rot*PI/180);
                x+=-cos(PI/180*rotV)*sin(PI/180*rot)*iner;
                z+=-cos(PI/180*rotV)*cos(PI/180*rot)*iner;
                if(y<0)y=0;
                int suelo;
                
                //y+=sin(PI/180*rotV)*iner;
                suelo = ((int)floor(y))/4;
				//y-=0.01;
                SetPosition(x,y,z);
                cRect rect;
                bool b=false;
                bool desliza_z=true;
                bool desliza_x=true;
                bool desliza_y=true;
                //if(suelo>1)suelo=1;
                //caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                terra.GetArea(&rect);
                /*if(Collides(&rect)) {
                        y=0;
                        rotV -= 2*rotV;
                }*/
                /*int i=0;
                int j=0;
                                if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0 || map[suelo+1][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
                                        caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                        if(!Collides(&rect)) {
                                                //y+=sin(PI/180*rotV)*iner;
                                                
                                                suelo = ((int)floor(y))/4;
                                                caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                                if(Collides(&rect)) {
                                                        if(rotV >=0 && rotV <= 90) {
                                                                //double rotaux = 90.0 - (rot);
                                                                rotV -= 2*rotV;
                                                                //rot = 360-(rot);
                                                                //rot = fmod(rot,360);

                                                        }
                                                        else if(rotV >=-90 && rotV < 0) {
                                                                //double rotaux = (rot-90);
                                                                //double rotaux2 = 90-rotaux;
                                                                rotV -= 2*rotV;
                                                        }
                                                        b = true;
                                                        y=yaux;
                                                        SetPosition(x,y,z);
                                                }
                                        }
                                }*/
                
                b=false;
                suelo = ((int)floor(y))/4;
                for(int i=-1;i<=1 && !b;++i) {
                    for(int j=-1;j<=1 && !b;++j) {
                            //if(!(i==0 && j==0)) {
                        if(map[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)]!=0) {
                            caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                            if(Collides(&rect)) {
                                z = zaux;
                                //y = yaux;
                                SetPosition(x,y,z);
                                b = true;
                                for(int i=-1;i<=1;++i) {
                                    for(int j=-1;j<=1;++j) {
                                        caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                        if(Collides(&rect)) {
                                            x = xaux;
                                            //y = yaux;
                                            desliza_x = false;
                                            //z-=0.1*cos(rot*PI/180);
                                            z+=-sin(PI/180*rotV)*cos(PI/180*rot)*iner;
                                            SetPosition(x,y,z);
                                            for(int i=-1;i<=1;++i) {
                                                for(int j=-1;j<=1;++j) {
                                                    caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                                                    if(Collides(&rect)) {
                                                        z = zaux;
                                                        //y = yaux;
                                                        desliza_z = false;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if(b) {
                        if(desliza_x) {
                                if(rot >=0 && rot < 90) {
                                        double rotaux = 90.0 - (rot);
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);

                                }
                                else if(rot >=90 && rot < 180) {
                                        double rotaux = (rot-90);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
                                else if(rot >=180 && rot < 270) {
                                        double rotaux =  90 - (rot - 180);
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
                                else if(rot >=270 && rot < 360) {
                                        double rotaux = (rot-270);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
                        }
                        else if(desliza_z) {
                                if(rot >=0 && rot < 90) {
                                        double rotaux = 90.0 - (rot);
                                        rot += 180 + 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);
										rebots++;

                                }
                                else if(rot >=90 && rot < 180) {
                                        double rotaux = 90.0 - (rot-90);
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
                                }
                                else if(rot >=180 && rot < 270) {
                                        double rotaux =  (rot - 180);
                                        //double rotaux2 = 90-rotaux;
                                        rot -= 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
                                else if(rot >=270 && rot < 360) {
                                        double rotaux = 90.0 - (rot-90);
                                        //double rotaux2 = 90-rotaux;
                                        rot += 2*rotaux;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
                        }
                }
                SetPosition(x,y,z);
                rot = fmod(rot,360);
                //SetRot(rot);
                /*for(unsigned int i=1;i<=4;++i) {
                        caixes[tx*SCENE_WIDTH+ty+i].GetArea(&rect);
                        if(Collides(&rect)) {
                                x = xaux;
                                z = zaux;
                        }
                }*/
                y+=sin(PI/180*rotV)*iner;
                SetPosition(x,y,z);
            if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] == 0) {
                    //y+=sin(PI/180*rotV)*iner;
                for(int i=-1;i<=1 && !b;++i) {
					for(int j=-1;j<=1 && !b;++j) {
						caixes[suelo+1][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
						if(Collides(&rect)) {
							b = true;
							if(rotV >=0 && rotV <= 90) {
									//double rotaux = 90.0 - (rot);
									rotV -= 2*rotV;
									Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
									rebots++;
									//rot = 360-(rot);
									//rot = fmod(rot,360);

							}
							else if(rotV >=-90 && rotV < 0) {
									//double rotaux = (rot-90);
									//double rotaux2 = 90-rotaux;
									rotV -= 2*rotV;
									Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
									rebots++;
							}
							y = yaux;
							SetPosition(x,y,z);
						}
					}
				}
            }
                        //if(!b) {
                                //if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] == 0) {
				//y = yaux;
				//y+=sin(PI/180*rotV)*iner;
                //SetPosition(x,y,z);
                b=false;
                suelo--;
                if(suelo<0)suelo=0;
                for(int i=-1;i<=1 && !b;++i) {
                    for(int j=-1;j<=1 && !b;++j) {
                        if(map[suelo][(ty)*SCENE_DEPTH+ (tx)] != 0) {
                            caixes[suelo][(ty+i)*SCENE_DEPTH+ (tx+j)].GetArea(&rect);
                            if(Collides(&rect)) {
                                b = true;
                                if(rotV >=0 && rotV <= 90) {
                                        //double rotaux = 90.0 - (rot);
                                        rotV -= 2*rotV;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                        //rot = 360-(rot);
                                        //rot = fmod(rot,360);

                                }
                                else if(rotV >=-90 && rotV < 0) {
                                        //double rotaux = (rot-90);
                                        //double rotaux2 = 90-rotaux;
										
                                        rotV -= 2*rotV;
										Sound.PlaySoundW("resources/music/ricochet.ogg",false,0.2);
										rebots++;
                                }
								//if(yaux<rect.ymax)
									y=rect.ymax;
								//else
									//y = yaux;
                                SetPosition(x,y,z);
                            }
                        }
                    }
                //}
        //}
                }


}