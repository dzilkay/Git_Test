#include <iostream>
#include "Trie.cpp"

int main()
{
  std::cout << "github changed" << std::endl; 

  Trie test;
  CustomerInfo tmp;
  tmp.name = "William";
  tmp.phoneNumber = "0907349129";
  test.AddChild("Smith",tmp);

  std::cin.get();

  return 0;
}
