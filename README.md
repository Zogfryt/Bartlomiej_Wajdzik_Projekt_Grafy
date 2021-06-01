#### Bartlomiej_Wajdzik_Projekt_Grafy

# Sposób przedstawienia grafu w pliku

Jako że przeglądając jak można robić niektóre rzeczy w pliki Json, żadne mi nie pasowałem postanowiłem zachować stary format, którego używałem testując ten program na plikach
txt, jednakże zapisanym w pliku json. Opis grafu musi zostać wykonany w pliku grafy.json

Zasada przedstawiana grafu w pliku jest następująca:

1. Każda grawędź przedstawiona w postaci bloku [początek,koniec,przepływ] zachowując ściśle tą formę (nie można użyć spacji ani innych "niewidocznych rozdzielaczy")
   - np: [2,4,7] lub [Stacja_1,Stacja_2,67]
2. Lista wszystkich krawędzi zawiera się w [] w której pierwszy blok jest odrazu za klamrą otwierającą
   - każde dwa bloki oddzielone są przeicnkiem i enterem (tak jak to było w przykładowym pliku json z zadania Pierwszego)
   - klamra zamykająca w osobnej linii poniżej bliku
3. Klamra otwierająca zbiór wierzchołków musi być pierwszym znakiem w pliku
4. w następnej linii po klamrze zamykającej zbiór krawędzi podajemy wierzchołek mający być źródłem oraz po spacji wierzchołek mający być ujściem

##### Przykład
    
![obraz](https://scontent.xx.fbcdn.net/v/t1.15752-9/191189416_1123195941508412_1652619867378825957_n.png?_nc_cat=109&ccb=1-3&_nc_sid=aee45a&_nc_ohc=CF9ZqFubmq8AX9clrY6&_nc_ad=z-m&_nc_cid=0&_nc_ht=scontent.xx&oh=baaee7cc9733194f4bffcca41aec8882&oe=60D322D1)

## Uwagi

Z racji tego że nie wiedziałem w jakim formacie Pan preferowałby przesłany program zamieszczam trzy wersje, pierwsza to kod źródłowy który można skompilować w IDE takim jak CLion, drugi czyli plik exe na Windows oraz trzeci rodzaj plik wykonywalny na linuxa. Dodatkowo kod wyrzuca w pliku wynik.txt to samo co wyrzuca na konsoli

### Plik wykonywalny na Windows

Żeby skorzystać z tego pliku należy umieścić w jednym folderze plik wykonywalny exe oraz plik grafy.json po czym uruchomić plik exe

### Plik wykonywalny Linux

Jako że nie jestem doświadczony w obsłudze Linuxa jedyny sposób w jaki udało mi się odaplić program to:
1. Wrzucić pliki do tego samego folderu tak jak w przypadku Windowsa
2. Odpalić konsole w tym folderze i uruchomić program za pomocą .\Ford_Fulkerson (jeśli pisze brak dostępu należy wcześniej uruchmić komendę sudo chmod 777 ./Ford_Fulkerson)
3. Jeśli program wypluwa "Nie ma takiego źródła" pomimo poprawnego uzupełnienia należy skożystać z pliku na Windows lub skompilować program z kodu źródłowego

### Kod źródłowy

Jeśli dwie powyższe opcje nie dzadzą rady, wystaczy skompilować kod źródłowy oraz umieścić plik grafy.json tam gdzie wygeneruje się plik exe 
