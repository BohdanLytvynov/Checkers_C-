#include"pch.h"
#include"GameEngine.h"

#pragma region GameObject definitions

#pragma region Ctors

//char[5] {186, 201, 205, 187, 188}, 5

game_engine_core::GameObject::GameObject(const ushort& width, const ushort& height, const WORD& backGround,
	const WORD& border,
	vector<ushort> position, char* charsToDraw, size_t charsToDrawSize) :
	m_width(width), m_height(height), m_backGround(backGround), m_border(border),
	m_position(position), m_chars(charsToDraw), m_charsToDrawSize(charsToDrawSize),
	m_selected(false)
{}

game_engine_core::GameObject::~GameObject() 
{
	
}



#pragma endregion

#pragma region Getters

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

