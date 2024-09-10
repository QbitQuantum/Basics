/** Reads pixel data and corresponding attributes like rows etc. from image
*  file and inserts them into dataset.
*  @param dset - [out] The dataset to export the pixel data attributes to
*  @param outputTS - [out] The proposed transfex syntax of the dataset
*  @return EC_Normal, if successful, error otherwise
*/
OFCondition I2DImgSource::readAndInsertSpecificTags( DcmDataset* dset, E_TransferSyntax& outputTS)
{
        Uint16 samplesPerPixel, rows, cols, bitsAlloc, bitsStored, highBit, pixelRepr, planConf;
        Uint16 pixAspectH = 1;
        Uint16 pixAspectV = 1;
        OFString photoMetrInt;
        outputTS = EXS_Unknown;
        char* pixData = NULL;
        Uint32 length;

        OFCondition cond = readPixelData(rows, cols,
                                         samplesPerPixel, photoMetrInt, bitsAlloc, bitsStored, highBit, pixelRepr,
                                         planConf, pixAspectH, pixAspectV, pixData, length, outputTS);
        if (cond.bad())
                return cond;

        if (m_debug)
                printMessage(m_logStream, "Document2Dcm: Store imported pixel data to DICOM file");

        cond = dset->putAndInsertUint16(DCM_SamplesPerPixel, samplesPerPixel);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertOFStringArray(DCM_PhotometricInterpretation, photoMetrInt);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertOFStringArray(DCM_ConversionType, "WSD");
        if (cond.bad())
                return cond;
        /*
        cond = dset->putAndInsertOFStringArray(DCM_ImagerPixelSpacing, "1.000000\\1.000000");
        if (cond.bad())
        return cond;

        cond = dset->putAndInsertOFStringArray(DCM_PixelSpacing, "1.000000\\1.000000");
        if (cond.bad())
        return cond;
        */
        cond = dset->putAndInsertOFStringArray(DCM_ImagePositionPatient, "0.000000\\0.000000\\0.000000");
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertOFStringArray(DCM_ImageOrientationPatient, "1.000000\\0.000000\\0.000000\\0.000000\\1.000000\\0.000000");
        if (cond.bad())
                return cond;


        // Should only be written if Samples per Pixel > 1
        if (samplesPerPixel > 1) {
                cond = dset->putAndInsertUint16(DCM_PlanarConfiguration, planConf);
                if (cond.bad())
                        return cond;
        }

        cond = dset->putAndInsertUint16(DCM_Rows, rows);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertUint16(DCM_Columns, cols);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertUint16(DCM_BitsAllocated, bitsAlloc);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertUint16(DCM_BitsStored, bitsStored);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertUint16(DCM_HighBit, highBit);
        if (cond.bad())
                return cond;

        cond = dset->putAndInsertUint16(DCM_PixelRepresentation, pixelRepr);
        if (cond.bad())
                return cond;


        if (Recompress()) {
                // create initial pixel sequence
                DcmElement* element = newDicomElement(DcmTag(DCM_PixelData, EVR_OW));
                element->putUint8Array((const Uint8*)pixData, length);
                cond = dset->insert(element);
                if (cond.bad()) {
                        delete element;
                        return cond;
                }

                //lo pasamos a jpeg lossless
                // create representation parameters for lossy and lossless
                OFCmdUnsignedInt opt_selection_value = 6;
                //este numero implica cierta perdida... si fuera 0 seria lossless real
                OFCmdUnsignedInt opt_point_transform = 3;

                E_TransferSyntax opt_oxfer;
                GNC::GCS::Permisos::EstadoPermiso codificacion = GNC::GCS::IControladorPermisos::Instance()->Get("core.importacion", "codec");
                switch (codificacion.ObtenerValor<int>()) {
                case 0: {
                        //baseline
                        opt_oxfer = EXS_JPEGProcess1;
                        DJ_RPLossy rp_lossy((int)90);
                        const DcmRepresentationParameter *rp = &rp_lossy;
                        dset->chooseRepresentation(opt_oxfer, rp);
                }
                break;
                case 1: {
                        //progresivo
                        opt_oxfer = EXS_JPEGProcess10_12;
                        DJ_RPLossy rp_lossy((int)90);
                        const DcmRepresentationParameter *rp = &rp_lossy;
                        dset->chooseRepresentation(opt_oxfer, rp);
                }
                break;
                case 2:
                default: {
                        //lossless
                        GNC::GCS::Permisos::EstadoPermiso estado = GNC::GCS::IControladorPermisos::Instance()->Get("core.importacion", "quality");
                        if (estado) {
                                opt_point_transform = std::min<int>(estado.ObtenerValor<int>(), 14);
                                opt_point_transform = std::max<int>(estado.ObtenerValor<int>(), 0);
                        }
                        opt_oxfer = EXS_JPEGProcess14SV1;
                        DJ_RPLossless rp_lossless((int)opt_selection_value, (int)opt_point_transform);
                        const DcmRepresentationParameter *rp = &rp_lossless;
                        dset->chooseRepresentation(opt_oxfer, rp);
                }
                break;
                }

                if(!dset->canWriteXfer(opt_oxfer))
                        return OFCondition(EC_UnsupportedEncoding);

                // force meta-header to refresh SOP Class/Instance UIDs.
                delete dset->remove(DCM_MediaStorageSOPClassUID);
                delete dset->remove(DCM_MediaStorageSOPInstanceUID);
                outputTS = opt_oxfer;

                return cond;
        } else {
                if (IsCompressed()) {
                        DcmPixelSequence *pixelSequence = NULL;

                        if (m_debug)
                                printMessage(m_logStream, "Document2Dcm: Store imported pixel data to DICOM file");
                        // create initial pixel sequence
                        pixelSequence = new DcmPixelSequence(DcmTag(DCM_PixelData, EVR_OB));
                        if (pixelSequence == NULL)
                                return EC_MemoryExhausted;
                        // insert empty offset table into sequence
                        DcmPixelItem *offsetTable = new DcmPixelItem(DcmTag(DCM_Item, EVR_OB));
                        if (offsetTable == NULL) {
                                delete pixelSequence;
                                pixelSequence = NULL;
                                return EC_MemoryExhausted;
                        }
                        cond = pixelSequence->insert(offsetTable);
                        if (cond.bad()) {
                                delete offsetTable;
                                offsetTable = NULL;
                                delete pixelSequence;
                                pixelSequence = NULL;
                                return cond;
                        }

                        // insert frame into pixel sequence
                        DcmOffsetList dummyList;
                        cond = pixelSequence->storeCompressedFrame(dummyList, (Uint8*) pixData, length, 0);
                        // storeCompressedFrame(..) does a deep copy, so the pixdata memory can be freed now
                        delete[] pixData;
                        if (cond.bad()) {
                                delete pixelSequence;
                                return cond;
                        }
                        cond = dset->insert(pixelSequence);
                        if (cond.bad())
                                delete pixelSequence;

                        if (m_debug)
                                printMessage(m_logStream, "Document2Dcm: Inserting Image Pixel module information");
                        return dset->putAndInsertUint16(DCM_PixelRepresentation, pixelRepr);
                } else {
                        //little endian to little endian...
                        // create initial pixel sequence
                        DcmElement* element = newDicomElement(DcmTag(DCM_PixelData, EVR_OW));
                        element->putUint8Array((const Uint8*)pixData, length);
                        cond = dset->insert(element);
                        if (cond.bad()) {
                                delete element;
                                return cond;
                        }
                        outputTS = EXS_LittleEndianExplicit;

                        return cond;
                }
        }
}