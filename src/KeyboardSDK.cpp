#include "KeyboardSDK.h"


bool USBHelper::SendBuffer(std::vector<unsigned char> Buffer) {
	if (hid_send_feature_report(Handle, &Buffer[0], 1032) > 0) {
		return true;
	}
	return false;
}
bool USBHelper::SendRawBuffer(hid_device* device_handle, std::vector<unsigned char> Buffer) {
	if (hid_send_feature_report(device_handle, &Buffer[0], 1032) > 0) {
		return true;
	}
	return false;
}

bool KeyboardSDK::FindKeyboard() {

	BufferBuilder Buffer, Buffer2;

	Device.GetDevHandles(0x258A, 0x0016);
	Buffer.Build(0, 0, 0, ValidKeys);
	for (auto device : Device.Handle_vec) {


		if (Device.SendRawBuffer(device, Buffer.devBuffer)) {
			Device.Handle = device;
			return true;
			break;
		}

	}

	return false;
}

bool KeyboardSDK::SetColorAllKeys(int R, int G, int B) {
	BufferBuilder Buffer;
	Buffer.Build(R, G, B, ValidKeys);
	if (Device.SendBuffer(Buffer.devBuffer)) {
		return true;
	}
	return false;
}


void USBHelper::GetDevHandles(int VID, int PID) {
	devs = hid_enumerate(VID, PID);
	cur_dev = devs;
	while (cur_dev) {
		Handle = hid_open_path(cur_dev->path);
		Handle_vec.push_back(Handle);
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);

}

void USBHelper::GetPathList(int VID, int PID) {
	devs = hid_enumerate(VID, PID);
	cur_dev = devs;
	while (cur_dev) {
		DevPath = cur_dev->path;
		std::cout << DevPath << std::endl;
		paths_vec.push_back(DevPath);
		cur_dev = cur_dev->next;
	}
	hid_free_enumeration(devs);
}

void BufferBuilder::Build(uint8_t R, uint8_t G, uint8_t B, std::vector<KeyList> Keys) {
	initBuffer = { 0x06, 0x09, 0xAC, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00 };
	for (auto iterate : Keys) {
		BBuffer.at(iterate) = B;
		GBuffer.at(iterate) = G;
		RBuffer.at(iterate) = R;
	}
	devBuffer.insert(devBuffer.begin(), std::begin(initBuffer), std::end(initBuffer));
	devBuffer.insert(devBuffer.end(), std::begin(BBuffer), std::end(BBuffer));
	devBuffer.insert(devBuffer.end(), std::begin(GBuffer), std::end(GBuffer));
	devBuffer.insert(devBuffer.end(), std::begin(RBuffer), std::end(RBuffer));
}
//bool USBHelper::init() {
//	
//
//	devs = hid_enumerate(DEVICE_VID, DEVICE_PID);
//	cur_dev = devs;
//	while (cur_dev) {
//		KBHandle = hid_open_path(cur_dev->path);
//		cur_dev = cur_dev->next;
//		if (hid_send_feature_report(KBHandle, &fullVector[0], 1032) > 0) {
//			std::cout << cur_dev->path << std::endl;
//			std::cout << KBHandle << std::endl;
//			break;
//		}
//		
//
//	}
//	std::cout << KBHandle << std::endl;
//	hid_free_enumeration(devs);
//	return true;
//}