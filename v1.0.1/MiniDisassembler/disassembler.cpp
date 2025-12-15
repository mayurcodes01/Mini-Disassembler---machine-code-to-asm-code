#include "disassembler.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>


struct OpcodeEntry {
	uint8_t code;
	std::string mnemonic;
	InstrType type;
};


const OpcodeEntry opcodeTable[] = {
{0xB8, "MOV EAX, imm32", InstrType::MOV},
{0xBB, "MOV EBX, imm32", InstrType::MOV},
{0x01, "ADD r/m32, r32", InstrType::ADD},
{0x29, "SUB r/m32, r32", InstrType::SUB},
{0xE9, "JMP rel32", InstrType::JMP},
};


Disassembler::Disassembler(const std::string& filePath) {
	std::ifstream file(filePath, std::ios::binary);
	if (!file) {
		std::cerr << "Cannot open file: " << filePath << std::endl;
		return;
	}
	buffer = std::vector<uint8_t>(std::istreambuf_iterator<char>(file), {});
}


void Disassembler::decodeInstruction(size_t& idx) {
	if (idx >= buffer.size()) return;


	uint8_t byte = buffer[idx];
	for (const auto& entry : opcodeTable) {
		if (byte == entry.code) {
			Instruction instr;
			instr.type = entry.type;
			instr.mnemonic = entry.mnemonic;
			instr.offset = idx;
			instr.operands = "";
			instructions.push_back(instr);
			idx += 1;
			return;
		}
	}


	instructions.push_back({ InstrType::UNKNOWN, "UNKNOWN", "", idx });
	idx += 1;
}


void Disassembler::parse() {
	size_t idx = 0;
	while (idx < buffer.size()) {
		decodeInstruction(idx);
	}
}


void Disassembler::printInstructions() const {
	for (const auto& instr : instructions) {
		std::cout << std::hex << instr.offset << " : "
			<< instr.mnemonic << " " << instr.operands << "\n";
	}
}