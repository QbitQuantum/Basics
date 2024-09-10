void Beam::update()
{
    uint32_t button = InfraRood::getInstance()->read();
    cs->setHex(button);
    Uart *uart = Uart::getInstance();

    switch (button >> 16)
    {
    case ::TerasicRemote::A:
        uart->puts("A\r\n");
        break;
    case TerasicRemote::B:
        uart->puts("B\r\n");
        break;
    case TerasicRemote::C:
        uart->puts("C\r\n");
        break;
    case TerasicRemote::POWER:
        uart->puts("Power\r\n");
        break;
    case TerasicRemote::NUM_0:
        uart->puts("0\r\n");
        break;
    case TerasicRemote::NUM_1:
        uart->puts("1\r\n");
        break;
    case TerasicRemote::NUM_2:
        uart->puts("2\r\n");
        break;
    case TerasicRemote::NUM_3:
        uart->puts("3\r\n");
        break;
    case TerasicRemote::NUM_4:
        uart->puts("4\r\n");
        break;
    case TerasicRemote::NUM_5:
        uart->puts("5\r\n");
        break;
    case TerasicRemote::NUM_6:
        uart->puts("6\r\n");
        break;
    case TerasicRemote::NUM_7:
        uart->puts("7\r\n");
        break;
    case TerasicRemote::NUM_8:
        uart->puts("8\r\n");
        break;
    case TerasicRemote::NUM_9:
        uart->puts("9\r\n");
        break;
    case TerasicRemote::CH_UP:
        uart->puts("Channel Up\r\n");
        break;
    case TerasicRemote::CH_DOWN:
        uart->puts("Channel Down\r\n");
        break;
    case TerasicRemote::VOL_UP:
        uart->puts("Volume Up\r\n");
        break;
    case TerasicRemote::VOL_DOWN:
        uart->puts("Volume Down\r\n");
        break;
    case TerasicRemote::MENU:
        uart->puts("Menu\r\n");
        break;
    case TerasicRemote::RETURN:
        uart->puts("Return\r\n");
        break;
    case TerasicRemote::PLAY:
        uart->puts("Play\r\n");
        break;
    case TerasicRemote::LEFT:
        uart->puts("Left\r\n");
        break;
    case TerasicRemote::RIGHT:
        uart->puts("Right\r\n");
        break;
    case TerasicRemote::MUTE:
        uart->puts("Mute\r\n");
        break;
    default:
        uart->puts("Onbekende knop ingeduwd\r\n");
        break;
    }
}