/**
 * Write an 8-bit integer in memory.
 * @param memory	Memory to write in.
 * @param address	Address to write integer to.
 * @param val		Integer to write.
 * @ingroup memory
 */
void gliss_mem_write8(gliss_memory_t* mem, gliss_address_t address, uint8_t val)
{
    gliss_address_t offset;
    page_entry_t*   pte;
    pte    = mem_get_page(mem, address);
    offset = FMOD(address, MEM_PAGE_SIZE);


#   if HOST_ENDIANNESS != TARGET_ENDIANNESS
    	pte->storage[MEM_PAGE_SIZE-1 - offset] = val;
#   else
    	pte->storage[offset] = val;
#   endif

#	ifdef GLISS_MEM_SPY
    	mem->spy_fun(mem, address, sizeof(val), gliss_access_write, mem->spy_data);
#	endif
}