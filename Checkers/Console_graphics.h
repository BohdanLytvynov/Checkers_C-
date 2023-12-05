#ifndef CONSOLE_GRAPHICS_H

#define CONSOLE_GRAPHICS_H

#include"v_math.h"

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
		void SetCursorPosition(const vector<ushort> &vector);

		vector<ushort> GetCursorPosition() const;
		
		void Print(char c, WORD foreGround = console_graphics::Colors::White);

		void Print(std::string s, WORD foreGround = console_graphics::Colors::White);
		
		void PrintAtCenter(std::string s, WORD foreGround = console_graphics::Colors::White, ushort offset = 0);

		static console_graphics_utility* Init(const HANDLE &consoleHandle, 
			WORD defColor = console_graphics::Colors::White);
		
	private:

		static bool init;

		console_graphics_utility(const HANDLE& consoleHandle, WORD defColor);

		HANDLE m_consoleHandle;

		vector<ushort> m_position;

		ushort m_width;

		ushort m_height;

		WORD m_defColor;
	};	
}

#endif // CONSOLE_GRAPHICS_H

