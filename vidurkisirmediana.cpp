#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

double avg(const std::vector<int>& a) {
    return a.empty() ? 0.0
                     : std::accumulate(a.begin(), a.end(), 0.0) / a.size();
}

static void sort(std::vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) {
        int key = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > key) { a[j] = a[j - 1]; --j; }
        a[j] = key;
    }
}

double med(std::vector<int> a) {
    if (a.empty()) return 0.0;
    sort(a);
    size_t n = a.size();
    return (n % 2) ? a[n/2] : (a[n/2 - 1] + a[n/2]) / 2.0;
}

static void spausdink(const std::vector<std::string>& vardai,
                      const std::vector<std::string>& pavardes,
                      const std::vector<double>& galVid,
                      const std::vector<double>& galMed,
                      int mode) {
    std::cout << std::left << std::setw(15) << "Pavarde"
              << std::setw(15) << "Vardas";
    if (mode == 1 || mode == 3) std::cout << std::right << std::setw(16) << "Galutinis(Vid)";
    if (mode == 2 || mode == 3) std::cout << std::right << std::setw(16) << "Galutinis(Med)";
    std::cout << "\n";

    int bruksniai = (mode == 3) ? 62 : 46;
    std::cout << std::string(bruksniai, '-') << "\n"
              << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < vardai.size(); ++i) {
        std::cout << std::left << std::setw(15) << pavardes[i]
                  << std::setw(15) << vardai[i];
        if (mode == 1 || mode == 3) std::cout << std::right << std::setw(16) << galVid[i];
        if (mode == 2 || mode == 3) std::cout << std::right << std::setw(16) << galMed[i];
        std::cout << "\n";
    }
}

struct Student {
    std::string pav;
    std::string var;
    double gal;
};

static void irasykGrupesPagal(
    std::vector<std::string>& vardai,
    std::vector<std::string>& pavardes,
    const std::vector<double>& metrika,
    const char* stulpelioAntraste
){
    std::vector<Student> S;
    S.reserve(vardai.size());
    for (size_t i = 0; i < vardai.size(); ++i) {
        S.push_back({ std::move(pavardes[i]),
                      std::move(vardai[i]),
                      metrika[i] });
    }
    std::vector<std::string>().swap(vardai);
    std::vector<std::string>().swap(pavardes);

    std::sort(S.begin(), S.end(), [](const Student& a, const Student& b){
        if (a.gal != b.gal) return a.gal < b.gal;
        if (a.pav != b.pav) return a.pav < b.pav;
        return a.var < b.var;
    });

    auto cut = std::stable_partition(S.begin(), S.end(),
                                     [](const Student& s){ return s.gal < 5.0; });

    std::ofstream outV("vargsiukai.txt");
    std::ofstream outK("kietiakai.txt");
    if (!outV || !outK) { std::cerr << "Nepavyko sukurti išvesties failų.\n"; return; }

    auto rasykAntraste = [&](std::ostream& out){
        out << std::left  << std::setw(15) << "Pavarde"
            << std::setw(15) << "Vardas"
            << std::right << std::setw(16) << stulpelioAntraste << "\n"
            << std::string(46, '-') << "\n"
            << std::fixed << std::setprecision(2);
    };
    auto rasykEilute = [](std::ostream& out, const Student& s){
        out << std::left  << std::setw(15) << s.pav
            << std::setw(15) << s.var
            << std::right << std::setw(16) << s.gal << "\n";
    };

    rasykAntraste(outV);
    for (auto it = S.begin(); it != cut; ++it) rasykEilute(outV, *it);

    rasykAntraste(outK);
    for (auto it = cut; it != S.end(); ++it) rasykEilute(outK, *it);
}

int main(int argc, char** argv) {
    int mode = 3;
    std::cout << "Pasirinkite rezultata: 1-Vid. 2-Med. 3-Abu = ";
    if (!(std::cin >> mode) || mode < 1 || mode > 3) mode = 3;
    std::string dump; std::getline(std::cin, dump);

    std::srand((unsigned)std::time(nullptr));

    while (true) {
        std::cout << "\n=== MENIU ===\n"
                  << "1) Skaityti is failo\n"
                  << "2) Interaktyvus ivedimas\n"
                  << "3) Generuoti atsitiktinai\n"
                  << "4) Keisti isvedimo rezima (dabar: "
                  << (mode==1?"Vid":mode==2?"Med":"Abu") << ")\n"
                  << "0) Baigti\n"
                  << "Pasirinkite: ";
        int mnu;
        if (!(std::cin >> mnu)) return 0;
        std::getline(std::cin, dump);

        if (mnu == 0) break;
        if (mnu == 4) {
            std::cout << "Naujas rezimas 1-Vid 2-Med 3-Abu: ";
            if (!(std::cin >> mode) || mode < 1 || mode > 3) mode = 3;
            std::getline(std::cin, dump);
            continue;
        }

        std::vector<std::string> vardai, pavardes;
        std::vector<double> galut, galutMed;

        if (mnu == 1) {
            std::string path;
            if (argc >= 2) path = argv[1];
            else { std::cout << "Failo kelias: "; std::getline(std::cin, path); }

            std::ifstream f(path.c_str());
            if (!f) { std::cerr << "cannot open " << path << "\n"; continue; }

            auto trim = [](std::string& s){
                const char* ws = " \t\r\n";
                auto a = s.find_first_not_of(ws);
                auto b = s.find_last_not_of(ws);
                if (a == std::string::npos) s.clear();
                else s = s.substr(a, b - a + 1);
            };
            auto isDigits = [](const std::string& s){
                return !s.empty() && std::all_of(s.begin(), s.end(),
                       [](unsigned char ch){ return std::isdigit(ch); });
            };

            auto parseLine = [&](std::string line){
                trim(line);
                if (line.empty() || line[0] == '-') return;
                for (char& c : line) if (c == ',') c = '.';

                std::istringstream in(line);

                std::string first;
                if (!(in >> first)) return;
                if (isDigits(first)) {
                    if (!(in >> first)) return;
                }
                std::string pav = first, var;
                if (!(in >> var)) return;

                double gVid, gMed;
                if (!(in >> gVid)) return;
                if (!(in >> gMed)) gMed = gVid;

                if (pav == "Pavarde" || pav == "Pavardė" || var == "Vardas") return;

                pavardes.push_back(pav);
                vardai.push_back(var);
                galut.push_back(gVid);
                galutMed.push_back(gMed);
            };

            for (std::string line; std::getline(f, line); )
                parseLine(line);

            std::cerr << "Uzkrauta irasu: " << galut.size() << "\n";

            spausdink(vardai, pavardes, galut, galutMed, mode);

            int sk=1;
            std::cout << "Skirstyti pagal: 1-Vid 2-Med = ";
            if (!(std::cin >> sk) || (sk!=1 && sk!=2)) sk = 1;
            std::getline(std::cin, dump);

            if (sk == 1) irasykGrupesPagal(vardai, pavardes, galut,    "Galutinis(Vid)");
            else         irasykGrupesPagal(vardai, pavardes, galutMed, "Galutinis(Med)");
            continue;

        } else if (mnu == 2) {
            int m; std::cout << "Kiek studentu? ";
            if (!(std::cin >> m) || m <= 0) return 0;
            std::getline(std::cin, dump);

            vardai.resize(m); pavardes.resize(m); galut.resize(m); galutMed.resize(m);

            for (int i = 0; i < m; ++i) {
                std::cout << "Vardas Pavarde: ";
                std::cin >> vardai[i] >> pavardes[i];
                std::getline(std::cin, dump);

                std::cout << "Iveskite visus ND balus vienoje eiluteje: ";
                std::string ndLine; std::getline(std::cin, ndLine);
                std::istringstream nds(ndLine);
                std::vector<int> nd; int v; while (nds >> v) nd.push_back(v);

                std::cout << "Egzamino balas: ";
                int egz; std::cin >> egz;
                std::getline(std::cin, dump);

                galut[i]    = 0.4 * avg(nd) + 0.6 * egz;
                galutMed[i] = 0.4 * med(nd) + 0.6 * egz;
            }
            spausdink(vardai, pavardes, galut, galutMed, mode);

            int sk=1;
            std::cout << "Skirstyti pagal: 1-Vid 2-Med = ";
            if (!(std::cin >> sk) || (sk!=1 && sk!=2)) sk = 1;
            std::getline(std::cin, dump);

            if (sk == 1) irasykGrupesPagal(vardai, pavardes, galut,    "Galutinis(Vid)");
            else         irasykGrupesPagal(vardai, pavardes, galutMed, "Galutinis(Med)");

        } else if (mnu == 3) {
            int m; std::cout << "Kiek studentu generuoti? ";
            if (!(std::cin >> m) || m <= 0) { std::getline(std::cin, dump); continue; }

            std::cout << "Kiek ND kiekvienam?: ";
            int n; if (!(std::cin >> n)) { std::getline(std::cin, dump); continue; }
            std::getline(std::cin, dump);

            vardai.resize(m); pavardes.resize(m);
            galut.resize(m);  galutMed.resize(m);

            for (int i = 0; i < m; ++i) {
                vardai[i]   = "Vardas" + std::to_string(i+1);
                pavardes[i] = "Pavarde" + std::to_string(i+1);

                int kiekND = n;
                if (kiekND == 0) kiekND = 5 + std::rand() % 8;
                std::vector<int> nd(kiekND);
                for (int j = 0; j < kiekND; ++j) nd[j] = 1 + std::rand() % 10;
                int egz = 1 + std::rand() % 10;

                galut[i]    = 0.4 * avg(nd) + 0.6 * egz;
                galutMed[i] = 0.4 * med(nd) + 0.6 * egz;
            }
            spausdink(vardai, pavardes, galut, galutMed, mode);

            int sk=1;
            std::cout << "Skirstyti pagal: 1-Vid 2-Med = ";
            if (!(std::cin >> sk) || (sk!=1 && sk!=2)) sk = 1;
            std::getline(std::cin, dump);

            if (sk == 1) irasykGrupesPagal(vardai, pavardes, galut,    "Galutinis(Vid)");
            else         irasykGrupesPagal(vardai, pavardes, galutMed, "Galutinis(Med)");

        } else {
            std::cout << "Blogas pasirinkimas\n";
        }
    }

    return 0;
}
