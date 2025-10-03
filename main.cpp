#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "student.h"
#include "io.h"
#include "utils.h"

static void benchmark_file(const std::string& path, Mode m) {
    using clock = std::chrono::high_resolution_clock;
    auto now = [] { return clock::now(); };
    auto ms  = [](auto d) {
        using namespace std::chrono;
        return duration_cast<microseconds>(d).count() / 1000.0;
    };

    auto t_all0 = now();

    auto t0 = now();
    auto S = read_students(path);
    auto t_read = now() - t0;

    t0 = now();
    std::sort(S.begin(), S.end(), [](const Student& a, const Student& b){
        if (a.pav != b.pav) return a.pav < b.pav;
        return a.var < b.var;
    });
    auto t_sort = now() - t0;

    t0 = now();
    std::vector<Student> varg, kiet;
    varg.reserve(S.size());
    kiet.reserve(S.size());
    for (auto &st : S) {
        double v = (m == Mode::Vid ? st.galVid : st.galMed);
        (v < 5.0 ? varg : kiet).push_back(std::move(st));
    }
    std::vector<Student>().swap(S);
    auto t_split = now() - t0;

    t0 = now();
    write_group("vargsiukai.txt", varg, m);
    auto t_w1 = now() - t0;

    t0 = now();
    write_group("kietiakiai.txt", kiet, m);
    auto t_w2 = now() - t0;

    auto t_all = now() - t_all0;

    std::cout << "Vector\n";
    std::cout << "Failas uzdarytas\n";
    std::cout << "Failo is " << (varg.size()+kiet.size())
              << " irasu nuskaitymo laikas: " << std::fixed << std::setprecision(6) << ms(t_read) << "\n";
    std::cout << (varg.size()+kiet.size()) << " irasu rusiavimo didejimo tvarka laikas, su sort funkcija: "
              << ms(t_sort) << "\n";
    std::cout << (varg.size()+kiet.size()) << " irasu dalijimo i dvi grupes laikas, panaikinant pradini Vektoriu: "
              << ms(t_split) << "\n";
    std::cout << (varg.size()+kiet.size()) << " irasu isvedimo i pirma faila laikas: "
              << ms(t_w1) << "\n";
    std::cout << (varg.size()+kiet.size()) << " irasu isvedimo i antra faila laikas: "
              << ms(t_w2) << "\n\n";
    std::cout << (varg.size()+kiet.size()) << " irasu testo laikas: " << ms(t_all) << "\n\n";
    std::cout << "Press Enter to continue . . .";
    std::string _;
    std::getline(std::cin, _);
}

int main(int argc, char** argv) {
    Mode mode = Mode::Vid;
    std::string dump;

    while (true) {
        std::cout << "\n=== MENIU ===\n"
                  << "1) Skaityti is failo\n"
                  << "2) Interaktyvus demo (atsitiktiniai 5)\n"
                  << "3) Generuoti ir isvesti i vargsiukai/kietiakiai (pagal esama rezima)\n"
                  << "4) Keisti isvedimo rezima (dabar: " << (mode==Mode::Vid ? "Vid" : "Med") << ")\n"
                  << "5) Spartos testas (benchmark)\n"
                  << "0) Baigti\n"
                  << "Pasirinkite: ";

        int mnu;
        if (!(std::cin >> mnu)) return 0;
        std::getline(std::cin, dump);

        if (mnu == 0) break;

        if (mnu == 4) {
            std::cout << "Naujas rezimas 1-Vid 2-Med: ";
            int x; if (!(std::cin >> x)) x = 1;
            std::getline(std::cin, dump);
            mode = (x == 2 ? Mode::Med : Mode::Vid);
            continue;
        }

        if (mnu == 1) {
            std::string path;
            if (argc >= 2) path = argv[1];
            else { std::cout << "Failo kelias: "; std::getline(std::cin, path); }
            auto S = read_students(path);
            std::cerr << "Uzkrauta irasu: " << S.size() << "\n";
            print_table(S, mode);
            split_and_write(S, mode);
            continue;
        }

        if (mnu == 2) {
            auto S = generate_students(5);
            print_table(S, mode);
            continue;
        }

        if (mnu == 3) {
            int n; std::cout << "Kiek irasu generuoti? ";
            if (!(std::cin >> n) || n <= 0) { std::getline(std::cin, dump); continue; }
            std::getline(std::cin, dump);
            auto S = generate_students(n);
            split_and_write(S, mode);
            std::cout << "Irasyta i vargsiukai.txt ir kietiakiai.txt\n";
            continue;
        }

        if (mnu == 5) {
            std::string path;
            if (argc >= 2) path = argv[1];
            else { std::cout << "Failo kelias: "; std::getline(std::cin, path); }
            benchmark_file(path, mode);
            continue;
        }

        std::cout << "Blogas pasirinkimas\n";
    }

    return 0;
}
