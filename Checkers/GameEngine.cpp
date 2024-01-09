#include"pch.h"
#include"GameEngine.h"
#include<queue>

#pragma region GameObject definitions

#pragma region Ctors

//char[5] {186, 201, 205, 187, 188}, 5

game_engine_core::GameObject::GameObject() : GameObject(0, 0, console_graphics::Colors::WhiteBack,
	console_graphics::Colors::ORANGEBack,
	vector_math::Vector<ushort>(0, 0), nullptr, 0)
{

}

game_engine_core::GameObject::GameObject(const ushort& width, const ushort& height,
	const WORD& backGround,
	const WORD& focusColor,
	Vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	m_width(width), m_height(height), m_backGround(backGround),
	m_position(position),
	m_focused(false), m_chars(charsToDraw), m_charsToDrawSize(charsToDrawSize),
	m_focusColor(focusColor)
{

}

game_engine_core::GameObject::GameObject(const GameObject& other)
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_backGround = other.m_backGround;
	m_focused = other.m_focused;
	m_position = other.m_position;
	m_charsToDrawSize = other.m_charsToDrawSize;
	m_focusColor = other.m_focusColor;

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

WORD game_engine_core::GameObject::GetFocusColor() const
{
	return m_focusColor;
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

vector_math::Vector<ushort> game_engine_core::GameObject::GetPosition() const
{
	return m_position;
}

bool game_engine_core::GameObject::isFocused() const { return m_focused; }

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

void game_engine_core::GameObject::SetPosition(const Vector<ushort>& v)
{
	m_position = v;
}

void game_engine_core::GameObject::SetFocusColor(WORD selColor)
{
	m_focusColor = selColor;
}

void game_engine_core::GameObject::Focus()
{
	m_focused = true;
}

void game_engine_core::GameObject::UnFocus()
{
	m_focused = false;
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

	m_focusColor = other.m_focusColor;

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
	const WORD& focusColor,
	Vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	GameObject(width, height, backGround, focusColor, position, charsToDraw, charsToDrawSize),
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
m_BorderHighlightColor(console_graphics::Colors::GREENBack),
m_borderHighLight(false), m_Move_Selected(false) {}

game_engine_core::Cell::Cell(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& borderColor, const WORD& selColor, const WORD& borderHighlightColor,
	Vector<ushort> position, bool isWhite, char* charsToDraw, size_t charsToDrawSize)
	: GameObject(width, height, backGround, selColor, position, charsToDraw, charsToDrawSize),
	m_isWhite(isWhite), m_borderColor(borderColor), m_BorderHighlightColor(borderHighlightColor),
	m_borderHighLight(false), m_Move_Selected(false)
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
	m_BorderHighlightColor(other.m_BorderHighlightColor), m_borderHighLight(other.m_borderHighLight)
{}

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

bool game_engine_core::Cell::IsMoveSelected() const
{
	return m_Move_Selected;
}

void game_engine_core::Cell::SelectMove()
{
	m_Move_Selected = true;
}

void game_engine_core::Cell::DeSelectMove()
{
	m_Move_Selected = false;
}


const WORD& game_engine_core::Cell::GetBorderHighlightColor() const
{
	return m_BorderHighlightColor;
}

void game_engine_core::Cell::SetBorderHighlightColor(const WORD& borderHighlightColor)
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

	bool selected = this->isFocused();

	auto focus_Color = this->GetFocusColor();

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			dec_symbol = false;

			utility.SetCursorPosition(pos + Vector<ushort>(j, i));

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
				color = selected ? focus_Color : backGroundColor;
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
	Vector<ushort> position, bool isWhite, ushort HorbaseLength, ushort VertbaseLength, char* charsToDraw, size_t charsToDrawSize)
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
	if (!this->isAlive())
		return;

	auto pos = this->GetPosition();

	auto width = this->GetWidth();

	auto height = this->GetHeight();

	auto back = this->GetBackColor();

	auto selColor = this->GetFocusColor();

	//1) Calc 2 hor and vert midle elements

	size_t Hormid1 = width / 2;

	size_t Hormid2 = Hormid1 + m_HorbaseLength - 1;

	size_t Vertmid1 = height / 2;

	size_t Vertmid2 = Vertmid1 + m_VertBaseLength - 1;

	bool shouldPrint = false;

	ushort last1 = 0;

	ushort last2 = 0;

	ushort tempi = 0;

	for (size_t i = 1; i < height - 1; i++)
	{
		for (size_t j = 1; j < width - 1; j++)
		{
			utility.SetCursorPosition(pos + Vector<ushort>(j, i));

			if (i < Vertmid1 && j >= (Hormid1 - i - 1) && j <= (Hormid2 + i - 1))
			{
				last1 = Hormid1 - i - 1;

				last2 = Hormid2 + i - 1;

				if (!m_isDamka)//Ordinary Checker
				{
					utility.Print(*this->GetChars(), this->isFocused() ? selColor : back);
				}
				else  //Checker is Damka
				{
					if (i >= (Vertmid1 - 1) && (j > last1 && j < last2))
					{
						utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
					}
					else
					{
						utility.Print(*(this->GetChars()), this->isFocused() ? selColor : back);
					}
				}

				tempi = i;
			}
			if (i >= Vertmid1 && i < Vertmid2 && j >= last1 && j <= last2)
			{
				if (!m_isDamka)
				{
					utility.Print(*this->GetChars(), this->isFocused() ? selColor : back);
				}
				else if (j > last1 && j < last2)
				{
					utility.Print(*(this->GetChars() + 1), console_graphics::Colors::BLACKBack);
				}
				else
				{
					utility.Print(*(this->GetChars()), this->isFocused() ? selColor : back);
				}

			}
			else if (i >= Vertmid2 && j >= (last1 + tempi - 1) && j <= (last2 - tempi + 1))
			{
				utility.Print(*this->GetChars(), this->isFocused() ? selColor : back);
			}
		}
	}
}

#pragma endregion


#pragma endregion

#pragma region Main Game logic definitions

game_engine_core::Main_Game_logic::Main_Game_logic(console_graphics_utility* cgu) :
	m_console_graphics_utility(cgu)
{}

game_engine_core::Cell* game_engine_core::Main_Game_logic::FindCellUsingPosition(const Vector<short>& positionVector)
{
	bool stop = false;

	Vector<short> pos;

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

game_engine_core::Checker* game_engine_core::Main_Game_logic::FindCheckerUsingPosition(
	const Vector<short>& positionVector, Checker* checkers,
	size_t checkers_count)
{
	if (checkers == nullptr)
		return nullptr;

	if (checkers_count == 0)
		return nullptr;

	for (size_t i = 0; i < checkers_count; i++)
	{
		if ((checkers + i)->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT) == positionVector)
			return (checkers + i);
	}

	return nullptr;
}

bool game_engine_core::Main_Game_logic::OutOfBorders(const Vector<short>& position)
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

vector_math::Vector<short> game_engine_core::Main_Game_logic::FindOrthogonalVector(const Vector<short>& v) const
{
	Vector<short> result;

	size_t count = std::size(m_dirVectors);

	Vector<short> oneInput = Vector<short>(v[0] / std::abs(v[0]), v[1] / std::abs(v[1]));

	Vector<short> oneDirVector;

	for (size_t i = 0; i < count; i++)
	{
		oneDirVector = Vector<short>(m_dirVectors[i][0] / std::abs(m_dirVectors[i][0]), m_dirVectors[i][1] / std::abs(m_dirVectors[i][1]));

		if (oneDirVector * oneInput == 0)
		{
			result = m_dirVectors[i];

			break;
		}
	}

	return result;
}

void game_engine_core::Main_Game_logic::FindAllPosibleTurnsForKingRecursive(
	Checker* selectedChecker,
	const Vector<short>& position,
	Vector<short>& prevPosition, Checker* checkers, size_t checkers_count,
	bool& on_Callback, const Vector<short>& dirVector,
	bool checker_under_attack)
{
	//Base Case

	//m_console_graphics_utility->SetCursorPosition(position.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

	if (OutOfBorders(position) && checker_under_attack)//If we have take 1 checker already 
	{
		on_Callback = true;

		return;
	}

	if (OutOfBorders(position))
	{
		return;
	}
	//Way separator
	if (position == prevPosition && !checker_under_attack)
	{
		size_t count = std::size(m_dirVectors);

		for (size_t i = 0; i < count; i++)
		{
			//Examine all directions but only if we are at he same cell position as our King is.
			FindAllPosibleTurnsForKingRecursive(selectedChecker, position + m_dirVectors[i], prevPosition,
				checkers, checkers_count, on_Callback, m_dirVectors[i]);
		}
	}
	else
	{
		//determine wether next cell is empty
		auto enemyChecker = FindCheckerUsingPosition(position, checkers, checkers_count);

		if (enemyChecker == nullptr)
		{
			auto Cell = FindCellUsingPosition(position);

			if (!on_Callback)
			{
				m_possibleTurns.AddToTheEnd(Cell);
				//next cell is empty make another move.
				FindAllPosibleTurnsForKingRecursive(selectedChecker, position + dirVector, prevPosition,
					checkers, checkers_count,
					on_Callback, dirVector, checker_under_attack);
			}

			if (on_Callback)
			{
				//m_console_graphics_utility->SetCursorPosition(position.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

				Checker* ch = FindCheckerUsingPosition(position + (dirVector * -1), checkers, checkers_count);

				if (ch != nullptr)
				{
					if (ch->IsCheckerWhite() != selectedChecker->IsCheckerWhite())
					{
					}
					else
					{
						m_possibleTurns.RemoveNode(Cell);

						return;
					}
				}
				else
				{
					m_possibleTurns.RemoveNode(Cell);

					return;
				}

				return;
			}

		}
		else //Next cell is not empty maybe there can be enemy checker
		{
			bool nextIsFriend = selectedChecker->IsCheckerWhite() == enemyChecker->IsCheckerWhite();

			if (nextIsFriend)//It is the checker who's color is the same with the King
			{
				if (checker_under_attack)
				{
					on_Callback = true;
				}

				return;//Stop search of possible moves
			}
			else//Enemy checker detected
			{
				//Need to understand wether it is open or not
				Vector<short> positionBehind_theEnemyChecker = position + dirVector;

				//m_console_graphics_utility->SetCursorPosition(positionBehind_theEnemyChecker.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

				//Attack is Imposible 
				if (OutOfBorders(positionBehind_theEnemyChecker))
				{
					if (checker_under_attack)
					{
						on_Callback = true;
					}

					return;
				}

				auto Checker_Behind = FindCheckerUsingPosition(positionBehind_theEnemyChecker, checkers, checkers_count);

				if (Checker_Behind == nullptr)//Enemy checker is open -> Attack it
				{
					if (!m_checkersToBeKilled.Contains(enemyChecker))
					{
						m_checkersToBeKilled.AddToTheEnd(enemyChecker);

						m_multipleTakes++;
					}
					else
					{
						return;
					}


					//Find 2 ortogonal vectors to current direction

					Vector<short> orthogonal = FindOrthogonalVector(positionBehind_theEnemyChecker -
						enemyChecker->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT));

					auto v1 = positionBehind_theEnemyChecker + orthogonal;

					auto v2 = positionBehind_theEnemyChecker + orthogonal * -1;

					bool CallBack = false;

					//Expend Search in orthogonal direction to find the new possible targets
					FindAllPosibleTurnsForKingRecursive(selectedChecker, v1, v1, checkers, checkers_count, CallBack, orthogonal, true);
					//Expend Search in orthogonal opposite direction to find the new possible targets

					CallBack = false;

					FindAllPosibleTurnsForKingRecursive(selectedChecker, v2, v2, checkers, checkers_count, CallBack, orthogonal * -1, true);

					CallBack = false;

					FindAllPosibleTurnsForKingRecursive(selectedChecker, positionBehind_theEnemyChecker,
						positionBehind_theEnemyChecker, checkers, checkers_count,
						CallBack, dirVector, true);
				}
				else
				{
					if (checker_under_attack)
					{
						on_Callback = true;
					}

					return;//Checker is Covered and Attack is impossible
				}

			}
		}


	}
}

void game_engine_core::Main_Game_logic::DrawBoard(Cell** board, size_t rows_count, size_t colums_count)
{
	for (size_t i = 0; i < rows_count; i++)
	{
		for (size_t j = 0; j < colums_count; j++)
		{
			(board[i] + j)->Render(*m_console_graphics_utility);
		}
	}
}

void game_engine_core::Main_Game_logic::DrawCheckers(Checker* checkers, size_t checkers_count)
{
	for (size_t i = 0; i < checkers_count; i++)
	{
		(checkers + i)->Render(*m_console_graphics_utility);
	}
}

void game_engine_core::Main_Game_logic::FindPossibleTurnRecursive(
	Checker* selectedChecker,
	const Vector<short>& current_position,
	Vector<short>& prev_position, Checker* checkers, size_t checkers_count,
	const Vector<short>& dirVector, bool multiKill,
	std::function<void(Vector<short> prev_position, Vector<short> current_position, bool multiKill)> func)
{
	m_console_graphics_utility->SetCursorPosition(current_position.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

	//Base cases
	if (current_position != prev_position)//initial Situation when we are at the same position
	{
		if (OutOfBorders(current_position))
		{
			return;
		}

		Checker* currentchecker = FindCheckerUsingPosition(current_position, checkers, checkers_count);

		if (currentchecker == nullptr && !multiKill)//Position of the empty cell (No checkers exists at this posVector)
		{
			if (selectedChecker->IsCheckerWhite() && ((dirVector * m_boardBasis[1]) < 0))//Move of the white checker
			{
				if (func != nullptr)
				{
					func(prev_position, current_position, multiKill);
				}
				else
				{
					m_possibleTurns.AddToTheEnd(FindCellUsingPosition(current_position));//Add Cells To be Highlighted
				}

				return;
			}
			else if (!selectedChecker->IsCheckerWhite() && (dirVector * m_boardBasis[1]) > 0)//Move for the black checker
			{
				if (func != nullptr)
				{
					func(prev_position, current_position, multiKill);
				}
				else
				{
					m_possibleTurns.AddToTheEnd(FindCellUsingPosition(current_position));//Add Cells To be Highlighted
				}

				return;
			}
			else
			{
				return;
			}
		}
		else if (currentchecker != nullptr)
		{
			if (selectedChecker->IsCheckerWhite() != currentchecker->IsCheckerWhite()) //Cell contains checker, also case when checkers can fight
			{
				//Fighting We can attack only if the cell behind the checker is empty
				//and the checker can't be attacked twice

				if (m_checkersToBeKilled.Contains(FindCheckerUsingPosition(current_position, checkers, checkers_count)))
				{
					return;
				}

				Vector<short> posBehind = current_position + dirVector;

				m_console_graphics_utility->SetCursorPosition(posBehind.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

				if (FindCheckerUsingPosition(posBehind, checkers, checkers_count) == nullptr)//Enemy checker is open
				{
					if (OutOfBorders(posBehind))
					{
						return;
					}

					m_multipleTakes++;

					m_possibleTurns.AddToTheEnd(FindCellUsingPosition(posBehind));

					m_checkersToBeKilled.AddToTheEnd(FindCheckerUsingPosition(current_position, checkers, checkers_count));

					if (func != nullptr)
					{
						func(prev_position, posBehind, multiKill);
					}

					//Posibility of multiKill

					bool multiKill = true;

					FindPossibleTurnRecursive(selectedChecker, posBehind + m_dirVectors[0], posBehind, checkers, checkers_count, m_dirVectors[0], multiKill, func);//Move leftUp
					FindPossibleTurnRecursive(selectedChecker, posBehind + m_dirVectors[1], posBehind, checkers, checkers_count, m_dirVectors[1], multiKill, func);//Move rightUp
					FindPossibleTurnRecursive(selectedChecker, posBehind + m_dirVectors[2], posBehind, checkers, checkers_count, m_dirVectors[2], multiKill, func);//Move leftDown
					FindPossibleTurnRecursive(selectedChecker, posBehind + m_dirVectors[3], posBehind, checkers, checkers_count, m_dirVectors[3], multiKill, func);//Move rightDown

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

	if (current_position == prev_position && func != nullptr)
	{
		func(prev_position, current_position, multiKill);
	}

	FindPossibleTurnRecursive(selectedChecker, current_position + m_dirVectors[0], prev_position, checkers, checkers_count, m_dirVectors[0], false, func);//Move leftUp
	FindPossibleTurnRecursive(selectedChecker, current_position + m_dirVectors[1], prev_position, checkers, checkers_count, m_dirVectors[1], false, func);//Move rightUp
	FindPossibleTurnRecursive(selectedChecker, current_position + m_dirVectors[2], prev_position, checkers, checkers_count, m_dirVectors[2], false, func);//Move leftDown
	FindPossibleTurnRecursive(selectedChecker, current_position + m_dirVectors[3], prev_position, checkers, checkers_count, m_dirVectors[3], false, func);//Move rightDown	
}

bool game_engine_core::Main_Game_logic::IsAllPossibleTurnsSelected()
{
	bool result = true;

	m_possibleTurns.Iterate([&result](Cell* cell)-> bool
		{
			result = cell->isFocused();

			return true;
		});

	return result;
}

void game_engine_core::Main_Game_logic::FindPossibleTurns(bool whiteBlack, std::function<void(Vector<short> position, Vector<short> PrevPos, bool multiKill)> func)
{
	if (Main_Game_logic::m_use_AI && m_selectedRouts.GetCount() > 0 && !whiteBlack)
	{
		m_selectedChecker = FindCheckerUsingPosition(m_selectedRouts[(size_t)0]->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT),
			m_checkers, m_checkersCount);

		m_selectedRouts.RemoveNode(m_selectedRouts[(size_t)0]);

		return;
	}

	Vector<short> pos = m_selectedChecker->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT);

	bool CallBack = false;

	if (m_selectedChecker->IsDamka())
	{
		m_multipleTakes = 1;

		FindAllPosibleTurnsForKingRecursive(m_selectedChecker, pos, pos, m_checkers, m_checkersCount, CallBack);
	}
	else
	{
		FindPossibleTurnRecursive(m_selectedChecker, pos, pos, m_checkers, m_checkersCount, Vector<short>(), false, func);
	}
}

void game_engine_core::Main_Game_logic::Reset_Game_Logic_State()
{
	m_multipleTakes = -1;

	m_possibleTurns.Clear();

	m_checkersToBeKilled.Clear();

	m_selectedRouts.Clear();
}

#pragma region Static Definitions

vector_math::Vector<short> game_engine_core::Main_Game_logic::m_dirVectors[4] =
{
	Vector<short>(-1, 1), //left up
	Vector<short>(1, 1), //right up
	Vector<short>(-1, -1),//left down
	Vector<short>(1, -1) //right down
};

vector_math::Vector<short> game_engine_core::Main_Game_logic::m_boardBasis[2] =
{
	Vector<short>(1, 0),
	Vector<short>(0, 1)
};

signed char game_engine_core::Main_Game_logic::m_multipleTakes = -1;

#pragma endregion

#pragma endregion

#pragma region Checker ai definitions

#pragma region Ctor

game_engine_core::ai_modules::checker_ai::checker_ai(console_graphics_utility* cgu) :
	m_id_of_max_takes(-1), m_max_takes(0),
	Main_Game_logic(cgu) {}

#pragma endregion


#pragma region Functions

void game_engine_core::ai_modules::checker_ai::Set_Difficulty(const difficulty_level& diff)
{
	m_difficulty = diff;
}

void game_engine_core::ai_modules::checker_ai::Move(Vector<ushort> selPosition)
{
	auto chToBeKilledPtr = &m_checkersToBeKilled;

	Checker* selCheckerPtr = m_selectedChecker;

	const auto& boardPos = m_Board_position;

	const auto& boardWidth = m_boardWidth;

	//Fighting

	//Ordinary fightting

	//Calculate direction vector from slected checker position to selected cell position
	auto MoveDir = selPosition - selCheckerPtr->GetPosition();
	//Move selected checker to selected cell position
	selCheckerPtr->SetPosition(selPosition);

	if (chToBeKilledPtr->isEmpty())
	{
		if (!m_selectedChecker->IsDamka())
		{
			if (m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] <= m_Board_position["Y"])//White Checker
			{
				m_selectedChecker->MakeDamka();
			}
			else if (!m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] >= m_Board_position["Y"] + m_boardHeight - m_Cell_Height)
			{
				m_selectedChecker->MakeDamka();
			}
		}

		return;
	}

	//Find vector colinear to one of the Dir vectors
	size_t dirVectorsCount = std::size(m_dirVectors);

	Vector<short> colinearToDirection = Vector<short>(0, 0);

	Vector<short> diff;

	for (size_t i = 0; i < dirVectorsCount; i++)
	{
		if (m_dirVectors[i].IsCoDirectional(MoveDir.Convert_To(value_convertion::Converters::USHORT_TO_SHORT)))
		{
			colinearToDirection = m_dirVectors[i];

			break;
		}
	}

	if (colinearToDirection != Vector<short>(0, 0))
	{
		diff = selCheckerPtr->GetPosition().
			Convert_To(value_convertion::Converters::USHORT_TO_SHORT)
			- colinearToDirection;
	}

	//Iterate all posible checkers for kill
	chToBeKilledPtr->Iterate([diff, boardPos, boardWidth]
	(Checker* ch)->bool
		{
			if (diff.Convert_To(value_convertion::Converters::SHORT_TO_USHORT) == ch->GetPosition())
			{
				ch->Kill();

				ch->SetPosition(Vector<ushort>(boardPos[0] + boardWidth + 10, 2));
			}
			return true;
		}

	);

	//Determine Damka
	if (!m_selectedChecker->IsDamka())
	{
		if (m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] <= m_Board_position["Y"])//White Checker
		{
			m_selectedChecker->MakeDamka();
		}
		else if (!m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] >= m_Board_position["Y"] + m_boardHeight - m_Cell_Height)
		{
			m_selectedChecker->MakeDamka();
		}
	}
}

void game_engine_core::ai_modules::checker_ai::Initialize_AI_Variables(ushort board_Width,
	ushort board_Height,
	Vector<ushort> board_Position, Checker* checkers, Cell** board,
	ushort cell_Height)
{
	m_boardWidth = board_Width;

	board_Height = board_Height;

	m_Board_position = board_Position;

	m_checkers = checkers;

	m_board = board;

	m_selectedChecker = nullptr;

	m_Cell_Height = cell_Height;
}

int game_engine_core::ai_modules::checker_ai::FindEuristicValue(Checker* board)
{
	size_t WhiteCount = 0;

	size_t BlackCount = 0;

	size_t start = 0;

	size_t end = (m_checkersCount - 1) / 2;//11

	bool OneTime = true;

	for (size_t i = 0; i < 2; i++)
	{
		if (i == 1 && OneTime)//Calculate White checkers count
		{
			start = end + 1;

			end = m_checkersCount - 1;

			OneTime = false;
		}

		for (size_t j = start; j <= end; j++)
		{
			if (board[j].isAlive())
			{
				if (i == 0)
				{
					BlackCount++;
				}
				else
				{
					WhiteCount++;
				}
			}
		}
	}

	return BlackCount - WhiteCount;
}

void game_engine_core::ai_modules::checker_ai::ClearPossible_Calculated_Turns()
{
	m_Possible_Calculated_Turns.Clear();
}

size_t game_engine_core::ai_modules::checker_ai::GetMaxTakesCount()
{
	return m_max_takes;
}

void game_engine_core::ai_modules::checker_ai::Reset_Data()
{
	this->ClearPossible_Calculated_Turns();

	this->m_id_of_max_takes = -1;

	this->m_max_takes = 0;
}

game_engine_core::ai_modules::turn<vector_math::Vector<short>> game_engine_core::ai_modules::checker_ai::SelectPossibleTurn(bool whiteBlack)
{
	bool ai_checker = true;

	game_engine_core::ai_modules::turn<vector_math::Vector<short>> result;

	if (whiteBlack)
	{
		ai_checker = false;
	}

	if (ai_checker)
	{
		using namespace nonlinear_data_structures;
		
		using namespace vector_math;

		using namespace::game_engine_core::ai_modules;

		auto board = this->DeepBoardCopy(m_checkers, m_checkersCount);

		size_t start;
		size_t end;
		size_t mid = (m_checkersCount - 1) / 2;

		if (!whiteBlack)//Black checkers calculations
		{
			start = 0;

			end = mid;
		}

		Vector<short> start_Point_Temp;

		Vector<short> start_Vertex;

		bool startDetected = false;

		bool take_sequence = false;

		edge_list_graph<Vector<short>> moveGraph;

		for (size_t i = start; i <= end; i++)
		{
			//Pre examination analizer

			m_selectedChecker = m_checkers + i;

			if (!m_selectedChecker->isAlive())
			{
				continue;
			}

			m_console_graphics_utility->SetCursorPosition(m_selectedChecker->GetPosition());

			bool multikill_temp = false;

			//Try to build graph of possible moves of one checker
			this->FindPossibleTurns(true, [&start_Point_Temp, &moveGraph, &multikill_temp,
				&startDetected, &start_Vertex]
			(Vector<short> prev_position, Vector<short> current_Pos, bool multikill)
				{
					if (!startDetected)
					{
						start_Vertex = prev_position;

						startDetected = true;
					}
								
					if (multikill)
					{
						start_Point_Temp = prev_position;

						multikill_temp = multikill;
					}

					if (multikill != multikill_temp)
					{
						start_Point_Temp = prev_position;

						multikill_temp = multikill;
					}

					if (prev_position == current_Pos)
					{
						start_Point_Temp = prev_position;
					}
					else
					{
						moveGraph.AddEdge(edge<Vector<short>>(start_Point_Temp, current_Pos));
					}
				});

			if (moveGraph.isEmpty())
			{
				startDetected = false;

				moveGraph.Clear();

				m_checkersToBeKilled.Clear();

				continue;
			}

			turn<Vector<short>> current_turn = turn<Vector<short>>(start_Vertex);

			m_checkersToBeKilled.Iterate(
				[&current_turn](Checker* elem)->bool
				{
					current_turn.AddCheckerToBeKilled_Coord(elem->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT));

					return true;
				}
			);

			//current_turn.Set_CountOfTakes(m_checkersToBeKilled.GetCount());

			auto prev_visit_dictionary = moveGraph.generate_prev_dictionary(Vector<short>());

			moveGraph.depth_first_search(start_Vertex,
				[&prev_visit_dictionary, &current_turn](Vector<short> prev, Vector<short> current, std::map<Vector<short>, bool> v_d, bool isEnd)->bool
				{
					prev_visit_dictionary[current] = prev;

					if (isEnd)//End of current graph found
					{
						current_turn.AddEnd(current);
					}

					return true;
				});

			current_turn.Set_Prev_Dictionary(prev_visit_dictionary);

			if (m_checkersToBeKilled.GetCount() != 0)//Some possible takes detected
			{
				size_t current_count_of_takes = m_checkersToBeKilled.GetCount();

				current_turn.Set_CountOfTakes(current_count_of_takes);

				if (current_count_of_takes > m_max_takes)
				{
					m_id_of_max_takes = current_turn.Getid();

					m_max_takes = current_count_of_takes;
				}

				m_Possible_Calculated_Turns.AddToTheEnd(current_turn);
			}
			else//Possible takes not detected
			{
				switch (m_difficulty)
				{
				case game_engine_core::ai_modules::easy:

					m_Possible_Calculated_Turns.AddToTheEnd(current_turn);// Write to the turn collection

					break;
				case game_engine_core::ai_modules::medium:

					//Use Min_Max depth = 2

					break;
				case game_engine_core::ai_modules::hard:

					//Use Min_Max depth = 3

					break;
				}
			}

			startDetected = false;

			moveGraph.Clear();

			m_checkersToBeKilled.Clear();

#pragma region Commented
			//if (m_checkersToBeKilled.GetCount() > 0)//Attack is possible
			//{
			//	//Check this multi kill attacking sequence


			//}
			//else//Analize using Mini Max
			//{
			//	/*if (m_checkersToBeKilled.GetCount() > 0)
			//	{
			//		m_checkersToBeKilled.Clear();
			//	}

			//	if (m_possibleTurns.GetCount() > 0)
			//	{
			//		m_possibleTurns.Clear();
			//	}

			//	BuildGameTreeRecursive(board + i, board + i, !whiteBlack, 2, 0, board, m_checkersCount);
			//			
			//	system("CLS");

			//	m_console_graphics_utility->SetCursorPosition(Vector<ushort>(0 ,0));

			//	m_game_tree.For([this](nonlinear_data_structures::edge<Vector<ushort>> edge)->bool
			//		{
			//			auto from = edge.GetFrom();

			//			auto to = edge.GetTo();

			//			std::cout << "From: " << from << "| To:" << to << std::endl;

			//			return true;
			//		});

			//	m_eur_ValueTable.Iterate([](linear_data_structures::key_value_pair<Vector<short>, int> k_v)->bool
			//		{
			//			auto key = k_v.GetKey();

			//			auto value = k_v.GetValue();

			//			std::cout << "Key: " << key << "| Value:" << value << std::endl;

			//			return true;
			//		});

			//	int a = 0;*/

			//	//Analize game tree
			//}
#pragma endregion

		}

		delete[] board;

		if (m_id_of_max_takes > 0)//Possible attacking sequence Exists
		{
			m_Possible_Calculated_Turns.Iterate(
				[this, &result](turn<Vector<short>> elem)->bool
				{
					if (m_id_of_max_takes == elem.Getid())
					{
						result = elem;

						return false;
					}

					return true;
				}
			);
		}
		else// No Possible attacking sequences
		{
			if (m_difficulty == game_engine_core::ai_modules::easy)//Select rndom turn
			{
				auto turns_count = m_Possible_Calculated_Turns.GetCount();

				result = m_Possible_Calculated_Turns[std::rand() % turns_count];
			}
			else
			{

			}
		}
	}

	return result;

}

game_engine_core::Checker* game_engine_core::ai_modules::checker_ai::DeepBoardCopy(Checker* checkers,
	size_t checkers_count)
{
	Checker* copy = new Checker[checkers_count];

	for (size_t i = 0; i < checkers_count; i++)
	{
		copy[i] = checkers[i];
	}

	return copy;
}

void game_engine_core::ai_modules::checker_ai::BuildGameTreeRecursive(Checker* current_checker,
	Checker* prev_checker, bool whiteBlack,
	size_t depth, size_t current_depth, Checker* checkers_Copy, size_t checkers_count, bool init)
{
	using namespace nonlinear_data_structures;

	using namespace linear_data_structures;

	using namespace value_convertion;

	m_console_graphics_utility->SetCursorPosition(current_checker->GetPosition());

	console_graphics_utility* cgu = m_console_graphics_utility;


	if (depth == current_depth)//Stop analizing
		return;

	size_t start;
	size_t end;
	size_t mid = (m_checkersCount - 1) / 2;


	if (whiteBlack)//White checkers calculations borders
	{
		start = mid + 1;

		end = m_checkersCount - 1;
	}
	else//Black checkers calculations borders
	{
		start = 0;

		end = mid;
	}

	auto pos = current_checker->GetPosition().Convert_To(value_convertion::Converters::USHORT_TO_SHORT);

	static Vector<short> tempCurrPos;

	this->FindPossibleTurnRecursive(current_checker, pos, pos, checkers_Copy, checkers_count,
		Vector<short>(), false,
		[this, start, end, checkers_Copy, current_checker, cgu,
		whiteBlack, depth, current_depth, prev_checker, checkers_count]
	(Vector<short> Check_Pos, Vector<short> Check_Pos2, bool multiKill)
		{
			if (!multiKill)//Calculating a single move
			{
				cgu->SetCursorPosition(Check_Pos.Convert_To(Converters::SHORT_TO_USHORT));

				edge<Vector<ushort>> e = edge<Vector<ushort>>(prev_checker->isAlive() == true ? prev_checker->GetPosition() : m_Prev_Checker_Temp, Check_Pos.Convert_To(Converters::SHORT_TO_USHORT));

				m_selectedChecker = current_checker;

				Move(Check_Pos.Convert_To(Converters::SHORT_TO_USHORT));

				//system("CLS");

				//this->DrawBoard(m_board, 8, 8);

				//this->DrawCheckers(checkers_Copy, m_checkersCount);

				int e_v = FindEuristicValue(checkers_Copy);

				m_eur_ValueTable.AddToTheEnd(key_value_pair<Vector<short>, int>(Check_Pos, e_v));

				m_game_tree.AddEdge(e);

				m_Prev_Checker_Temp = e.GetFrom();

				tempCurrPos = Check_Pos;
			}

			if (multiKill) //Calculate multiple kill 
			{
				cgu->SetCursorPosition(Check_Pos.Convert_To(Converters::SHORT_TO_USHORT));

				m_selectedChecker = current_checker;

				Move(Check_Pos.Convert_To(Converters::SHORT_TO_USHORT));

				//system("CLS");

				//this->DrawBoard(m_board, 8, 8);

				//this->DrawCheckers(checkers_Copy, m_checkersCount);

				int e_v = FindEuristicValue(checkers_Copy);

				//Modify

				auto* const edge = m_game_tree.GetEdge(m_Prev_Checker_Temp, tempCurrPos.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));
				if (edge != nullptr)
					edge->GetData().SetTo(Check_Pos.Convert_To(value_convertion::Converters::SHORT_TO_USHORT));

				m_eur_ValueTable.RemoveNode(key_value_pair<Vector<short>, int>(tempCurrPos, 0));

				m_eur_ValueTable.AddToTheEnd(key_value_pair<Vector<short>, int>(Check_Pos, e_v));

				tempCurrPos = Check_Pos;
			}

			if (m_checkersToBeKilled.GetCount() > 0)
			{
				m_checkersToBeKilled.Clear();
			}

			if (m_possibleTurns.GetCount() > 0)
			{
				m_possibleTurns.Clear();
			}

			if (depth != current_depth + 1)
			{
				for (size_t i = start; i <= end; i++)
				{
					auto copy = this->DeepBoardCopy(checkers_Copy, checkers_count);

					if ((copy + i)->isAlive())
						BuildGameTreeRecursive(copy + i, current_checker, !whiteBlack, depth, current_depth + 1, copy, checkers_count);

					delete[] copy;
				}
			}



		});

}

#pragma endregion


#pragma endregion


#pragma region GameController definitions

#pragma region Ctor

game_engine_core::GameController::GameController(console_graphics_utility* utility,
	Vector<ushort> boardPosition, CellBuildingOptions* cellbuildingOptions,
	CheckerBuildingOptions* checkerBuildingOptions, ai_modules::checker_ai* ai_modules) :
	Main_Game_logic(utility)
{
	if (ai_modules != nullptr)
	{
		m_use_AI = true;

		m_ai = ai_modules;
	}
	else
	{
		m_use_AI = false;
	}

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

	auto focusColor = m_cellBuildingOptions->GetFocusColor();

	///Checkers initialization

	m_checkers = new Checker[m_checkersCount];

	size_t mid = m_checkersCount / 2;

	auto CheckerWidth = m_checkerBuildingOpions->GetCheckerWidth();

	auto CheckerHeight = m_checkerBuildingOpions->GetCheckerHeight();

	WORD CheckerBlackColor = m_checkerBuildingOpions->GetBlackCheckerColor();

	WORD CheckerWhiteColor = m_checkerBuildingOpions->GetWhiteCheckerColor();

	Vector<ushort> positionTemp;

	auto CheckerSelColor = m_checkerBuildingOpions->GetSelectionColor();

	size_t k = 0;//Variable to use in checkers array

	for (size_t i = 0; i < 8; i++)
	{
		m_board[i] = new Cell[8];

		for (size_t j = 0; j < 8; j++)
		{
			positionTemp = m_Board_position + Vector<ushort>(j * Cellwidth, i * Cellheight);

			*(m_board[i] + j) = Cell(Cellwidth, Cellheight,
				whiteBlack == true ? CellWhiteColor : CellBlackColor,
				CellBorderColor,
				focusColor, CellBorderHighlightColor,
				positionTemp, whiteBlack);

			if (!m_board[i][j].IsWhite())
			{
				//Main function of checkers deploy
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

	//Initialize AI Module
	if (m_use_AI)
		m_ai->Initialize_AI_Variables(m_boardWidth, m_boardHeight, m_Board_position, m_checkers,
			m_board, Cellheight);
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

void game_engine_core::GameController::SetDifficulty(const game_engine_core::ai_modules::difficulty_level& diff)
{
	if (m_use_AI)
		m_ai->Set_Difficulty(diff);
}

void game_engine_core::GameController::HighLightPossibleTurns(bool whiteBlack)
{
	if (Main_Game_logic::m_use_AI && !whiteBlack)
	{
		m_selectedRouts.Iterate([](Cell* ptr)->bool { ptr->HighlightBorder(); return true; });

		//return;
	}

	m_possibleTurns.Iterate([](Cell* ptr)->bool { ptr->HighlightBorder(); return true; });

	system("CLS");

	Draw();
}

bool game_engine_core::GameController::IsGameOver(bool& winner)
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
	CellBuildingOptions* cboptr = m_cellBuildingOptions;

	m_selectedChecker->UnFocus();

	m_possibleTurns.Iterate([cboptr](Cell* cell)->bool
		{
			cell->UnHighLightBorder();
			cell->SetBorderHighlightColor(cboptr->GetBorderHighlightColor());
			cell->DeSelectMove();
			cell->UnFocus();

			return true;
		});

	m_selectedRouts.Iterate([cboptr](Cell* cell) -> bool { cell->SetBackColor(cell->IsWhite() ? cboptr->GetWhiteColor() :
		cboptr->GetBlackColor());

	cell->UnHighLightBorder();

	return true;
		});
}

void game_engine_core::GameController::Move()
{
	size_t selRoutsCount = this->m_selectedRouts.GetCount();

	auto chToBeKilledPtr = &m_checkersToBeKilled;

	const auto& boardPos = m_Board_position;

	const auto& boardWidth = m_boardWidth;

	Checker* selCheckerPtr = m_selectedChecker;

	//Fighting

	//Ordinary fightting


	m_selectedRouts.Iterate([selCheckerPtr, chToBeKilledPtr, boardPos, boardWidth](Cell* cell)->bool
		{
			if (cell == nullptr)
			{
				return true;
			}

			auto Sel_pos = cell->GetPosition();//Take 1 selected position
			//Calculate direction vector from slected checker position to selected cell position
			auto MoveDir = Sel_pos - selCheckerPtr->GetPosition();
			//Move selected checker to selected cell position
			selCheckerPtr->SetPosition(Sel_pos);

			if (chToBeKilledPtr->isEmpty())
			{
				return false;
			}

			//Find vector colinear to one of the Dir vectors
			size_t dirVectorsCount = std::size(m_dirVectors);

			Vector<short> colinearToDirection = Vector<short>(0, 0);

			Vector<short> diff;

			for (size_t i = 0; i < dirVectorsCount; i++)
			{
				if (m_dirVectors[i].IsCoDirectional(MoveDir.Convert_To(value_convertion::Converters::USHORT_TO_SHORT)))
				{
					colinearToDirection = m_dirVectors[i];

					break;
				}
			}

			if (colinearToDirection != Vector<short>(0, 0))
			{
				diff = selCheckerPtr->GetPosition().
					Convert_To(value_convertion::Converters::USHORT_TO_SHORT)
					- colinearToDirection;
			}

			//Iterate all posible checkers for kill
			chToBeKilledPtr->Iterate([diff,
				boardPos, boardWidth](Checker* ch)->bool
				{
					if (diff.Convert_To(value_convertion::Converters::SHORT_TO_USHORT) == ch->GetPosition())
					{
						ch->Kill();

						ch->SetPosition(Vector<ushort>(boardPos[0] + boardWidth + 10, 2));
					}
					return true;
				}

			);
			return true;
		});


	//Determine Damka
	if (!m_selectedChecker->IsDamka())
	{
		if (m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] <= m_Board_position["Y"])//White Checker
		{
			m_selectedChecker->MakeDamka();
		}
		else if (!m_selectedChecker->IsCheckerWhite() && m_selectedChecker->GetPosition()["Y"] >= m_Board_position["Y"] + m_boardHeight - m_cellBuildingOptions->GetCellHeight())
		{
			m_selectedChecker->MakeDamka();
		}
	}
}

void game_engine_core::GameController::SelectMove(bool whiteBlack, std::function<void()> PrintFunc,
	std::function<void()> PrintConfirmFunc)
{
	if (Main_Game_logic::m_use_AI && !whiteBlack)
	{
		return;
	}

	if (m_possibleTurns.GetCount() == 0)
		return;

	char* cptr = m_controls;

	char input;

	int start = 0;

	size_t end = m_possibleTurns.GetCount();

	Cell* ptr = nullptr;

	WORD prevColor;

	auto cboptr = m_cellBuildingOptions;

	auto MoveSelectionColor = m_cellBuildingOptions->GetMoveSelectColor();

	auto BorderHighLightColor = m_cellBuildingOptions->GetBorderHighlightColor();

	do
	{
		do
		{
			ptr = m_possibleTurns[start];

			ptr->Focus();

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
				if (ptr->isFocused())
					ptr->UnFocus();

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
				if (!ptr->IsMoveSelected())
				{
					ptr->SelectMove();

					ptr->SetBorderHighlightColor(MoveSelectionColor);

					m_selectedRouts.AddToTheEnd(ptr);
				}
				else
				{
					ptr->DeSelectMove();

					ptr->SetBorderHighlightColor(BorderHighLightColor);

					m_selectedRouts.RemoveNode(ptr);
				}
			}
			else if (input == cptr[4] || input == std::toupper(cptr[4]))//Confirm Pressed
			{
				break;
			}

			if ((m_multipleTakes <= 0) && ptr->IsMoveSelected())//true -> break
			{
				break;
			}
			else if (IsAllPossibleTurnsSelected() && m_multipleTakes > 0)
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
			m_possibleTurns.Iterate([cboptr, BorderHighLightColor](Cell* cell)->bool
				{
					cell->SetBackColor(cell->IsWhite() ? cboptr->GetWhiteColor() : cboptr->GetBlackColor());

					cell->SetBorderHighlightColor(BorderHighLightColor);

					return true;
				});

			m_selectedRouts.Iterate([](Cell* cell)-> bool
				{
					cell->DeSelectMove();

					return true;
				}
			);

			m_selectedRouts.Clear();
		}

	} while (!(input == cptr[3] || input == std::toupper(cptr[3])));

}

void game_engine_core::GameController::Draw()
{
	this->DrawBoard(m_board, 8, 8);

	this->DrawCheckers(m_checkers, m_checkersCount);
}

game_engine_core::GameController* game_engine_core::GameController::Initialize(console_graphics_utility* utility,
	Vector<ushort> controllerPosiion, CellBuildingOptions* cellbuildingOptions,
	CheckerBuildingOptions* checkerBuildingOptions, ai_modules::checker_ai* ai_module)
{
	if (!m_init)
	{
		static GameController gc(utility, controllerPosiion, cellbuildingOptions,
			checkerBuildingOptions, ai_module);

		m_init = true;

		return &gc;
	}
}

void game_engine_core::GameController::SelectChecker(bool whiteblack, std::function<void()> PrintFunc,
	std::function<void()> PrintConfirmFunc)

{
	using namespace nonlinear_data_structures::graph_math;

	using namespace linear_data_structures;

	if (m_use_AI && !whiteblack)//Selection made by AI
	{		
		system("CLS");

		this->Draw();

		auto sel_turn = m_ai->SelectPossibleTurn(whiteblack);

		auto prev = sel_turn.Get_Prev_Dictionary();

		auto end_points = sel_turn.GetEndPoints();

		size_t end_point_count = end_points.size();

		std::vector<Vector<short>> path; 

		if (sel_turn.GetTakesCount() > 0)//need to find the longest path for attacking sequence
		{			
			size_t length_current = 0;
			
			std::map<size_t, std::vector<Vector<short>>> temp;

			for (size_t i = 0; i < end_point_count; i++)
			{
				path = shortest_path_problem<Vector<short>>::reconstruct_path(sel_turn.GetStart(), 
					end_points[i], prev, Vector<short>());

				temp.emplace(path.size(), path);
			}

			size_t size = temp.size();

			size_t i = 0;

			auto start = temp.begin();

			auto end = temp.end();

			while (start != end)
			{
				if (i == size - 1)
				{
					path = start->second;

					break;
				}

				start++;

				i++;
			}
		}
		else
		{
			path = shortest_path_problem<Vector<short>>::reconstruct_path(sel_turn.GetStart(),
				sel_turn.GetEndPoints()[std::rand() % end_point_count], prev, Vector<short>());			
		}
		
		if (path.size() > 0)//path was found
		{
			for (auto v : path)
			{
				m_selectedRouts.AddToTheEnd(FindCellUsingPosition(v));
			}
		}

		sel_turn.GetCheckersToBeKilled_Coord().Iterate(
			[this](Vector<short> elem)->bool
			{
				m_checkersToBeKilled.AddToTheEnd(FindCheckerUsingPosition(elem, m_checkers, m_checkersCount));

				return true;
			}
		);

		m_ai->Reset_Data();

		return;
	}

	if (m_selectedChecker != nullptr)
		if (m_selectedChecker->isFocused())
			m_selectedChecker->UnFocus();

	char* cptr = m_controls;

	char input;

	int index = 0;

	int start;

	int end;

	int mid = (m_checkersCount / 2) - 1; //11	

	Checker* temp = nullptr;

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
			temp = m_checkers + index;

			while (!temp->isAlive())//Manual shifting
			{
				index += 1;

				if (index < start)
					index = end;
				else if (index > end)
					index = start;

				temp = m_checkers + index;
			}

			m_selectedChecker = m_checkers + index;

			m_selectedChecker->Focus();

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
				if (m_selectedChecker->isFocused())
					m_selectedChecker->UnFocus();

			if (index < start)
				index = end;
			else if (index > end)
				index = start;

			temp = m_checkers + index;

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
			if (!m_selectedChecker->isFocused())
				m_selectedChecker->Focus();

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

bool game_engine_core::GameController::m_init = false;

#pragma endregion

#pragma endregion

#pragma region CellBuildingOptions

#pragma region Ctor

game_engine_core::CellBuildingOptions::CellBuildingOptions(
	WORD BlackColor,
	WORD WhiteColor, WORD borderColor, WORD borderHighlightColor, WORD focusColor,
	WORD border_Selection_Color,
	ushort width, ushort height) :
	m_cellWidth(width), m_cellHeight(height), m_blackColor(BlackColor), m_whiteColor(WhiteColor),
	m_borderColor(borderColor), m_FocusColor(focusColor),
	m_BorderHighlightColor(borderHighlightColor),
	m_MoveSelectColor(border_Selection_Color)
{}

game_engine_core::CellBuildingOptions::CellBuildingOptions(ushort width, ushort height) :
	CellBuildingOptions(console_graphics::Colors::BLACKBack,
		console_graphics::Colors::WhiteBack, console_graphics::Colors::BLACK |
		console_graphics::Colors::LIGHTGRAYBack, console_graphics::Colors::GREENBack,
		console_graphics::Colors::ORANGEBack, console_graphics::Colors::ORANGEBack | console_graphics::Colors::BLACK,
		width, height) {}

#pragma endregion

const WORD& game_engine_core::CellBuildingOptions::GetMoveSelectColor() const
{
	return m_MoveSelectColor;
}

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

const WORD& game_engine_core::CellBuildingOptions::GetFocusColor() const
{
	return m_FocusColor;
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




