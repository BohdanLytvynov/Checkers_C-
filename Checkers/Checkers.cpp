#include"pch.h"
#include"v_math.h"
#include"GameEngine.h"
#include"Console_graphics.h"




int main()
{
    typedef unsigned short ushort;

    using namespace std;

    using namespace vector_math;

    using namespace game_engine_core;

    using namespace console_graphics;

    std::cout << "Checkers!\n";
    
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    console_graphics_utility* cgu = console_graphics_utility::Init(console);

    /*GameObject* cell = new Cell(10,5, Colors::WhiteBack, Colors::BLACK | Colors::LIGHTGRAYBack,
        vector<ushort>(2,2));

    cell->Render(*cgu);

    delete cell;*/

    //Try to draw a circle

    int s = 0;

    int end = 360;

    vector<ushort> pos;

    while (s != end)
    {
        pos.SetX(std::cos(s * (M_PI/180 )) + 4);

        pos.SetY(std::sin(s * (M_PI/180)) + 4);

        cgu->SetCursorPosition(pos);

        cgu->Print("*");

        s++;
    }
}

