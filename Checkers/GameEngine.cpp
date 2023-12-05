#include"pch.h"
#include"GameEngine.h"

#pragma region GameObject definitions

#pragma region Ctors

//char[5] {186, 201, 205, 187, 188}, 5

game_engine_core::GameObject::GameObject(const ushort& width, const ushort& height, 
	const WORD& backGround,
	const WORD& borderColor,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	m_width(width), m_height(height), m_backGround(backGround), m_border(borderColor),
	m_position(position),
	m_selected(false)
{
	if (charsToDraw == nullptr && charsToDrawSize == 0)
	{
		m_charsToDrawSize = 6;

		m_chars = new char[m_charsToDrawSize];

		m_chars[0] = (char)201; //left upper corner symbol
		m_chars[1] = (char)187; //right upper corner symbol
		m_chars[2] = (char)188; //right lower corner symbol
		m_chars[3] = (char)200; //left lower corner symbol
		m_chars[4] = (char)205; //horizontal line symbol
		m_chars[5] = (char)186; //vertical line symbol		
	}
	else
	{
		m_chars = charsToDraw;

		m_charsToDrawSize = charsToDrawSize;
	}
}

game_engine_core::GameObject::~GameObject() 
{
	delete[] m_chars;
}



#pragma endregion

#pragma region Getters

const char* game_engine_core::GameObject::GetChars() const
{
	return m_chars;
}

ushort game_engine_core::GameObject::GetWidth() const
{
	return m_width;
}

ushort game_engine_core::GameObject::GetHeight() const
{
	return m_height;
}

ushort game_engine_core::GameObject::GetBackColor() const
{
	return m_backGround;
}

ushort game_engine_core::GameObject::GetBorderColor() const
{
	return m_border;
}

vector_math::vector<ushort> game_engine_core::GameObject::GetPosition() const
{
	return m_position;
}

bool game_engine_core::GameObject::isSelected() const { return m_selected; }

#pragma endregion

#pragma region Setters

void game_engine_core::GameObject::SetWidth(ushort width)
{
	m_width = width;
}

void game_engine_core::GameObject::SetHeight(ushort height)
{
	m_height = height;
}

void game_engine_core::GameObject::SetBackColor(const WORD& backColor)
{
	m_backGround = backColor;
}

void game_engine_core::GameObject::SetBorderColor(const WORD& borderColor)
{
	m_border = borderColor;
}

void game_engine_core::GameObject::SetPosition(const vector<ushort> &v)
{
	m_position = v;
}



void game_engine_core::GameObject::Select()
{
	m_selected = true;
}

void game_engine_core::GameObject::Deselct()
{
	m_selected = false;
}

#pragma endregion


#pragma endregion

#pragma region Killable definitions

#pragma region Ctor

game_engine_core::Killable::Killable(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& border,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	GameObject(width, height, backGround, border, position, charsToDraw, charsToDrawSize)
{

}

#pragma endregion

#pragma region Getters
bool game_engine_core::Killable::isAlive() const { return m_alive; }


#pragma endregion

#pragma region Setters

void game_engine_core::Killable::Kill()
{
	m_alive = false;
}

#pragma endregion


#pragma endregion

#pragma region Cell Definition

#pragma region Ctor
game_engine_core::Cell::Cell(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& border,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize)
	: GameObject(width, height, backGround, border, position, charsToDraw, charsToDrawSize)
{
	
}
#pragma endregion

#pragma region Functions

void game_engine_core::Cell::Render(console_graphics_utility& utility)
{
	auto pos = this->GetPosition();

	auto backGroundColor = this->GetBackColor();

	auto borderColor = this->GetBorderColor();

	ushort width = this->GetWidth();

	ushort height = this->GetHeight();
	
	char selectedSymbol;

	WORD color;

	const char* symbols = this->GetChars();

	bool dec_symbol = false;

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			dec_symbol = false;

			utility.SetCursorPosition(pos + vector<ushort>(j, i));

			color = borderColor;

			//Corner Symbol Switcher
			if (i == 0 && j == 0)//Left upper corner
			{
				selectedSymbol = *symbols;	
				dec_symbol = true;
			}
			else if(i == 0 && j == width - 1)//Right upper corner
			{
				selectedSymbol = *(symbols + 1);
				dec_symbol = true;
			}
			else if (i == height - 1 && j == 0)//Left lower corner
			{
				selectedSymbol = *(symbols + 3);
				dec_symbol = true;
			}
			else if (i == height - 1 && j == width - 1)//Right lower corner
			{
				selectedSymbol = *(symbols + 2);
				dec_symbol = true;
			}

			//Line Symblo Switcher

			if (i == 0 && j < width - 1 && j > 0)//Upper horizontal Line
			{
				selectedSymbol = *(symbols + 4);
				dec_symbol = true;
			}
			else if (j == width - 1 && i > 0 && i < height - 1)//right Vertical Line
			{
				selectedSymbol = *(symbols + 5);
				dec_symbol = true;
			}
			else if (i == height - 1 && j > 0 && j < width - 1)//Lower horizontal Line
			{
				selectedSymbol = *(symbols + 4);
				dec_symbol = true;
			}
			else if (j == 0 && i > 0 && i < height - 1)//Left Vertical Line
			{
				selectedSymbol = *(symbols + 5);
				dec_symbol = true;
			}
			if(!dec_symbol) //Filler
			{
				selectedSymbol = ' ';
				color = backGroundColor;
			}

			utility.Print(selectedSymbol, color);

 		}
	}
}

#pragma endregion



#pragma endregion

#pragma region Checker Definition

#pragma endregion



