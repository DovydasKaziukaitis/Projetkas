#pragma once
#include <vector>
#include <string>
#include "student.h"

std::vector<Student> skaityti_studentus(const std::string& path);
void spausdinti_lentele(const std::vector<Student>& s, Mode m);
void spausdinti_lentele_abus(const std::vector<Student>& s);
void padalinti_ir_irasyti(std::vector<Student>& s, Mode m);
std::vector<Student> skaityti_rezultatus(const std::string& path);
