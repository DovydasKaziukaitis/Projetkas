#pragma once
#include <string>
#include <vector>
#include "student.h"

std::vector<Student> read_students(const std::string& path);
void print_table(const std::vector<Student>& s, Mode m);
void split_and_write(const std::vector<Student>& s, Mode m);

