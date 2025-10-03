#include "io.h"
#include "student.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <iostream>

static void trim(std::string& s) {
    const char* ws = " \t\r\n";
    auto a = s.find_first_not_of(ws);
    auto b = s.find_last_not_of(ws);
    if (a == std::string::npos) s.clear();
    else s = s.substr(a, b - a + 1);
}

static bool all_digits(const std::string& t) {
    if (t.empty()) return false;
    for (unsigned char ch : t) if (!std::isdigit(ch)) return false;
    return true;
}

std::vector<Student> read_students(const std::string& path) {
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Nepavyko atidaryti: " << path << "\n";
        return {};
    }
    std::vector<Student> out;
    std::string line;
    while (std::getline(f, line)) {
        trim(line);
        if (line.empty() || line[0] == '-') continue;
        for (char& c : line) if (c == ',') c = '.';
        std::istringstream in(line);
        std::vector<std::string> tok;
        std::string t;
        while (in >> t) tok.push_back(t);
        if (tok.size() < 3) continue;
        auto parse_d = [](const std::string& s, double& v)->bool {
            char* e = nullptr;
            v = std::strtod(s.c_str(), &e);
            return e && *e == '\0';
        };
        double gVid = 0, gMed = 0;
        bool have2 = tok.size() >= 4 && parse_d(tok[tok.size()-1], gMed)
                                   && parse_d(tok[tok.size()-2], gVid);
        bool have1 = !have2 && parse_d(tok.back(), gVid);
        std::string pav, var;
        if (have2) {
            size_t n = tok.size();
            if (n >= 5 && all_digits(tok[0])) { pav = tok[1]; var = tok[2]; }
            else { pav = tok[n-3]; var = tok[n-2]; }
        } else if (have1) {
            size_t n = tok.size();
            if (n >= 4 && all_digits(tok[0])) { pav = tok[1]; var = tok[2]; }
            else { pav = tok[n-3]; var = tok[n-2]; }
            gMed = gVid;
        } else {
            continue;
        }
        out.push_back(Student{pav, var, gVid, gMed});
    }
    return out;
}

void print_table(const std::vector<Student>& s, Mode m) {
    std::cout << std::left << std::setw(12) << "Pavarde"
              << std::setw(12) << "Vardas";
    if (m == Mode::Vid) std::cout << std::right << std::setw(14) << "Galutinis(Vid)";
    else                std::cout << std::right << std::setw(14) << "Galutinis(Med)";
    std::cout << "\n" << std::string(40, '-') << "\n";
    std::cout << std::fixed << std::setprecision(2);
    int shown = 0;
    for (const auto& st : s) {
        std::cout << std::left << std::setw(12) << st.pav
                  << std::setw(12) << st.var
                  << std::right << std::setw(14)
                  << (m == Mode::Vid ? st.galVid : st.galMed)
                  << "\n";
        if (++shown == 5) break;
    }
}

void split_and_write(const std::vector<Student>& s, Mode m) {
    std::vector<Student> varg, kiet;
    varg.reserve(s.size());
    kiet.reserve(s.size());
    for (const auto& st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(st);
    }
    write_group("vargsiukai.txt", varg, m);
    write_group("kietiakiai.txt", kiet, m);
}
