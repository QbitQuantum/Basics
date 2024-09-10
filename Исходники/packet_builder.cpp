    void PacketBuilder::WriteCreateBits(const MoveSpline& move_spline, ByteBuffer& data)
    {
        if (!data.WriteBit(!move_spline.Finalized()))
            return;

        MoveSplineFlag splineFlags = move_spline.splineflags;
        uint32 nodes = move_spline.getPath().size();
        bool hasSplineStartTime = move_spline.splineflags & (MoveSplineFlag::Trajectory | MoveSplineFlag::Animation);
        bool hasSplineVerticalAcceleration = (move_spline.splineflags & MoveSplineFlag::Trajectory) && move_spline.effect_start_time < move_spline.Duration();

        data.WriteBits(uint8(move_spline.spline.mode()), 2);
        data.WriteBit(hasSplineStartTime);
        data.WriteBits(nodes, 22);

        switch (move_spline.splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
            case MoveSplineFlag::Final_Target:
            {
                data.WriteBits(2, 2);

                data.WriteGuidMask<4, 3, 7, 2, 6, 1, 0, 5>(ObjectGuid(move_spline.facing.target));
                break;
            }
            case MoveSplineFlag::Final_Angle:
                data.WriteBits(0, 2);
                break;
            case MoveSplineFlag::Final_Point:
                data.WriteBits(1, 2);
                break;
            default:
                data.WriteBits(3, 2);
                break;
        }

        data.WriteBit(hasSplineVerticalAcceleration);
        data.WriteBits(move_spline.splineflags.raw(), 25);
    }