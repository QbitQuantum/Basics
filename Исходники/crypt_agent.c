static TACommandVerdict encrypt_cmd(TAThread thread,TAInputStream stream)

{

    char* block;

    int edflag;

   

    // Prepare

    block=(char*)readPointer(&stream);

    edflag=readInt(&stream);



    START_TARGET_OPERATION(thread);

    errno=0;

    encrypt(block, edflag);

    END_TARGET_OPERATION(thread);



    // Response

    writePointer(thread, block);

    writeInt(thread, errno);



    sendResponse(thread);

    

    return taDefaultVerdict;

}