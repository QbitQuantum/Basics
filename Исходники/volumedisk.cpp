VolumeRepresentation* RepresentationConverterLoadFromDisk::convert(const VolumeRepresentation* source) const {
    const VolumeDisk* dr = dynamic_cast<const VolumeDisk*>(source);

    if(dr) {
        VolumeRAM* volume = 0;
        LDEBUGC("voreen.RepresentationConverterLoadFromDisk", "creating volume from diskrepr. " << dr->getFileName() << " format: " << dr->getFormat());
        VolumeFactory vf;
        volume = vf.create(dr->getFormat(), dr->getDimensions());

        if(!volume)
            return 0;

        FILE* fin;
        fin = fopen(dr->getFileName().c_str(),"rb");

        if (fin == 0)
            throw tgt::IOException("Unable to open raw file for reading", dr->getFileName());

        size_t bytesPerVoxel = static_cast<size_t>(volume->getBitsAllocated() / 8);
        size_t numVoxels = hmul(dr->getDimensions());
        size_t numBytes = numVoxels * bytesPerVoxel;

        int64_t offset = dr->getOffset();
        if(offset < 0) {
            //Assume data is aligned to end of file.

            // get file size:
            fseek(fin, 0, SEEK_END);
            int64_t fileSize = ftell(fin);
            rewind(fin);

            //calculate real offset:
            offset = fileSize - numBytes;
        }
#ifdef _MSC_VER
        _fseeki64(fin, offset, SEEK_SET);
#else
        fseek(fin, offset, SEEK_SET);
#endif

        if(fread(reinterpret_cast<char*>(volume->getData()), numBytes, 1, fin) != 1) {
            LERRORC("voreen.RepresentationConverterLoadFromDisk", "fread() failed");
            fclose(fin);
            delete volume;
            return 0;
        }

        fclose(fin);

        if(dr->getSwapEndian()) {
            Volume* tempHandle = new Volume(volume, vec3(1.0f), vec3(0.0f));
            VolumeOperatorSwapEndianness::APPLY_OP(tempHandle);
            tempHandle->releaseAllRepresentations();
        }

        return volume;
    }
    else {
        //should have checked before...
        //LERROR("Failed to convert!");
        return 0;
    }
}