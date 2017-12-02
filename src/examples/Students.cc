#include "../SingleLinkedList/SingleLinkedList.thd"
#include "../SingleLinkedList/NodeAllocator/ChunkAllocator/ChunkAllocator.thd"
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <chrono>

struct Student {
    using Number = unsigned short;

    using GroupId = unsigned char;

    Student(const Number number, const GroupId groupId) noexcept
    : number{number}, groupId{groupId} { }

    Number number;

    GroupId groupId;
};

const unsigned seed = 4096;

const Student::GroupId groups = 7;

std::size_t groupSelector(const Student& student) noexcept {
    return student.groupId;
}

Student stubStudent() noexcept {
    const Student::Number number = static_cast<Student::Number>(std::rand());
    return {number,  static_cast<Student::GroupId>(number % groups)};
}

template<typename Students>
void run(Students& students) {
    std::srand(seed);

    auto start = std::chrono::steady_clock::now();

    for(std::size_t c = 0; c < 100000000; ++c) {
        students.append(stubStudent());
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "append: " << diff.count() << std::endl;

    start = std::chrono::steady_clock::now();
    students.template bucketSort<groups>(groupSelector);
    end = std::chrono::steady_clock::now();
    diff = end - start;
    std::cout << "sort: " << diff.count() << std::endl;
}

int main() {
    {
        SingleLinkedList<Student, ChunkAllocator> students{100000000};
        run(students);
    }
    
    {
        SingleLinkedList<Student, ChunkAllocator> students{100000};
        run(students);
    }
    
    {
        SingleLinkedList<Student, ChunkAllocator> students;
        run(students);
    }

    {
        SingleLinkedList<Student> students;
        run(students);
    }

    return 0;
}