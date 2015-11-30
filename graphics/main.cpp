#include <iostream>
#include <string>
#include "graphics.h"
#include "extgraph.h"
#include "random.h"

using namespace std;
void draw();

int main()
{
        InitGraphics();
        draw();
        SetWindowTitle("beauty and symmetry!");
//        ExitGraphics();
        return 0;
}

void draw()
{
        //string text[3] = {"A", "B", "C"};
        double r1 = 0.005;
        double r2 = 0.005;
        double mouseX[3];
        double mouseY[3];
        for(int i = 0; i < 3; i++)
        {
                WaitForMouseDown();
                if(MouseButtonIsDown())
                {
                        mouseX[i] = GetMouseX() - r1;
                        mouseY[i] = GetMouseY();
                        StartFilledRegion();
                        MovePen(GetMouseX(), GetMouseY());
                        DrawArc(r1, 0, 360);
                        //DrawTextString(text[i]);
                        EndFilledRegion();
                }
                WaitForMouseUp();
        }
        MovePen(mouseX[0], mouseY[0]);
        for(int i = 1; i < 4; i++)
        {
                DrawLine((mouseX[i%3] - mouseX[(i-1)%3]), (mouseY[i%3] - mouseY[(i-1)%3]));
        }
        //int prior;
        int randomNum = RandomInteger(0, 2);
        MovePen(mouseX[randomNum] + r1, mouseY[randomNum]);

        while(1)
        {
                StartFilledRegion();
                DrawArc(r2, 0, 360);
                EndFilledRegion();
                if(MouseButtonIsDown())
                        break;
                //prior = randomNum;
                randomNum = RandomInteger(0, 3);
                MovePen(0.5*(GetCurrentX() + mouseX[randomNum]) + r1, 0.5*(GetCurrentY() + mouseY[randomNum]));
        }
}
