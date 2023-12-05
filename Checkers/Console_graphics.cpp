#include"pch.h"
#include"Console_graphics.h"

#pragma region Colors definitions

WORD console_graphics::Colors::White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |

FOREGROUND_INTENSITY;

WORD console_graphics::Colors::BLACK = 0;

WORD console_graphics::Colors::GREY = FOREGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

WORD console_graphics::Colors::BLUE = FOREGROUND_BLUE;

WORD console_graphics::Colors::GREEN = FOREGROUND_GREEN;

WORD console_graphics::Colors::CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE;

WORD console_graphics::Colors::RED = FOREGROUND_RED;

WORD console_graphics::Colors::PURPLE = FOREGROUND_RED | FOREGROUND_BLUE;

WORD console_graphics::Colors::LIGHTBLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTGREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTRED = FOREGROUND_RED | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTPURPLE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

WORD console_graphics::Colors::ORANGE = FOREGROUND_RED | FOREGROUND_GREEN;

/// <summary>
/// Background colors
/// </summary>

WORD console_graphics::Colors::WhiteBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |

BACKGROUND_INTENSITY;

WORD console_graphics::Colors::BLACKBack = 0;

WORD console_graphics::Colors::GREYBack = BACKGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTGRAYBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

WORD console_graphics::Colors::BLUEBack = BACKGROUND_BLUE;

WORD console_graphics::Colors::GREENBack = BACKGROUND_GREEN;

WORD console_graphics::Colors::CYANBack = BACKGROUND_GREEN | BACKGROUND_BLUE;

WORD console_graphics::Colors::REDBack = BACKGROUND_RED;

WORD console_graphics::Colors::PURPLEBack = BACKGROUND_RED | BACKGROUND_BLUE;

WORD console_graphics::Colors::LIGHTBLUEBack = BACKGROUND_BLUE | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTGREENBack = BACKGROUND_GREEN | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTCYANBack = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTREDBack = BACKGROUND_RED | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::LIGHTPURPLEBack = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::YELLOWBack = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

WORD console_graphics::Colors::ORANGEBack = BACKGROUND_RED | BACKGROUND_GREEN;

#pragma endregion

#pragma region console_graphcs_utility definition

#pragma region Private Ctor

console_graphics::console_graphics_utility::console_graphics_utility(const HANDLE& consoleHandle, WORD defColor)
	:m_position(), m_consoleHandle(consoleHandle), m_defColor(defColor)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleBuf;

	if (GetConsoleScreenBufferInfo(m_consoleHandle, &consoleBuf))
	{
		m_height = consoleBuf.srWindow.Bottom - consoleBuf.srWindow.Top + 1;

		m_width = consoleBuf.srWindow.Right - consoleBuf.srWindow.Left + 1;
	}
}

#pragma endregion

#pragma region Functions

console_graphics::console_graphics_utility* 
console_graphics::console_graphics_utility::Init(const HANDLE& consoleHandle, WORD defColor)
{
	if (!init)
	{
		static console_graphics_utility cgu(consoleHandle, defColor);

		init = true;

		return &cgu;
	}
}

void console_graphics::console_graphics_utility::SetCursorPosition(const vector<ushort> &v)
{
	m_position = v;

	SetConsoleCursorPosition(m_consoleHandle, {(short)m_position[0], (short)m_position[1]});
}

vector_math::vector<ushort> console_graphics::console_graphics_utility::GetCursorPosition() const
{
	return m_position;
}

void console_graphics::console_graphics_utility::Print(char c, WORD foreGround)
{
	if (m_defColor == foreGround)	
		std::cout << c << std::endl;
	else
	{
		SetConsoleTextAttribute(m_consoleHandle, foreGround);

		std::cout << c << std::endl;

		SetConsoleTextAttribute(m_consoleHandle, m_defColor);
	}	
}

void console_graphics::console_graphics_utility::Print(std::string s, WORD foreGround)
{
	if (m_defColor == foreGround)
		std::cout << s << std::endl;
	else
	{
		SetConsoleTextAttribute(m_consoleHandle, foreGround);

		std::cout << s << std::endl;

		SetConsoleTextAttribute(m_consoleHandle, m_defColor);
	}
}

void console_graphics::console_graphics_utility::PrintAtCenter(std::string s, WORD foreGround, ushort yoffset)
{
	SetCursorPosition(vector<ushort>(m_width / 2 - s.size() / 2, yoffset));

	if (m_defColor == foreGround)
		std::cout << s << std::endl;
	else
	{
		SetConsoleTextAttribute(m_consoleHandle, foreGround);

		std::cout << s << std::endl;

		SetConsoleTextAttribute(m_consoleHandle, m_defColor);
	}
}

#pragma endregion

#pragma region Static definitions

bool console_graphics::console_graphics_utility::init = false;

#pragma endregion


#pragma endregion



