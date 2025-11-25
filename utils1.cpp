#include <fstream>
#include <iomanip>
#include "utils3.h"
#include <random>
#include <algorithm>
#include <numeric>
#include <list>

static double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n / 2];
    return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

static inline double galutinis(const Student& st, Mode m) {
    return (m == Mode::Vid ? st.galVid : st.galMed);
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

    out << std::left << std::setw(20) << "Vardas"
        << std::left << std::setw(20) << "Pavarde";
    for (int i = 1; i <= 15; ++i)
        out << std::right << std::setw(5) << ("ND" + std::to_string(i));
    out << std::right << std::setw(5) << "Egz." << "\n";

    for (const auto& st : s) {
        out << std::left << std::setw(20) << st.var
            << std::left << std::setw(20) << st.pav;
        for (int nd : st.nd) out << std::right << std::setw(5) << nd;
        out << std::right << std::setw(5) << st.egz << "\n";
    }
}

void rasyti_grupe(const std::string& path, const std::vector<Student>& s, Mode m) {
    std::ofstream out(path);
    if (!out) return;

    out << std::left << std::setw(20) << "Pavarde"
        << std::left << std::setw(20) << "Vardas";
    if (m == Mode::Vid) out << std::right << std::setw(14) << "Galutinis(Vid)\n";
    else               out << std::right << std::setw(14) << "Galutinis(Med)\n";

    out << std::string(38, '-') << "\n";
    out << std::fixed << std::setprecision(2);

    for (const auto& st : s) {
        out << std::left << std::setw(20) << st.pav
            << std::left << std::setw(20) << st.var
            << std::right << std::setw(14)
            << (m == Mode::Vid ? st.galVid : st.galMed)
            << "\n";
    }
}

void padalinimasStrategija1(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    varg.clear();
    kiet.clear();
    varg.reserve(s.size());
    kiet.reserve(s.size());
    for (const auto& st : s) {
        double v = galutinis(st, m);
        if (v <= 5.0) varg.push_back(st);
        else          kiet.push_back(st);
    }
}
void padalinimasStrategija1(const std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg.clear();
    kiet.clear();
    for (const auto& st : s) {
        double v = galutinis(st, m);
        if (v <= 5.0) varg.push_back(st);
        else          kiet.push_back(st);
    }
}

void padalinimasStrategija2(std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    varg.clear();
    kiet.clear();
    varg.reserve(s.size());

    auto it = std::remove_if(s.begin(), s.end(),
                             [&](Student& st) {
                                 double v = galutinis(st, m);
                                 if (v <= 5.0) {
                                     varg.push_back(std::move(st));
                                     return true;
                                 }
                                 return false;
                             });

    s.erase(it, s.end());
    kiet.swap(s);
}
void padalinimasStrategija2(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg.clear();
    kiet.clear();
    auto it = s.begin();
    while (it != s.end()) {
        auto cur = it++;
        double v = galutinis(*cur, m);
        if (v <= 5.0) {
            varg.splice(varg.end(), s, cur);
        }
    }
    kiet.swap(s);
}

void padalinimasStrategija3(const std::vector<Student>& s, Mode m,
                            std::vector<Student>& varg, std::vector<Student>& kiet) {
    std::vector<Student> tmp = s;

    auto pivot = std::partition(tmp.begin(), tmp.end(),
                                [&](const Student& st) {
                                    return galutinis(st, m) <= 5.0;
                                });

    varg.assign(tmp.begin(), pivot);
    kiet.assign(pivot, tmp.end());
}
void padalinimasStrategija3(std::list<Student>& s, Mode m,
                            std::list<Student>& varg, std::list<Student>& kiet) {
    varg.clear();
    kiet.clear();

    auto pred = [&](const Student& st) {
        return galutinis(st, m) <= 5.0;
    };
    auto pivot = std::partition(s.begin(), s.end(), pred);
    varg.splice(varg.end(), s, s.begin(), pivot);
    kiet.splice(kiet.end(), s, s.begin(), s.end());
}


