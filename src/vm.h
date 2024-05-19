#ifndef VM_H
#define VM_H

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>

typedef int32_t i32;

using namespace std;

const i32 INSTR_BIT = 24;
const i32 OPCODE_MASK = 0xf0000000;
const i32 IFUN_MASK = 0x0f000000;
const i32 RA_MASK = 0x00f00000;
const i32 RB_MASK = 0x000f0000;
const i32 DATA_MASK = 0x0000ffff;

class VM {
    i32 pc;  
    i32 rsp;
    vector<i32> stack;
    uint8_t rgstr[16];
    
    uint8_t opCode; 
    uint8_t ifun;
    uint8_t ra;
    uint8_t rb;
    i32 data;

    uint8_t is_running;

    void fetch();
    void decode();
    void execute();
    i32 ALU(uint8_t ifun);

    public:
    VM();
    void run();
    void loadPrgm(vector<i32> prgm);
};

#endif