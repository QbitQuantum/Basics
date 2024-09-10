    void PopBox(BufferOutputSerializer &output)
    {
        DWORD boxSize = (DWORD)output.GetPos()-boxOffsets[0];
        *(DWORD*)(endBuffer.Array()+boxOffsets[0]) = fastHtonl(boxSize);

        boxOffsets.Remove(0);
    }