#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> // to dela hacky a carky
using namespace std;
// ============================================================
// STRUKTURY
// ============================================================

struct Schopnost {
    string nazev;
    int poskozeni;    // kolik ubere zivotu
    int manaNaklady;  // kolik stoji many
};

struct Hrac {
    string jmeno;
    string trida;
    int maxZivoty;
    int zivoty;
    int maxMana;
    int mana;
    int zlato;
    int level;
    int zkusenosti;
    int zkusenostiDoLevelup;
    int utok;           // zakladni utok (bez many)
    Schopnost schopnosti[4];
    int pocetSchopnosti;
};

struct Nepritel {
    string nazev;
    int maxZivoty;
    int zivoty;
    int utok;
    int odmenaZkusenosti;
    int odmenaZlato;    // 0 = nema penize
    bool jeBoss;        // mini-boss nebo hlavni boss vždy ma zlato
};

// ============================================================
// POMOCNE FUNKCE - VYPIS
// ============================================================

void tiskniOddelovac() {
    cout << "========================================" << endl;
}

void tiskniHrace(const Hrac &h) {
    tiskniOddelovac();
    cout << " [" << h.jmeno << " - " << h.trida << "]  Level " << h.level << endl;
    cout << " Životy : " << h.zivoty << " / " << h.maxZivoty << endl;
    cout << " Mana   : " << h.mana   << " / " << h.maxMana   << endl;
    cout << " Zlato  : " << h.zlato  << endl;
    cout << " Útok   : " << h.utok   << endl;
    cout << " XP     : " << h.zkusenosti << " / " << h.zkusenostiDoLevelup << endl;
    tiskniOddelovac();
}

void tiskniNepritele(const Nepritel &n) {
    cout << " >> " << n.nazev
         << "  [Životy: " << n.zivoty << "/" << n.maxZivoty
         << "  Útok: " << n.utok << "]" << endl;
}

// ============================================================
// NASTAVENI CLASS (pardon nejsem moc kreativni)
// ============================================================

void nastavWarrior(Hrac &h) {
    h.trida             = "Warrior";
    h.maxZivoty         = 120;
    h.zivoty            = 120;
    h.maxMana           = 40;
    h.mana              = 40;
    h.utok              = 15;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Mocný úděs",    30, 10};
    h.schopnosti[1] = {"Vír ostři",     45, 20};
    h.schopnosti[2] = {"Beserkerský ryk",20, 5};
}

void nastavMage(Hrac &h) {
    h.trida             = "Mage";
    h.maxZivoty         = 70;
    h.zivoty            = 70;
    h.maxMana           = 100;
    h.mana              = 100;
    h.utok              = 8;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Ohnivá koule",  40, 15};
    h.schopnosti[1] = {"Blesk",         60, 30};
    h.schopnosti[2] = {"Mrazivá střela",25, 8};
}

void nastavRogue(Hrac &h) {
    h.trida             = "Rogue";
    h.maxZivoty         = 85;
    h.zivoty            = 85;
    h.maxMana           = 60;
    h.mana              = 60;
    h.utok              = 18;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Krití. údder",  50, 20};
    h.schopnosti[1] = {"Jedovatá šepel",35, 12};
    h.schopnosti[2] = {"Rychlý bodec",  22, 6};
}

void nastavPaladin(Hrac &h) {
    h.trida             = "Paladin";
    h.maxZivoty         = 105;
    h.zivoty            = 105;
    h.maxMana           = 55;
    h.mana              = 55;
    h.utok              = 12;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Svatý údšs",    35, 15};
    h.schopnosti[1] = {"Boží světlo",   50, 25};
    h.schopnosti[2] = {"Leéčivé požehnání", 0,  20}; // leceni - specialni pripad
}

// ============================================================
// VYBER CLASSY
// ============================================================

void vyberClassu(Hrac &h) {
    int volba;
    bool potvrzen = false;

    while (!potvrzen) {
        cout << "\n=== VYBER SI CLASSU ===" << endl;
        cout << "\n=== HP: životy, MP: útok manou ===" << endl;
        cout << "1) Warrior  - Silný bojovník s vysokými životy (120 HP, 40 MP, útok 15)" << endl;
        cout << "2) Mage     - Kouzelník co toho moc nevydrží, ale má silnou magii (70 HP, 100 MP, útok 8)" << endl;
        cout << "3) Rogue    - Hbitý zloděj s vysokým útokem (85 HP, 60 MP, útok 18)" << endl;
        cout << "4) Paladin  - Rytíř schopný léčení (105 HP, 55 MP, útok 12)" << endl;
        cout << "Volba: ";
        cin >> volba;

        switch (volba) {
            case 1: nastavWarrior(h); break;
            case 2: nastavMage(h);    break;
            case 3: nastavRogue(h);   break;
            case 4: nastavPaladin(h); break;
            default:
                cout << "Neplatná volba, zkus znovu." << endl;
                continue;
        }

        cout << "\nVybral jsi: " << h.trida << endl;
        cout << "Potvrzuješ tuto volbu? (1 = Ano, 0 = Ne): ";
        cin >> potvrzen;
    }

    cout << "\nZadej jmeno své postavy: ";
    cin >> h.jmeno;
}

// ============================================================
// LEVEL UP
// ============================================================

void zkontrolujLevelUp(Hrac &h) {
    while (h.zkusenosti >= h.zkusenostiDoLevelup) {
        h.zkusenosti       -= h.zkusenostiDoLevelup;
        h.level            += 1;
        h.zkusenostiDoLevelup = h.zkusenostiDoLevelup + 20 * h.level;

        int prirustek = 5;
        h.maxZivoty   += prirustek;
        h.zivoty      += prirustek;   // obnov cast zivotu
        h.maxMana     += 3;
        h.mana        += 3;
        h.utok        += 2;

        cout << "\n*** NOVÝ LEVEL! ***" << endl;
        cout << "Level: " << h.level - 1 << " => " << h.level << endl;
        cout << "Max životy +" << prirustek
             << ", Max mana +3, Útok +2" << endl;
    }
}

// ============================================================
// BOJ - 1  nepritel
// ============================================================

// Vraci: true = hrac zil, false = hrac zemrel
bool bojuj(Hrac &h, Nepritel &n, bool hracJdePrvni) {
    cout << "\n!!! SOUBOJ: " << h.jmeno << " vs " << n.nazev << " !!!" << endl;

    while (h.zivoty > 0 && n.zivoty > 0) {
        tiskniOddelovac();
        cout << "Tvoje životy: " << h.zivoty << "/" << h.maxZivoty
             << "  |  Mana: " << h.mana << "/" << h.maxMana << endl;
        tiskniNepritele(n);

        // tah hrace (nebo nepritel jde prvni)
        if (!hracJdePrvni && n.zivoty > 0) {
            // nepritel utoci prvni
            int skoda = n.utok;
            h.zivoty -= skoda;
            if (h.zivoty < 0) h.zivoty = 0;
            cout << n.nazev << " útočí! Způsobuje " << skoda << " poškození." << endl;
            if (h.zivoty <= 0) break;
        }

        // volba hrace
        cout << "\nJaký útok si vybereš?" << endl;
        cout << "0) Základní útok (" << h.utok << " poškození, zdarma)" << endl;
        for (int i = 0; i < h.pocetSchopnosti; i++) {
            cout << i + 1 << ") " << h.schopnosti[i].nazev
                 << " (" << h.schopnosti[i].poskozeni << " pos."
                 << ", " << h.schopnosti[i].manaNaklady << " many)" << endl;
        }
        cout << "Volba: ";
        int volba;
        cin >> volba;

        if (volba == 0) {
            // Zakladni utok
            int skoda = h.utok;
            n.zivoty -= skoda;
            if (n.zivoty < 0) n.zivoty = 0;
            cout << "Zasahujes " << n.nazev << " za " << skoda << " Poškození." << endl;
        } else if (volba >= 1 && volba <= h.pocetSchopnosti) {
            Schopnost &s = h.schopnosti[volba - 1];
            if (h.mana < s.manaNaklady) {
                cout << "Nedostatek many! Útočíš základním útokem." << endl;
                n.zivoty -= h.utok;
                if (n.zivoty < 0) n.zivoty = 0;
            } else {
                h.mana -= s.manaNaklady;
                // Specialni pripad: Lecive pozehani Paladina (poskozeni == 0)
                if (s.poskozeni == 0) {
                    int heal = 20;
                    h.zivoty += heal;
                    if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                    cout << "Lečíš se za " << heal << " zivotu!" << endl;
                } else {
                    n.zivoty -= s.poskozeni;
                    if (n.zivoty < 0) n.zivoty = 0;
                    cout << "Pouzivas " << s.nazev << "! "
                         << n.nazev << " ztrácí " << s.poskozeni << " životů." << endl;
                }
            }
        } else {
            cout << "Neplatná volba, útočíš základním útokem." << endl;
            n.zivoty -= h.utok;
            if (n.zivoty < 0) n.zivoty = 0;
        }

        if (n.zivoty <= 0) break;

        // tah nepritele (kdyz hrac siel prvni nebo normal monstra)
        if (hracJdePrvni && n.zivoty > 0) {
            int skoda = n.utok;
            h.zivoty -= skoda;
            if (h.zivoty < 0) h.zivoty = 0;
            cout << n.nazev << " útočí! Způsobuje " << skoda << " poškození." << endl;
        } else if (!hracJdePrvni && n.zivoty > 0) {
            // druhy utok bosse (boss zautocil jiz pred hracem)
            int skoda = n.utok;
            h.zivoty -= skoda;
            if (h.zivoty < 0) h.zivoty = 0;
            cout << n.nazev << " opět útočí! Způsobuje " << skoda << " poškození." << endl;
        }
    }

    if (h.zivoty <= 0) {
        cout << "\n*** " << h.jmeno << " zemřel jsi! KONEC HRY ***" << endl;
        return false;
    }

    // hrac vyhral souboj
    cout << "\n" << h.jmeno << " porazil " << n.nazev << "!" << endl;

    // zkusenosti
    h.zkusenosti += n.odmenaZkusenosti;
    cout << "Získáš " << n.odmenaZkusenosti << " XP." << endl;
    zkontrolujLevelUp(h);

    // Zlato
    if (n.odmenaZlato > 0) {
        h.zlato += n.odmenaZlato;
        cout << "Našels " << n.odmenaZlato << " zlata!" << endl;
    } else {
        cout << "Monstrum u sebe nic nemělo." << endl;
    }

    return true;
}

// ============================================================
// BOJ S VICE NEPRATELI NAJEDNOU
// ============================================================

bool bojujSkupina(Hrac &h, Nepritel nepratele[], int pocet) {
    cout << "\n!!! SKUPINOVÝ SOUBOJ (" << pocet << " nepratele) !!!" << endl;
    for (int i = 0; i < pocet; i++) {
        cout << "  - " << nepratele[i].nazev << endl;
    }

    //hrac jde prvni ve skupinovem souboji
    while (h.zivoty > 0) {
        int ziviPocet = 0;
        for (int i = 0; i < pocet; i++) {
            if (nepratele[i].zivoty > 0) ziviPocet++;
        }
        if (ziviPocet == 0) break;

        tiskniOddelovac();
        cout << "Tvoje životy: " << h.zivoty << "/" << h.maxZivoty
             << "  |  Mana: " << h.mana << "/" << h.maxMana << endl;
        cout << "Neprřátelé:" << endl;
        for (int i = 0; i < pocet; i++) {
            if (nepratele[i].zivoty > 0) {
                cout << "  " << i + 1 << ") ";
                tiskniNepritele(nepratele[i]);
            }
        }

        // vyber cile
        cout << "Zvol cíl (1-" << pocet << "): ";
        int cil;
        cin >> cil;
        cil--;   // index od 0
        if (cil < 0 || cil >= pocet || nepratele[cil].zivoty <= 0) {
            cout << "Neplatný cíl, útočíš na prvého živého." << endl;
            cil = 0;
            while (cil < pocet && nepratele[cil].zivoty <= 0) cil++;
        }

        // Volba akce
        cout << "Akce: 0) Zakládní útok";
        for (int i = 0; i < h.pocetSchopnosti; i++) {
            cout << "  " << i + 1 << ") " << h.schopnosti[i].nazev
                 << "(" << h.schopnosti[i].manaNaklady << " MP)";
        }
        cout << endl << "Volba: ";
        int volba;
        cin >> volba;

        if (volba == 0) {
            nepratele[cil].zivoty -= h.utok;
            if (nepratele[cil].zivoty < 0) nepratele[cil].zivoty = 0;
            cout << "Utočíš na " << nepratele[cil].nazev << " za " << h.utok << "." << endl;
        } else if (volba >= 1 && volba <= h.pocetSchopnosti) {
            Schopnost &s = h.schopnosti[volba - 1];
            if (h.mana < s.manaNaklady) {
                cout << "Nedostatek many!" << endl;
                nepratele[cil].zivoty -= h.utok;
                if (nepratele[cil].zivoty < 0) nepratele[cil].zivoty = 0;
            } else {
                h.mana -= s.manaNaklady;
                if (s.poskozeni == 0) {
                    int heal = 20;
                    h.zivoty += heal;
                    if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                    cout << "Lecis se za " << heal << " HP!" << endl;
                } else {
                    nepratele[cil].zivoty -= s.poskozeni;
                    if (nepratele[cil].zivoty < 0) nepratele[cil].zivoty = 0;
                    cout << s.nazev << " na " << nepratele[cil].nazev
                         << " za " << s.poskozeni << "." << endl;
                }
            }
        }

        // utoky zivyc nepritelu
        for (int i = 0; i < pocet; i++) {
            if (nepratele[i].zivoty > 0) {
                int skoda = nepratele[i].utok;
                h.zivoty -= skoda;
                if (h.zivoty < 0) h.zivoty = 0;
                cout << nepratele[i].nazev << " útočí za: " << skoda << "." << endl;
                if (h.zivoty <= 0) break;
            }
        }
    }

    if (h.zivoty <= 0) {
        cout << "\n*** " << h.jmeno << " zemrel! KONEC HRY ***" << endl;
        return false;
    }

    cout << "\nVyhrál jsi skupinový souboj!" << endl;

    for (int i = 0; i < pocet; i++) {
        h.zkusenosti += nepratele[i].odmenaZkusenosti;
        cout << "+" << nepratele[i].odmenaZkusenosti << " XP za " << nepratele[i].nazev << endl;
        if (nepratele[i].odmenaZlato > 0) {
            h.zlato += nepratele[i].odmenaZlato;
            cout << "+" << nepratele[i].odmenaZlato << " zlata za " << nepratele[i].nazev << endl;
        }
    }
    zkontrolujLevelUp(h);
    return true;
}

int main{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}