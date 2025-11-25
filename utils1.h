#pragma once
#include <vector>
#include <string>
#include "student3.h"
#include <list>

std::vector<Student> generuoti_studentus(int m);
void irasyti_pilna_faila(const std::string& path, const std::vector<Student>& s);
void rasyti_grupe(const std::string& path, const std::vector<Student>& s, Mode m);

void padalinimasStrategija1(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija1(const std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);

void padalinimasStrategija2(std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija2(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);

void padalinimasStrategija3(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet);
void padalinimasStrategija3(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet);
