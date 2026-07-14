#include <iostream>
using namespace std;

class Character
{
    char character;
    string font;
    int size;
    int row;
    int column;

public:
    Character(char c, string f, int s, int r, int col) : character(c), font(f), size(s), row(r), column(col) {}

    // getter and setter methods
    char getCharacter() { return character; }
    string getFont() { return font; }
    int getSize() { return size; }
    int getRow() { return row; }
    int getColumn() { return column; }
};

int main()
{
    cout << "===== Word Processor Issue =====" << endl;

    // DATA: Hello World
    // Total 11 characters, each character has its own copy of font and size, which takes a lot of memory.

    Character *c1 = new Character('H', "Arial", 12, 0, 0);
    Character *c2 = new Character('e', "Arial", 12, 0, 1);
    Character *c3 = new Character('l', "Arial", 12, 0, 2);
    Character *c4 = new Character('l', "Arial", 12, 0, 3);
    Character *c5 = new Character('o', "Arial", 12, 0, 4);
    Character *c6 = new Character(' ', "Arial", 12, 0, 5);
    Character *c7 = new Character('W', "Arial", 12, 0, 6);
    Character *c8 = new Character('o', "Arial", 12, 0, 7);
    Character *c9 = new Character('r', "Arial", 12, 0, 8);
    Character *c10 = new Character('l', "Arial", 12, 0, 9);
    Character *c11 = new Character('d', "Arial", 12, 0, 10);

    // Takes a lot of memory because we are creating 11 objects and each object has its own copy of font and size.

    return 0;
}