#include <iostream>

struct CustomerInfo
{
	std::string name;
	std::string phoneNumber;

	unsigned int unansweredCount = 0;

	bool operator == (const CustomerInfo& other)
	{
		return this->name == other.name && this->phoneNumber == other.phoneNumber;
	}
};