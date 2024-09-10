bool CollisionModel3DImpl::collision(CollisionModel3D* other, 
                                     int AccuracyDepth, 
                                     int MaxProcessingTime,
                                     float* other_transform)
{
  m_ColType=Models;
  CollisionModel3DImpl* o=static_cast<CollisionModel3DImpl*>(other);
  if (!m_Final) throw Inconsistency();
  if (!o->m_Final) throw Inconsistency();
  Matrix3D t=( other_transform==NULL ? o->m_Transform : *((Matrix3D*)other_transform) );
  if (m_Static) t *= m_InvTransform;
  else          t *= m_Transform.Inverse();
  RotationState rs(t);

  if (AccuracyDepth<0) AccuracyDepth=0xFFFFFF;
  if (MaxProcessingTime==0) MaxProcessingTime=0xFFFFFF;
  
  DWORD EndTime,BeginTime = GetTickCount();
  int num=Max(m_Triangles.size(),o->m_Triangles.size());
  int Allocated=Max(64,(num>>4));
  std::vector<Check> checks(Allocated);
  
  int queue_idx=1;
  Check& c=checks[0];
  c.m_first=&m_Root;
  c.depth=0;
  c.m_second=&o->m_Root;
  while (queue_idx>0)
  {
    if (queue_idx>(Allocated/2)) // enlarge the queue.
    {
      Check c;
      checks.insert(checks.end(),Allocated,c);
      Allocated*=2;
    }
    EndTime=GetTickCount();
    if (EndTime >= (BeginTime+MaxProcessingTime)) throw TimeoutExpired();

    // @@@ add depth check
    //Check c=checks.back();
    Check& c=checks[--queue_idx];
    BoxTreeNode* first=c.m_first;
    BoxTreeNode* second=c.m_second;
    assert(first!=NULL);
    assert(second!=NULL);
    if (first->intersect(*second,rs))
    {
      int tnum1=first->getTrianglesNumber();
      int tnum2=second->getTrianglesNumber();
      if (tnum1>0 && tnum2>0)
      {
        {
          for(int i=0;i<tnum2;i++)
          {
            BoxedTriangle* bt2=second->getTriangle(i);
            Triangle tt(Transform(bt2->v1,rs.t),Transform(bt2->v2,rs.t),Transform(bt2->v3,rs.t));
            for(int j=0;j<tnum1;j++)
            {
              BoxedTriangle* bt1=first->getTriangle(j);
              if (tt.intersect(*bt1)) 
              {
                m_ColTri1=*bt1;
                m_iColTri1=getTriangleIndex(bt1);
                m_ColTri2=tt;
                m_iColTri2=o->getTriangleIndex(bt2);
                return true;
              }
            }
          }
        }
      }
      else
      if (first->getSonsNumber()==0)
      {
        BoxTreeNode* s1=second->getSon(0);
        BoxTreeNode* s2=second->getSon(1);
        assert(s1!=NULL);
        assert(s2!=NULL);
        
        Check& c1=checks[queue_idx++];
        c1.m_first=first;
        c1.m_second=s1;

        Check& c2=checks[queue_idx++];
        c2.m_first=first;
        c2.m_second=s2;
      }
      else
      if (second->getSonsNumber()==0)
      {
        BoxTreeNode* f1=first->getSon(0);
        BoxTreeNode* f2=first->getSon(1);
        assert(f1!=NULL);
        assert(f2!=NULL);
        
        Check& c1=checks[queue_idx++];
        c1.m_first=f1;
        c1.m_second=second;

        Check& c2=checks[queue_idx++];
        c2.m_first=f2;
        c2.m_second=second;
      }
      else
      {
        float v1=first->getVolume();
        float v2=second->getVolume();
        if (v1>v2)
        {
          BoxTreeNode* f1=first->getSon(0);
          BoxTreeNode* f2=first->getSon(1);
          assert(f1!=NULL);
          assert(f2!=NULL);

          Check& c1=checks[queue_idx++];
          c1.m_first=f1;
          c1.m_second=second;

          Check& c2=checks[queue_idx++];
          c2.m_first=f2;
          c2.m_second=second;
        }
        else
        {
          BoxTreeNode* s1=second->getSon(0);
          BoxTreeNode* s2=second->getSon(1);
          assert(s1!=NULL);
          assert(s2!=NULL);

          Check& c1=checks[queue_idx++];
          c1.m_first=first;
          c1.m_second=s1;

          Check& c2=checks[queue_idx++];
          c2.m_first=first;
          c2.m_second=s2;
        }
      }
    }
  }
  return false;
}