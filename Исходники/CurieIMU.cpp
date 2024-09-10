/** Power on and prepare for general usage.
 * This will prepare the SPI communication interface for accessing the BMI160
 * on the Curie module, before calling BMI160::initialize() to activate the
 * BMI160 accelerometer and gyroscpoe with default settings.
 */
bool CurieIMUClass::begin()
{
    /* Configure pin-mux settings on the Intel Curie module to 
     * enable SPI mode usage */
    SET_PIN_MODE(35, QRK_PMUX_SEL_MODEA); // SPI1_SS_MISO 
    SET_PIN_MODE(36, QRK_PMUX_SEL_MODEA); // SPI1_SS_MOSI
    SET_PIN_MODE(37, QRK_PMUX_SEL_MODEA); // SPI1_SS_SCK
    SET_PIN_MODE(38, QRK_PMUX_SEL_MODEA); // SPI1_SS_CS_B[0]
 
    ss_spi_init();

    /* Perform a dummy read from 0x7f to switch to spi interface */
    uint8_t dummy_reg = 0x7F;
    serial_buffer_transfer(&dummy_reg, 1, 1);

    /* The SPI interface is ready - now invoke the base class initialization */
    BMI160Class::initialize();

    /** Verify the SPI connection.
     * MakgetGyroRatee sure the device is connected and responds as expected.
     * @return True if connection is valid, false otherwise
     */
    return (CURIE_IMU_CHIP_ID == getDeviceID());
}