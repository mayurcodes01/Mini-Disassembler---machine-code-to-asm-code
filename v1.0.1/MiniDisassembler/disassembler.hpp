#pragma once
#include <vector>
#include <string>


enum class InstrType {
	MOV,
	ADD,
	SUB,
	JMP,
	UNKNOWN
};


struct Instruction {
	InstrType type;
	std::string mnemonic;
	std::string operands;
	size_t offset;
};


class Disassembler {
public:
	Disassembler(const std::string& filePath);
	void parse();
	void printInstructions() const;


private:
	std::vector<uint8_t> buffer;
	std::vector<Instruction> instructions;


	void decodeInstruction(size_t& idx);
};

