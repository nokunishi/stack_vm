#include "vm.h"


/*
unlike Y86-64, the instructions are at most 8 bytes
(Value, Data is at most 4 bytes, not 8)
*/


VM::VM() {
    pc = 0;
    rsp = 0;
    is_running = 1;
    
    for (int i = 0; i < 16; i++) {
        rgstr[i] = 0;
    }
}

void VM::fetch() {
    pc--;
}

void VM::decode() {
    opCode = (OPCODE_MASK & stack[pc]) >> (INSTR_BIT - 4);
    ifun =  (IFUN_MASK & stack[pc]) >> (INSTR_BIT - 8);
    ra = (RA_MASK & stack[pc]) >> (INSTR_BIT - 12);
    rb = (RB_MASK & stack[pc]) >> (INSTR_BIT - 16);

    cout << opCode << endl;
    data = DATA_MASK & stack[pc];
    cout << data << endl;
}

i32 VM::ALU(uint8_t ifun) {
    switch (ifun)
    {
    case 0:
        cout << "add " << stack[rsp - 1] << " " << stack[rsp] << endl;
        stack[rsp-1] += stack[rsp];
        rsp--;
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    default:
        break;
    } 
    return 0;
}

void VM::execute() {
    switch (opCode)
    {
    case 0:     
        cout << "halt" << endl;
        is_running = 0;
        break;
    case 1:    
        cout << "nop" << endl;
        break;
    case 6:
        rsp++;
        stack[rsp] = data;
    default:
        break;
    }
}



void VM::run() {
    fstream log("log.txt", fstream::out| fstream::in | fstream::trunc);
    streambuf * cout_buf = cout.rdbuf();
    streambuf * log_buf = log.rdbuf();
    cout.rdbuf(log_buf);

    pc++;

    cout << pc << endl;
    
    while (is_running == 1) {
        fetch();
        decode();
        execute();
        cout << "top of stack: " << stack[rsp] << endl;
    }  

    cout.rdbuf(cout_buf);
}

void VM::loadPrgm(vector<i32> prgm) {
    pc = prgm.size() - 1;
    rsp = prgm.size() - 1;

    for (i32 i = pc; i >= 0; i--) {
        stack.push_back(prgm[i]);
    }
}