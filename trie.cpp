#include <iostream>
#include <list>
#include "Info.cpp"
#include <vector>
#include "customer.cpp"

class Trie
{
private:
	//undrlying container datastructure of Trie class
	struct Node
	{
		char letter = '\0';
		bool isLast = true;

		std::vector<CustomerInfo> info;

		Node* parent = nullptr;
		std::vector<Node*> children;
	};

	//Root node
	Node* Root = nullptr;

	//addds a child to the Trie
	void HelperFunctionAddChild(std::string surnameToAdd, CustomerInfo toAdd, Node* current, unsigned int position = 0)
	{
		for (int i = 0; i < current->children.size(); i++)
		{
			if (current->children[i]->letter == surnameToAdd[position])
			{
				//letter already exists and its the last letter
				if (position + 1 == surnameToAdd.size())
				{
					current->info.push_back(toAdd);

					return;
				}
				//letter exists but is not last, create a "split" - child
				else
				{
					HelperFunctionAddChild(surnameToAdd, toAdd, current->children[i], position + 1);
				}
			};
		}
		// letter is not yet contianed

		//creates a new letter Node
		Node* add = new Node();
		add->parent = current;
		add->letter = surnameToAdd[position];
		add->isLast = false;

		//letter is the last letter
		if (position + 1 == surnameToAdd.size())
		{
			add->isLast = true;
			current->children.push_back(add);
			return;
		}
		//letter is not yet the last letter of surname
		current->children.push_back(add);

		HelperFunctionAddChild(surnameToAdd, toAdd, add, position + 1);
	}

	// searches for the customer by phone number
	CustomerInfo* HelperFunctionGetCustomer(std::string phoneNumber, Node* current, std::string& name)
	{
		// Check current node's info vector if it's a complete word
		if (current->isLast)
		{
			for (int i = 0; i < current->info.size(); i++)
			{
				// Assuming phoneNumber field exists
				if (current->info[i].phoneNumber == phoneNumber)
				{
					return &current->info[i];
				}
			}
		}

		// Recursively search through children
		for (int i = 0; i < current->children.size(); i++)
		{
			// Add the current letter to the name
			name.push_back(current->children[i]->letter);
			CustomerInfo* result = HelperFunctionGetCustomer(phoneNumber, current->children[i], name);
			if (result != nullptr)
			{
				return result; // Keep the name as is, since we found a match
			}
			// If no match in this path, backtrack by removing the last letter
			name.pop_back();
		}

		return nullptr; // No match found in this subtree
	}

public:

	Trie()
	{
		Root = new Node();
	}

	void AddChild(std::string surnameToAdd, CustomerInfo toAdd)
	{
		HelperFunctionAddChild(surnameToAdd, toAdd, Root);
	}

	//retturns a customer 
	Customer& SearchByPhoneNumber(std::string phoneNumber)
	{
		std::string surname;
		CustomerInfo* result = HelperFunctionGetCustomer(phoneNumber, Root, surname);
		if (result != nullptr)
		{
			Customer c = AddCustomerInfo(*result, surname);
			return c;
		}

		throw std::runtime_error("Customer not found for phone number: " + phoneNumber);
	}

	Customer& AddCustomerInfo(CustomerInfo& toAdd, std::string surname)
	{
		Customer c;
		c.otherInfo = toAdd;
		c.surname = surname;

		return c;
	}

	void clear() {}

	~Trie()
	{
		clear();
		delete Root;
	}

};