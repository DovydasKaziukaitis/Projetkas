#pragma once
#include <vector>
#include <string>
#include "student.h"

std::vector<Student> generate_students(int m);
void write_group(const std::string& path, const std::vector<Student>& s, Mode m);

