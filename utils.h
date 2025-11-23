#pragma once
#include <vector>
#include <string>
#include "student.h"

std::vector<Student> generuoti_studentus(int m);
void irasyti_pilna_faila(const std::string& path, const std::vector<Student>& s);
void rasyti_grupe(const std::string& path, const std::vector<Student>& s, Mode m);
