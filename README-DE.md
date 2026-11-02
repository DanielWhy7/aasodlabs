## Sprachen
[Englisch](README.md) [Russisch](README-RU.md) [Deutsch](README-DE.md) [Japanisch](README-JA.md)

# Laborarbeit Nr. 2 — Verkettete Listen (Variante 1, C++26)

| Parameter         | Wert                                                           |
|-------------------|----------------------------------------------------------------|
| Listentyp         | **3** — Einfach verkettete zirkuläre Liste                     |
| Grundaufgabe      | **8** — Zwei sortierte Listen ohne Duplikate zusammenführen    |
| Fortgeschrittene Aufgabe | **3** — Türme von Hanoi mit drei (oder zwei) Listen     |
| Sprache           | **C++26** (Module, Contracts, `import std;`)                   |
| Build-System      | **CMake 4.1+** mit Ninja, Presets für GCC / Clang / MSVC       |

---

## Überblick

Das Projekt implementiert eine Template-Klasse `linked_list<T>` auf Basis einer
einfach verketteten **zirkulären** Liste zusammen mit der Hilfsstruktur
`node<T>`. Die Klasse besitzt die dynamisch allokierten Knoten (Rule of Three),
ist vollständig kopierbar und wirft bei ungültigen Argumenten Ausnahmen aus
`std::stdexcept`.

Auf der Klasse aufbauend werden zwei praktische Aufgaben gelöst:

* **(Grundaufgabe)** Zusammenführen zweier sortierter Listen zu einer
  sortierten Liste ohne Duplikate;
* **(fortgeschrittene Aufgabe)** die Türme von Hanoi, wobei jeder Stab durch
  eine Liste repräsentiert wird und der Zustand der Stäbe als ASCII-Türme
  ausgegeben wird.

Der Code ist im **K&R-Stil** geschrieben (`typ name() {`, 2 Leerzeichen
Einrückung, `snake_case`-Bezeichner) und nutzt **C++26-Features** wie in der
cppreference-Dokumentation beschrieben:

* **Named Modules** — `import std;` bringt die gesamte Standardbibliothek
  ohne Header-Dateien in den Gültigkeitsbereich;
* **Contracts** — `contract_assert` (sowie die Deklarator-Formen `pre` /
  `post`) drücken interne Invarianten aus wie `tail_->next == head_` und
  `size_ == expected`. Benutzerorientierte Fehler verwenden weiterhin
  Ausnahmen, damit der Aufrufer reagieren kann.

## Repository-Struktur

```
.
├── CMakeLists.txt
├── CMakePresets.json
├── .gitignore
├── README.md
├── LICENSE                       # GPLv3
└── src/
    ├── linked_list.cppm          # linked_list<T> und node<T>       (Modul-Schnittstelle)
    ├── tasks.cppm                # tasks-Modul                     (Modul-Schnittstelle)
    ├── tasks.cpp                 # tasks-Modul                     (Implementierung)
    ├── main.cpp                  # ▶ interaktives Programm — enthält main()
    └── test.cpp                  # ▶ Testsuite             — enthält main()
```

Sowohl `main.cpp` als auch `test.cpp` definieren ihr eigenes `main()`; sie
werden in **zwei separate ausführbare Dateien** (`main` und `tests`)
kompiliert, die sich eine statische Bibliothek `lablib` teilen, welche die
beiden Module enthält.

## Anforderungen

Die Arbeit folgt den Mindestanforderungen der Aufgabe:

1. Kompiliert ohne Warnungen bei höchster Warnstufe:
   * GCC / Clang: `-Wall -Wconversion -Wextra -Wpedantic`
   * MSVC: `/W4 /utf-8`
2. Keine globalen Variablen (Konstanten sind erlaubt).
3. Alle Bezeichner sind in Englisch geschrieben; keine Transliteration.
   Russisch wird nur in Kommentaren verwendet.
4. Keine zeilenweise Kommentierung — höchstens ein kurzer Kommentar pro
   logischem Block.
5. Ein einheitlicher Namensstil (K&R / `snake_case`) wird auf **alle**
   benannten Entitäten angewendet — Funktionen, Methoden, Klassen, Variablen,
   Parameter, Dateien.
6. Das Git-Repository enthält eine aussagekräftige Commit-Historie mit
   beschreibenden Nachrichten und einer korrekt konfigurierten `.gitignore`;
   Build-Artefakte werden niemals committet.

Zusätzliche Einschränkungen aus der Aufgabe:

* **Es werden keine STL-Container** verwendet (`std::vector`, `std::list`
  usw. sind verboten).
* Die Klasse ist kopierbar und verwaltet die von ihr allokierte Ressource
  direkt.
* Ungültige Situationen (`operator[]` auf leerer Liste, `pop_head` /
  `pop_tail` auf leerer Liste, …) werfen Ausnahmen aus `<stdexcept>`.
* Die gesamte Ein-/Ausgabe erfolgt ausschließlich über `std::cin` /
  `std::cout`.
* Die Aufgabenlösungen liegen **außerhalb** der Klasse — sie sind freie
  Funktionen im Modul `tasks`.

## Bauen

### Mit CMake (empfohlen)

```sh
cmake -G Ninja -B build -Wno-dev
cmake --build build
```

Der Build erzeugt zwei ausführbare Dateien unter `/build`:

| Binärdatei | Zweck |
|------------|-------|
| `main`     | interaktives Programm — führt Aufgabe 8, dann Aufgabe 3 aus |
| `tests`    | automatisierte Testsuite (17 Tests); beendet mit `0` bei Erfolg |

### Direkt mit dem Compiler (GCC 16.1+)

```sh
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/main.cpp src/tasks.cpp -o main
g++ -std=c++26 -fmodules -fcontracts \
    -Wall -Wconversion -Wextra -Wpedantic \
    --compile-std-module \
    src/test.cpp src/tasks.cpp -o tests
```

Das Flag `-fcontracts` aktiviert die C++26-Contract-Assertions, die in
`linked_list` und `tasks.cpp` verwendet werden.

## Ausführen

```sh
# 1) Zuerst die automatisierte Testsuite
./build/linux-debug/tests
# 2) Dann das interaktive Programm
./build/linux-debug/main
```

### Ausgabe der Testsuite

```
=== Automated tests ===
  PASS: default constructor
  PASS: random fill constructor
  PASS: push_tail / push_head
  PASS: modulo indexing
  PASS: empty index throws
  PASS: copy constructor
  PASS: assignment
  PASS: pop_head
  PASS: pop_tail
  PASS: delete_node
  PASS: push_tail(list)
  PASS: push_head(list)
  PASS: merge_sorted_unique
  PASS: merge with empty
  PASS: merge both empty
  PASS: merge collapses duplicates
  PASS: hanoi(0) is a no-op
=== All tests passed ===
```

### Interaktive Sitzung

```
Task 8: merging two sorted lists without duplicates
Enter first list (count then values): 4 1 3 5 7
Enter second list (count then values): 5 2 3 4 5 8
Merged: [1, 2, 3, 4, 5, 7, 8]

Task 3: Tower of Hanoi
Enter number of disks: 3

Initial state:
A            B            C
============================
[1]          [ ]          [ ]
[2]          [ ]          [ ]
[3]          [ ]          [ ]

Move 1: A -> C
...
Total moves: 7
```

## API von `linked_list<T>`

| Member                                          | Beschreibung                                                         |
|-------------------------------------------------|----------------------------------------------------------------------|
| `linked_list()`                                 | Standardkonstruktor — leere Liste.                                   |
| `linked_list(const linked_list&)`               | Kopierkonstruktor (tiefe Kopie).                                     |
| `linked_list(std::size_t, seed, min, max)`      | Konstruktor mit zufälliger Befüllung (`requires std::integral<T>`).  |
| `~linked_list()`                                | Gibt alle Knoten frei.                                               |
| `operator=`                                     | Zuweisung per Kopie (copy-and-swap).                                 |
| `swap(linked_list&)`                            | O(1)-Member-Swap.                                                    |
| `size()` / `empty()`                            | Größenabfragen.                                                      |
| `push_tail(const T&)`                           | Fügt ein Element am Ende ein.                                        |
| `push_tail(const linked_list&)`                 | Fügt eine andere Liste am Ende ein.                                  |
| `push_head(const T&)`                           | Fügt ein Element am Anfang ein.                                      |
| `push_head(const linked_list&)`                 | Fügt eine andere Liste am Anfang ein.                                |
| `pop_head()`                                    | Entfernt das erste Element; wirft bei leerer Liste.                  |
| `pop_tail()`                                    | Entfernt das letzte Element; wirft bei leerer Liste.                 |
| `delete_node(const T&)`                         | Entfernt alle Knoten, deren Wert dem Argument entspricht.            |
| `operator[](std::size_t)`                       | Elementzugriff; Index wird **modulo Größe** reduziert (zirkuläre Liste). |
| `operator[](std::size_t) const`                 | Dasselbe, nur lesend.                                                |
| `operator<<`                                    | Gibt die Liste auf `std::ostream` aus (verwendet von `std::cout`).   |

Da die Liste zirkulär ist, wird jeder Index modulo der aktuellen Größe
reduziert, sodass jeder Index ein gültiges Element liefert. Bei einer leeren
Liste wird dennoch `std::out_of_range` geworfen.

## Grundaufgabe 8 — sortierte Listen ohne Duplikate zusammenführen

```cpp
linked_list<int> merge_sorted_unique(const linked_list<int>& first,
                                     const linked_list<int>& second);
```

Beide Eingaben werden als aufsteigend sortiert angenommen. Die Funktion führt
eine lineare **Zwei-Zeiger-Verschmelzung** durch, überspringt gleiche
Nachbarn und gibt eine neue sortierte Liste zurück, die jeden unterschiedlichen
Wert aus beiden Eingaben genau einmal enthält. Duplikate *innerhalb* einer
einzelnen Eingabe werden ebenfalls zusammengefasst.

Komplexität: `O(n + m)` Zeit, `O(n + m)` zusätzliche Knoten.

## Fortgeschrittene Aufgabe 3 — Türme von Hanoi mit Listen

```cpp
void hanoi(unsigned int disk_count);
```

Drei Instanzen von `linked_list<unsigned>` repräsentieren die Stäbe `A`, `B`,
`C`. Die Scheiben werden als ihre Größen gespeichert (größerer Wert = größere
Scheibe), sodass jeder Stab eine absteigend sortierte Liste ist — die kleinste
Scheibe befindet sich immer an seinem **Kopf**. Dadurch ist der legale Zug
`pop_head` auf dem Quellstab + `push_head` auf dem Zielstab, denn bei Hanoi
darf nur die oberste (kleinste) Scheibe bewegt werden.

Die rekursive Lösung bewegt `n` Scheiben von `A` nach `C` und verwendet `B`
als Hilfsstab. Nach jedem Zug wird der Zustand aller drei Stäbe als
ASCII-Türme ausgegeben (z. B. `[3]` für eine Scheibe der Größe 3, `[ ]` für
einen leeren Platz). Da die Stäbe unten ausgerichtet gezeichnet werden,
„ruhen" die Scheiben stets auf dem Boden.

Die rekursive Lösung benötigt `2^n - 1` Züge.

## Verwendete C++26-Features

| Feature | Wo | Zweck |
|---------|-----|-------|
| **Named Modules** (`import std;`) | `linked_list.cppm`, `tasks.cppm`, `tasks.cpp`, `main.cpp`, `test.cpp` | Schnellere, saubere Kompilierung ohne Präprozessor-Header. |
| **Contracts** (`contract_assert`) | Memberfunktionen von `linked_list` | Prüft interne Invarianten (`tail_->next == head_`, `size_ == other.size_`, …) in Debug-Builds. |
| **`requires`-Klauseln** | `linked_list(count, seed, min, max)` | Beschränkt den Zufallskonstruktor auf ganzzahlige Typen. |
| **Standardbibliotheks-Module** | `import std;` | Die gesamte Standardbibliothek ist ohne `#include` verfügbar. |

> **Hinweis:** Pattern Matching ist **nicht** in C++26 enthalten; es wurde
> auf C++29 verschoben. Das Projekt verwendet daher kein `std::match`.

## Modul-Layout (warum `tasks.cppm` + `tasks.cpp`?)

Das Modul `tasks` ist in eine **Module Interface Unit** (`tasks.cppm`, die die
beiden exportierten Funktionen deklariert) und eine **Module Implementation
Unit** (`tasks.cpp`, die deren Rümpfe definiert) aufgeteilt. Dies ist das
Modul-Äquivalent zur Aufteilung von Header und `.cpp`:

* Das Bearbeiten des Rumpfes von `hanoi` oder `merge_sorted_unique`
  kompiliert nur `tasks.cpp` neu, **nicht** `main.cpp` oder `test.cpp`.
* Datei-lokale Helfer (`print_disk_field`, `print_rod_cell`, `print_state`,
  `hanoi_recursive`) liegen in `tasks.cpp` als `static`-Funktionen und sind
  für Nutzer des Moduls unsichtbar.

`linked_list` ist **nicht** auf dieselbe Weise aufgeteilt, weil es ein
Template ist — seine vollständige Definition muss in jeder
Übersetzungseinheit sichtbar sein, die es instanziiert, daher liegt alles in
`linked_list.cppm`.

## Kodierungsstil

K&R / Linux-Kernel-Stil:

* Klassen, Structs, Funktionen, Variablen, Parameter, Dateien: `snake_case`
  (`linked_list`, `node`, `push_tail`, `merge_sorted_unique`).
* **Rückgabetyp und Funktionsname auf derselben Zeile**, öffnende Klammer
  auf derselben Zeile:

  ```cpp
  int main() {
    ...
  }
  ```

* 2 Leerzeichen Einrückung.
* `nullptr` statt `NULL`, `static_cast<>` statt C-Casts.
* Kein Leerzeichen zwischen Funktionsname und `(`.

Der Stil wird einheitlich auf jede benannte Entität im Projekt angewendet.
