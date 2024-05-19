#include "vm.h"

int main() {
    VM vm;
    vector<i32> prgm{3, 4, 0x6001, 0x0000};
    vm.loadPrgm(prgm);
    vm.run();
    return 0;
}