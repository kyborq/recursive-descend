#pragma once
#include <iostream>
#include <string>

class ErrorHandler
{
private:
	int position;
public:
	ErrorHandler();
	void Call(std::string);
	void SetPosition(int);
};

