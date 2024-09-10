BinaryInput::BinaryInput(
    const std::string&  filename,
    G3DEndian           fileEndian,
    bool                compressed) :
    m_filename(filename),
    m_bitPos(0),
    m_bitString(0),
    m_beginEndBits(0),
    m_alreadyRead(0),
    m_length(0),
    m_bufferLength(0),
    m_buffer(NULL),
    m_pos(0),
    m_freeBuffer(true) {

    setEndian(fileEndian);

    // Update global file tracker
    _internal::currentFilesUsed.insert(m_filename);


    if (! fileExists(m_filename, false)) {
        std::string zipfile;
        std::string internalfile;
        if (zipfileExists(m_filename, zipfile, internalfile)) {
            // Load from zipfile
            void* v;
            size_t s;
            zipRead(filename, v, s);
            m_buffer = reinterpret_cast<uint8*>(v);
            m_bufferLength = m_length = s;
            if (compressed) {
                decompress();
            }
            m_freeBuffer = true;
        } else {
            Log::common()->printf("Warning: File not found: %s\n", m_filename.c_str());
        }
        return;
    }

    // Figure out how big the file is and verify that it exists.
    m_length = fileLength(m_filename);

    // Read the file into memory
    FILE* file = fopen(m_filename.c_str(), "rb");

    if (! file || (m_length == -1)) {
        throw format("File not found: \"%s\"", m_filename.c_str());
        return;
    }

    if (! compressed && (m_length > INITIAL_BUFFER_LENGTH)) {
        // Read only a subset of the file so we don't consume
        // all available memory.
        m_bufferLength = INITIAL_BUFFER_LENGTH;
    } else {
        // Either the length is fine or the file is compressed
        // and requires us to read the whole thing for zlib.
        m_bufferLength = m_length;
    }

    debugAssert(m_freeBuffer);
    m_buffer = (uint8*)System::alignedMalloc(m_bufferLength, 16);
    if (m_buffer == NULL) {
        if (compressed) {
            throw "Not enough memory to load compressed file. (1)";
        }

        // Try to allocate a small array; not much memory is available.
        // Give up if we can't allocate even 1k.
        while ((m_buffer == NULL) && (m_bufferLength > 1024)) {
            m_bufferLength /= 2;
            m_buffer = (uint8*)System::alignedMalloc(m_bufferLength, 16);
        }
    }
    debugAssert(m_buffer);

    fread(m_buffer, m_bufferLength, sizeof(int8), file);
    fclose(file);
    file = NULL;

    if (compressed) {
        if (m_bufferLength != m_length) {
            throw "Not enough memory to load compressed file. (2)";
        }

        decompress();
    }
}