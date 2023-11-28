#pragma once

#include <cstddef>
#include <iostream>

class ListFrame;

class Frame
{
public: 

	Frame();
	Frame(Frame&& frame) noexcept;

	~Frame();

	//решил создать enum на сллучай, если программа будет дальше маштабироваться,enum 
	// в этом случае упростит данное маштабирвоание
	enum sizeEnum {
		sizeIdentifier = 2,
		sizeAddress = 2,
		sizeCommand = 2,
		sizeDataLength = 4,

		sizeOffInformation = 18
	};

	int getDataLengthtoInt() const;
	
	//void setArrayData(const size_t size);

private:

	char identifier[sizeIdentifier];
	char address[sizeAddress];
	char command[sizeCommand];
	char dataLength[sizeDataLength];
	char* arrayData = nullptr;

	friend class ListFrame;
};

