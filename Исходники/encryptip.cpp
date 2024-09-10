/*
 * @func init_random_iv initiates iv with a random number
 * @param OUT uint8_t* iv, pointer to output random IV
 * @return encip_ret_e: 
 * ENCIP_ERROR_RANDIV_INVALID_PARAM if iv is NULL
 * ENCIP_ERROR_RDRAND_NOT_SUPPORTED if platform does not support RDRAND
 * ENCIP_ERROR_RDRAND_FAILED if random number gneration fails
    * ENCIP_SUCCESS if successfull
 */
static encip_ret_e init_random_iv(OUT uint8_t* iv)
{
    if(NULL == iv)
        return ENCIP_ERROR_RANDIV_INVALID_PARAM;
    if(rdrand_supported())
    {
        uint32_t* ivp = (uint32_t*)iv;
        // Get a random IV for encryption: 
        for(uint32_t i=0;i < SGX_AESGCM_IV_SIZE / sizeof(uint32_t);i++)
        {
            uint32_t randval = 0;
            int rdrand32ret = _rdrand32_step(&randval);
            if(RDRAND_SUCCESS != rdrand32ret)
                return ENCIP_ERROR_RDRAND_FAILED;
            *ivp = randval;
            ivp++;
        }
    }
    else
    {
        return ENCIP_ERROR_RDRAND_NOT_SUPPORTED;
    }
    return ENCIP_SUCCESS;
}