std::vector<RAWINPUTDEVICELIST> rawinput_device_list(){
	UINT _num_devices;
    UINT _result;

	if(0 != GetRawInputDeviceList(0, &_num_devices, sizeof(RAWINPUTDEVICELIST))){
		std::cerr << "0 != GetRawInputDeviceList(0, &num_devices, sizeof(RAWINPUTDEVICELIST))" << std::endl;
        return std::vector<RAWINPUTDEVICELIST>();
	}

    std::vector<RAWINPUTDEVICELIST> device_list(_num_devices);
    _result = GetRawInputDeviceList(&device_list[0], &_num_devices, sizeof(RAWINPUTDEVICELIST));
	if(-1 == _result){
		std::cerr << "-1 == _result" << std::endl;
		return std::vector<RAWINPUTDEVICELIST>();
	}
	
    device_list.resize(_result);
	return device_list;
}