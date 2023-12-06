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
    
    CellBuildingOptions cellOpt = CellBuildingOptions(10,5);

    CheckerBuildingOptions checkOpt = CheckerBuildingOptions();

    game_engine_core::GameController* gc = GameController::Initialize(cgu, vector<ushort>(1, 3),
        &cellOpt, &checkOpt);
   
    gc->DrawBoard();

   
}

