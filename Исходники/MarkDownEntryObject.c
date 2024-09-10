char*
OxMarkDownToHtml(char* sMarkDown)
{
	hoedown_renderer *renderer;
	hoedown_document *document;
	hoedown_buffer *buffer;
	unsigned int extensions = 0, render_flags = 0;
	const uint8_t *sHtml;

	renderer = hoedown_html_renderer_new(render_flags, 0);
	document = hoedown_document_new(renderer, extensions, 16);
	buffer = hoedown_buffer_new(16);
    
	hoedown_document_render(document, buffer, (const uint8_t *)sMarkDown, strlen(sMarkDown));
	sHtml = (char*)OxAllocate(buffer->size + 1);
	StringCchCopyA(sHtml, buffer->size + 1, buffer->data);
	hoedown_buffer_reset(buffer);
	hoedown_html_smartypants(buffer, sHtml, buffer->size);
	
	hoedown_buffer_free(buffer);
	hoedown_document_free(document);
	hoedown_html_renderer_free(renderer);

	return sHtml;
}