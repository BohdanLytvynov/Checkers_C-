#ifndef GAMEENGINE_H

#define GAMEENGINE_H

typedef unsigned short ushort;

#include"v_math.h"
#include"Console_graphics.h"

namespace game_engine_core
{
	using namespace vector_math;
	using namespace console_graphics;

	struct GameObject
	{		
		GameObject(const ushort& m_width, const ushort& m_height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw, size_t charsToDrawSize);

		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;

		GameObject& operator = (const GameObject& other) = delete;

		void virtual Render(console_graphics_utility &utility) = 0;

#pragma region Getters

		ushort GetWidth() const;

		ushort GetHeight() const;

		ushort GetBackColor() const;

		ushort GetBorderColor() const;

		vector<ushort> GetPosition() const;

		const char* GetChars() const;
		
		virtual bool isSelected() const;

#pragma endregion

#pragma region Setters

		void SetWidth(ushort width);

		void SetHeight(ushort height);

		void SetBackColor(const WORD &backColor);

		void SetBorderColor(const WORD& foreColor);

		void SetPosition(const vector<ushort> &v);
		
		//void SetChars(char* chars);

		virtual void Select();

		virtual void Deselct();

#pragma endregion


	private:

		char* m_chars;

		size_t m_charsToDrawSize;

		WORD m_backGround;

		WORD m_border;

		vector<ushort> m_position;

		ushort m_width;

		ushort m_height;

		bool m_selected;			
	};
	
	struct Killable : public GameObject
	{
		Killable(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw, size_t charsToDrawSize);

		virtual bool isAlive() const;

		virtual void Kill();

		private:

		bool m_alive;
	};

	struct Cell : public GameObject
	{
		Cell(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		void Render(console_graphics_utility& utility) override;
	};

	struct Checker : public Killable
	{
		void Render(console_graphics_utility& utility) override;
	};
}



#endif // !GAMEENGINE_H

