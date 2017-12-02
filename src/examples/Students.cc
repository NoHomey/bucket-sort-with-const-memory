#include "../SingleLinkedList/SingleLinkedList.thd"
#include <cstdlib>
#include <cstdlib>
#include <iostream>

struct Student {
    using Number = unsigned short;

    using GroupId = unsigned char;

    Student(const Number number, const GroupId groupId) noexcept
    : number{number}, groupId{groupId} { }

    Number number;

    GroupId groupId;
};

using Students = SingleLinkedList<Student>;

const unsigned seed = 4096;

const Student::GroupId groups = 7;

std::size_t groupSelector(const Student& student) noexcept {
    return student.groupId;
}

Student stubStudent() noexcept {
    const Student::Number number = static_cast<Student::Number>(std::rand());
    return {number,  static_cast<Student::GroupId>(number % groups)};
}

void print(const Students& students) noexcept {
    for(Students::ConstIterator iter = students.first(); iter; ++iter) {
        std::cout << static_cast<unsigned short>(iter->groupId) << ' ' << iter->number << std::endl;
    }
    std::cout << "count " << students.length() << std::endl; 
}

int main() {
    std::srand(seed);

    Students students;

    for(std::size_t c = 0; c < 10000; ++c) {
        students.append(stubStudent());
    }

    print(students);

    std::cout << "-----------------------------------------------------" << std::endl;

    students.bucketSort<groups>(groupSelector);

    print(students);

    return 0;
}