    inline void cut(Eigen::PlainObjectBase<DerivedO> &Handle_Seams)
    {
      F_visited.setConstant(F.rows(),0);
      Handle_Seams.setConstant(F.rows(),3,1);

      int index=0;
      for (unsigned f = 0; f<F.rows(); f++)
      {
        if (!F_visited(f))
        {
          index++;
          FloodFill(f, Handle_Seams);
        }
      }

      Retract(Handle_Seams);

      for (unsigned int f=0;f<F.rows();f++)
        for (int j=0;j<3;j++)
          if (IsRotSeam(f,j))
            Handle_Seams(f,j)=true;

    }