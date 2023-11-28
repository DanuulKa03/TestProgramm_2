
#include "Frame.h"

Frame::Frame()
{
}

Frame::Frame(Frame&& moved) noexcept
{
	std::swap(identifier, moved.identifier);
	std::swap(address, moved.address);
	std::swap(command, moved.command);
	std::swap(dataLength, moved.dataLength);
	arrayData = moved.arrayData;
	
	moved.arrayData = nullptr;
}

Frame::~Frame()
{
	if (arrayData) delete[] arrayData;
}

int Frame::getDataLengthtoInt() const
{
	int integerValue = 0;

	for (int i = 0; i < sizeDataLength; ++i) {
		integerValue = (integerValue << 8) | static_cast<unsigned char>(dataLength[i]);
	}

	return integerValue;
}

//void Frame::setArrayData(const size_t size)
//{
//	arrayData = new char[size];
//}