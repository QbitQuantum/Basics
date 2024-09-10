vec2Di::vec2Di(const wchar_t* file) : m_width(0), m_height(0)
{
        int val;

        FILE* fp = _wfopen(file, L"rt");
        if (fp) {
                if (fwscanf(fp, L"%d %d", &m_height, &m_width) != 2) {
                        fclose(fp);
                        init(1, 1);
                        return;
                }

                init(m_height, m_width);

                for (unsigned int y = 0; y < height(); y++) {
                        for (unsigned int x = 0; x < width(); x++) {
                                if (fwscanf(fp, L"%d", &val) != 1) {
                                        m_data[y][x] = 0;
                                } else
                                        m_data[y][x] = val;
                        }
                }

                fclose(fp);
        } else {
                init(1, 1);
                set(0);
        }
}