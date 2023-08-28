#include "employees.h"
#include "bin_manip.h"

namespace employees {
    Employee::Employee() {
        _name = new char[1];
        _name[0] = '\0';

        _base_salary = 0;
    }

    Employee::Employee(char *name,
                       int32_t base_salary) {
        if (name) {
            _name = new char[strlen(name) + 1];
            _name[strlen(name)] = '\0';
            strcpy(_name, name);
        } else {
            _name = new char[1];
            _name[0] = '\0';
        }

        _base_salary = base_salary;
    }

    Employee::Employee(const Employee &other) {
        _name = new char[strlen(other._name) + 1];
        strcpy(_name, other._name);

        _base_salary = other._base_salary;
    }

    Employee &Employee::operator=(const Employee &other) {
        if (this == &other)
            return *this;

        delete[] _name;

        _name = new char[strlen(other._name) + 1];
        strcpy(_name, other._name);

        _base_salary = other._base_salary;

        return *this;
    }

    Employee::~Employee() {
        delete[] _name;
    }

    std::ostream &operator<<(std::ostream &out, Employee &employee) {
        employee.print(out);
        return out;
    }

    std::istream &operator>>(std::istream &in, Employee &employee) {
        employee.input(in);
        return in;
    }

    std::ofstream &operator<<(std::ofstream &out, Employee &employee) {
        employee.printf(out);
        return out;
    }

    std::ifstream &operator>>(std::ifstream &in, Employee &employee) {
        employee.inputf(in);
        return in;
    }

    void Employee::print(std::ostream &out) {
        out << "Name: " << _name << std::endl <<
            "Base Salary: " << _base_salary;
    }

    void Employee::input(std::istream &in) {
        std::string name;
        in >> name >> _base_salary;

        delete[] _name;

        _name = new char[name.size() + 1];
        for (size_t i = 0; i < name.size(); ++i)
            _name[i] = name[i];
        _name[name.size()] = '\0';
    }

    void Employee::printf(std::ofstream &out) {
        out << bin_manip::write_c_str(_name) << bin_manip::write_le_int32(_base_salary);
    }

    void Employee::inputf(std::ifstream &in) {
        in >> bin_manip::read_c_str(_name, 256) >> bin_manip::read_le_int32(_base_salary);
    }

    Developer::Developer() : Employee() {
        _has_bonus = false;
    }

    Developer::Developer(char *name,
                         int32_t base_salary,
                         bool has_bonus) : Employee(name, base_salary) {
        _has_bonus = has_bonus;
    }

    Developer::Developer(const Developer &other) : Employee(other) {
        _has_bonus = other._has_bonus;
    }

    Developer &Developer::operator=(const Developer &other) {
        if (this == &other)
            return *this;

        Employee::operator=(other);

        _has_bonus = other._has_bonus;

        return *this;
    }

    int Developer::salary() const {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
        return salary;
    }

    void Developer::print(std::ostream &out) {
        out << "Developer" << std::endl;
        Employee::print(out);
        out << std::endl << "Has bonus: " << (_has_bonus ? "+" : "-");
    }

    void Developer::input(std::istream &in) {
        Employee::input(in);
        in >> _has_bonus;
    }

    void Developer::printf(std::ofstream &out) {
        out << bin_manip::write_le_int32(1);
        Employee::printf(out);
        out << bin_manip::write_bool(_has_bonus);
    }

    void Developer::inputf(std::ifstream &in) {
        Employee::inputf(in);
        in >> bin_manip::read_bool(_has_bonus);
    }

    SalesManager::SalesManager() : Employee() {
        _sold_nm = 0;
        _price = 0;
    }

    SalesManager::SalesManager(char *name,
                               int32_t base_salary,
                               int32_t sold_nm,
                               int32_t price) : Employee(name, base_salary) {
        _sold_nm = sold_nm;
        _price = price;
    }

    SalesManager::SalesManager(const SalesManager &other) : Employee(other) {
        _sold_nm = other._sold_nm;
        _price = other._price;
    }

    SalesManager &SalesManager::operator=(const SalesManager &other) {
        if (this == &other)
            return *this;

        Employee::operator=(other);

        _sold_nm = other._sold_nm;
        _price = other._price;

        return *this;
    }

    int SalesManager::salary() const {
        return int(_base_salary + _sold_nm * _price * 0.01);
    }

    void SalesManager::print(std::ostream &out) {
        out << "Sales Manager" << std::endl;
        Employee::print(out);
        out << std::endl <<
            "Sold items: " << _sold_nm << std::endl <<
            "Item price: " << _price;
    }

    void SalesManager::input(std::istream &in) {
        Employee::input(in);
        in >> _sold_nm >> _price;
    }

    void SalesManager::printf(std::ofstream &out) {
        out << bin_manip::write_le_int32(2);
        Employee::printf(out);
        out << bin_manip::write_le_int32(_sold_nm) << bin_manip::write_le_int32(_price);
    }

    void SalesManager::inputf(std::ifstream &in) {
        Employee::inputf(in);
        in >> bin_manip::read_le_int32(_sold_nm) >> bin_manip::read_le_int32(_price);
    }

    EmployeesArray::EmployeesArray() {
        _size = 0;
        _capacity = 0;
        _employees = nullptr;
    }

    EmployeesArray::EmployeesArray(size_t capacity) {
        _capacity = capacity;
        _size = 0;
        _employees = nullptr;

        if (_capacity == 0)
            return;

        _employees = new Employee *[_capacity];
        std::fill(_employees, _employees + _capacity, nullptr);
    }

    EmployeesArray::~EmployeesArray() {
        if (!_employees)
            return;

        for (size_t i = 0; i < _capacity; ++i) {
            if (_employees[i] == nullptr)
                continue;
            delete _employees[i];
        }

        delete[] _employees;
    }

    void EmployeesArray::_reserve(size_t new_capacity) {
        if (_capacity >= new_capacity) return;

        auto new_employees = new Employee *[new_capacity];
        std::fill(new_employees, new_employees + new_capacity, nullptr);
        std::memcpy(new_employees, _employees, _size * sizeof(Employee *));

        delete[] _employees;

        _capacity = new_capacity;
        _employees = new_employees;
    }

    void EmployeesArray::add(Employee *e) {
        if (e == nullptr)
            throw std::runtime_error("Cannon add null-Employee to EmployeesArray");

        if (_size == _capacity)
            _reserve(std::max((size_t) 1, _capacity) * 2);

        _employees[_size++] = e;
    }

    int EmployeesArray::total_salary() const {
        int total = 0;

        for (size_t i = 0; i < _size; ++i) {
            if (_employees[i] == nullptr)
                continue;
            total += _employees[i]->salary();
        }

        return total;
    }

    std::ostream &operator<<(std::ostream &out, const EmployeesArray &employeesArray) {
        for (size_t i = 0; i < employeesArray._size; ++i) {
            if (employeesArray._employees[i] == nullptr)
                continue;

            out << i + 1 << ". " << *employeesArray._employees[i] << std::endl;
        }

        out << "== Total salary: " << employeesArray.total_salary() << std::endl;

        return out;
    }

    std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &employeesArray) {
        out << bin_manip::write_le_int32(int32_t(employeesArray._size));

        for (size_t i = 0; i < employeesArray._size; ++i) {
            if (employeesArray._employees[i] == nullptr)
                continue;

            out << *employeesArray._employees[i];
        }

        return out;
    }
}