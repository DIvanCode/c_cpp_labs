#include "bin_manip.h"
#include "employees.h"

#include <iostream>

employees::EmployeesArray employeesList(0);

bool process_operation() {
    std::string operation;
    std::cin >> operation;

    if (operation == "exit")
        return false;

    if (operation == "load") {
        std::string file_name;
        std::cin >> file_name;

        std::ifstream in(file_name, std::ios::binary);

        int n;
        in >> bin_manip::read_le_int32(n);

        for (int i = 0; i < n; ++i) {
            int type;
            in >> bin_manip::read_le_int32(type);

            if (type == 1) {
                auto employee = new employees::Developer();
                in >> *employee;
                employeesList.add(employee);
            } else {
                auto employee = new employees::SalesManager();
                in >> *employee;
                employeesList.add(employee);
            }
        }

        in.close();
    } else if (operation == "save") {
        std::string file_name;
        std::cin >> file_name;

        std::ofstream out(file_name, std::ios::binary);

        out << employeesList;

        out.close();
    } else if (operation == "add") {
        int type;
        std::cin >> type;

        if (type == 1) {
            auto employee = new employees::Developer();
            std::cin >> *employee;
            employeesList.add(employee);
        } else {
            auto employee = new employees::SalesManager();
            std::cin >> *employee;
            employeesList.add(employee);
        }
    } else {
        std::cout << employeesList << std::endl;
    }

    return true;
}

int main() {
    while (process_operation());
    return 0;
}