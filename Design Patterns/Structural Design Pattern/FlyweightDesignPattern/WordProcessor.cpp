#include <iostream>
using namespace std;

class ILetter
{
public:
    virtual void display(int row, int column) = 0;
};

class DocumentCharacter : public ILetter
{
    char character;
    string font;
    int size;

public:
    DocumentCharacter(char c, string f, int s) : character(c), font(f), size(s) {}

    void display(int row, int column) override
    {
        cout << "Displaying character: " << character
             << " Font: " << font
             << " Size: " << size
             << " Coordinate: " << row << ", " << column << endl;
    }
};

class CharacterFactory
{
private:
    static unordered_map<char, ILetter *> characterMap;

public:
    CharacterFactory() {}

    static ILetter *getCharacter(char c)
    {
        auto it = characterMap.find(c);
        if (it != characterMap.end())
        {
            return it->second;
        }
        else
        {
            ILetter *letter = new DocumentCharacter(c, "Arial", 12);
            characterMap[c] = letter;
            return letter;
        }
    }
};

unordered_map<char, ILetter *> CharacterFactory::characterMap;

int main()
{
    cout << "===== Word Processor - Flyweight Pattern =====" << endl;

    // DATA: Hello World
    // Total 11 characters, each character has its own copy of font and size, which takes a lot of memory.

    ILetter *c1 = CharacterFactory::getCharacter('H');
    c1->display(0, 0);

    ILetter *c2 = CharacterFactory::getCharacter('e');
    c2->display(0, 1);
    ILetter *c3 = CharacterFactory::getCharacter('l');
    c3->display(0, 2);
    ILetter *c4 = CharacterFactory::getCharacter('l');
    c4->display(0, 3);
    ILetter *c5 = CharacterFactory::getCharacter('o');
    c5->display(0, 4);
    ILetter *c6 = CharacterFactory::getCharacter(' ');
    c6->display(0, 5);
    ILetter *c7 = CharacterFactory::getCharacter('W');
    c7->display(0, 6);
    ILetter *c8 = CharacterFactory::getCharacter('o');
    c8->display(0, 7);
    ILetter *c9 = CharacterFactory::getCharacter('r');
    c9->display(0, 8);
    ILetter *c10 = CharacterFactory::getCharacter('l');
    c10->display(0, 9);
    ILetter *c11 = CharacterFactory::getCharacter('d');
    c11->display(0, 10);

    // Takes a lot of memory because we are creating 11 objects and each object has its own copy of font and size.

    return 0;
}