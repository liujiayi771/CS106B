#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include "genlib.h"
#include "lexicon.h"
#include "grid.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "extgraph.h"
#include "gboggle.h"
#include "set.h"

using namespace std;

typedef struct point
{
        int row;
        int col;
}pointT;

void initBoard(Grid<char> & cubes, int size);
void humanPlay(Grid<char> cubes, int size, Lexicon lex);
void computerPlay(Grid<char> cubes, int size, Lexicon lex);
void curHuman(Grid<char> cubes, int row, int col, string word, bool & target, Grid<bool> & visited, Vector<pointT> & path, string constWord, Lexicon lex);
void curComputer(Grid<char> cubes, int row, int col, string word, Lexicon lex, Grid<bool> & visited, Set<string> & words);

string StandardCubes[16]  =
{"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
 "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

string BigBoggleCubes[25]  =
{"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM", "AEEGMU", "AEGMNN", "AFIRSY",
"BJKQXZ", "CCNSTW", "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT", "DHHLOR",
"DHLNOR", "EIIITT", "EMOTTT", "ENSSSU", "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"};

void GiveInstructions()
{
    cout << endl << "The boggle board is a grid onto which I will randomly distribute "
	 << "cubes. These 6-sided cubes have letters rather than numbers on the faces, "
	 << "creating a grid of letters on which you try to form words. You go first, "
	 << "entering all the words you can find that are formed by tracing adjoining "
	 << "letters. Two letters adjoin if they are next to each other horizontally, "
	 << "vertically, or diagonally. A letter can only be used once in the word. Words "
	 << "must be at least 4 letters long and can only be counted once. You score points "
	 << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
	 << "points, and so on. After your puny brain is exhausted, I, the super computer, "
	 << "will find all the remaining words and double or triple your paltry score." << endl;

    cout << "\nHit return when you're ready...";
    GetLine();
}

static void Welcome()
{
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. "
	 << "The good news is that you might improve your vocabulary a bit.  The "
	 << "bad news is that you're probably going to lose miserably to this little "
	 << "dictionary-toting hunk of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}


int main()
{
        Grid<char> cubes;
        Lexicon lex("lexicon.dat");
        int size;
        Welcome();
        GiveInstructions();
        while(1)
	{
	        InitGraphics();
                SetWindowSize(9, 10);
                cout << endl;
                cout << "Enter the size of the board(4-5): ";
                size = GetInteger();
                DrawBoard(size,size);
                initBoard(cubes, size);
                humanPlay(cubes, size, lex);
                computerPlay(cubes, size, lex);
                getchar();
	}
	return 0;
}

void initBoard(Grid<char> & cubes, int size)
{
        cubes.resize(size, size);
        Randomize();
        for(int row = 0; row < cubes.numRows(); row++)
        {
                for(int col = 0; col < cubes.numCols(); col++)
                {
                        string temp;
                        if(size == 4)
                                temp = StandardCubes[(row + 1) * (col + 1) - 1];
                        if(size == 5)
                                temp = BigBoggleCubes[(row + 1) * (col + 1) - 1];
                        cubes.setAt(row, col, temp[RandomInteger(0, temp.size())]);

                }
        }
        for(int row = 0; row < cubes.numRows(); row++)
        {
                for(int col = 0; col < cubes.numCols(); col++)
                {
                        int randomRow = RandomInteger(row, cubes.numRows() - 1);
                        int randomCol = RandomInteger(col, cubes.numCols() - 1);
                        char temp = cubes.getAt(row, col);
                        cubes.setAt(row, col, cubes.getAt(randomRow, randomCol));
                        cubes.setAt(randomRow, randomCol, temp);
                }
        }
        for(int row = 0; row < cubes.numRows(); row++)
        {
                for(int col = 0; col < cubes.numCols(); col++)
                {
                        LabelCube(row, col, cubes.getAt(row, col));
                }
        }
}

void humanPlay(Grid<char> cubes, int size, Lexicon lex)
{
        cout << "It is the turn for human..." << endl;
        cout << "Enter the words you find(at least 4 words): " << endl;
        Set<string> words;
        while(1)
        {
                string word;

                while(1)
                {
                        word = GetLine();
                        if(word == "")
                        {
                                return;
                        }
                        else if(word.size() < 4)
                        {
                                cout << "Enter 4 letters at least!" << endl;
                        }
                        else
                                break;
                }

                for(int i = 0; i < cubes.numRows(); i++)
                {
                        for(int j = 0; j < cubes.numCols(); j++)
                        {

                                HighlightCube(i, j, false);
                        }
                }

                transform(word.begin(), word.end(), word.begin(), ::toupper);

                Vector<pointT> index;
                for(int row = 0; row < cubes.numRows(); row++)
                {
                        for(int col = 0; col < cubes.numCols(); col++)
                        {
                                if(cubes.getAt(row, col) == word[0])
                                {
                                        pointT temp = {row, col};
                                        index.add(temp);
                                }
                        }
                }
                bool target = false;

                for(int i = 0; i < index.size(); i++)
                {
                        Grid<bool> visited;
                        Vector<pointT> path;
                        visited.resize(cubes.numRows(), cubes.numCols());
                        for(int row = 0; row < visited.numRows(); row++)
                        {
                                for(int col = 0; col < visited.numCols(); col++)
                                {
                                        visited.setAt(row, col, false);
                                }
                        }
                        visited.setAt(index[i].row, index[i].col, true);
                        pointT firstPath = {index[i].row, index[i].col};
                        path.add(firstPath);
                        curHuman(cubes, index[i].row, index[i].col, word, target, visited, path, word, lex);
                }
                if(target)
                {
                        if(!words.contains(word))
                        {
                                words.add(word);
                                RecordWordForPlayer(word, Human);
                        }
                        else
                        {
                                cout << "You have already enter this word!" << endl;
                        }
                }
        }
}

void curHuman(Grid<char> cubes, int row, int col, string word, bool & target, Grid<bool> & visited, Vector<pointT> & path, string constWord, Lexicon lex)
{
        if(word.size() == 0)
        {
                if(lex.containsWord(constWord))
                {
                        int size = constWord.size();
                        for(int i = 0; i < size; i++)
                        {
                                HighlightCube(path[i].row, path[i].col, true);
                        }
                        target = true;
                }
                return;
        }
        else
        {
                if(word[0] != cubes.getAt(row, col))
                {
                        return;
                }
                else
                {
                        if(cubes.inBounds(row - 1, col - 1) && !visited.getAt(row - 1, col - 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row - 1, col - 1, true);
                                pointT temp = {row - 1, col - 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row - 1, col - 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row - 1, col) && !visited.getAt(row - 1, col))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row - 1, col, true);
                                pointT temp = {row - 1, col};
                                pathTemp.add(temp);
                                curHuman(cubes, row - 1, col, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row - 1, col + 1) && !visited.getAt(row - 1, col + 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row - 1, col + 1, true);
                                pointT temp = {row - 1, col + 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row - 1, col + 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row, col + 1) && !visited.getAt(row, col + 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row, col + 1, true);
                                pointT temp = {row, col + 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row, col + 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row + 1, col + 1) && !visited.getAt(row + 1, col + 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row + 1, col + 1, true);
                                pointT temp = {row + 1, col + 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row + 1, col + 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row + 1, col) && !visited.getAt(row + 1, col))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row + 1, col, true);
                                pointT temp = {row + 1, col};
                                pathTemp.add(temp);
                                curHuman(cubes, row + 1, col, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row + 1, col - 1) && !visited.getAt(row + 1, col - 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row + 1, col - 1, true);
                                pointT temp = {row + 1, col - 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row + 1, col - 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                        if(cubes.inBounds(row, col - 1) && !visited.getAt(row, col - 1))
                        {
                                Grid<bool> visitedTemp = visited;
                                Vector<pointT> pathTemp = path;
                                visitedTemp.setAt(row, col - 1, true);
                                pointT temp = {row, col - 1};
                                pathTemp.add(temp);
                                curHuman(cubes, row, col - 1, word.substr(1), target, visitedTemp, pathTemp, constWord, lex);
                        }
                }
        }
}

void computerPlay(Grid<char> cubes, int size, Lexicon lex)
{
        cout << "It is the turn for computer..." << endl;
        Set<string> words;
        for(int row = 0; row < cubes.numRows(); row++)
        {
                for(int col = 0; col < cubes.numCols(); col++)
                {
                        Grid<bool> visited;
                        visited.resize(cubes.numRows(), cubes.numCols());
                        for(int i = 0; i < visited.numRows(); i++)
                        {
                                for(int j = 0; j < visited.numCols(); j++)
                                {
                                        visited.setAt(i, j, false);
                                }
                        }
                        curComputer(cubes, row, col, "", lex, visited, words);
                }
        }
}

void curComputer(Grid<char> cubes, int row, int col, string word, Lexicon lex, Grid<bool> & visited, Set<string> & words)
{
        if(word.size() >= 4 && word.size() <= 8 && lex.containsWord(word) && !words.contains(word))
        {
                words.add(word);
                RecordWordForPlayer(word, Computer);
        }
        else
        {
                word += cubes.getAt(row, col);
                visited.setAt(row, col, true);
                if(!lex.containsPrefix(word))
                        return;
                if(cubes.inBounds(row - 1, col - 1) && !visited.getAt(row - 1, col - 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row - 1, col - 1, true);
                        curComputer(cubes, row - 1, col - 1, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row - 1, col) && !visited.getAt(row - 1, col))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row - 1, col, true);
                        curComputer(cubes, row - 1, col, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row - 1, col + 1) && !visited.getAt(row - 1, col + 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row - 1, col + 1, true);
                        curComputer(cubes, row - 1, col + 1, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row, col + 1) && !visited.getAt(row, col + 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row, col + 1, true);
                        curComputer(cubes, row, col + 1, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row + 1, col + 1) && !visited.getAt(row + 1, col + 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row + 1, col + 1, true);
                        curComputer(cubes, row + 1, col + 1, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row + 1, col) && !visited.getAt(row + 1, col))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row + 1, col, true);
                        curComputer(cubes, row + 1, col, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row + 1, col - 1) && !visited.getAt(row + 1, col - 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row + 1, col - 1, true);
                        curComputer(cubes, row + 1, col - 1, word, lex, visitedTemp, words);
                }
                if(cubes.inBounds(row, col - 1) && !visited.getAt(row, col - 1))
                {
                        Grid<bool> visitedTemp = visited;
                        visitedTemp.setAt(row, col - 1, true);
                        curComputer(cubes, row, col - 1, word, lex, visitedTemp, words);
                }
        }
}
