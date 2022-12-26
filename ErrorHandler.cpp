#include "ErrorHandler.h"

ErrorHandler::ErrorHandler()
{
	this->position = 0;
}

void ErrorHandler::Call(std::string error)
{
	for (int i = 0; i < this->position; i++)
	{
		std::cout << " ";
	}
	std::cout << "^ " << error << std::endl;
}

void ErrorHandler::SetPosition(int position)
{
	this->position = position;
}
