#include <iostream>
#include <map>
#include <vector>
#include <utility>

struct Toy {
  char* family;
  unsigned int department;
  unsigned int year_of_birth;
};

struct DepartmentPayload {
  unsigned int employees_count;
  unsigned int sum_of_birth_years;
};

int main() {
  std::vector<Toy> employees = {
    Toy { new char[] { "Empl1" }, 1, 1991 },
    Toy { new char[] { "Empl2" }, 2, 1992 },
    Toy { new char[] { "Empl3" }, 1, 1993 },
    Toy { new char[] { "Empl4" }, 2, 1994 },
    Toy { new char[] { "Empl5" }, 1, 1995 },
    Toy { new char[] { "Empl6" }, 2, 1996 },
    Toy { new char[] { "Empl7" }, 1, 1997 },
    Toy { new char[] { "Empl8" }, 2, 1998 },
    Toy { new char[] { "Empl9" }, 1, 1999 },
    Toy { new char[] { "Empl10" }, 3, 2000 },
    Toy { new char[] { "Empl11" }, 3, 2001 },
  };


  std::map<int, DepartmentPayload> department_state;

  for (const auto &employee : employees) {
    auto department_code = employee.department;

    auto department = department_state.find(employee.department);

    if (department == department_state.end()) {
      department_state[employee.department] = DepartmentPayload {1, employee.year_of_birth};
    } else {
      (*department).second.employees_count++;
      (*department).second.sum_of_birth_years += employee.year_of_birth;
    }
  }

  std::cout.precision(4);
  std::fixed(std::cout);

  for (const auto &department : department_state) {
    const auto department_code = department.first;
    const auto employees_count = department.second.employees_count;
    const auto average_year = static_cast<float> ( department.second.sum_of_birth_years ) / employees_count;

    std::cout << "Department: " << department_code << " ";
    std::cout << "Average year: " << average_year << std::endl;
  }

  return 0;
}
