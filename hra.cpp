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
    int poskozeni; // kolik ubere zivotu
    int manaNaklady; // kolik stoji many
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
    int utok;                       // zakladni utok (bez many)
    Schopnost schopnosti[4];
    int pocetSchopnosti;
};

struct Nepritel {
    string nazev;
    int maxZivoty;
    int zivoty;
    int utok;
    int odmenaZkusenosti;
    int odmenaZlato;          // 0 = nema penize
    bool jeBoss;             // mini-boss nebo hlavni boss vždy ma zlato
};

// ============================================================
// POMOCNE FUNKCE VYPIS
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
// NASTAVENI CLASS
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

// ============================================================
// VESNICE
// ============================================================

void navstivVesnici(Hrac &h, const string &nazev) {
    int volba;
    bool odchod = false;

    cout << "\n=== VESNICE: " << nazev << " ===" << endl;
    cout << "Vítej, poutníku!" << endl;

    while (!odchod) {
        tiskniHrace(h);
        cout << "\nCo chceš udělat?" << endl;
        cout << "1) Doplnit životy (10 zlata = full)" << endl;
        cout << "2) Zvýšit životy +10 (25 zlata)" << endl;
        cout << "3) Zvysit max manu +10 (20 zlata)" << endl;
        cout << "4) Zvysit utok +5 (30 zlata)" << endl;
        cout << "5) Odejit z vesnice" << endl;
        cout << "Volba: ";
        cin >> volba;

        switch (volba) {
            case 1:
                if (h.zlato < 10) {
                    cout << "Nemáš dost zlata! ( potřebuješ 10)" << endl;
                } else {
                    h.zlato  -= 10;
                    h.zivoty  = h.maxZivoty;
                    h.mana    = h.maxMana;
                    cout << "Jsi plně vyléčen!" << endl;
                }
                break;
            case 2:
                if (h.zlato < 25) {
                    cout << "Nemáš dost zlata! (potrebujes 25)" << endl;
                } else {
                    h.zlato    -= 25;
                    h.maxZivoty += 10;
                    h.zivoty   += 10;
                    if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                    cout << "Max životy zvýšeny na " << h.maxZivoty << "!" << endl;
                }
                break;
            case 3:
                if (h.zlato < 20) {
                    cout << "Nemáš dost zlata! (potřebuješ 20)!" << endl;
                } else {
                    h.zlato  -= 20;
                    h.maxMana += 10;
                    h.mana   += 10;
                    if (h.mana > h.maxMana) h.mana = h.maxMana;
                    cout << "Max mana zvýšena na " << h.maxMana << "!" << endl;
                }
                break;
            case 4:
                if (h.zlato < 30) {
                    cout << "Nemáš dost zlata! (potřebuješ 30)!" << endl;
                } else {
                    h.zlato -= 30;
                    h.utok  += 5;
                    cout << "Útok zvýšen na " << h.utok << "!" << endl;
                }
                break;
            case 5:
                odchod = true;
                cout << "Hodně štěstí na cestě!" << endl;
                break;
            default:
                cout << "Neplatná volba!" << endl;
        }
    }
}

// ============================================================
// 50% NA ZLATO Z MONSTER
// ============================================================

int nahodneZlato(int min, int max) {
    if (rand() % 2 == 0) return 0;           // 50% nema nic
    return min + rand() % (max - min + 1);
}

// ============================================================
// NEPRITELE
// ============================================================

Nepritel vytvorMonstrrum(const string &nazev, int zivoty, int utok,
                          int xp, int minZlato, int maxZlato) {
    Nepritel n;
    n.nazev              = nazev;
    n.maxZivoty          = zivoty;
    n.zivoty             = zivoty;
    n.utok               = utok;
    n.odmenaZkusenosti   = xp;
    n.odmenaZlato        = nahodneZlato(minZlato, maxZlato);
    n.jeBoss             = false;
    return n;
}

Nepritel vytvorBosse(const string &nazev, int zivoty, int utok,
                     int xp, int zlato) {
    Nepritel n;
    n.nazev              = nazev;
    n.maxZivoty          = zivoty;
    n.zivoty             = zivoty;
    n.utok               = utok;
    n.odmenaZkusenosti   = xp;
    n.odmenaZlato        = zlato;  // Boss ma zlato vzdy
    n.jeBoss             = true;
    return n;
}

// ============================================================
// COINCLING
// ============================================================
// 10 20 30 40 50
// poskozeni = hracovo aktualni zlatp

bool bojujCoincling(Hrac &h) {
    cout << "\n========================================" << endl;
    cout << "  $$$ ZJEVI SE COINCLING $$$" << endl;
    cout << "========================================" << endl;
    cout << "Vejdeš do místnosti a vidíš jak se na tebe malý trpaslík zubí." << endl;
    cout << "\"Ty... ty jsi tu kvůli MÉMU zlatu, viď?!\"" << endl;
    cout << "\"Od tuď vyjde s plnými kapsami a na živu jen jeden z nás...\"" << endl;

    int pocatecniUtok = h.zlato;
    cout << "\n*Coincling spatří tvoje zlato a zuřivě se na tebe vrhne*" << endl;
    cout << "\nVymlátím z tebe každou minci!" << endl;
    cout << "*Způsobuje ti " << pocatecniUtok << " poškození (dává poškození podle toho, kolik máš zlata)*" << endl;
    h.zivoty -= pocatecniUtok;
    if (h.zivoty < 0) h.zivoty = 0;

    if (h.zivoty <= 0) {
        cout << "\n*** " << h.jmeno << " Zemřel jsi! *KONEC HRY!*" << endl;
        return false;
    }

    // Coincling ti da 20 zlata
    cout << "\nCoincling se zahihňá \"*Vypadne mu 20 zlata z kapsy*\"" << endl;
    h.zlato += 20;
    cout << "Získáváš 20 zlata. Tvoje zlato: " << h.zlato << endl;

    // Coincling statistiky
    int coinclingZivoty    = 180;
    int coinclingMaxZivoty = 180;

    // 0=10 zlata 1=20 2=30 3=40 4=50
    bool prahSpusten[5] = {false, false, false, false, false};
    int prahy[5]        = {10, 20, 30, 40, 50};

    cout << "\n--- BOJ ZACINA ---" << endl;

    while (h.zivoty > 0 && coinclingZivoty > 0) {

        tiskniOddelovac();
        cout << "Tvoje životy : " << h.zivoty  << "/" << h.maxZivoty  << endl;
        cout << "Tvoje mana   : " << h.mana    << "/" << h.maxMana    << endl;
        cout << "Tvoje zlato  : " << h.zlato   << endl;
        cout << " >> COINCLING  [Životy: " << coinclingZivoty << "/" << coinclingMaxZivoty << "]" << endl;

        // HRACUV TAH
        cout << "\nCo uděláš?" << endl;
        cout << "0) Základní útok (" << h.utok << " poškození)" << endl;
        for (int i = 0; i < h.pocetSchopnosti; i++) {
            cout << i + 1 << ") " << h.schopnosti[i].nazev
                 << " (" << h.schopnosti[i].poskozeni << " poškození. "
                 << h.schopnosti[i].manaNaklady << " MP)" << endl;
        }
        cout << "Volba: ";
        int volba;
        cin >> volba;

        if (volba == 0) {
            coinclingZivoty -= h.utok;
            if (coinclingZivoty < 0) coinclingZivoty = 0;
            cout << "Zasahuješ Coinclinga za " << h.utok << "." << endl;
        } else if (volba >= 1 && volba <= h.pocetSchopnosti) {
            Schopnost &s = h.schopnosti[volba - 1];
            if (h.mana < s.manaNaklady) {
                cout << "Nedostatek many! Útočíš základním útokem." << endl;
                coinclingZivoty -= h.utok;
                if (coinclingZivoty < 0) coinclingZivoty = 0;
            } else {
                h.mana -= s.manaNaklady;
                if (s.poskozeni == 0) {
                    int heal = 20;
                    h.zivoty += heal;
                    if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                    cout << "Léčíš se za " << heal << " HP!" << endl;
                } else {
                    coinclingZivoty -= s.poskozeni;
                    if (coinclingZivoty < 0) coinclingZivoty = 0;
                    cout << "Používáš " << s.nazev << "! Coincling ztrácí "
                         << s.poskozeni << " životů." << endl;
                }
            }
        } else {
            cout << "Neplatná volba. Útočíš základním útokem." << endl;
            coinclingZivoty -= h.utok;
            if (coinclingZivoty < 0) coinclingZivoty = 0;
        }

        if (coinclingZivoty <= 0) break;

        // Coinclinguv tah zlato roste a boli

        // 1) Urok 10%
        int urok = h.zlato / 10;
        if (urok < 1) urok = 1;  // aspon 1
        h.zlato += urok;
        cout << "\nCoincling kouzli urok! +10% zlata = +" << urok
             << " (zlato: " << h.zlato << ")" << endl;

        // 2) Za kazych 10 zlata +1 dalsi
        int bonus = h.zlato / 10;
        h.zlato += bonus;
        cout << "Peníze rostou na stromech! +" << bonus
             << " (zlato: " << h.zlato << ")" << endl;

        // 3) Poskozeni = zlato hrace
        int skodaZlata = h.zlato;
        h.zivoty -= skodaZlata;
        if (h.zivoty < 0) h.zivoty = 0;
        cout << "Coincling tě přetáhne zlatou cihlou a udělí ti poškození "
             << skodaZlata << " !" << endl;

        if (h.zivoty <= 0) break;

        // kontrola prahu zlata
        for (int i = 0; i < 5; i++) {
            if (!prahSpusten[i] && h.zlato >= prahy[i]) {
                prahSpusten[i] = true;

                switch (prahy[i]) {
                    case 10:
                        coinclingZivoty += 10;
                        if (coinclingZivoty > coinclingMaxZivoty)
                            coinclingMaxZivoty = coinclingZivoty;
                        cout << "\n[PRÁH 10 zlata] Coincling se uzdravuje o 10 HP! "
                             << "(" << coinclingZivoty << " HP)" << endl;
                        break;
                    case 20:
                        h.maxZivoty -= 10;
                        if (h.maxZivoty < 1) h.maxZivoty = 1;
                        if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                        cout << "\n[PRÁH 20 zlata] Tíže zlata ti ubírá sílu! "
                             << "Max zivoty -10 => " << h.maxZivoty << endl;
                        break;
                    case 30:
                        coinclingZivoty += 10;
                        if (coinclingZivoty > coinclingMaxZivoty)
                            coinclingMaxZivoty = coinclingZivoty;
                        cout << "\n[PRÁH 30 zlata] Coincling se uzdravuje o 10 HP! "
                             << "(" << coinclingZivoty << " HP)" << endl;
                        break;
                    case 40:
                        h.maxZivoty -= 10;
                        if (h.maxZivoty < 1) h.maxZivoty = 1;
                        if (h.zivoty > h.maxZivoty) h.zivoty = h.maxZivoty;
                        cout << "\n[PRÁH 40 zlata] Topíš se ve zlatě! "
                             << "Max zivoty -10 => " << h.maxZivoty << endl;
                        break;
                    case 50:
                        cout << "\n[PRÁH 50 zlata] *** PROPADLI JSTE SE DO PEKLA Z TOHO JAK PLNÉ KAPSY UKRADENÉHO ZLATA MÁŠ! ***" << endl;
                        h.zivoty -= 20;
                        if (h.zivoty < 0) h.zivoty = 0;
                        coinclingZivoty -= 20;
                        if (coinclingZivoty < 0) coinclingZivoty = 0;
                        cout << "Oba obdržíte 20 poškození! "
                             << "(Ty: " << h.zivoty << " HP, "
                             << "Coincling: " << coinclingZivoty << " HP)" << endl;
                        break;
                }

                if (h.zivoty <= 0 || coinclingZivoty <= 0) break;
            }
        }
    }

    // --- Vysledek ---
    if (h.zivoty <= 0) {
        cout << "\n*** " << h.jmeno << " byl rozdrcen tíhou zlata! *KONEC HRY*" << endl;
        return false;
    }

    cout << "\n========================================" << endl;
    cout << "*** COINCLING PORAZEN! ***" << endl;
    cout << "Trpaslík leží nehybně na zemi, zatím co mu kradeš poslední zlaté mince z kapes..." << endl;
    cout << "\"...Stálo ti to za to?\"" << endl;
    cout << "\"Dobrá práce.\"" << endl;
    cout << "========================================" << endl;

    h.zkusenosti += 150;
    h.zlato += 100;
    cout << "+150 XP, +100 zlata" << endl;
    zkontrolujLevelUp(h);

    return true;
}

// ============================================================
// HLAVNI FUNKCE
// ============================================================

int main{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
        srand((unsigned)time(0));

    cout << "========================================" << endl;
    cout << "       VITEJ V TEXTOVEM RPG!            " << endl;
    cout << "========================================" << endl;

    // ---- Hrac ----
    Hrac hrac;
    hrac.level                = 1;
    hrac.zkusenosti           = 0;
    hrac.zkusenostiDoLevelup  = 50;
    hrac.zlato                = 20;

    vyberClassu(hrac);
    tiskniHrace(hrac);
    cout << "\nDobra cesta, " << hrac.jmeno << "!" << endl;

    // ================================================================
    //  MAPA: |V| M | M | 2xM | MB | V | M | 2xM | 2xM | MB |
    //        | V | 2xM | 2xM | 3xM | V | HB |
    //  Celkem: 16 monster (1+1+2+2+1+2+2+2 = 13 solo + 3 ve skupine)
    //  + 2 mini-bossove + 1 hlavni boss
    // ================================================================

    bool ziv = true;

    // ---- VESNICE 1: Nástupní město ----
    navstivVesnici(hrac, "Pocatecni vesnice");
    if (hrac.zivoty <= 0) { return 0; }

    // ---- 1. Monstrum ----
    if (ziv) {
        Nepritel m = vytvorMonstrum("Gobling", 30, 8, 15, 3, 8);
        ziv = bojuj(hrac, m, true);
    }

    // ---- 2. Monstrum ----
    if (ziv) {
        Nepritel m = vytvorMonstrum("Vlk", 35, 10, 18, 4, 9);
        ziv = bojuj(hrac, m, true);
    }

    // ---- 2x Monstrum ----
    if (ziv) {
        Nepritel skupina[2];
        skupina[0] = vytvorMonstrum("Gobling strazce", 28, 7, 12, 2, 7);
        skupina[1] = vytvorMonstrum("Goblin luchshtar", 25, 9, 12, 2, 7);
        ziv = bojujSkupina(hrac, skupina, 2);
    }

    // ---- MINI-BOSS 1 ----
    if (ziv) {
        Nepritel mb = vytvorBosse("Orksky nacelink", 80, 18, 50, 25);
        ziv = bojuj(hrac, mb, false);  // Boss ide prvni
    }

    // ---- VESNICE 2 ----
    if (ziv) {
        navstivVesnici(hrac, "Lesni vesnicka");
    }

    // ---- 3. Monstrum ----
    if (ziv) {
        Nepritel m = vytvorMonstrum("Prales vpr", 40, 11, 20, 5, 10);
        ziv = bojuj(hrac, m, true);
    }

    // ---- 2x Monstrum ----
    if (ziv) {
        Nepritel skupina[2];
        skupina[0] = vytvorMonstrum("Jedovaty pavouci", 32, 10, 14, 3, 8);
        skupina[1] = vytvorMonstrum("Jedovaty pavouci", 32, 10, 14, 3, 8);
        ziv = bojujSkupina(hrac, skupina, 2);
    }

    // ---- 2x Monstrum ----
    if (ziv) {
        Nepritel skupina[2];
        skupina[0] = vytvorMonstrum("Kamenny golem (maly)", 50, 12, 20, 5, 12);
        skupina[1] = vytvorMonstrum("Kamenny golem (maly)", 50, 12, 20, 5, 12);
        ziv = bojujSkupina(hrac, skupina, 2);
    }
}
