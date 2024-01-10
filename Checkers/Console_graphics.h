#ifndef CONSOLE_GRAPHICS_H

#define CONSOLE_GRAPHICS_H

#include"v_math.h"
#include<functional>
typedef unsigned short ushort;

namespace console_graphics
{
	using namespace vector_math;

	class Colors
	{
	public:
		/// <summary>
		/// Foreground Colors
		/// </summary>
		static WORD White;

		static WORD BLACK;

		static WORD GREY;

		static WORD LIGHTGRAY;

		static WORD BLUE;

		static WORD GREEN;

		static WORD CYAN;

		static WORD RED;

		static WORD PURPLE;

		static WORD LIGHTBLUE;

		static WORD LIGHTGREEN;

		static WORD LIGHTCYAN;

		static WORD LIGHTRED;

		static WORD LIGHTPURPLE;

		static WORD YELLOW;

		static WORD ORANGE;
		/// <summary>
		/// BackGround Colors
		/// </summary>
		static WORD WhiteBack;

		static WORD BLACKBack;

		static WORD GREYBack;

		static WORD LIGHTGRAYBack;

		static WORD BLUEBack;

		static WORD GREENBack;

		static WORD CYANBack;

		static WORD REDBack;

		static WORD PURPLEBack;

		static WORD LIGHTBLUEBack;

		static WORD LIGHTGREENBack;

		static WORD LIGHTCYANBack;

		static WORD LIGHTREDBack;

		static WORD LIGHTPURPLEBack;

		static WORD YELLOWBack;

		static WORD ORANGEBack;
	};

	struct console_graphics_utility
	{		
		void SetCursorPosition(const Vector<ushort> &vector);

		Vector<ushort> GetCursorPosition() const;
		
		void Print(char c, WORD foreGround = console_graphics::Colors::White);

		void Print(std::string s, WORD foreGround = console_graphics::Colors::White);
		
		void PrintAtCenter(std::string s, WORD foreGround = console_graphics::Colors::White, ushort offset = 0);

		void Print(std::string s, Vector<ushort> position, WORD foreGround = console_graphics::Colors::White);

		void Print(char c, Vector<ushort> position, WORD foreGround = console_graphics::Colors::White);

		const ushort& GetConsoleWidth() const;

		const ushort& GetConsoleHeight() const;

		static console_graphics_utility* Init(const HANDLE &consoleHandle, 
			WORD defColor = console_graphics::Colors::White);
		
	private:

		static bool init;

		console_graphics_utility(const HANDLE& consoleHandle, WORD defColor);

		HANDLE m_consoleHandle;

		Vector<ushort> m_position;

		ushort m_width;

		ushort m_height;

		WORD m_defColor;
	};	
}

namespace console_funcs
{
	template<class Tout, class TWrite>
	Tout Input(std::function<bool(TWrite&)> inputValidator,
		bool enterRequire, std::function<Tout(TWrite&)> converter = nullptr,
		const std::string& msg = "")
	{
		TWrite input;

		do
		{
			if (!msg.empty())
				std::cout << msg << std::endl;
			if (enterRequire)
			{
				std::cin >> input;
			}
			else
			{
				input = _getch();
			}			

		} while (!inputValidator(input));

		if (converter!= nullptr)
		{
			return converter(input);
		}

		return input;
	}

	
}

#endif // CONSOLE_GRAPHICS_H

