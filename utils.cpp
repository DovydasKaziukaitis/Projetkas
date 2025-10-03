#include "utils.h"
#include <fstream>
#include <iomanip>
#include <random>

std::vector<Student> generate_students(int m) {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<double> d(2.0, 9.9);
    std::vector<Student> v;
    v.reserve(m);
    for (int i = 1; i <= m; ++i) {
        Student st;
        st.pav = "Pavarde" + std::to_string(i);
        st.var = "Vardas"  + std::to_string(i);
        st.galVid = d(rng);
        st.galMed = d(rng);
        v.push_back(st);
    }
    return v;
}

void write_group(const std::string& path, const std::vector<Student>& s, Mode m) {
    std::ofstream out(path);
    if (!out) return;
    out << std::left << std::setw(12) << "Pavarde"
        << std::setw(12) << "Vardas";
    if (m == Mode::Vid) out << std::right << std::setw(14) << "Galutinis(Vid)\n";
    else                out << std::right << std::setw(14) << "Galutinis(Med)\n";
    out << std::string(38, '-') << "\n";
    out << std::fixed << std::setprecision(2);
    for (const auto& st : s) {
        out << std::left << std::setw(12) << st.pav
            << std::setw(12) << st.var
            << std::right << std::setw(14)
            << (m == Mode::Vid ? st.galVid : st.galMed)
            << "\n";
    }
}
