#include "io3.h"
#include "utils3.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <cctype>
#include <cstdlib>
#include <iostream>

static void trim(std::string& s) {
    const char* ws = " \t\r\n";
    auto a = s.find_first_not_of(ws);
    auto b = s.find_last_not_of(ws);
    if (a == std::string::npos) s.clear();
    else s = s.substr(a, b - a + 1);
}

std::vector<Student> skaityti_studentus(const std::string& path) {
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Nepavyko atidaryti: " << path << "\n";
        return {};
    }

    std::vector<Student> out;
    std::string line;
    bool header_passed = false;

    auto parse_int = [&](const std::string& s, int& outv)->bool {
        char* e = nullptr;
        long v = std::strtol(s.c_str(), &e, 10);
        if (e && *e == '\0') { outv = (int)v; return true; }
        return false;
    };

    auto mediana = [](std::vector<int> v)->double {
        if (v.empty()) return 0.0;
        std::sort(v.begin(), v.end());
        size_t n = v.size();
        if (n % 2 == 1) return v[n/2];
        return (v[n/2-1] + v[n/2]) / 2.0;
    };

    while (std::getline(f, line)) {
        trim(line);
        if (line.empty()) continue;

        if (!header_passed) {
            header_passed = true;
            continue;
        }

        std::istringstream in(line);
        std::vector<std::string> tok;
        std::string t;
        while (in >> t) tok.push_back(t);
        if (tok.size() < 3) continue;

        Student st;
        st.var = tok[0];
        st.pav = tok[1];

        std::vector<int> nums;
        for (size_t i = 2; i < tok.size(); ++i) {
            int x;
            if (parse_int(tok[i], x)) nums.push_back(x);
        }
        if (nums.size() < 2) continue;

        st.egz = nums.back();
        nums.pop_back();
        st.nd = nums;

        double avg = std::accumulate(st.nd.begin(), st.nd.end(), 0.0) / st.nd.size();
        double med = mediana(st.nd);

        st.galVid = 0.4 * avg + 0.6 * st.egz;
        st.galMed = 0.4 * med + 0.6 * st.egz;

        out.push_back(std::move(st));
    }

    return out;
}

void spausdinti_lentele(const std::vector<Student>& s, Mode m) {
    std::cout << std::left << std::setw(20) << "Pavarde"
              << std::left << std::setw(20) << "Vardas";
    if (m == Mode::Vid) std::cout << std::right << std::setw(14) << "Galutinis(Vid)";
    else               std::cout << std::right << std::setw(14) << "Galutinis(Med)";
    std::cout << "\n" << std::string(40, '-') << "\n";

    std::cout << std::fixed << std::setprecision(2);
    int shown = 0;
    for (const auto& st : s) {
        std::cout << std::left << std::setw(20) << st.pav
                  << std::left << std::setw(20) << st.var
                  << std::right << std::setw(14)
                  << (m == Mode::Vid ? st.galVid : st.galMed)
                  << "\n";
    }
}

void spausdinti_lentele_abus(const std::vector<Student>& s) {
    std::cout << std::left << std::setw(20) << "Pavarde"
              << std::left << std::setw(20) << "Vardas"
              << std::right << std::setw(14) << "Galutinis(Vid)"
              << std::right << std::setw(14) << "Galutinis(Med)"
              << "\n" << std::string(52, '-') << "\n";

    std::cout << std::fixed << std::setprecision(2);
    int shown = 0;
    for (const auto& st : s) {
        std::cout << std::left << std::setw(20) << st.pav
                  << std::left << std::setw(20) << st.var
                  << std::right << std::setw(14) << st.galVid
                  << std::right << std::setw(14) << st.galMed
                  << "\n";
    }
}


void padalinti_ir_irasyti(std::vector<Student>& s, Mode m) {
    std::vector<Student> varg, kiet;
    varg.reserve(s.size());
    kiet.reserve(s.size());

    for (auto &st : s) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        if (v < 5.0) varg.push_back(st);
        else          kiet.push_back(st);
    }

    rasyti_grupe("vargsiukai.txt", varg, m);
    rasyti_grupe("kietiakiai.txt", kiet, m);
}


std::vector<Student> skaityti_rezultatus(const std::string& path) {
    std::ifstream f(path);
    if (!f) {
        std::cerr << "Nepavyko atidaryti: " << path << "\n";
        return {};
    }

    std::vector<Student> out;
    std::string line;

    auto parse_double = [&](const std::string& s, double& outv)->bool {
        char* e = nullptr;
        double v = std::strtod(s.c_str(), &e);
        if (e && *e == '\0') { outv = v; return true; }
        return false;
    };

    while (std::getline(f, line)) {
        trim(line);
        if (line.empty()) continue;

        std::istringstream in(line);
        std::vector<std::string> tok;
        std::string t;
        while (in >> t) tok.push_back(t);

        if (tok.size() < 3) continue;

        Student st;
        st.pav = tok[0];
        st.var = tok[1];

        std::vector<double> nums;
        for (size_t i = 2; i < tok.size(); ++i) {
            double x;
            if (parse_double(tok[i], x)) nums.push_back(x);
        }

        if (nums.size() == 2) {
            st.galVid = nums[0];
            st.galMed = nums[1];
        } else if (nums.size() == 1) {
            st.galVid = nums[0];
            st.galMed = nums[0];
        } else {
            continue;
        }

        out.push_back(std::move(st));
    }

    return out;
}
