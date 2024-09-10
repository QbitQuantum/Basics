int main(int argc, char **argv){
    // Load the bitcode
    cl::ParseCommandLineOptions(argc, argv, "helper_call_modifier\n");
    SMDiagnostic Err;     
    LLVMContext &Context = getGlobalContext();
    Module *Mod = ParseIRFile(InputFile, Err, Context);
    if (!Mod) {
        Err.print(argv[0], errs());
        exit(1);
    }
    
    /*
     * This iterates through the list of functions, copies/renames, and deletes
     * the original function.  This is how we have to do it with the while loop
     * because of how the LLVM function list is implemented.
     */
    Module::iterator i = Mod->begin();
    while (i != Mod->end()){
        Function *f = i;
        i++;
        
        Module *m = f->getParent();
        assert(m);
        if (!f->isDeclaration()){ // internal functions only
            StringRef fname = f->getName();
            if (!fname.compare("__ldb_mmu")
                    || !fname.compare("__ldw_mmu")
                    || !fname.compare("__ldl_mmu")
                    || !fname.compare("__ldq_mmu")
                    || !fname.compare("__stb_mmu")
                    || !fname.compare("__stw_mmu")
                    || !fname.compare("__stl_mmu")
                    || !fname.compare("__stq_mmu")){

                /* Replace LLVM memory functions with ASM panda (logging) memory
                 * functions and delete original.  For example, we want to call
                 * out of the LLVM module to __ldb_mmu_panda().
                 */
                Function *pandaFunc =
                    m->getFunction(StringRef(f->getName().str() + "_panda"));
                assert(pandaFunc);
                if (!pandaFunc->isDeclaration()){
                    pandaFunc->deleteBody();
                }
                f->replaceAllUsesWith(pandaFunc);
                f->eraseFromParent();
            }
            else if (!fname.compare("slow_ldb_mmu")
                    || !fname.compare("slow_ldw_mmu")
                    || !fname.compare("slow_ldl_mmu")
                    || !fname.compare("slow_ldq_mmu")
                    || !fname.compare("slow_stb_mmu")
                    || !fname.compare("slow_stw_mmu")
                    || !fname.compare("slow_stl_mmu")
                    || !fname.compare("slow_stq_mmu")
                    || !fname.compare("slow_ldb_mmu_panda")
                    || !fname.compare("slow_ldw_mmu_panda")
                    || !fname.compare("slow_ldl_mmu_panda")
                    || !fname.compare("slow_ldq_mmu_panda")
                    || !fname.compare("slow_stb_mmu_panda")
                    || !fname.compare("slow_stw_mmu_panda")
                    || !fname.compare("slow_stl_mmu_panda")
                    || !fname.compare("slow_stq_mmu_panda")){

                /* These functions are just artifacts, and are only contained
                 * within the previous functions.  We want these deleted from
                 * the LLVM module too, this is just kind of a hacky way to make
                 * sure the functions are deleted in the right order without
                 * making LLVM angry.
                 */
                if (f->hasNUsesOrMore(3)){
                    m->getFunctionList().remove(f);
                    m->getFunctionList().push_back(f);
                    continue;
                }
                else {
                    f->eraseFromParent();
                }
            }
            else {
                ValueToValueMapTy VMap;
                Function *newFunc = CloneFunction(f, VMap, false);
                std::string origName = f->getName();
                std::string newName = origName.append("_llvm");
                newFunc->setName(newName);
                /*
                 * XXX: We need to remove stack smash protection from helper
                 * functions that are to be compiled with the JIT.  There is a bug
                 * in LLVM 3.0 that causes the JIT to generate stack protection code
                 * that causes the program to segfault.  More information available
                 * here: http://llvm.org/bugs/show_bug.cgi?id=11089
                 */
                const AttributeSet AS = newFunc->getAttributes();
                newFunc->setAttributes(AS.removeAttribute(newFunc->getContext(),
                    AttributeSet::FunctionIndex, Attribute::StackProtectReq));
                // push to the front so the iterator doesn't see them again
                m->getFunctionList().push_front(newFunc);
                f->replaceAllUsesWith(newFunc);
                f->eraseFromParent();
            }
        }
    }
    
    // Verify the new bitcode and write it out, printing errors if necessary
    std::string errstring;
    verifyModule(*Mod, PrintMessageAction, &errstring);
    raw_fd_ostream *fstream = new raw_fd_ostream(OutputFile.c_str(), errstring);
    WriteBitcodeToFile(Mod, *fstream);
    printf("%s", errstring.c_str());
    fstream->close();

    return 0;
}