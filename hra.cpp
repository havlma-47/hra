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
//  POMOCNE FUNKCE - VYPIS
// ============================================================

void tiskniOddelovac() {
    cout << "========================================" << endl;
}

void tiskniHrace(const Hrac &h) {
    tiskniOddelovac();
    cout << " [" << h.jmeno << " - " << h.trida << "]  Level " << h.level << endl;
    cout << " Zivoty : " << h.zivoty << " / " << h.maxZivoty << endl;
    cout << " Mana   : " << h.mana   << " / " << h.maxMana   << endl;
    cout << " Zlato  : " << h.zlato  << endl;
    cout << " Utok   : " << h.utok   << endl;
    cout << " XP     : " << h.zkusenosti << " / " << h.zkusenostiDoLevelup << endl;
    tiskniOddelovac();
}

void tiskniNepritele(const Nepritel &n) {
    cout << " >> " << n.nazev
         << "  [Zivoty: " << n.zivoty << "/" << n.maxZivoty
         << "  Utok: " << n.utok << "]" << endl;
}

// ============================================================
//  NASTAVENI CLASS (pardon nejsem moc kreativni a napady clankera se mi nelibily)
// ============================================================

void nastavWarrior(Hrac &h) {
    h.trida             = "Warrior";
    h.maxZivoty         = 120;
    h.zivoty            = 120;
    h.maxMana           = 40;
    h.mana              = 40;
    h.utok              = 15;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Mocny udes",    30, 10};
    h.schopnosti[1] = {"Vir ostri",     45, 20};
    h.schopnosti[2] = {"Beserkersky ryk",20, 5};
}

void nastavMage(Hrac &h) {
    h.trida             = "Mage";
    h.maxZivoty         = 70;
    h.zivoty            = 70;
    h.maxMana           = 100;
    h.mana              = 100;
    h.utok              = 8;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Ohniva koule",  40, 15};
    h.schopnosti[1] = {"Blesk",         60, 30};
    h.schopnosti[2] = {"Mraziva strela",25, 8};
}

void nastavRogue(Hrac &h) {
    h.trida             = "Rogue";
    h.maxZivoty         = 85;
    h.zivoty            = 85;
    h.maxMana           = 60;
    h.mana              = 60;
    h.utok              = 18;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Kriti. udder",  50, 20};
    h.schopnosti[1] = {"Jedovata cepel",35, 12};
    h.schopnosti[2] = {"Rychly bodec",  22, 6};
}

void nastavPaladin(Hrac &h) {
    h.trida             = "Paladin";
    h.maxZivoty         = 105;
    h.zivoty            = 105;
    h.maxMana           = 55;
    h.mana              = 55;
    h.utok              = 12;
    h.pocetSchopnosti   = 3;

    h.schopnosti[0] = {"Svaty udes",    35, 15};
    h.schopnosti[1] = {"Bozi svetlo",   50, 25};
    h.schopnosti[2] = {"Lecive pozeh.", 0,  20}; // leceni - specialni pripad
}

// ============================================================
//  VYBER CLASSY
// ============================================================

void vyberClassu(Hrac &h) {
    int volba;
    bool potvrzen = false;

    while (!potvrzen) {
        cout << "\n=== VYBER SVE POVOLANI ===" << endl;
        cout << "\n=== HP: zivotyI ===" << endl;
        cout << "1) Warrior  - Silny bojovnik s vysokymi zivoty (120 HP, 40 MP, utok 15)" << endl;
        cout << "2) Mage     - Kouzelnik co toho moc nevydrzi ale ma silnou magi (70 HP, 100 MP, utok 8)" << endl;
        cout << "3) Rogue    - Hbitý zlodej s vysokym utokem (85 HP, 60 MP, utok 18)" << endl;
        cout << "4) Paladin  - Rytir schopny leceni (105 HP, 55 MP, utok 12)" << endl;
        cout << "Volba: ";
        cin >> volba;

        switch (volba) {
            case 1: nastavWarrior(h); break;
            case 2: nastavMage(h);    break;
            case 3: nastavRogue(h);   break;
            case 4: nastavPaladin(h); break;
            default:
                cout << "Neplatna volba, zkus znovu." << endl;
                continue;
        }

        cout << "\nVybral jsi: " << h.trida << endl;
        cout << "Potvrzujes tuto volbu? (1 = Ano, 0 = Ne): ";
        cin >> potvrzen;
    }

    cout << "\nZadej jmeno sve postavy: ";
    cin >> h.jmeno;
}

// ============================================================
//  LEVEL UP
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

        cout << "\n*** NOVY LEVEL! ***" << endl;
        cout << "Level: " << h.level - 1 << " => " << h.level << endl;
        cout << "Max zivoty +" << prirustek
             << ", Max mana +3, Utok +2" << endl;
    }
}
int main{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}