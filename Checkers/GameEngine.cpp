#include"pch.h"
#include"GameEngine.h"

#pragma region GameObject definitions

#pragma region Ctors

//char[5] {186, 201, 205, 187, 188}, 5

game_engine_core::GameObject::GameObject() : GameObject(0, 0, console_graphics::Colors::WhiteBack,
	console_graphics::Colors::ORANGEBack,
	vector_math::vector<ushort>(0, 0), nullptr, 0)
{

}

game_engine_core::GameObject::GameObject(const ushort& width, const ushort& height,
	const WORD& backGround,
	const WORD& selColor,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	m_width(width), m_height(height), m_backGround(backGround),
	m_position(position),
	m_selected(false), m_chars(charsToDraw), m_charsToDrawSize(charsToDrawSize),
	m_selectionColor(selColor)
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
	m_selectionColor = other.m_selectionColor;

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

WORD game_engine_core::GameObject::GetSelectionColor() const
{
	return m_selectionColor;
}

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

void game_engine_core::GameObject::SetPosition(const vector<ushort>& v)
{
	m_position = v;
}

void game_engine_core::GameObject::SetSelectionColor(WORD selColor)
{
	m_selectionColor = selColor;
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

	m_selectionColor = other.m_selectionColor;

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
	const WORD& selColor,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	GameObject(width, height, backGround, selColor, position, charsToDraw, charsToDrawSize),
	m_alive(true)
{

}

game_engine_core::Killable::Killable(const Killable& other) : GameObject(other)
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
m_borderColor(console_graphics::Colors::LIGHTGRAYBack | console_graphics::Colors::BLACK),
m_BorderHighlightColor(console_graphics::Colors::GREENBack), m_borderHighLight(false) {}

game_engine_core::Cell::Cell(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& borderColor, const WORD& selColor, const WORD& borderHighlightColor,
	vector<ushort> position, bool isWhite, char* charsToDraw, size_t charsToDrawSize)
	: GameObject(width, height, backGround, selColor, position, charsToDraw, charsToDrawSize),
	m_isWhite(isWhite), m_borderColor(borderColor), m_BorderHighlightColor(borderHighlightColor),
	m_borderHighLight(false)
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
	GameObject(other), m_isWhite(other.m_isWhite), m_borderColor(other.m_borderColor),
	m_BorderHighlightColor(other.m_BorderHighlightColor), m_borderHighLight(other.m_borderHighLight) {}

#pragma endregion

#pragma region Operators

game_engine_core::Cell& game_engine_core::Cell::operator=(const Cell& other)
{
	this->GameObject::operator=(other);

	m_isWhite = other.m_isWhite;

	m_borderColor = other.m_borderColor;

	m_BorderHighlightColor = other.m_BorderHighlightColor;

	m_borderHighLight = other.m_borderHighLight;

	return *this;
}

#pragma endregion

#pragma region Functions

const WORD& game_engine_core::Cell::GetBorderSelectionColor() const
{
	return m_BorderHighlightColor;
}

void game_engine_core::Cell::SetBorderSelectionColor(const WORD& borderHighlightColor)
{
	m_BorderHighlightColor = borderHighlightColor;
}

void game_engine_core::Cell::HighlightBorder()
{
	m_borderHighLight = true;
}

void game_engine_core::Cell::UnHighLightBorder()
{
	m_borderHighLight = false;
}

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

	bool selected = this->isSelected();

	auto sel_Color = this->GetSelectionColor();

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			dec_symbol = false;

			utility.SetCursorPosition(pos + vector<ushort>(j, i));

			color = m_borderHighLight ? m_BorderHighlightColor : borderColor;

			//Corner Symbol Switcher
			if (i == 0 && j == 0)//Left upper corner
			{
				selectedSymbol = *symbols;
				dec_symbol = true;
			}
			else if (i == 0 && j == width - 1)//Right upper corner
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
			if (!dec_symbol) //Filler
			{
				selectedSymbol = ' ';
				color = selected ? sel_Color : backGroundColor;
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
	const WORD& selColor,
	vector<ushort> position, bool isWhite, ushort HorbaseLength, ushort VertbaseLength, char* charsToDraw, size_t charsToDrawSize)
	: Killable(width, height, backGround, selColor, position, charsToDraw, charsToDrawSize),
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
bool game_engine_core::Checker::IsDamka() const
{
	return m_isDamka;
}

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
	/*if (!this->isAlive())
		return;*/

	auto pos = this->GetPosition();

	auto width = this->GetWidth();

	auto height = this->GetHeight();

	auto back = this->GetBackColor();

	auto selColor = this->GetSelectionColor();

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
			utility.SetCursorPosition(pos + vector<ushort>(j, i));

			if (i < Vertmid1 && j >= (Hormid1 - i - 1) && j <= (Hormid2 + i - 1))
			{
				last1 = Hormid1 - i - 1;

				last2 = Hormid2 + i - 1;

				if (!m_isDamka)//Ordinary Checker
				{
					utility.Print(*this->GetChars(), this->isSelected() ? selColor : back);
				}
				else  //Checker is Damka
				{
					if (i >= (Vertmid1 - 1) && (j > last1 && j < last2))
					{
						utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
					}
					else
					{
						utility.Print(*(this->GetChars()), this->isSelected() ? selColor : back);
					}
				}

				tempi = i;
			}
			if (i >= Vertmid1 && i < Vertmid2 && j >= last1 && j <= last2)
			{
				if (!m_isDamka)
				{
					utility.Print(*this->GetChars(), this->isSelected() ? selColor : back);
				}
				else if (j > last1 && j < last2)
				{
					utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
				}
				else
				{
					utility.Print(*(this->GetChars()), this->isSelected() ? selColor : back);
				}

			}
			else if (i >= Vertmid2 && j >= (last1 + tempi - 1) && j <= (last2 - tempi + 1))
			{
				utility.Print(*this->GetChars(), this->isSelected() ? selColor : back);
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
	m_controls = new char[5];

	m_controls[0] = 'a';//Move selection left

	m_controls[1] = 'd';//Move selection right

	m_controls[2] = 's';//Perform selection

	m_controls[3] = 'c';//Confirm selection

	m_controls[4] = 'r';//Abort

	m_Board_position = boardPosition;

	m_cellBuildingOptions = cellbuildingOptions;

	m_checkerBuildingOpions = checkerBuildingOptions;

	m_console_graphics_utility = utility;
	//Initialization of the Board
	m_board = new Cell * [8];

	bool whiteBlack = true;

	auto Cellwidth = m_cellBuildingOptions->GetCellWidth();

	auto Cellheight = m_cellBuildingOptions->GetCellHeight();

	auto CellWhiteColor = m_cellBuildingOptions->GetWhiteColor();

	auto CellBlackColor = m_cellBuildingOptions->GetBlackColor();

	auto CellBorderHighlightColor = m_cellBuildingOptions->GetBorderHighlightColor();

	auto CellBorderColor = m_cellBuildingOptions->GetBorderColor();

	auto selColor = m_cellBuildingOptions->GetSelectionColor();

	///Checkers initialization

	m_checkers = new Checker[m_checkersCount];

	size_t mid = m_checkersCount / 2;

	auto CheckerWidth = m_checkerBuildingOpions->GetCheckerWidth();

	auto CheckerHeight = m_checkerBuildingOpions->GetCheckerHeight();

	WORD CheckerBlackColor = m_checkerBuildingOpions->GetBlackCheckerColor();

	WORD CheckerWhiteColor = m_checkerBuildingOpions->GetWhiteCheckerColor();

	vector<ushort> positionTemp;

	auto CheckerSelColor = m_checkerBuildingOpions->GetSelectionColor();

	size_t k = 0;//Variable to use in checkers array

	for (size_t i = 0; i < 8; i++)
	{
		m_board[i] = new Cell[8];

		for (size_t j = 0; j < 8; j++)
		{
			positionTemp = m_Board_position + vector<ushort>(j * Cellwidth, i * Cellheight);

			*(m_board[i] + j) = Cell(Cellwidth, Cellheight,
				whiteBlack == true ? CellWhiteColor : CellBlackColor,
				CellBorderColor,
				selColor, CellBorderHighlightColor,
				positionTemp, whiteBlack);

			if (!m_board[i][j].IsWhite())
			{
				if (i >= 0 && i <= 2)//Place Black Checkers
				{
					*(m_checkers + k) = Checker(CheckerWidth, CheckerHeight,
						CheckerBlackColor, CheckerSelColor, positionTemp, false);

					k++;
				}
				else if (i >= (8 - 3))//Place white checkers 
				{
					*(m_checkers + k) = Checker(CheckerWidth, CheckerHeight,
						CheckerWhiteColor, CheckerSelColor, positionTemp, true);

					k++;
				}
			}

			if (j != 8 - 1)
				whiteBlack = !whiteBlack;
		}
	}

	//Update dir Vectors magnitudes using a propriate cell size parametrs

	short arr[2] = { Cellwidth, Cellheight };

	for (size_t i = 0; i < 4; i++)
	{
		m_dirVectors[i] = m_dirVectors[i] * arr;
	}

	for (size_t i = 0; i < 2; i++)
	{
		m_boardBasis[i] * arr;
	}

	//Calculate Width and Height Of the Board

	m_boardWidth = 8 * Cellwidth;

	m_boardHeight = 8 * Cellheight;
}

game_engine_core::GameController::~GameController()
{
	for (size_t i = 0; i < 8; i++)
	{
		delete[] m_board[i];
	}

	delete[] m_checkers;

	delete[] m_controls;
}

#pragma endregion

#pragma region Functions

game_engine_core::Cell* game_engine_core::GameController::FindCellUsingPosition(const vector<short>& positionVector)
{
	bool stop = false;

	vector<short> pos;

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			pos = (m_board[i] + j)->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT);

			if (pos == positionVector)
				return (m_board[i] + j);
		}
	}

	return nullptr;
}

game_engine_core::Checker* game_engine_core::GameController::FindCheckerUsingPosition(const vector<short>& positionVector)
{
	vector<short> shortvector;

	for (size_t i = 0; i < m_checkersCount; i++)
	{
		if (m_checkers + i == nullptr)
			break;

		shortvector = (m_checkers + i)->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT);

		if (shortvector == positionVector)
			return (m_checkers + i);

		int a;
	}

	return nullptr;
}

bool game_engine_core::GameController::OutOfBorders(const vector<short>& position)
{
#pragma region Near Border Cases

	if (position["X"] < m_Board_position["X"] && position["Y"] < m_Board_position["Y"])//checker is about to cross Upper left corner
	{
		return true;
	}
	else if (position["X"] < m_Board_position["X"] && position["Y"] >= m_Board_position["Y"] + m_boardHeight)//checker is about to cross Lower left corner
	{
		return true;
	}
	else if (position["X"] > m_Board_position["X"] && position["Y"] < m_Board_position["Y"])//checker is about to cross Upper right corner
	{
		return true;
	}
	else if (position["X"] >= m_Board_position["X"] + m_boardWidth && position["Y"] >= m_Board_position["Y"] + m_boardHeight)//checker is about to cross Lower right corner
	{
		return true;
	}

#pragma endregion

#pragma region Borders of the board

	else if (position["X"] < m_Board_position["X"] && position["Y"] >= m_Board_position["Y"])//Left vertical border
	{
		return true;
	}
	else if (position["X"] >= m_Board_position["X"] && position["Y"] < m_Board_position["Y"])//Upper horizontal border
	{
		return true;
	}
	else if (position["X"] >= m_Board_position["X"] + m_boardWidth && position["Y"] >= m_Board_position["Y"])//Right vertical border
	{
		return true;
	}
	else if (position["X"] > m_Board_position["X"] && position["Y"] >= m_Board_position["Y"] + m_boardHeight)//Lower  Horizontal border
	{
		return true;
	}

#pragma endregion
}

void game_engine_core::GameController::FindPossibleTurnRecursive(
	const vector<short>& position,
	vector<short>& startPosition, const vector<short>& dirVector, bool multiKill)
{
	m_console_graphics_utility->SetCursorPosition(position.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

	//Base cases
	if (position != startPosition)//initial Situation when we are at the same position
	{

		if (OutOfBorders(position))
		{
			return;
		}

		Checker* currentchecker = FindCheckerUsingPosition(position);

		if (currentchecker == nullptr && !multiKill)//Position of the empty cell (No checkers exists at this posVector)
		{
			if (m_selectedChecker->IsCheckerWhite() && ((dirVector * m_boardBasis[1]) < 0))//Move of the white checker
			{
				m_possibleTurns.AddToTheEnd(FindCellUsingPosition(position));//Add Cells To be Highlighted

				return;
			}
			else if (!m_selectedChecker->IsCheckerWhite() && (dirVector * m_boardBasis[1]) > 0)//Move for the black checker
			{
				m_possibleTurns.AddToTheEnd(FindCellUsingPosition(position));//Add Cells To be Highlighted

				return;
			}
			else
			{
				return;
			}
		}
		else if (currentchecker != nullptr)
		{
			if (m_selectedChecker->IsCheckerWhite() != currentchecker->IsCheckerWhite()) //Cell contains checker, also case when checkers can fight
			{
				//Fighting We can attack only if the cell behind the checker is empty
				//and the checker can't be attacked twice

				if (m_checkersToBeKilled.Contains(FindCheckerUsingPosition(position)))
				{
					return;
				}

				vector<short> posBehind = position + dirVector;

				m_console_graphics_utility->SetCursorPosition(posBehind.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

				if (FindCheckerUsingPosition(posBehind) == nullptr)//Enemy checker is open
				{
					if (OutOfBorders(posBehind))
					{
						return;
					}

					m_multipleMoves++;

					m_possibleTurns.AddToTheEnd(FindCellUsingPosition(posBehind));

					m_checkersToBeKilled.AddToTheEnd(FindCheckerUsingPosition(position));
					//Posibility of multiKill

					bool multiKill = true;

					FindPossibleTurnRecursive(posBehind + m_dirVectors[0], posBehind, m_dirVectors[0], multiKill);//Move leftUp
					FindPossibleTurnRecursive(posBehind + m_dirVectors[1], posBehind, m_dirVectors[1], multiKill);//Move rightUp
					FindPossibleTurnRecursive(posBehind + m_dirVectors[2], posBehind, m_dirVectors[2], multiKill);//Move leftDown
					FindPossibleTurnRecursive(posBehind + m_dirVectors[3], posBehind, m_dirVectors[3], multiKill);//Move rightDown

					return;
				}
				else
				{
					return;
				}
			}
			else//Case when the cell contains checker of the same color
			{
				return;
			}
		}
		else
		{
			return;
		}

	}

	FindPossibleTurnRecursive(position + m_dirVectors[0], startPosition, m_dirVectors[0]);//Move leftUp
	FindPossibleTurnRecursive(position + m_dirVectors[1], startPosition, m_dirVectors[1]);//Move rightUp
	FindPossibleTurnRecursive(position + m_dirVectors[2], startPosition, m_dirVectors[2]);//Move leftDown
	FindPossibleTurnRecursive(position + m_dirVectors[3], startPosition, m_dirVectors[3]);//Move rightDown	
}

void game_engine_core::GameController::HighLightPossibleTurns()
{
	m_possibleTurns.Iterate([](Cell* ptr) { ptr->HighlightBorder(); });

	system("CLS");

	Draw();
}

bool game_engine_core::GameController::IsGameOver(bool &winner)
{
	size_t count = m_checkersCount;

	size_t mid = (m_checkersCount / 2) - 1;//11

	size_t whiteAlivedCount = 0;

	size_t BlackAlivedCount = 0;

	for (size_t i = 0; i < count; i++)
	{
		if (i >= 0 && i <= mid && (m_checkers + i)->isAlive())
		{
			BlackAlivedCount++;			
		}
		else if (i > mid && i < count && (m_checkers + i)->isAlive())
		{
			whiteAlivedCount++;
		}			
	}

	if (whiteAlivedCount == 0 && BlackAlivedCount > 0)//White loses
	{
		winner = false;

		return true;
	}
	else if (whiteAlivedCount > 0 && BlackAlivedCount == 0)//Black loses
	{
		winner = true;

		return true;
	}

	return false;
}

void game_engine_core::GameController::DeselectAllGameObjects()
{
	//Deselect

	m_selectedChecker->Deselct();

	m_possibleTurns.Iterate([](Cell* cell) { cell->UnHighLightBorder(); });

	CellBuildingOptions* cboptr = m_cellBuildingOptions;

	m_selectedRouts.Iterate([cboptr](Cell* cell) { cell->SetBackColor(cell->IsWhite() ? cboptr->GetWhiteColor() :
		cboptr->GetBlackColor());

	cell->Deselct();
		});

	/*system("CLS");

	this->Draw();*/
}

void game_engine_core::GameController::Move()
{
	size_t selRoutsCount = m_selectedRouts.GetCount();

	m_selectedChecker->SetPosition(m_selectedRouts[selRoutsCount - 1]->GetPosition());

	//Determine Damka

	if (m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] <= m_Board_position["Y"])//White Checker
	{
		m_selectedChecker->MakeDamka();
	}
	else if(m_selectedChecker->GetPosition()["Y"] >= m_Board_position["Y"] + m_boardHeight - m_cellBuildingOptions->GetCellHeight())
	{
		m_selectedChecker->MakeDamka();
	}

	auto chToBeKilledPtr = &m_checkersToBeKilled;

	const auto& boardPos = m_Board_position;

	const auto& boardWidth = m_boardWidth;

	//Fighting

	//Ordinary fightting

	if (!m_selectedChecker->IsDamka())
	{
		m_selectedRouts.Iterate([chToBeKilledPtr, boardPos, boardWidth](Cell* cell)
			{
				auto Sel_pos = cell->GetPosition();

				chToBeKilledPtr->Iterate([Sel_pos, boardPos, boardWidth](Checker* ch)
					{
						vector<short> v = ch->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT) -
							Sel_pos.Convert_To(value_convertion::Converters::USHORT_TO_SHORT);

						size_t dirVectorsCount = std::size(m_dirVectors);

						for (size_t i = 0; i < dirVectorsCount; i++)
						{
							if (v == m_dirVectors[i])
							{
								ch->Kill();

								ch->SetPosition(vector<ushort>(boardPos[0] + boardWidth, 2));
							}
						}
					}

				);
			});
	}
	else
	{

	}
	
}

void game_engine_core::GameController::SelectMove(std::function<void()> PrintFunc,
	std::function<void()> PrintConfirmFunc)
{
	if (m_possibleTurns.GetCount() == 0)
		return;

	char* cptr = m_controls;

	char input;

	size_t start = 0;

	size_t end = m_possibleTurns.GetCount();

	Cell* ptr = nullptr;

	WORD prevColor;

	auto cboptr = m_cellBuildingOptions;

	bool select_= false;
	
	do
	{
		do
		{
			ptr = m_possibleTurns[start];

			ptr->Select();

			system("CLS");

			Draw();

			if (PrintFunc != nullptr)
				PrintFunc();

			input = console_funcs::Input<char, char>([cptr](char& inp)->bool
				{
					if (inp == cptr[0] || inp == std::toupper(cptr[0]))//move left
					{
						return true;
					}
					else if (inp == cptr[1] || inp == std::toupper(cptr[1]))//move right
					{
						return true;
					}
					else if (inp == cptr[2] || inp == std::toupper(cptr[2]))//selection
					{
						return true;
					}
					else if (inp == cptr[3] || inp == std::toupper(cptr[3]))//confirm
					{
						return true;
					}
					else if (inp == cptr[4] || inp == std::toupper(cptr[4]))//abort
					{
						return true;
					}

					return false;
				}, false);

			if (input == *m_controls)//Move left
			{
				start -= 1;
			}
			else if (input == *(m_controls + 1))//Move Right
			{
				start += 1;
			}

			if (ptr != nullptr)
				if (ptr->isSelected())
					ptr->Deselct();

			if (start > end - 1)
			{
				start = 0;
			}
			else if (start < 0)
			{
				start = end - 1;
			}

			if (input == cptr[2] || input == std::toupper(cptr[2]))//Select cell
			{
				if (!select_)
				{
					ptr->SetBackColor(ptr->GetSelectionColor());

					m_selectedRouts.AddToTheEnd(ptr);

					select_ = true;
				}
				else
				{
					ptr->SetBackColor(ptr->IsWhite() ? cboptr->GetWhiteColor() : cboptr->GetBlackColor());

					m_selectedRouts.RemoveNode(ptr);

					select_ = false;
				}
				
			}

			if ((m_multipleMoves <= 0) && select_)//true -> break
			{
				break;
			}

		} while (!(input == m_controls[3] || input == std::toupper(m_controls[3])));// confirmation of selection

		if (PrintConfirmFunc != nullptr)
			PrintConfirmFunc();

		input = console_funcs::Input<char, char>([cptr](char& inp)->bool
			{
				if (inp == cptr[3] || inp == std::toupper(cptr[3]))// confirm
				{
					return true;
				}
				else if (inp == cptr[4] || inp == std::toupper(cptr[4])) // reselection
				{
					return true;
				}
				return false;
			}, false);

		if (input == m_controls[4] || input == std::toupper(m_controls[4]))
		{
			select_ = false;

			m_possibleTurns.Iterate([cboptr](Cell* cell) { cell->SetBackColor(cell->IsWhite() ? cboptr->GetWhiteColor() : cboptr->GetBlackColor()); });

			m_selectedRouts.Clear();
		}

	} while (!(input == cptr[3] || input == std::toupper(cptr[3])));
	
}

bool game_engine_core::GameController::IsAllPossibleTurnsSelected()
{
	bool result = true;

	m_possibleTurns.Iterate([&result](Cell* cell)
		{
			result = cell->isSelected();
		});

	return result;
}

void game_engine_core::GameController::FindPossibleTurns()
{
	m_multipleMoves = -1;

	m_possibleTurns.Clear();

	m_checkersToBeKilled.Clear();

	m_selectedRouts.Clear();

	vector<ushort> pos = m_selectedChecker->GetPosition();

	vector<short> selectedCheckerPos = vector<short>(pos[0], pos[1]);

	vector<short> checkerTempPosition = selectedCheckerPos;

	FindPossibleTurnRecursive(selectedCheckerPos, checkerTempPosition);
}

void game_engine_core::GameController::Draw()
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

void game_engine_core::GameController::SelectChecker(bool whiteblack, std::function<void()> PrintFunc,
	std::function<void()> PrintConfirmFunc)

{
	if (m_selectedChecker != nullptr)
		if (m_selectedChecker->isSelected())
			m_selectedChecker->Deselct();

	char* cptr = m_controls;

	char input;

	int index = 0;

	int start;

	int end;

	int mid = (m_checkersCount / 2) - 1; //11	

	if (!whiteblack)//Black
	{
		start = 0;

		end = mid;
	}
	else//White
	{
		start = mid + 1;

		end = m_checkersCount - 1;
	}

	index = start;

	do
	{
		do
		{
			m_selectedChecker = m_checkers + index;

			m_selectedChecker->Select();

			system("CLS");

			this->Draw();

			if (PrintFunc != nullptr)
				PrintFunc();

			input = console_funcs::Input<char, char>([cptr](char& inp)->bool
				{
					if (inp == cptr[0] || inp == std::toupper(cptr[0]))
					{
						return true;
					}
					else if (inp == cptr[1] || inp == std::toupper(cptr[1]))
					{
						return true;
					}
					else if (inp == cptr[2] || inp == std::toupper(cptr[2]))
					{
						return true;
					}

					return false;
				}, false);

			if (input == *m_controls)//Move left
			{
				index -= 1;
			}
			else if (input == *(m_controls + 1))
			{
				index += 1;
			}

			if (m_selectedChecker != nullptr)
				if (m_selectedChecker->isSelected())
					m_selectedChecker->Deselct();

			if (index < start)
				index = end;
			else if (index > end)
				index = start;

			auto temp = m_checkers + index;

			while (!temp->isAlive())//Manual shifting
			{
				if (input == *m_controls)//Move left
				{
					index -= 1;
				}
				else if (input == *(m_controls + 1))
				{
					index += 1;
				}

				if (index < start)
					index = end;
				else if (index > end)
					index = start;

				temp = m_checkers + index;
			}



		} while (!(input == *(m_controls + 2) || input == std::toupper(*(m_controls + 2))));

		if (m_selectedChecker != nullptr)
			if (!m_selectedChecker->isSelected())
				m_selectedChecker->Select();

		system("CLS");

		this->Draw();

		if (PrintConfirmFunc != nullptr)
			PrintConfirmFunc();

		input = console_funcs::Input<char, char>([cptr](char& inp)->bool
			{
				if (inp == cptr[3] || inp == std::toupper(cptr[3]))
				{
					return true;
				}
				else if (inp == cptr[4] || inp == std::toupper(cptr[4]))
				{
					return true;
				}
				return false;
			}, false);

		if (input == cptr[4] || input == std::toupper(cptr[4]))
		{
			continue;
		}

	} while (!(input == *(m_controls + 3) || input == std::toupper(*(m_controls + 3))));	
}


#pragma endregion

#pragma region Static definitions

signed char game_engine_core::GameController::m_multipleMoves = -1;

bool game_engine_core::GameController::m_init = false;


vector_math::vector<short> game_engine_core::GameController::m_dirVectors[4] =
{
	vector<short>(-1, 1), //left up
	vector<short>(1, 1), //right up
	vector<short>(-1, -1),//left down
	vector<short>(1, -1) //right down
};

vector_math::vector<short> game_engine_core::GameController::m_boardBasis[2] =
{
	vector<short>(1, 0),
	vector<short>(0, 1)
};

#pragma endregion


#pragma endregion

#pragma region CellBuildingOptions

#pragma region Ctor

game_engine_core::CellBuildingOptions::CellBuildingOptions(
	WORD BlackColor,
	WORD WhiteColor, WORD borderColor, WORD borderHighlightColor, WORD selColor,
	ushort width, ushort height) :
	m_cellWidth(width), m_cellHeight(height), m_blackColor(BlackColor), m_whiteColor(WhiteColor),
	m_borderColor(borderColor), m_SelectionColor(selColor),
	m_BorderHighlightColor(borderHighlightColor)

{}

game_engine_core::CellBuildingOptions::CellBuildingOptions(ushort width, ushort height) :
	CellBuildingOptions(console_graphics::Colors::BLACKBack,
		console_graphics::Colors::WhiteBack, console_graphics::Colors::BLACK |
		console_graphics::Colors::LIGHTGRAYBack, console_graphics::Colors::GREENBack,
		console_graphics::Colors::ORANGEBack,
		width, height) {}

#pragma endregion

const WORD& game_engine_core::CellBuildingOptions::GetBorderHighlightColor() const
{
	return m_BorderHighlightColor;
}

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

const WORD& game_engine_core::CellBuildingOptions::GetSelectionColor() const
{
	return m_SelectionColor;
}

#pragma endregion

#pragma region CheckerBuildingOptions

#pragma region Ctor

game_engine_core::CheckerBuildingOptions::CheckerBuildingOptions() :
	CheckerBuildingOptions(console_graphics::Colors::WhiteBack,
		console_graphics::Colors::BLACKBack, console_graphics::Colors::ORANGEBack)
{}
game_engine_core::CheckerBuildingOptions::CheckerBuildingOptions(WORD whiteCheckerColor,
	WORD blackCheckerColor, WORD SelectionColor,
	ushort width, ushort height) :
	m_blackCheckerColor(blackCheckerColor),
	m_whiteCheckerColor(whiteCheckerColor),
	m_CheckerWidth(width), m_CheckerHeight(height),
	m_SelectionColor(SelectionColor)
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

const WORD& game_engine_core::CheckerBuildingOptions::GetSelectionColor() const
{
	return m_SelectionColor;
}

#pragma endregion


#pragma endregion




