#include <iostream>
#include "random.h"

using namespace std;

void dataIn(int &voterNum, double &candidatesPercentage, double &errorPercentage);
double invalidElection(int voterNum, double candidatesPercentage, double errorPercentage);
const int TRIAL_NUM = 500;

int main()
{
    int voterNum;
    double candidatesPercentage;
    double errorPercentage;
    Randomize();
    dataIn(voterNum, candidatesPercentage, errorPercentage);

    cout << "Chance of an invalid election result after 500 trials = ";
    cout << invalidElection(voterNum, candidatesPercentage, errorPercentage) * 100 << "%" << endl;
    getchar();
    return 0;
}

void dataIn(int &voterNum, double &candidatesPercentage, double &errorPercentage)
{
    float temp;
    cout << "Enter number of voters: ";
    cin >> temp;
    while((int)temp - temp != 0 || temp <= 0)
    {
        cout << "Please enter the correct number of voters!" << endl;
        cout << "Enter number of voters: ";
        cin >> temp;
    }
    voterNum = (int)temp;
    cout << "Enter percentage spread between candidates: ";
    cin  >> candidatesPercentage;
    while(candidatesPercentage >= 1 || candidatesPercentage <=0)
    {
        cout << "Please enter the correct number of percentage spread between candidates!" << endl;
        cout << "Enter percentage spread between candidates: ";
        cin >> candidatesPercentage;
    }
    cout << "Enter voting error percentage: ";
    cin >> errorPercentage;
    while(errorPercentage >= 1 || errorPercentage <= 0)
    {
        cout << "Please enter the correct number of voting error percentage!" << endl;
        cout << "Enter voting error percentage: ";
        cin >> errorPercentage;
    }
}

double invalidElection(int voterNum, double candidatesPercentage, double errorPercentage)
{
    int numA, numB;
    int numA_result = 0;
    int numB_result = 0;
    int errorSum = 0;
    numA = 0.5 * voterNum * (1 + candidatesPercentage * 2);
    numB = voterNum - numA;

    for(int i = 0; i < TRIAL_NUM; i++)
    {
        for(int m = 0; m < numA; m++)
        {
            if(RandomChance(errorPercentage))
                numB_result++;
            else
                numA_result++;
        }
        for(int n = 0; n < numB; n++)
        {
            if(RandomChance(errorPercentage))
                numA_result++;
            else
                numB_result++;
        }
        if(numB_result >= numA_result)
        {
            errorSum++;
        }
        numA_result = 0;
        numB_result = 0;
    }
    return (double)errorSum/TRIAL_NUM;
}
