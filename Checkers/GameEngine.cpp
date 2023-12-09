#include"pch.h"
#include"GameEngine.h"

#pragma region GameObject definitions

#pragma region Ctors

//char[5] {186, 201, 205, 187, 188}, 5

game_engine_core::GameObject::GameObject(): GameObject(0,0, console_graphics::Colors::WhiteBack,	
	vector_math::vector<ushort>(0,0), nullptr, 0)
{

}

game_engine_core::GameObject::GameObject(const ushort& width, const ushort& height,
	const WORD& backGround,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	m_width(width), m_height(height), m_backGround(backGround),
	m_position(position),
	m_selected(false), m_chars(charsToDraw), m_charsToDrawSize(charsToDrawSize)
{
	
}

game_engine_core::GameObject::GameObject(const GameObject& other)
{
	m_width = other.m_width;
	m_height = other.m_height;	
	m_backGround = other.m_backGround;
	m_selected = other.m_selected;
	m_position = other.m_position;
	m_charsToDrawSize = other.m_charsToDrawSize;

	if (m_chars != nullptr)
	{
		delete[] m_chars;
	}

	m_chars = new char[m_charsToDrawSize];

	for (size_t i = 0; i < m_charsToDrawSize; i++)
	{
		*(m_chars + i) = *(other.m_chars + i);
	}
}

game_engine_core::GameObject::~GameObject() 
{
	delete[] m_chars;
}



#pragma endregion

#pragma region Getters

size_t game_engine_core::GameObject::GetCharsToDrawSize() const
{
	return m_charsToDrawSize;
}

char* game_engine_core::GameObject::GetChars() const
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

WORD game_engine_core::GameObject::GetBackColor() const
{
	return m_backGround;
}

vector_math::vector<ushort> game_engine_core::GameObject::GetPosition() const
{
	return m_position;
}

bool game_engine_core::GameObject::isSelected() const { return m_selected; }

#pragma endregion

#pragma region Setters

void game_engine_core::GameObject::SetChars(char* chars)
{
	m_chars = chars;
}

void game_engine_core::GameObject::SetCharsToDrawSize(size_t size)
{
	m_charsToDrawSize = size;
}

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

#pragma region Operators

game_engine_core::GameObject& game_engine_core::GameObject::operator=(const GameObject& other)
{
	m_width = other.m_width;

	m_height = other.m_height;

	m_backGround = other.m_backGround;
	
	m_position = other.m_position;

	m_charsToDrawSize = other.m_charsToDrawSize;

	if (m_chars != nullptr)
	{
		delete[] m_chars;
	}

	m_chars = new char[m_charsToDrawSize];

	for (size_t i = 0; i < m_charsToDrawSize; i++)
	{
		*(m_chars + i) = *(other.m_chars + i);
	}

	return *this;	
}

#pragma endregion


#pragma endregion

#pragma region Killable definitions

#pragma region Ctor

game_engine_core::Killable::Killable() : GameObject(), m_alive(true) {}

game_engine_core::Killable::Killable(const ushort& width, const ushort& height, const WORD& backGround,	
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	GameObject(width, height, backGround, position, charsToDraw, charsToDrawSize),
	m_alive(true)
{

}

game_engine_core::Killable::Killable(const Killable &other) : GameObject(other)
{
	m_alive = other.m_alive;
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

#pragma region Functions

game_engine_core::Killable& game_engine_core::Killable::operator=(const Killable& other)
{
	this->GameObject::operator=(other);

	this->m_alive = other.m_alive;

	return *this;
}

#pragma endregion


#pragma endregion

#pragma region Cell Definition

#pragma region Ctor

game_engine_core::Cell::Cell() : GameObject(), m_isWhite(false), 
m_borderColor(console_graphics::Colors::LIGHTGRAYBack | console_graphics::Colors::BLACK) {}

game_engine_core::Cell::Cell(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& borderColor,
	vector<ushort> position, bool isWhite, char* charsToDraw, size_t charsToDrawSize)
	: GameObject(width, height, backGround, position, charsToDraw, charsToDrawSize),
	m_isWhite(isWhite), m_borderColor(borderColor)
{
	char* ptr = nullptr;

	if (charsToDraw == nullptr && charsToDrawSize == 0)
	{
		this->SetCharsToDrawSize(6);		
		ptr = new char[this->GetCharsToDrawSize()];

		ptr[0] = (char)201; //left upper corner symbol
		ptr[1] = (char)187; //right upper corner symbol
		ptr[2] = (char)188; //right lower corner symbol
		ptr[3] = (char)200; //left lower corner symbol
		ptr[4] = (char)205; //horizontal line symbol
		ptr[5] = (char)186; //vertical line symbol		
	}
	else
	{
		ptr = charsToDraw;

		this->SetCharsToDrawSize(charsToDrawSize);
	}

	this->SetChars(ptr);
}

game_engine_core::Cell::Cell(const Cell& other) :
	GameObject(other), m_isWhite(other.m_isWhite), m_borderColor(other.m_borderColor) {}

#pragma endregion

#pragma region Operators

game_engine_core::Cell& game_engine_core::Cell::operator=(const Cell& other)
{
	this->GameObject::operator=(other);

	m_isWhite = other.m_isWhite;

	m_borderColor = other.m_borderColor;

	return *this;
}

#pragma endregion

#pragma region Functions

WORD game_engine_core::Cell::GetBorderColor() const
{
	return m_borderColor;
}

void game_engine_core::Cell::SetBorderColor(const WORD& borderColor)
{
	m_borderColor = borderColor;
}

bool game_engine_core::Cell::IsWhite() const
{
	return m_isWhite;
}

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

#pragma region Ctor

game_engine_core::Checker::Checker() : Killable(), m_HorbaseLength(2), m_VertBaseLength(2),
m_isDamka(false), m_isWhite(false) {}

game_engine_core::Checker::Checker(const ushort& width, const ushort& height, const WORD& backGround,	
	vector<ushort> position, bool isWhite, ushort HorbaseLength, ushort VertbaseLength, char* charsToDraw, size_t charsToDrawSize)
	: Killable(width, height, backGround, position, charsToDraw, charsToDrawSize),
	m_HorbaseLength(HorbaseLength), m_VertBaseLength(VertbaseLength), m_isDamka(false),
	m_isWhite(isWhite)
{
	char* ptr = nullptr;

	if (charsToDraw == nullptr && charsToDrawSize == 0)
	{
		this->SetCharsToDrawSize(2);
		ptr = new char[this->GetCharsToDrawSize()];

		ptr[0] = '*'; //Checker filler
		ptr[1] = ' '; //Damka empty filler
	}
	else
	{
		ptr = charsToDraw;

		this->SetCharsToDrawSize(charsToDrawSize);
	}

	this->SetChars(ptr);
}

game_engine_core::Checker::Checker(const Checker& other) : Killable(other)
{
	m_HorbaseLength = other.m_HorbaseLength;

	m_VertBaseLength = other.m_VertBaseLength;

	m_isDamka = other.m_isDamka;

	m_isWhite = other.m_isWhite;
}

#pragma endregion

#pragma region Operators

game_engine_core::Checker& game_engine_core::Checker::operator=(const Checker& other)
{
	this->Killable::operator=(other);

	m_HorbaseLength = other.m_HorbaseLength;

	m_VertBaseLength = other.m_VertBaseLength;

	m_isDamka = other.m_isDamka;

	m_isWhite = other.m_isWhite;

	return *this;
}

#pragma endregion


#pragma region Functions

void game_engine_core::Checker::MakeDamka()
{
	m_isDamka = true;
}

bool game_engine_core::Checker::IsCheckerWhite() const
{
	return m_isWhite;
}

void game_engine_core::Checker::Render(console_graphics::console_graphics_utility& utility)
{
	if (!this->isAlive())
		return;

	auto pos = this->GetPosition();

	auto width = this->GetWidth();

	auto height = this->GetHeight();

	auto back = this->GetBackColor();
					
	//1) Calc 2 hor and vert midle elements

	size_t Hormid1 = width / 2;

	size_t Hormid2 = Hormid1 + m_HorbaseLength - 1;

	size_t Vertmid1 = height / 2;

	size_t Vertmid2 = Vertmid1 + m_VertBaseLength - 1;
	
	bool shouldPrint = false;

	ushort last1;

	ushort last2;

	ushort tempi = 0;

	for (size_t i = 1; i < height - 1; i++)
	{
		for (size_t j = 1; j < width - 1; j++)
		{
			utility.SetCursorPosition(pos + vector<ushort> (j, i));

			if (i < Vertmid1 && j >= (Hormid1 - i - 1) && j <= (Hormid2 + i - 1) )
			{
				last1 = Hormid1 - i - 1;

				last2 = Hormid2 + i - 1;

				if (!m_isDamka)//Ordinary Checker
				{
					utility.Print(*this->GetChars(), back);
				}
				else  //Checker is Damka
				{
					if (i >= (Vertmid1 - 1) && (j > last1  && j  < last2 ))
					{
						utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
					}
					else
					{
						utility.Print(*(this->GetChars()), back);
					}
				}
												
				tempi = i;
			}
			if (i >= Vertmid1 && i < Vertmid2 && j >= last1 && j <= last2)
			{					
				if (!m_isDamka)
				{
					utility.Print(*this->GetChars(), back);
				}
				else if (j > last1 && j < last2)
				{
					utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
				}
				else
				{
					utility.Print(*(this->GetChars()), back);
				}
												
			}
			else if (i >= Vertmid2 && j >= (last1 + tempi - 1) && j <= (last2 - tempi + 1))
			{
				utility.Print(*this->GetChars(), back);
			}										
		}
	}
}

#pragma endregion


#pragma endregion

#pragma region GameController definitions

#pragma region Ctor

game_engine_core::GameController::GameController(console_graphics_utility* utility,
	vector<ushort> boardPosition, CellBuildingOptions* cellbuildingOptions,
	CheckerBuildingOptions* checkerBuildingOptions)
{
	m_position = boardPosition;

	m_cellBuildingOptions = cellbuildingOptions;

	m_checkerBuildingOpions = checkerBuildingOptions;

	m_console_graphics_utility = utility;
	//Initialization of the Board
	m_board = new Cell* [8];
		
	bool whiteBlack = true;
	
	auto Cellwidth = m_cellBuildingOptions->GetCellWidth();

	auto Cellheight = m_cellBuildingOptions->GetCellHeight();

	///Checkers initialization

	m_checkers = new Checker[m_checkersCount];

	size_t mid = m_checkersCount / 2;

	auto CheckerWidth = m_checkerBuildingOpions->GetCheckerWidth();

	auto CheckerHeight = m_checkerBuildingOpions->GetCheckerHeight();

	WORD CheckerBlackColor = m_checkerBuildingOpions->GetBlackCheckerColor();

	WORD CheckerWhiteColor = m_checkerBuildingOpions->GetWhiteCheckerColor();

	vector<ushort> positionTemp;

	size_t k = 0;//Variable to use in checkers array

	for (size_t i = 0; i < 8; i++)
	{
		m_board[i] = new Cell[8];
	
		for (size_t j = 0; j < 8; j++)
		{		
			positionTemp = m_position + vector<ushort>(j * Cellwidth, i * Cellheight);

			*(m_board[i] + j) = Cell( Cellwidth, Cellheight, 				
				whiteBlack == true? console_graphics::Colors::WhiteBack : console_graphics::Colors::BLACKBack,
				console_graphics::Colors::BLACK | console_graphics::Colors::LIGHTGRAYBack,
				positionTemp, whiteBlack);

			if (!m_board[i][j].IsWhite())
			{
				if (i >= 0 && i <= 2)//Place Black Checkers
				{
					*(m_checkers + k) = Checker(CheckerWidth, CheckerHeight,
						CheckerBlackColor, positionTemp, false);

					k++;
				}
				else if(i >= (8 - 3))//Place white checkers 
				{
					*(m_checkers + k) = Checker(CheckerWidth, CheckerHeight,
						CheckerWhiteColor, positionTemp, true);

					k++;
				}				
			}
						
			if(j != 8 -1)
				whiteBlack = !whiteBlack;			
		}		
	}

	//Initialization of the Checkers		
}

game_engine_core::GameController::~GameController()
{
	for (size_t i = 0; i < 8; i++)
	{
		delete[] m_board[i];
	}

	delete m_checkers;
}

#pragma endregion

#pragma region Functions

void game_engine_core::GameController::InitGame()
{
	this->DrawBoard();

	this->DrawCheckers();
}



void game_engine_core::GameController::DrawBoard()
{
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			(m_board[i] + j)->Render(*m_console_graphics_utility);
		}
	}
}

void game_engine_core::GameController::DrawCheckers()
{
	size_t checkersCount = this->m_checkersCount;

	for (size_t i = 0; i < checkersCount; i++)
	{
		(m_checkers + i)->Render(*m_console_graphics_utility);
	}
}

game_engine_core::GameController* game_engine_core::GameController::Initialize(console_graphics_utility* utility,
	vector<ushort> controllerPosiion, CellBuildingOptions* cellbuildingOptions,
	CheckerBuildingOptions* checkerBuildingOptions)
{
	if (!m_init)
	{		
		static GameController gc(utility, controllerPosiion, cellbuildingOptions, 
			checkerBuildingOptions);

		m_init = true;

		return &gc;
	}
}

#pragma endregion

#pragma region Static definitions

bool game_engine_core::GameController::m_init = false;

#pragma endregion


#pragma endregion

#pragma region CellBuildingOptions

#pragma region Ctor

game_engine_core::CellBuildingOptions::CellBuildingOptions(
	WORD BlackColor,
	WORD WhiteColor, WORD borderColor, ushort width, ushort height) :
	m_cellWidth(width), m_cellHeight(height), m_blackColor(BlackColor), m_whiteColor(WhiteColor),
	m_borderColor(borderColor)
{}

game_engine_core::CellBuildingOptions::CellBuildingOptions(ushort width, ushort height) :
	CellBuildingOptions(console_graphics::Colors::BLACKBack,
		console_graphics::Colors::WhiteBack, console_graphics::Colors::BLACK |
		console_graphics::Colors::LIGHTGRAY,
		width, height) {}

#pragma endregion

WORD game_engine_core::CellBuildingOptions::GetBorderColor() const
{
	return m_borderColor;
}

void game_engine_core::CellBuildingOptions::SetBorderColor(const WORD& borderColor)
{
	m_borderColor = borderColor;
}

const WORD& game_engine_core::CellBuildingOptions::GetBlackColor() const
{
	return m_blackColor;
}

const WORD& game_engine_core::CellBuildingOptions::GetWhiteColor() const
{
	return m_whiteColor;
}

const ushort& game_engine_core::CellBuildingOptions::GetCellWidth() const
{
	return m_cellWidth;
}

const ushort& game_engine_core::CellBuildingOptions::GetCellHeight() const
{
	return m_cellHeight;
}

#pragma endregion

#pragma region CheckerBuildingOptions

#pragma region Ctor

game_engine_core::CheckerBuildingOptions::CheckerBuildingOptions() :
	CheckerBuildingOptions(console_graphics::Colors::WhiteBack,
		console_graphics::Colors::BLACKBack)
{}
game_engine_core::CheckerBuildingOptions::CheckerBuildingOptions(WORD whiteCheckerColor, 
	WORD blackCheckerColor, 
	ushort width, ushort height):	
	m_blackCheckerColor(blackCheckerColor),
	m_whiteCheckerColor(whiteCheckerColor),
	m_CheckerWidth(width), m_CheckerHeight(height)	
{}
#pragma endregion

#pragma region Getters

const ushort& game_engine_core::CheckerBuildingOptions::GetCheckerWidth() const
{
	return m_CheckerWidth;
}

const ushort& game_engine_core::CheckerBuildingOptions::GetCheckerHeight() const
{
	return m_CheckerHeight;
}

const WORD& game_engine_core::CheckerBuildingOptions::GetBlackCheckerColor() const
{
	return m_blackCheckerColor;
}

const WORD& game_engine_core::CheckerBuildingOptions::GetWhiteCheckerColor() const
{
	return m_whiteCheckerColor;
}

#pragma endregion


#pragma endregion




