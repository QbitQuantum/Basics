void Model::MakeRaft(GCodeState &state, float &z)
{
  vector<InFillHit> HitsBuffer;

  uint LayerNr = 0;
  float size = settings.Raft.Size;

  Vector2f raftMin =  Vector2f(Min.x - size + printOffset.x, Min.y - size + printOffset.y);
  Vector2f raftMax =  Vector2f(Max.x + size + printOffset.x, Max.y + size + printOffset.y);

  Vector2f Center = (Vector2f(Max.x + size, Max.y + size)-Vector2f(Min.x + size, Min.y + size))/2+Vector2f(printOffset.x, printOffset.y);

  float Length = sqrtf(2)*(   ((raftMax.x)>(raftMax.y)? (raftMax.x):(raftMax.y))  -  ((raftMin.x)<(raftMin.y)? (raftMin.x):(raftMin.y))  )/2.0f;	// bbox of object

  float E = 0.0f;
  float rot;

  while(LayerNr < settings.Raft.Phase[0].LayerCount + settings.Raft.Phase[1].LayerCount)
    {
      Settings::RaftSettings::PhasePropertiesType *props;
      props = LayerNr < settings.Raft.Phase[0].LayerCount ?
	&settings.Raft.Phase[0] : &settings.Raft.Phase[1];
      rot = (props->Rotation+(float)LayerNr * props->RotationPrLayer)/180.0f*M_PI;
      Vector2f InfillDirX(cosf(rot), sinf(rot));
      Vector2f InfillDirY(-InfillDirX.y, InfillDirX.x);

      Vector3f LastPosition;
      bool reverseLines = false;

      Vector2f P1, P2;
      for(float x = -Length ; x < Length ; x+=props->Distance)
	{
	  P1 = (InfillDirX *  Length)+(InfillDirY*x) + Center;
	  P2 = (InfillDirX * -Length)+(InfillDirY*x) + Center;

	  if(reverseLines)
	    {
	      Vector2f tmp = P1;
	      P1 = P2;
	      P2 = tmp;
			}

	  //			glBegin(GL_LINES);
	  //			glVertex2fv(&P1.x);
	  //			glVertex2fv(&P2.x);

	  // Crop lines to bbox*size
	  Vector3f point;
	  InFillHit hit;
	  HitsBuffer.clear();
	  Vector2f P3(raftMin.x, raftMin.y);
	  Vector2f P4(raftMin.x, raftMax.y);
	  //			glVertex2fv(&P3.x);
	  //			glVertex2fv(&P4.x);
	  if(IntersectXY(P1,P2,P3,P4,hit))	//Intersect edges of bbox
	    HitsBuffer.push_back(hit);
	  P3 = Vector2f(raftMax.x,raftMax.y);
	  //			glVertex2fv(&P3.x);
	  //			glVertex2fv(&P4.x);
	  if(IntersectXY(P1,P2,P3,P4,hit))
	    HitsBuffer.push_back(hit);
	  P4 = Vector2f(raftMax.x,raftMin.y);
	  //			glVertex2fv(&P3.x);
	  //			glVertex2fv(&P4.x);
	  if(IntersectXY(P1,P2,P3,P4,hit))
	    HitsBuffer.push_back(hit);
	  P3 = Vector2f(raftMin.x,raftMin.y);
	  //			glVertex2fv(&P3.x);
	  //			glVertex2fv(&P4.x);
	  if(IntersectXY(P1,P2,P3,P4,hit))
	    HitsBuffer.push_back(hit);
	  //			glEnd();

	  if(HitsBuffer.size() == 0)	// it can only be 2 or zero
	    continue;
	  if(HitsBuffer.size() != 2)
	    continue;

	  std::sort(HitsBuffer.begin(), HitsBuffer.end(), InFillHitCompareFunc);

	  P1 = HitsBuffer[0].p;
	  P2 = HitsBuffer[1].p;

	  state.MakeAcceleratedGCodeLine (Vector3f(P1.x,P1.y,z), Vector3f(P2.x,P2.y,z),
					  props->MaterialDistanceRatio,
					  E, z, settings.Slicing, settings.Hardware);
	  reverseLines = !reverseLines;
	}
      // Set startspeed for Z-move
      Command g;
      g.Code = SETSPEED;
      g.where = Vector3f(P2.x, P2.y, z);
      g.f=settings.Hardware.MinPrintSpeedZ;
      g.comment = "Move Z";
      g.e = E;
      gcode.commands.push_back(g);
      z += props->Thickness * settings.Hardware.LayerThickness;

      // Move Z
      g.Code = ZMOVE;
      g.where = Vector3f(P2.x, P2.y, z);
      g.f = settings.Hardware.MinPrintSpeedZ;
      g.comment = "Move Z";
      g.e = E;
      gcode.commands.push_back(g);

      LayerNr++;
    }

  // restore the E state
  Command gotoE;
  gotoE.Code = GOTO;
  gotoE.e = 0;
  gotoE.comment = _("Reset E for the remaining print");
  gcode.commands.push_back(gotoE);
}