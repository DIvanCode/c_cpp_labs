#include "matrix.h"

#include <iostream>

const int REGS = 10;

Matrix regs[REGS];

bool process(const std::string &type) {
    if (type == "exit") {
        return false;
    } else if (type == "load") {
        std::string reg, file_name;
        std::cin >> reg >> file_name;

        size_t reg_number = reg.back() - '0';

        regs[reg_number].load(file_name);
    } else if (type == "print") {
        std::string reg;
        std::cin >> reg;

        size_t reg_number = reg.back() - '0';

        regs[reg_number].print(std::cout);
    } else if (type == "add") {
        std::string reg1, reg2;
        std::cin >> reg1 >> reg2;

        size_t reg1_number = reg1.back() - '0';
        size_t reg2_number = reg2.back() - '0';

        regs[reg1_number].add(regs[reg2_number]);
    } else if (type == "mul") {
        std::string reg1, reg2;
        std::cin >> reg1 >> reg2;

        size_t reg1_number = reg1.back() - '0';
        size_t reg2_number = reg2.back() - '0';

        regs[reg1_number].mul(regs[reg2_number]);
    } else if (type == "elem") {
        std::string reg;
        int row, col;
        std::cin >> reg >> row >> col;

        size_t reg_number = reg.back() - '0';

        regs[reg_number].elem(std::cout, row, col);
    }

    return true;
}


int main() {
    bool go = true;
    std::string type;
    while (go && std::cin >> type) {
        try {
            go = process(type);
        } catch (const MatrixException &m) {
            std::cout << m.what() << std::endl;
        }
    }
    return 0;
}