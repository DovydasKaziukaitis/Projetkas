#include <iostream>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "student3.h"
#include "io3.h"
#include "utils3.h"
#include<list>
#include <chrono>
#include <iomanip>

static void spartos_testas(const std::string& path, Mode m) {
    using clock = std::chrono::high_resolution_clock;
    auto now = [] { return clock::now(); };
    auto ms = [](auto d) {
        using namespace std::chrono;
        return duration_cast<milliseconds>(d).count() / 1000.0;
    };

    auto t_all0 = now();

    auto t0 = now();
    auto S = skaityti_studentus(path);
    auto t_read = now() - t0;

    if (S.empty()) {
        std::cout << "Nepavyko nuskaityti failo.\n";
        return;
    }

    t0 = now();
    std::sort(S.begin(), S.end(),
              [](const Student& a, const Student& b) {
                  if (a.pav != b.pav) return a.pav < b.pav;
                  return a.var < b.var;
              });
    auto t_sort = now() - t0;

    std::vector<Student> baz1 = S;
    std::vector<Student> varg1, kiet1;

    t0 = now();
    padalinimasStrategija1(baz1, m, varg1, kiet1);
    auto t_split1 = now() - t0;

    t0 = now();
    rasyti_grupe("vargsiukai_vec_s1.txt", varg1, m);
    rasyti_grupe("kietiakiai_vec_s1.txt", kiet1, m);
    auto t_write1 = now() - t0;

    std::vector<Student> baz2 = S;
    std::vector<Student> varg2, kiet2;

    t0 = now();
    padalinimasStrategija2(baz2, m, varg2, kiet2);
    auto t_split2 = now() - t0;

    t0 = now();
    rasyti_grupe("vargsiukai_vec_s2.txt", varg2, m);
    rasyti_grupe("kietiakiai_vec_s2.txt", kiet2, m);
    auto t_write2 = now() - t0;

    std::vector<Student> baz3 = S;
    std::vector<Student> varg3, kiet3;

    t0 = now();
    padalinimasStrategija3(baz3, m, varg3, kiet3);
    auto t_split3 = now() - t0;

    t0 = now();
    rasyti_grupe("vargsiukai_vec_s3.txt", varg3, m);
    rasyti_grupe("kietiakiai_vec_s3.txt", kiet3, m);
    auto t_write3 = now() - t0;

    auto t_all = now() - t_all0;

    std::cout << "Vector\n";
    std::cout << "Failas uzdarytas\n";
    std::cout << "Failo is " << S.size() << " irasu nuskaitymo laikas: "
              << std::fixed << std::setprecision(6) << ms(t_read) << " ms\n";
    std::cout << S.size() << " irasu rusiavimo didėjimo tvarka laikas, su sort funkcija: "
              << ms(t_sort) << " ms\n\n";

    std::cout << "--- Strategija 1 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split1) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write1) << " ms\n\n";

    std::cout << "--- Strategija 2 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split2) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write2) << " ms\n\n";

    std::cout << "--- Strategija 3 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split3) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write3) << " ms\n\n";

    std::cout << S.size() << " irasu testo laikas: "
              << ms(t_all) << " ms\n";

    std::cout << "Spauskite enter kad testi";
    std::string tmp;
    std::getline(std::cin, tmp);
}

static double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return v[n/2];
    return (v[n/2 - 1] + v[n/2]) / 2.0;
}

static void spartos_testas_list(const std::string& path, Mode m) {
    using clock = std::chrono::high_resolution_clock;
    auto now = [] { return clock::now(); };
    auto ms = [](auto d) {
        using namespace std::chrono;
        return duration_cast<milliseconds>(d).count() / 1000.0;
    };

    auto t0 = now();
    auto vec = skaityti_studentus(path);
    auto t_read = now() - t0;

    if (vec.empty()) {
        std::cout << "Nepavyko nuskaityti failo list testui.\n";
        return;
    }

    std::list<Student> L(vec.begin(), vec.end());

    t0 = now();
    L.sort([](const Student& a, const Student& b) {
        if (a.pav != b.pav) return a.pav < b.pav;
        return a.var < b.var;
    });
    auto t_sort = now() - t0;

    auto t_all0 = now();

    std::list<Student> baz1 = L;
    std::list<Student> varg1, kiet1;

    t0 = now();
    padalinimasStrategija1(baz1, m, varg1, kiet1);
    auto t_split1 = now() - t0;

    t0 = now();
    std::vector<Student> v1(varg1.begin(), varg1.end());
    std::vector<Student> k1(kiet1.begin(), kiet1.end());
    rasyti_grupe("vargsiukai_list_s1.txt", v1, m);
    rasyti_grupe("kietiakiai_list_s1.txt", k1, m);
    auto t_write1 = now() - t0;

    std::list<Student> baz2 = L;
    std::list<Student> varg2, kiet2;

    t0 = now();
    padalinimasStrategija2(baz2, m, varg2, kiet2);
    auto t_split2 = now() - t0;

    t0 = now();
    std::vector<Student> v2(varg2.begin(), varg2.end());
    std::vector<Student> k2(kiet2.begin(), kiet2.end());
    rasyti_grupe("vargsiukai_list_s2.txt", v2, m);
    rasyti_grupe("kietiakiai_list_s2.txt", k2, m);
    auto t_write2 = now() - t0;

    std::list<Student> baz3 = L;
    std::list<Student> varg3, kiet3;

    t0 = now();
    padalinimasStrategija3(baz3, m, varg3, kiet3);
    auto t_split3 = now() - t0;

    t0 = now();
    std::vector<Student> v3(varg3.begin(), varg3.end());
    std::vector<Student> k3(kiet3.begin(), kiet3.end());
    rasyti_grupe("vargsiukai_list_s3.txt", v3, m);
    rasyti_grupe("kietiakiai_list_s3.txt", k3, m);
    auto t_write3 = now() - t0;

    auto t_all = now() - t_all0;

    std::cout << "List\n";
    std::cout << "Failas uzdarytas\n";
    std::cout << "Failo is " << vec.size() << " irasu nuskaitymo laikas: "
              << std::fixed << std::setprecision(6) << ms(t_read) << " ms\n";
    std::cout << vec.size() << " irasu rusiavimo laikas (list.sort): "
              << ms(t_sort) << " ms\n\n";

    std::cout << "--- Strategija 1 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split1) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write1) << " ms\n\n";

    std::cout << "--- Strategija 2 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split2) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write2) << " ms\n\n";

    std::cout << "--- Strategija 3 ---\n";
    std::cout << "Dalijimo laikas: " << ms(t_split3) << " ms\n";
    std::cout << "Irasymo i failus laikas: " << ms(t_write3) << " ms\n\n";

    std::cout << vec.size() << " irasu testo laikas: "
              << ms(t_all) << " ms\n";

    std::cout << "Press Enter to continue . . .";
    std::string tmp;
    std::getline(std::cin, tmp);
}

static std::vector<Student> interaktyvus_ivedimas() {
    int m;
    std::cout << "Kiek studentu? ";
    if (!(std::cin >> m) || m <= 0) return {};
    std::string dump;
    std::getline(std::cin, dump);

    std::vector<Student> s;
    s.reserve(m);

    for (int i = 0; i < m; ++i) {
        Student st;

        std::cout << "Vardas Pavarde: ";
        std::cin >> st.var >> st.pav;
        std::getline(std::cin, dump);

        std::cout << "Iveskite visus ND balus vienoje eiluteje: ";
        std::string ndLine;
        std::getline(std::cin, ndLine);
        std::istringstream nds(ndLine);
        int v;
        while (nds >> v) st.nd.push_back(v);

        std::cout << "Egzamino balas: ";
        std::cin >> st.egz;
        std::getline(std::cin, dump);

        double avg = st.nd.empty()
            ? 0.0
            : std::accumulate(st.nd.begin(), st.nd.end(), 0.0) / st.nd.size();
        double med = mediana(st.nd);

        st.galVid = 0.4 * avg + 0.6 * st.egz;
        st.galMed = 0.4 * med + 0.6 * st.egz;

        s.push_back(std::move(st));
    }
    return s;
}

int main(int argc, char** argv) {
    std::string dump;
    std::vector<Student> paskutiniai;

    while (true) {
        std::cout << "\n=== MENIU ===\n"
            << "1) Nuskaityti studentu pazymiu faila (rodyti Vid/Med/Abu)\n"
            << "2) Interaktyvus ivedimas\n"
            << "3) Sugeneruoti studentu pazymiu faila\n"
            << "4) Padalinti i vargsiukus/kietiakius (galutinis <= 5)\n"
            << "5) Spartos testas(vector/list)\n"
            << "0) Baigti\n"
            << "Pasirinkite: ";

        int mnu;
        if (!(std::cin >> mnu)) return 0;
        std::getline(std::cin, dump);

        if (mnu == 0) break;

        if (mnu == 1) {
            std::string path;
            if (argc >= 2) path = argv[1];
            else {
                std::cout << "Failo kelias: ";
                std::getline(std::cin, path);
            }

            paskutiniai = skaityti_studentus(path);
            std::cerr << "Uzkrauta irasu: " << paskutiniai.size() << "\n";

            std::cout << "Ka rodyti?\n"
                      << "1) Galutinis(Vid)\n"
                      << "2) Galutinis(Med)\n"
                      << "3) Abu\n"
                      << "Pasirinkite: ";
            int show;
            if (!(std::cin >> show)) show = 1;
            std::getline(std::cin, dump);

            if (show == 2) spausdinti_lentele(paskutiniai, Mode::Med);
            else if (show == 3) spausdinti_lentele_abus(paskutiniai);
            else spausdinti_lentele(paskutiniai, Mode::Vid);

            continue;
        }

        if (mnu == 2) {
            paskutiniai = interaktyvus_ivedimas();
            std::cerr << "Ivedete irasu: " << paskutiniai.size() << "\n";

            std::cout << "Ka rodyti?\n"
                      << "1) Galutinis(Vid)\n"
                      << "2) Galutinis(Med)\n"
                      << "3) Abu\n"
                      << "Pasirinkite: ";
            int show;
            if (!(std::cin >> show)) show = 1;
            std::getline(std::cin, dump);

            if (show == 2) spausdinti_lentele(paskutiniai, Mode::Med);
            else if (show == 3) spausdinti_lentele_abus(paskutiniai);
            else spausdinti_lentele(paskutiniai, Mode::Vid);

            continue;
        }

        if (mnu == 3) {
            int n;
            std::cout << "Kiek irasu generuoti? ";
            if (!(std::cin >> n) || n <= 0) { std::getline(std::cin, dump); continue; }
            std::getline(std::cin, dump);

            paskutiniai = generuoti_studentus(n);
            std::string fn = "studentai" + std::to_string(n) + ".txt";
            irasyti_pilna_faila(fn, paskutiniai);

            std::cout << "Sugeneruotas failas: " << fn << "\n";
            continue;
        }

        if (mnu == 4) {
            std::string path;
            std::cout << "Iveskite failo kelia padalinimui: ";
            std::getline(std::cin, path);

            auto s = skaityti_rezultatus(path);
            if (s.empty()) {
                std::cout << "Failas tuscias arba nepavyko nuskaityti.\n";
                continue;
            }

            std::cout << "Pagal ka dalinti?\n"
                    << "1) Galutinis(Vid)\n"
                    << "2) Galutinis(Med)\n"
                    << "Pasirinkite: ";

            int x;
            if (!(std::cin >> x)) x = 1;
            std::getline(std::cin, dump);

            Mode mode = (x == 2 ? Mode::Med : Mode::Vid);

            padalinti_ir_irasyti(s, mode);

            std::cout << "Padalinta i vargsiukai.txt ir kietiakiai.txt (is failo: "
                    << path << ", rezimas: "
                    << (mode == Mode::Vid ? "Galutinis(Vid)" : "Galutinis(Med)")
                    << ")\n";
            continue;
    }
        if (mnu == 5) {
            std::string path;
            if (argc >= 2) path = argv[1];
            else {
                std::cout << "Failo kelias: ";
                std::getline(std::cin, path);
            }

            std::cout << "Pagal ka skaiciuoti galutini?\n"
                    << "1) Galutinis(Vid)\n"
                    << "2) Galutinis(Med)\n"
                    << "Pasirinkite: ";
            int x;
            if (!(std::cin >> x)) x = 1;
            std::getline(std::cin, dump);
            Mode mode = (x == 2 ? Mode::Med : Mode::Vid);

            std::cout << "Kuri konteineri testuoti?\n"
                    << "1) vector\n"
                    << "2) list\n"
                    << "Pasirinkite: ";
            int c;
            if (!(std::cin >> c)) c = 1;
            std::getline(std::cin, dump);

            if (c == 2) spartos_testas_list(path, mode);
            else        spartos_testas(path, mode);

            continue;
        }


        std::cout << "Blogas pasirinkimas.\n";
    }

    return 0;
}
