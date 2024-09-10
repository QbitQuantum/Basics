inline void run_cleanup()
{
    // only call this once, on exit
    // to make sure valgrind output is clean
    // http://xmlsoft.org/xmlmem.html
    xmlCleanupCharEncodingHandlers();
    xmlCleanupEncodingAliases();
    xmlCleanupGlobals();
    xmlCleanupParser();
    xmlCleanupThreads();
    xmlCleanupInputCallbacks();
    xmlCleanupOutputCallbacks();
    xmlCleanupMemory();

#if defined(HAVE_CAIRO)
    // http://cairographics.org/manual/cairo-Error-handling.html#cairo-debug-reset-static-data
    cairo_debug_reset_static_data();
#endif

    // http://icu-project.org/apiref/icu4c/uclean_8h.html#a93f27d0ddc7c196a1da864763f2d8920
    u_cleanup();

#ifdef MAPNIK_USE_PROJ4
    // http://trac.osgeo.org/proj/ticket/149
 #if PJ_VERSION >= 480
    pj_clear_initcache();
 #endif
    // https://trac.osgeo.org/proj/wiki/ProjAPI#EnvironmentFunctions
    pj_deallocate_grids();
#endif    
}