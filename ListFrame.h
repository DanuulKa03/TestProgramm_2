#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdio>   
#include <cctype>
#include<iomanip>


#include "Frame.h"

class ListFrame
{
public:
	void LoadFromfile(const std::string fileName);
	void SaveToText(const std::string txtFileName);
	
	int charToInt(const char symbol);
	void insertDataToFile(Frame& frame, std::ofstream& file, size_t n);
	void service(Frame& frame, std::ifstream& file, size_t n);

private:
	std::vector<Frame> frameList;
};

