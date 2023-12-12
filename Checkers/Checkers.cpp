#include"pch.h"
#include"v_math.h"
#include"GameEngine.h"
#include"Console_graphics.h"

#pragma region Functions


#pragma endregion



int main()
{
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	typedef unsigned short ushort;

#pragma region using namespaces

	using namespace std;

	using namespace vector_math;

	using namespace game_engine_core;

	using namespace console_graphics;

#pragma endregion

#pragma region Main game Variables

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	console_graphics_utility* cgu = console_graphics_utility::Init(console);

	bool whiteBlack = true;

	vector<ushort> CheckerBoardPosition = vector_math::vector<ushort>(5, 1);

	ushort consoleHeight = cgu->GetConsoleHeight();

	ushort consoleWidth = cgu->GetConsoleWidth();

	ushort CheckerBoardLength = 8 * 10;

	ushort temp = 30;

	vector<ushort> textPos = vector_math::vector<ushort>(CheckerBoardLength + CheckerBoardPosition[0] +
		temp, consoleHeight / 2);

	CellBuildingOptions cellOpt = CellBuildingOptions();

	CheckerBuildingOptions checkOpt = CheckerBuildingOptions(console_graphics::Colors::BLUEBack,
		console_graphics::Colors::REDBack, console_graphics::Colors::GREENBack);

	game_engine_core::GameController* gc = GameController::Initialize(cgu, CheckerBoardPosition,
		&cellOpt, &checkOpt);

	char moveLeft = 'a';

	char moveRight = 'd';

	char input;

	auto PrintFunc = [cgu, textPos, whiteBlack]()
	{
		cgu->PrintAtCenter("<<<Checkers the Game>>>");

		cgu->Print("Turn of:" + whiteBlack ? "white Checkers(Player 1)" : "black Checkers(Player 2)",
			textPos);

		cgu->Print("Pressing A D please select the checker you want to use for the turn.",
			textPos + vector_math::vector<ushort>(0, 1));

		cgu->Print("After you selected the propriate checker press Enter.",
			textPos + vector<ushort>(0, 2));
	};

#pragma endregion

#pragma region Game
	
	gc->SelectChecker(whiteBlack, PrintFunc);

	gc->HighLightPossibleTurns();

	whiteBlack = !whiteBlack;



#pragma endregion   

	//Select Checker Cycle



	/*Cell c = Cell(10, 6, console_graphics::Colors::WhiteBack, console_graphics::Colors::BLACK |
	console_graphics::Colors::LIGHTGRAYBack, vector<ushort>(3,3), true);

	Checker ch = Checker(10, 6, console_graphics::Colors::GREYBack, console_graphics::Colors::BLACK,
		vector<ushort>(3, 3));

	ch.MakeDamka();

	c.Render(*cgu);

	ch.Render(*cgu);*/

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

