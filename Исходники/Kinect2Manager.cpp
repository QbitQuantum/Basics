void load_buffer(const char * filename, void * buffer, size_t size, size_t count) {
    FILE * file;

    if (fopen_s(&file, filename, "r") == 0) {
        fread_s(buffer, size * count, size, count, file);
    }
    else {
        std::cout << "Problem loading buffer\n";
    }

    fclose(file);
}