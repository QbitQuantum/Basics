void Unreal3DExport::WriteTracking()
{
    Tab<Point3> Loc;
    Tab<Quat> Quat;
    Tab<Point3> Euler;

    Loc.SetCount(FrameCount);
    Quat.SetCount(FrameCount);
    Euler.SetCount(FrameCount);

    for( int n=0; n<TrackedNodes.Count(); ++n )
    {
        IGameNode* node = TrackedNodes[n];

        for( int t=0; t<FrameCount; ++t )
        {            
            // Progress
            CheckCancel();
            
            // Set frame
            int curframe = FrameStart + t;
            pScene->SetStaticFrame(curframe);

            // Write tracking
            GMatrix objTM = node->GetWorldTM();
            Loc[t] = objTM.Translation();
            Quat[t] = objTM.Rotation();

            float eu[3];
            QuatToEuler(Quat[t],eu);
            Euler[t]=Point3(eu[0],eu[1],eu[2]);
            Euler[t] *= 180.0f/pi;

            eu[1] *= -1;
            EulerToQuat(eu,Quat[t],EULERTYPE_YXZ);
        }
        
        for( int t=0; t<FrameCount; ++t )
        {    
            _ftprintf( fLog, _T("%sLoc[%d]=(X=%f,Y=%f,Z=%f)\n"), node->GetName(), t, Loc[t].x, Loc[t].y, Loc[t].z );
        }
        
        for( int t=0; t<FrameCount; ++t )
        {    
            _ftprintf( fLog, _T("%sQuat[%d]=(W=%f,X=%f,Y=%f,Z=%f)\n"), node->GetName(), t, Quat[t].w, Quat[t].x, Quat[t].y, Quat[t].z ); 
        }
        
        for( int t=0; t<FrameCount; ++t )
        {    
            _ftprintf( fLog, _T("%sEuler[%d]=(X=%f,Y=%f,Z=%f)\n"), node->GetName(), t, Euler[t].x, Euler[t].y, Euler[t].z ); 
        }
    }
}