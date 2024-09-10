    void emitOverallMake() {
	// Generate the makefile
	V3OutMkFile of (v3Global.opt.makeDir()+"/"+ v3Global.opt.prefix() + ".mk");
	of.putsHeader();
	of.puts("# DESCR" "IPTION: Verilator output: Makefile for building Verilated archive or executable\n");
	of.puts("#\n");
	of.puts("# Execute this makefile from the object directory:\n");
	of.puts("#    make -f "+v3Global.opt.prefix()+".mk"+"\n");
	of.puts("\n");

	if (v3Global.opt.exe()) {
	    of.puts("default: "+v3Global.opt.exeName()+"\n");
	} else {
	    of.puts("default: "+v3Global.opt.prefix()+"__ALL.a\n");
	}
	of.puts("\n### Constants...\n");
	of.puts("# Perl executable (from $PERL)\n");
	of.puts("PERL = "+V3Options::getenvPERL()+"\n");
	of.puts("# Path to Verilator kit (from $VERILATOR_ROOT)\n");
	of.puts("VERILATOR_ROOT = "+V3Options::getenvVERILATOR_ROOT()+"\n");
	of.puts("# Path to SystemPerl kit top (from $SYSTEMPERL)\n");
	of.puts("SYSTEMPERL = "+V3Options::getenvSYSTEMPERL()+"\n");
	of.puts("# Path to SystemPerl kit includes (from $SYSTEMPERL_INCLUDE)\n");
	of.puts("SYSTEMPERL_INCLUDE = "+V3Options::getenvSYSTEMPERL_INCLUDE()+"\n");
	of.puts("# SystemC include directory with systemc.h (from $SYSTEMC_INCLUDE)\n");
	of.puts(string("SYSTEMC_INCLUDE ?= ")+V3Options::getenvSYSTEMC_INCLUDE()+"\n");
	of.puts("# SystemC library directory with libsystemc.a (from $SYSTEMC_LIBDIR)\n");
	of.puts(string("SYSTEMC_LIBDIR ?= ")+V3Options::getenvSYSTEMC_LIBDIR()+"\n");

	of.puts("\n### Switches...\n");
	of.puts("# SystemPerl output mode?  0/1 (from --sp)\n");
	of.puts(string("VM_SP = ")+(v3Global.opt.systemPerl()?"1":"0")+"\n");
	of.puts("# SystemC output mode?  0/1 (from --sc)\n");
	of.puts(string("VM_SC = ")+((v3Global.opt.systemC()&&!v3Global.opt.systemPerl())?"1":"0")+"\n");
	of.puts("# SystemPerl or SystemC output mode?  0/1 (from --sp/--sc)\n");
	of.puts(string("VM_SP_OR_SC = ")+(v3Global.opt.systemC()?"1":"0")+"\n");
	of.puts("# Deprecated\n");
	of.puts(string("VM_PCLI = ")+(v3Global.opt.systemC()?"0":"1")+"\n");
	of.puts("# Deprecated: SystemC architecture to find link library path (from $SYSTEMC_ARCH)\n");
	of.puts(string("VM_SC_TARGET_ARCH = ")+V3Options::getenvSYSTEMC_ARCH()+"\n");

	of.puts("\n### Vars...\n");
	of.puts("# Design prefix (from --prefix)\n");
	of.puts(string("VM_PREFIX = ")+v3Global.opt.prefix()+"\n");
	of.puts("# Module prefix (from --prefix)\n");
	of.puts(string("VM_MODPREFIX = ")+v3Global.opt.modPrefix()+"\n");

	of.puts("# User CFLAGS (from -CFLAGS on Verilator command line)\n");
	of.puts("VM_USER_CFLAGS = \\\n");
	for (V3StringSet::const_iterator it = v3Global.opt.cFlags().begin();
	     it != v3Global.opt.cFlags().end(); ++it) {
	    of.puts("\t"+*it+" \\\n");
	}
	of.puts("\n");

	of.puts("# User LDLIBS (from -LDFLAGS on Verilator command line)\n");
	of.puts("VM_USER_LDLIBS = \\\n");
	for (V3StringSet::const_iterator it = v3Global.opt.ldLibs().begin();
	     it != v3Global.opt.ldLibs().end(); ++it) {
	    of.puts("\t"+*it+" \\\n");
	}
	of.puts("\n");

	V3StringSet dirs;
	of.puts("# User .cpp files (from .cpp's on Verilator command line)\n");
	of.puts("VM_USER_CLASSES = \\\n");
	for (V3StringSet::const_iterator it = v3Global.opt.cppFiles().begin();
	     it != v3Global.opt.cppFiles().end(); ++it) {
	    string cppfile = *it;
	    of.puts("\t"+V3Options::filenameNonExt(cppfile)+" \\\n");
	    string dir = V3Options::filenameDir(cppfile);
	    if (dirs.find(dir) == dirs.end()) dirs.insert(dir);
	}
	of.puts("\n");

	of.puts("# User .cpp directories (from .cpp's on Verilator command line)\n");
	of.puts("VM_USER_DIR = \\\n");
	for (V3StringSet::iterator it = dirs.begin(); it!=dirs.end(); ++it) {
	    of.puts("\t"+*it+" \\\n");
	}
	of.puts("\n");

	of.puts("\n### Default rules...\n");
	of.puts("# Include list of all generated classes\n");
	of.puts("include "+v3Global.opt.prefix()+"_classes.mk\n");
	of.puts("# Include global rules\n");
	of.puts("include $(VERILATOR_ROOT)/include/verilated.mk\n");

	if (v3Global.opt.exe()) {
	    of.puts("\n### Executable rules... (from --exe)\n");
	    of.puts("VPATH += $(VM_USER_DIR)\n");
	    of.puts("\n");
	    for (V3StringSet::const_iterator it = v3Global.opt.cppFiles().begin();
		 it != v3Global.opt.cppFiles().end(); ++it) {
		string cppfile = *it;
		string basename = V3Options::filenameNonExt(cppfile);
		of.puts(basename+".o: "+cppfile+"\n");
		of.puts("\t$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OPT_FAST) -c -o $@ $<\n");
	    }

	    of.puts("\n### Link rules... (from --exe)\n");
	    of.puts(v3Global.opt.exeName()+": $(VK_USER_OBJS) $(VK_GLOBAL_OBJS) $(VM_PREFIX)__ALL.a\n");
	    of.puts("\t$(LINK) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@ $(LIBS) $(SC_LIBS) 2>&1 | c++filt\n");
	    of.puts("\n");
	}

	of.puts("\n");
	of.putsHeader();
    }