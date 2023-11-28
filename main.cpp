#include <iostream>

#include "ListFrame.h"

int main()
{
	ListFrame a;
	a.LoadFromfile("test.raw");
	a.SaveToText("test.txt");
}