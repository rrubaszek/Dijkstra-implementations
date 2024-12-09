**Algorytmy najkrótszej ścieżki**
Ten projekt implementuje trzy różne algorytmy do znajdowania najkrótszych ścieżek w grafie. Implementacja została napisana w języku C++ i jest uruchamiana przy użyciu pliku Makefile.

**Reprezentacja grafu:**
Klasa Graph obsługuje grafy skierowane i nieskierowane.
Grafy są reprezentowane za pomocą list sąsiedztwa, co zapewnia efektywne przetwarzanie i oszczędność pamięci.

**Zaimplementowane algorytmy:**
Algorytm Dijkstry:
Standardowa implementacja z wykorzystaniem kolejki priorytetowej.

Algorytm Diala:
Wykorzystuje listę kubełkową do wyznaczania ścieżek.

Dijkstra oparty na Radix Heap:
Wykorzystuje strukturę radix heap, co przyspiesza operacje na kolejce priorytetowej.

**Wczytywanie grafu:**
Obsługuje wczytywanie grafu z odpowiednio sformatowanego pliku tekstowego.
Obsługuje wczytywanie problemu do rozwiązania z odpowiednio sformatowanego pliku tekstowego.

Makefile: Kompilacja projektu.
make stworzy folder build oraz trzy pliki wyjściowe (dijkstra, dial, radixheap)

Przykładowe uruchomienie: ./dijkstra -d graph.gr -ss sources.ss -oss results.oss.res

Plik sources.ss powinien zawierać zródła. W pliku results.oss.res zostaną wyświetlone wyniki algorytmu.

Istnieje również opcja uruchomienia z flagą -p2p pairs.p2p -op2p results.op2p.res; Wówczas algorytm wyznaczy ścieżkę między parą wierzchołków.

Wymagania:
Kompilator C++ obsługujący standard C++17 lub wyższy.
Narzędzie make.

Aby wyczyścić pliki po kompilacji:
make clean
