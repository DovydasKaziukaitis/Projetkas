#include "utils.h"
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <numeric>

static double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

std::vector<Student> generuoti_studentus(int m) {
    std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> d(1, 10);

    std::vector<Student> v;
    v.reserve(m);

    for (int i = 1; i <= m; ++i) {
        Student st;
        st.pav = "Pavarde" + std::to_string(i);
        st.var = "Vardas" + std::to_string(i);

        st.nd.resize(15);
        for (int k = 0; k < 15; ++k) st.nd[k] = d(rng);
        st.egz = d(rng);

        double avg = std::accumulate(st.nd.begin(), st.nd.end(), 0.0) / st.nd.size();
        double med = mediana(st.nd);

        st.galVid = 0.4 * avg + 0.6 * st.egz;
        st.galMed = 0.4 * med + 0.6 * st.egz;

        v.push_back(std::move(st));
    }
    return v;
}

void irasyti_pilna_faila(const std::string& path, const std::vector<Student>& s) {
    std::ofstream out(path);
    if (!out) return;

    out << std::left << std::setw(12) << "Vardas"
        << std::left << std::setw(12) << "Pavarde";
    for (int i = 1; i <= 15; ++i)
        out << std::right << std::setw(5) << ("ND" + std::to_string(i));
    out << std::right << std::setw(5) << "Egz." << "\n";

    for (const auto& st : s) {
        out << std::left << std::setw(12) << st.var
            << std::left << std::setw(12) << st.pav;
        for (int nd : st.nd) out << std::right << std::setw(5) << nd;
        out << std::right << std::setw(5) << st.egz << "\n";
    }
}

void rasyti_grupe(const std::string& path, const std::vector<Student>& s, Mode m) {
    std::ofstream out(path);
    if (!out) return;

    out << std::left << std::setw(12) << "Pavarde"
        << std::left << std::setw(12) << "Vardas";
    if (m == Mode::Vid) out << std::right << std::setw(14) << "Galutinis(Vid)\n";
    else               out << std::right << std::setw(14) << "Galutinis(Med)\n";

    out << std::string(38, '-') << "\n";
    out << std::fixed << std::setprecision(2);

    for (const auto& st : s) {
        out << std::left << std::setw(12) << st.pav
            << std::left << std::setw(12) << st.var
            << std::right << std::setw(14)
            << (m == Mode::Vid ? st.galVid : st.galMed)
            << "\n";
    }
}
