    void PacketBuilder::WriteCreateData(MoveSpline const& moveSpline, ByteBuffer& data, Unit* unit)
    {
        if (/*!moveSpline.Finalized()*/true)
        {
            MoveSplineFlag splineFlags = moveSpline.splineflags;

            uint8 splineType = 0;
            switch (splineFlags & MoveSplineFlag::Mask_Final_Facing)
            {
                case MoveSplineFlag::Final_Target:
                    splineType = MonsterMoveFacingTarget;
                    break;
                case MoveSplineFlag::Final_Angle:
                    splineType = MonsterMoveFacingAngle;
                    break;
                case MoveSplineFlag::Final_Point:
                    splineType = MonsterMoveFacingSpot;
                    break;
                default:
                    splineType = MonsterMoveNormal;
                    break;
            }

            data << float(1.0f);                             // splineInfo.duration_mod_next; added in 3.1
            uint32 nodes = moveSpline.getPath().size();
            for (uint32 i = 0; i < nodes; ++i)
            {
                data << float(moveSpline.getPath()[i].z);
                data << float(moveSpline.getPath()[i].y);
                data << float(moveSpline.getPath()[i].x);
            }

            data << uint8(splineType);
            data << float(1.0f);                             // splineInfo.duration_mod; added in 3.1

            if (splineFlags.final_point)
                data << moveSpline.facing.f.x << moveSpline.facing.f.y << moveSpline.facing.f.z;

            if (splineFlags.parabolic)
                data << moveSpline.vertical_acceleration;   // added in 3.1

            if (splineFlags.final_angle)
                data << moveSpline.facing.angle;

            data << moveSpline.Duration();

            if (splineFlags.parabolic || splineFlags.animation)
                data << moveSpline.effect_start_time;       // added in 3.1

            data << moveSpline.timePassed();
        }

        if (!moveSpline.isCyclic())
        {
            Vector3 dest = moveSpline.FinalDestination();
            data << moveSpline.GetId();
            data << float(dest.x);
            data << float(dest.y);
            data << float(dest.z);
        }
        else
        {
            data << moveSpline.GetId();
            data << float(0.0f);
            data << float(0.0f);
            data << float(0.0f);
        }
    }