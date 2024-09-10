/*{{{  PcmTranscoder_SetGlobalParams*/
static MME_ERROR PcmTranscoder_SetGlobalParams(void* Context, MME_Command_t* Command)
{
    struct PcmContext_s*                PcmContext      = (struct PcmContext_s*)Context;
    MME_LxAudioDecoderGlobalParams_t*   GlobalParams    = Command->Param_p;
    MME_CommandStatus_t*                CommandStatus   = &Command->CmdStatus;
    MME_LxPcmAudioConfig_t*             Config          = (MME_LxPcmAudioConfig_t*)GlobalParams->DecConfig;

    CommandStatus->Error        = InitializeContext (PcmContext, Config);
    CommandStatus->State        = MME_COMMAND_COMPLETED;

    return CommandStatus->Error;
}