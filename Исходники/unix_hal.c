/*
 * sigaltstack will cause this function to be called on an alternate stack.
 * This allows us to bootstrap new threads.
 */
void HalStackTrampoline( int SignalNumber )
{
        int status;
        //Save stack startup state before releaseing the tempContext.
        STACK_INIT_ROUTINE * foo = halTempContext->Foo;
        void * arg = halTempContext->Arg;

        status = _setjmp( halTempContext->Registers );

        if( status == 0 ) {
                //Because status was 0 we know that this is the creation of
                //the stack frame. We can use the locals to construct the frame.

                halTempContextProcessed = TRUE;
                halTempContext = NULL;
                return;
        } else {
                //If we get here, then someone has jumped into a newly created thread.
                //Test to make sure we are atomic
                ASSERT( HalIsIrqAtomic(IRQ_LEVEL_MAX) );

                foo(arg);

                //Returning from a function which was invoked by siglongjmp is not
                //supported. Foo should never retrun.
                HalPanic("Tried to return from trampoline!");
                return;
        }
}