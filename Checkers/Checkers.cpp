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
    
   /* CellBuildingOptions cellOpt = CellBuildingOptions(10,6);

    CheckerBuildingOptions checkOpt = CheckerBuildingOptions();

    game_engine_core::GameController* gc = GameController::Initialize(cgu, vector<ushort>(1, 1),
        &cellOpt, &checkOpt);
   
    gc->DrawBoard();*/

    Cell c = Cell(10, 6, console_graphics::Colors::WhiteBack, console_graphics::Colors::BLACK |
    console_graphics::Colors::LIGHTGRAYBack, vector<ushort>(3,3));

    Checker ch = Checker(10, 6, console_graphics::Colors::GREYBack, console_graphics::Colors::BLACK,
        vector<ushort>(3, 3));

    ch.MakeDamka();

    c.Render(*cgu);

    ch.Render(*cgu);
}

