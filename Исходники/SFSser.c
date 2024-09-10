/**
 * @brief This function builds an openSAFETY frame and provides it to the HNF, which is in charge of transmission.
 *
 * The calling function has to request the memory block by using {SFS_GetMemBlock()}. The memory block has
 * to be of size of the complete openSAFETY frame and data to be transmitted is stored at the place inside the
 * memory block where payload data of sub frame one is located. The memory block is provided by reference
 * to this function. The calling function also has to provide the header info by reference. The data structure
 * must be of type EPLS_t_FRM_HDR and assembles all necessary header info to build the openSAFETY frame.
 * All frame header info is checked before is is put into the right order and stored into sub frame one and two.
 * Frame data, already stored in sub frame one, is copied into sub frame two. To pass the openSAFETY frame to the
 * SHNF and so transmitting it the function SHNF_MarkTxMemBlock() is used.
 *
 * @see          EPLS_t_FRM_HDR
 *
 * @param        b_instNum         instance number (not checked, called with EPLS_k_SCM_INST_NUM or checked in
 *                    SSC_ProcessSNMTSSDOFrame() or SPDO_BuildTxSpdo())) valid range: 0 .. &lt;EPLS_cfg_MAX_INSTANCES&gt; - 1
 *
 * @param        ps_hdrInfo        reference to header info, stored into an internal data structure (not checked,
 *                    only called with reference to struct), valid range: <> NULL
 *
 * @param        pb_frame          reference to an openSAFETY frame (payload data is already stored in sub frame ONE).
 *                    Reference is provided by function SFS_GetMemBlock() (not checked, checked in transmitRequest()
 *                    or SNMTM_SnErrorAck() or SNMTS_TxRespRstGuardScm() or SendTxSpdo() processStateSer() or
 *                    reqBufferSend()), valid range: <> NULL
 *
 * @return
 * - TRUE            - openSAFETY frame serialized and passed to the SHNF successfully
 * - FALSE           - error during marking the memory block openSAFETY frame passing failed
 */
BOOLEAN SFS_FrmSerialize(BYTE_B_INSTNUM_ const EPLS_t_FRM_HDR *ps_hdrInfo,
                         UINT8 *pb_frame)
{
    BOOLEAN o_return = FALSE;     /* predefined return value */
    UINT8 b_subFrm1Id = 0u;       /* variable to build the value of the ID field
                                   in sub frame 1 */
    UINT8 b_subFrm2Id = 0u;       /* variable to build the value of the ID field
                                   in sub frame 2 */
    UINT8 b_subFrm2Adr = 0u;      /* variable to build the value of ADR field */
    UINT8 b_subFrm2Tr = 0u;       /* variable to build the value of TR field */

    UINT8 b_calcCrc1Short = 0u;   /* calculated 8 bit CRC, provided by SHNF */
    UINT8 b_calcCrc2Short = 0u;   /* calculated 8 bit CRC, provided by SHNF */
    UINT16 w_calcCrc1Long = 0u;   /* calculated 16 bit CRC, provided by SHNF */
    UINT16 w_calcCrc2Long = 0u;   /* calculated 16 bit CRC, provided by SHNF */

    UINT16 w_subFrm1Len = 0u;     /* number of bytes of sub frame ONE */
    UINT16 w_subFrm2Len = 0u;     /* number of bytes of sub frame ONE */
    UINT8 *pb_subFrm1Crc = 0u;    /* pointer to CRC in sub frame ONE */
    UINT8 *pb_subFrm2Crc = 0u;    /* pointer to CRC in sub frame TWO */

    /* reference to sub frame ONE within received openSAFETY frame
       NOTE:
       sub frame ONE and TWO are twisted within the openSAFETY frame in tx dir. !!! */
    UINT8 *pb_subFrm1 = (UINT8 *)NULL;


    /* if the header info provided by the calling function is correct */
    if(checkTxFrameHeader(B_INSTNUM_ ps_hdrInfo))
    {
        /* Build 8 bit value of openSAFETY frame ID field in sub frame ONE */
        b_subFrm1Id = ps_hdrInfo->b_id;                            /* 00XX|XXXX */
        b_subFrm1Id = (UINT8)(b_subFrm1Id << 2u);                  /* XXXX|XX00 */
        b_subFrm1Id = (UINT8)(b_subFrm1Id |
                              (HIGH8(ps_hdrInfo->w_adr) & k_ADR_MASK_AND)); /* XXXX|XXYY */

        /* Build 8 bit value of openSAFETY frame ADR field in sub frame TWO */
        b_subFrm2Adr = LOW8(ps_hdrInfo->w_adr);
        b_subFrm2Adr = (UINT8)(b_subFrm2Adr ^ LOW8(ps_hdrInfo->w_sdn));

        /* Build 8 bit value of openSAFETY frame ID field in sub frame TWO,
        *     ID field = 6bit frame ID, ((2bit sadr) XOR (2bit domain number))
        *
        *       HIGH8(w_sdn) : SSSS|SSZZ
        * AND  k_ID_MASK_AND : 0000|0011
        * -------------------> 0000|00ZZ
        * XOR    b_subFrm1Id : XXXX|XXYY
        * -------------------> XXXX|XXQQ   ( Q = Y xor Z )
        */
        b_subFrm2Id  = (UINT8)(b_subFrm1Id ^
                               (HIGH8(ps_hdrInfo->w_sdn) & k_SDN_HB_MASK_AND));

        /* Build 8 bit value of openSAFETY frame TR field in sub frame TWO */
        b_subFrm2Tr = ps_hdrInfo->b_tr;                            /* 00XX|XXXX */
        b_subFrm2Tr = (UINT8)(b_subFrm2Tr << 2u);                  /* XXXX|XX00 */
        b_subFrm2Tr = (UINT8)(b_subFrm2Tr | (HIGH8(ps_hdrInfo->w_tadr)
                                             & k_TADR_MASK_AND));                        /* XXXX|XXYY */

        /* check if payload data is doubled */
        if ( k_SERVICE_REQ_FAST == (ps_hdrInfo->b_id & k_SERVICE_REQ_FAST))
        {
            /* no double payload data */
            /* if payload data length is larger than 8 bytes, 2 byte CRC is used */
            if(ps_hdrInfo->b_le > k_MAX_DATA_LEN_SHORT)
            {
                /* calculate reference to start of sub frame ONE header (2 byte CRC)
                    NOTE: sub frame ONE and TWO are twisted within the openSAFETY frame in
                          tx dir. !!! */
                pb_subFrm1 =
                    &pb_frame[(k_SFRM2_HDR_LEN + k_CRC_LEN_LONG)];
            }
            else  /* payload data length is 8 byte or less and 1 byte CRC is used */
            {
                /* calculate reference to start of sub frame ONE header (1 byte CRC)
                    NOTE: sub frame ONE and TWO are twisted within the openSAFETY frame in
                          tx dir. !!! */
                pb_subFrm1 =
                    &pb_frame[(k_SFRM2_HDR_LEN + k_CRC_LEN_SHORT)];
            }
            /* calculate length of sub frames and
                calculate reference to CRC field of sub frames TWO and sub frame ONE */
            w_subFrm1Len  = (UINT16)(k_SFRM1_HDR_LEN + ps_hdrInfo->b_le);
            w_subFrm2Len  = (UINT16)(k_SFRM2_HDR_LEN);

            pb_subFrm1Crc = &pb_subFrm1[k_SFRM1_DATA + ps_hdrInfo->b_le];
            pb_subFrm2Crc = &pb_frame[k_SFRM2_DATA];
        }
        else
        {
            /* if payload data length is larger than 8 bytes, 2 byte CRC is used */
            if(ps_hdrInfo->b_le > k_MAX_DATA_LEN_SHORT)
            {
                /* calculate reference to start of sub frame ONE header (2 byte CRC)
                    NOTE: sub frame ONE and TWO are twisted within the openSAFETY frame in
                          tx dir. !!! */
                pb_subFrm1 =
                    &pb_frame[(k_SFRM2_HDR_LEN + ps_hdrInfo->b_le + k_CRC_LEN_LONG)];
            }
            else  /* payload data length is 8 byte or less and 1 byte CRC is used */
            {
                /* calculate reference to start of sub frame ONE header (1 byte CRC)
                    NOTE: sub frame ONE and TWO are twisted within the openSAFETY frame in
                          tx dir. !!! */
                pb_subFrm1 =
                    &pb_frame[(k_SFRM2_HDR_LEN + ps_hdrInfo->b_le + k_CRC_LEN_SHORT)];
            }
            /* calculate length of sub frames and
                calculate reference to CRC field of sub frames TWO and sub frame ONE */
            w_subFrm1Len  = (UINT16)(k_SFRM1_HDR_LEN + ps_hdrInfo->b_le);
            w_subFrm2Len  = (UINT16)(k_SFRM2_HDR_LEN + ps_hdrInfo->b_le);

            pb_subFrm1Crc = &pb_subFrm1[k_SFRM1_DATA + ps_hdrInfo->b_le];
            pb_subFrm2Crc = &pb_frame[k_SFRM2_DATA + ps_hdrInfo->b_le];
        }

        /* copy payload data from sub frame TWO into sub frame ONE */
        /*lint -save -e119 -e746 -i830: the prototype is not really missing but there is a problem with the
         * standard lib*/
        (void)MEMMOVE(&pb_subFrm1[k_SFRM1_DATA], &pb_frame[k_SFRM2_DATA],
                      (UINT32)ps_hdrInfo->b_le);
        /*lint -restore */

        /* fill header bytes and data bytes of sub frame ONE into the memory
            block of serialized openSAFETY frame. */
        SFS_NET_CPY8(&(pb_subFrm1[k_SFRM1_HDR_ADR]),&LOW8(ps_hdrInfo->w_adr));
        SFS_NET_CPY8(&(pb_subFrm1[k_SFRM1_HDR_ID]), &b_subFrm1Id);
        SFS_NET_CPY8(&(pb_subFrm1[k_SFRM1_HDR_LE]), &ps_hdrInfo->b_le);
        SFS_NET_CPY8(&(pb_subFrm1[k_SFRM1_HDR_CT]), &LOW8(ps_hdrInfo->w_ct));

        /* fill header bytes and data bytes of sub frame TWO into the memory
            block of serialized openSAFETY frame. */
        SFS_NET_CPY8(&(pb_frame[k_SFRM2_HDR_ADR]), &b_subFrm2Adr);
        SFS_NET_CPY8(&(pb_frame[k_SFRM2_HDR_ID]), &b_subFrm2Id);
        SFS_NET_CPY8(&(pb_frame[k_SFRM2_HDR_CT]), &(HIGH8(ps_hdrInfo->w_ct)));
        SFS_NET_CPY8(&(pb_frame[k_SFRM2_HDR_TADR]), &(LOW8(ps_hdrInfo->w_tadr)));
        SFS_NET_CPY8(&(pb_frame[k_SFRM2_HDR_TR]), &b_subFrm2Tr);

        /* NOTE: payload data is already written into sub frame TWO
            by the calling function and for special frame types already overwritten */


        /* if payload data length is larger than 8 bytes */
        if(ps_hdrInfo->b_le > k_MAX_DATA_LEN_SHORT)
        {
            if ( k_SERVICE_REQ_FAST == (ps_hdrInfo->b_id & k_SERVICE_REQ_FAST))
            {
                /* get 16 bit CRC as reference for sub frame TWO/ONE from unit SHNF */
                w_calcCrc1Long = SHNF_Crc16CalcSlim(0U, (INT32)w_subFrm1Len,
                                                    (void *)pb_subFrm1);
                w_calcCrc2Long = SHNF_Crc16CalcSlim(0U, (INT32)w_subFrm2Len,
                                                    (void *)pb_frame);
            }
            else
            {
                /* get 16 bit CRC as reference for sub frame TWO/ONE from unit SHNF */
                w_calcCrc1Long = SHNF_Crc16Calc(0U, (INT32)w_subFrm1Len,
                                                (void *)pb_subFrm1);
                w_calcCrc2Long = SHNF_Crc16Calc(0U, (INT32)w_subFrm2Len,
                                                (void *)pb_frame);
            }

            SFS_NET_CPY16(pb_subFrm1Crc, &w_calcCrc1Long);
            SFS_NET_CPY16(pb_subFrm2Crc, &w_calcCrc2Long);
        }
        else  /* payload data length is 8 byte or less */
        {
            /* get 8 bit CRC as reference for sub frame TWO/ONE from unit SHNF */
            b_calcCrc1Short = SHNF_Crc8Calc(0U, (INT32)w_subFrm1Len,
                                            (void *)pb_subFrm1);
            b_calcCrc2Short = SHNF_Crc8Calc(0U, (INT32)w_subFrm2Len,
                                            (void *)pb_frame);
            SFS_NET_CPY8(pb_subFrm1Crc, &b_calcCrc1Short);
            SFS_NET_CPY8(pb_subFrm2Crc, &b_calcCrc2Short);
        }

        /* the UDID of the SCM encoding */
        SFS_ScmUdidCode(B_INSTNUM_ ps_hdrInfo->b_id, pb_frame);

        /* if openSAFETY frame cannot be passed to SHNF */
        if(!(SHNF_MarkTxMemBlock(B_INSTNUM_ pb_frame)))
        {
            /* error: SHNF cannot mark openSAFETY frame as "ready to process" */
            SERR_SetError(B_INSTNUM_ SFS_k_ERR_SHNF_CANNOT_MARK_MEM_BLK,
                          SERR_k_NO_ADD_INFO);
        }
        else  /* openSAFETY frame processed successfully from SHNF */
        {
            o_return = TRUE;
        }
    }
    /* else the header info provided by the calling function is incorrect */
    SCFM_TACK_PATH();
    return o_return;
}