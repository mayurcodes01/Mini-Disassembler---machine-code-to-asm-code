#include "disassembler.hpp"
#include <iostream>


int main() {
	Disassembler dis("test.bin"); // Replace with your binary file
	dis.parse();
	dis.printInstructions();
	return 0;
}