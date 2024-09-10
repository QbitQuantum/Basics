static void display(void) {
    startTime = OS::GetTime();
    Trace::Call *call;

    while ((call = parser.parse_call())) {
        const char *name = call->name();

        if (retrace::verbosity >= 1) {
            std::cout << *call;
            std::cout.flush();
        }

        if (name[0] == 'C' && name[1] == 'G' && name[2] == 'L') {
            glretrace::retrace_call_cgl(*call);
        }
        else if (name[0] == 'w' && name[1] == 'g' && name[2] == 'l') {
            glretrace::retrace_call_wgl(*call);
        }
        else if (name[0] == 'g' && name[1] == 'l' && name[2] == 'X') {
            glretrace::retrace_call_glx(*call);
        } else {
            retrace::retrace_call(*call);
        }

        if (!insideGlBeginEnd &&
            drawable && context &&
            call->no >= dump_state) {
            glstate::dumpCurrentContext(std::cout);
            exit(0);
        }

        delete call;
    }

    // Reached the end of trace
    glFlush();

    long long endTime = OS::GetTime();
    float timeInterval = (endTime - startTime) * 1.0E-6;

    if (retrace::verbosity >= -1) { 
        std::cout << 
            "Rendered " << frame << " frames"
            " in " <<  timeInterval << " secs,"
            " average of " << (frame/timeInterval) << " fps\n";
    }

    if (wait) {
        while (ws->processEvents()) {}
    } else {
        exit(0);
    }
}