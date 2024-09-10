void node_init() {
    node_bundled_backend_js = str_printf("%s/bin/livereload-backend.js", os_bundled_backend_path);
    _beginthread(node_thread, 0, NULL);
}