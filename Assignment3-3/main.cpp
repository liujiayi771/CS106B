#include <iostream>
#include "vector.h"
#include "simpio.h"

using namespace std;

int CountCriticalVotes(Vector<int> & blocks, int blockIndex);
int votesRecursion(Vector<int> combination, Vector<int> rest, int winVotes, int lastVote);

int main()
{
        Vector<int> blocks;
        blocks.add(9);
        blocks.add(9);
        blocks.add(7);
        blocks.add(3);
        blocks.add(1);
        blocks.add(1);
        cout << "The critical votes: " << CountCriticalVotes(blocks, 5) << endl;
        return 0;
}

int CountCriticalVotes(Vector<int> & blocks, int blockIndex)
{
        int sum = 0;
        for(int i = 0; i < blocks.size(); i++)
        {
                sum += blocks[i];
        }
        int winVotes = sum / 2 + 1;
        int lastVote = blocks[blockIndex];
        Vector<int> emptyVec;
        blocks.removeAt(blockIndex);
        return votesRecursion(emptyVec, blocks, winVotes, lastVote);
}

int votesRecursion(Vector<int> combination, Vector<int> rest, int winVotes, int lastVote)
{
        if(rest.isEmpty())
        {
                int sum = 0;
                for(int i = 0; i < combination.size(); i++)
                {
                        sum += combination[i];
                }
                if(sum + lastVote > winVotes && sum < winVotes)
                {
                        return 1;
                }
                else
                {
                        return 0;
                }
        }
        else
        {
                Vector<int> addCombination = combination;
                addCombination.add(rest[0]);
                rest.removeAt(0);
                return votesRecursion(addCombination, rest, winVotes, lastVote) + votesRecursion(combination, rest, winVotes, lastVote);
        }
}
