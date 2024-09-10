void renderstart(void *hrender)
{
    if (!hrender) return;
    RENDER *render = (RENDER*)hrender;
    waveOutRestart(render->hWaveOut);
    render->nRenderStatus &= ~RS_PAUSE;
}