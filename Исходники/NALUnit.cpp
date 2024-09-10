bool 
SeqParamSet::Parse(NALUnit* pnalu)
{
    if (pnalu->Type() != NALUnit::NAL_Sequence_Params)
    {
        return false;
    }

    // with the UE/SE type encoding, we must decode all the values
    // to get through to the ones we want
    pnalu->ResetBitstream();
    pnalu->Skip(8);     // type
    m_Profile = pnalu->GetWord(8);
    m_Compatibility = (BYTE) pnalu->GetWord(8);
    m_Level = pnalu->GetWord(8);

    /*int seq_param_id =*/ pnalu->GetUE();

    if ((m_Profile == 100) || (m_Profile == 110) || (m_Profile == 122) || (m_Profile == 144))
    {
        int chroma_fmt = pnalu->GetUE();
        if (chroma_fmt == 3)
        {
            pnalu->Skip(1);
        }
        /* int bit_depth_luma_minus8 = */ pnalu->GetUE();
        /* int bit_depth_chroma_minus8 = */ pnalu->GetUE();
        pnalu->Skip(1);
        int seq_scaling_matrix_present = pnalu->GetBit();
        if (seq_scaling_matrix_present)
        {
            for (int i = 0; i < 8; i++)
            {
                if (pnalu->GetBit())
                {
                    if (i < 6)
                    {
                        ScalingList(16, pnalu);
                    }
                    else
                    {
                        ScalingList(64, pnalu);
                    }
                }
            }
        }
    }

    int log2_frame_minus4 = pnalu->GetUE();
    m_FrameBits = log2_frame_minus4 + 4;
    int POCtype = pnalu->GetUE();
    if (POCtype == 0)
    {
        /*int log2_poc_minus4 =*/ pnalu->GetUE();
    } else if (POCtype == 1) 
    {
        pnalu->Skip(1); // delta always zero
        /*int nsp_offset =*/ pnalu->GetSE();
        /*int nsp_top_to_bottom = */ pnalu->GetSE();
        int num_ref_in_cycle = pnalu->GetUE();
        for (int i = 0; i < num_ref_in_cycle; i++)
        {
            /*int sf_offset =*/ pnalu->GetSE();
        }
    } 
    else if (POCtype != 2)
    {
        return false;
    }
    // else for POCtype == 2, no additional data in stream
    
    /*int num_ref_frames =*/ pnalu->GetUE();
    /*int gaps_allowed =*/ pnalu->GetBit();

    int mbs_width = pnalu->GetUE();
    int mbs_height = pnalu->GetUE();
    m_cx = (mbs_width+1) * 16;
    m_cy = (mbs_height+1) * 16;

    // smoke test validation of sps
    if ((m_cx > 2000) || (m_cy > 2000))
    {
        return false;
    }

    // if this is false, then sizes are field sizes and need adjusting
    m_bFrameOnly = pnalu->GetBit() ? true : false;
    
    if (!m_bFrameOnly)
    {
        pnalu->Skip(1); // adaptive frame/field
    }
    pnalu->Skip(1);     // direct 8x8

    SetRect(&m_rcFrame, 0, 0, 0, 0);
    bool bCrop = pnalu->GetBit() ? true : false;
    if (bCrop) {
        // get cropping rect 
        // store as exclusive, pixel parameters relative to frame
        m_rcFrame.left = pnalu->GetUE() * 2;
        m_rcFrame.right = pnalu->GetUE() * 2;
        m_rcFrame.top = pnalu->GetUE() * 2;
        m_rcFrame.bottom = pnalu->GetUE() * 2;
    }

    if (!IsRectEmpty(&m_rcFrame))
    {
        m_rcFrame.right = m_cx - m_rcFrame.right;
        m_rcFrame.bottom = m_cy - m_rcFrame.bottom;
    }

    // adjust rect from 2x2 units to pixels

    if (!m_bFrameOnly)
    {
        // adjust heights from field to frame
        m_cy *= 2;
        m_rcFrame.top *= 2;
        m_rcFrame.bottom *= 2;
    }

    // .. rest are not interesting yet
    return true;
}