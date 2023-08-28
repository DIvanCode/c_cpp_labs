#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <iostream>
#include <stdexcept>

namespace employees {
    class Employee {
    public:
        Employee();

        explicit Employee(char *name,
                          int32_t base_salary = 0);

        Employee(const Employee &other);

        Employee &operator=(const Employee &other);

        virtual ~Employee();

        virtual int salary() const = 0;

        friend std::ostream &operator<<(std::ostream &out, Employee &employee);

        friend std::istream &operator>>(std::istream &in, Employee &employee);

        friend std::ofstream &operator<<(std::ofstream &out, Employee &employee);

        friend std::ifstream &operator>>(std::ifstream &in, Employee &employee);

        virtual void print(std::ostream &out);

        virtual void input(std::istream &in);

        virtual void printf(std::ofstream &out);

        virtual void inputf(std::ifstream &in);

    protected:
        char *_name;
        int32_t _base_salary;
    };

    class Developer : public Employee {
    public:
        Developer();

        explicit Developer(char *name,
                           int32_t base_salary = 0,
                           bool has_bonus = false);

        Developer(const Developer &other);

        Developer &operator=(const Developer &other);

        ~Developer() override = default;

        int salary() const override;

        void print(std::ostream &out) override;

        void input(std::istream &in) override;

        void printf(std::ofstream &out) override;

        void inputf(std::ifstream &in) override;

    private:
        bool _has_bonus;
    };

    class SalesManager : public Employee {
    public:
        SalesManager();

        explicit SalesManager(char *name,
                              int32_t base_salary = 0,
                              int32_t sold_nm = 0,
                              int32_t price = 0);

        SalesManager(const SalesManager &other);

        SalesManager &operator=(const SalesManager &other);

        ~SalesManager() override = default;

        int salary() const override;

        void print(std::ostream &out) override;

        void input(std::istream &in) override;

        void printf(std::ofstream &out) override;

        void inputf(std::ifstream &in) override;

    private:
        int32_t _sold_nm, _price;
    };

    class EmployeesArray {
    public:
        EmployeesArray();

        explicit EmployeesArray(size_t capacity);

        EmployeesArray(const EmployeesArray &other) = delete;

        EmployeesArray &operator=(const EmployeesArray &other) = delete;

        ~EmployeesArray();

        void add(Employee *e);

        int total_salary() const;

        friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &employeesArray);

        friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &employeesArray);

    private:
        size_t _capacity;
        size_t _size;
        Employee **_employees;

        void _reserve(size_t new_capacity);
    };
}

#endif