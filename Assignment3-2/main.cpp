#include <iostream>
#include "graphics.h"
#include "extgraph.h"
#include "simpio.h"

using namespace std;

void DrawRuler(double x, double y, double w, double h);

int main()
{
        double width, height;
        cout << "Enter the width of the rectangle: ";
        cin >> width;
        cout << "Enter the height of the rectangle: ";
        cin >> height;
        InitGraphics();
        SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
        MovePen(0.5 * GetFullScreenWidth(), 0.5 * GetFullScreenHeight());
        DrawLine(-width / 2, 0);
        MovePen(0.5 * GetFullScreenWidth(), 0.5 * GetFullScreenHeight());
        DrawLine(+width / 2, 0);
        DrawRuler(0.5 * GetFullScreenWidth(), 0.5 * GetFullScreenHeight(), width / 2, height);
        getchar();
        return 0;
}

void DrawRuler(double x, double y, double w, double h)
{
        if(h > 0.05)
        {
                MovePen(x, y);
                DrawLine(0, h);
                DrawRuler(x - w / 2, y, w / 2, h / 2);
                DrawRuler(x + w / 2, y, w / 2, h / 2);
        }
}
