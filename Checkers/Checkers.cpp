#include"pch.h"
#include"v_math.h"
#include"GameEngine.h"
#include"Console_graphics.h"
#include"DataStructures.h"

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

	using namespace game_engine_core::ai_modules;

	using namespace console_graphics;

#pragma endregion

#pragma region Main game Variables
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	console_graphics_utility* cgu = console_graphics_utility::Init(console);

	bool whiteBlack = true;

	bool whiteBlack_Winner = false;

	vector_math::Vector<ushort> CheckerBoardPosition = vector_math::Vector<ushort>(5, 1);

	ushort consoleHeight = cgu->GetConsoleHeight();

	ushort consoleWidth = cgu->GetConsoleWidth();

	ushort CheckerBoardLength = 8 * 10;

	ushort temp = 30;

	vector_math::Vector<ushort> textPos = vector_math::Vector<ushort>(CheckerBoardLength + CheckerBoardPosition[0] +
		temp, consoleHeight / 2);

	CellBuildingOptions cellOpt = CellBuildingOptions();

	CheckerBuildingOptions checkOpt = CheckerBuildingOptions(console_graphics::Colors::BLUEBack,
		console_graphics::Colors::REDBack, console_graphics::Colors::GREENBack);

	ai_modules::checker_ai* ai = new ai_modules::checker_ai(cgu);

	game_engine_core::GameController* gc = GameController::Initialize(cgu, CheckerBoardPosition,
		&cellOpt, &checkOpt, ai);
	
	char input;

	string comp_names[4] = {"<<Mr_Processor>>", "<<MeatBall_Anihilator>>", "SUPER_CPU", "I'll_divide_you_ByZERO"};
	
	string pl1;

	string pl2;
    
	bool start = false;

#pragma endregion

#pragma region DoubledLinked List

	/*linear_data_structures::circular_doubled_linked_list<int> dll;

	dll.AddToTheBegining(1);

	dll.AddToTheBegining(2);

	dll.AddToTheBegining(3);

	dll.IterateFromStartToEnd([](int elem)->bool { std::cout << elem << endl; return true; });

	dll.~circular_doubled_linked_list();*/

#pragma endregion
	
#pragma region Game
		
	do
	{
//		cgu->PrintAtCenter("<<<Checkers the Game>>>");
//
//		//Selection menu
//		input = console_funcs::Input<char, char>([cgu](char inp)->bool
//			{
//				if (inp == '1' || inp == '2' || inp == '3')
//				{
//					return true;
//				}
//				else
//				{
//					cgu->Print("Incorrect Input!");
//
//					return false;
//				}
//
//				return true;
//
//			}, false, nullptr, "Choose an option:\n\t Press 1 -> 2 Players \n\t Press 2 -> 1 Player\n\t Press 3 -> if you want to exit");
//
#pragma region Main game cycle
//		
//		std::system("CLS");
//
//		if (input == '1')
//		{
//			cgu->Print("You have selected option 2 Players!");
//
//			pl1 = console_funcs::Input<string, string>([](string inp)->bool {return true; }, true, nullptr,
//				"Enter name of the first Player(white Checkers): ");
//
//			pl2 = console_funcs::Input<string, string>([](string inp)->bool {return true; }, true, nullptr,
//				"Enter name of the second Player(black Checkers): ");
//		}
//		else if (input == '2')
//		{
//			cgu->Print("You have selected option 1 Player!");
//
//			pl1 = console_funcs::Input<string, string>([](string inp)->bool {return true; }, true, nullptr,
//				"Enter name of the first Player(white Checkers): ");
//			
//			pl2 = comp_names[std::rand() % size(comp_names)];
//
//			
//		}
//		else if (input == '3')
//		{
//			return 0;
//		}
//
//		cgu->Print("1 - Player: " + pl1);
//
//		cgu->Print("2 - Player: " + pl2);
//
//		input = console_funcs::Input<char, char>([](char inp)->bool {return true; }, true, nullptr,
//			"Are you ready to start game? press y or n: ");
//
//		if (input == 'y' || input == 'Y')
//		{
//			start = true;
//		}
//
//		string name1 = "white_Checkers: " + pl1;
//
//		string name2 = "black_Checkers: " + pl2;

		start = true;

		string name1 = "Pl1";

		string name2 = "Pl2";

		gc->SetDifficulty(difficulty_level::easy);

		if (start)
		{
			do
			{
				gc->SelectChecker(whiteBlack, [name1, name2, cgu, textPos, whiteBlack]()
					{
						cgu->PrintAtCenter("<<<Checkers the Game>>>");

						string whiteBlackStr = whiteBlack ? name1 : name2;

						cgu->Print("Turn of:" + whiteBlackStr,
							textPos);

						cgu->Print("By pressing A D please chose the checker you want to use for the turn.",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("After you chose the propriate object press s.",
							textPos + vector_math::Vector<ushort>(0, 2));
					}, [cgu, textPos, whiteBlack]()
					{
						cgu->PrintAtCenter("<<<Checkers the Game>>>");

						cgu->Print("                                   ",
							textPos);

						cgu->Print("                                   ",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("                                   ",
							textPos + vector_math::Vector<ushort>(0, 2));

						cgu->Print("Selection done succesfuly!",
							textPos);

						cgu->Print("Press c to confirm your selection. ",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("If you want to cancel move set press r!        ",
							textPos + vector_math::Vector<ushort>(0, 2));
					});

				gc->FindPossibleTurns(whiteBlack);

				gc->HighLightPossibleTurns(whiteBlack);

				gc->SelectMove(whiteBlack, [name1, name2, cgu, textPos, whiteBlack]()
					{
						cgu->PrintAtCenter("<<<Checkers the Game>>>");

						string whiteBlackStr = whiteBlack ? name1 : name2;

						cgu->Print("Turn of:" + whiteBlackStr,
							textPos);

						cgu->Print("By pressing A D please chose the cell you want to use for the turn.",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("After you chose the propriate object press s.",
							textPos + vector_math::Vector<ushort>(0, 2));

						cgu->Print("In case of multiselection: By using A D choose the turn",
							textPos + vector_math::Vector<ushort>(0, 3));

						cgu->Print("then press s to select this move. After you have choosen all",
							textPos + vector_math::Vector<ushort>(0, 4));

						cgu->Print("the turns you want press c to confirm this moveset, if you want",
							textPos + vector_math::Vector<ushort>(0, 5));

						cgu->Print("to change it, press r, it will clear the selected moveset",
							textPos + vector_math::Vector<ushort>(0, 6));
					}, [cgu, textPos, whiteBlack]()
					{
						cgu->PrintAtCenter("<<<Checkers the Game>>>");

						cgu->Print("                                                                   ",
							textPos);

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 2));

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 3));

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 4));

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 5));

						cgu->Print("                                                                   ",
							textPos + vector_math::Vector<ushort>(0, 6));

						cgu->Print("Selection done succesfuly!",
							textPos);

						cgu->Print("Press c to confirm your selection.                                   ",
							textPos + vector_math::Vector<ushort>(0, 1));

						cgu->Print("If you want to cancel move set press r!                              ",
							textPos + vector_math::Vector<ushort>(0, 2));
					});

				gc->Move();

				gc->DeselectAllGameObjects();

				whiteBlack = !whiteBlack;
			} while (!gc->IsGameOver(whiteBlack_Winner));

			std::system("CLS");

			if (whiteBlack_Winner)
			{
				std::cout << name1 + " wins!" << endl;
			}
			else
			{
				std::cout << name2 + " wins!" << endl;
			}

#pragma endregion
		}
				
		std::system("CLS");

		input = console_funcs::Input<char, char>([](char inp)->bool 
			{
				return true;
			}, false, nullptr, "Do you want to cancel the game? Press q if not, press any key!");

	} while (!(input == 'q' || input == 'Q'));
	
#pragma endregion   

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	return 0;
}

