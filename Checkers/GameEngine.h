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
		GameObject();

		GameObject(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		virtual ~GameObject();

		//virtual void Initialize(const GameObject &other);

		GameObject(const GameObject& other);

		GameObject& operator = (const GameObject& other);

		void virtual Render(console_graphics_utility &utility) = 0;

#pragma region Getters

		ushort GetWidth() const;

		ushort GetHeight() const;

		WORD GetBackColor() const;

		WORD GetBorderColor() const;

		vector<ushort> GetPosition() const;

		char* GetChars() const;

		size_t GetCharsToDrawSize() const;
		
		virtual bool isSelected() const;

#pragma endregion

#pragma region Setters

		void SetChars(char* chars);

		void SetWidth(ushort width);

		void SetHeight(ushort height);

		void SetBackColor(const WORD &backColor);

		void SetBorderColor(const WORD& foreColor);

		void SetPosition(const vector<ushort> &v);
		
		void SetCharsToDrawSize(size_t size);

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
		Killable();

		Killable(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw, size_t charsToDrawSize);

		Killable(const Killable& other);		

		Killable& operator =(const Killable& other);

		virtual bool isAlive() const;

		virtual void Kill();

		virtual void Render(console_graphics_utility& utility) = 0;

		private:

		bool m_alive;
	};

	struct Cell : public GameObject
	{
		Cell();

		Cell(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		void Render(console_graphics_utility& utility) override;

		Cell(const Cell& other);

		Cell& operator = (const Cell& other);
	};

	struct Checker : public Killable
	{
		Checker();

		Checker(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border,
			vector<ushort> position, ushort HorBaseLength = 2, ushort VertBaseLength = 2,
			char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		Checker(const Checker& other);
		
		void Render(console_graphics_utility& utility) override;

		void MakeDamka();

		Checker& operator = (const Checker& other);

	private:
		ushort m_HorbaseLength;

		ushort m_VertBaseLength;

		bool m_isDamka;
	};

	struct CellBuildingOptions
	{				
		CellBuildingOptions(ushort cellWidth, ushort cellHeight);

		CellBuildingOptions(ushort cellWidth, ushort cellHeight, WORD BlackColor,
			WORD WhiteColor);

		const ushort& GetCellWidth() const;

		const ushort& GetCellHeight() const;

		const WORD& GetBlackColor() const;

		const WORD& GetWhiteColor() const;

	private:
		ushort m_cellWidth;

		ushort m_cellHeight;

		WORD m_blackColor;

		WORD m_whiteColor;
	};

	struct CheckerBuildingOptions
	{		
		CheckerBuildingOptions();

		CheckerBuildingOptions(WORD whiteCheckerColor, WORD blackCheckerColor);

		const WORD& GetBlackCheckerColor() const;

		const WORD& GetWhiteCheckerColor() const;

	private:
		WORD m_blackCheckerColor;

		WORD m_whiteCheckerColor;
	};

	struct GameController
	{
	public:		
		void DrawBoard();
		
		static GameController* Initialize(console_graphics_utility* console_graphics_utility, 
			vector<ushort> controllerPosition, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions *checkerBuildingOptions);

		GameController(const GameController&) = delete;

		GameController& operator = (const GameController&) = delete;

	private:
		GameController(console_graphics_utility *console_graphics_utility,
			vector<ushort> BoardPosiion, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions* checkerBuildingOptions);

		~GameController();
		
		console_graphics_utility* m_console_graphics_utility;

		Cell** m_board;

		static bool m_init;

		vector<ushort> m_position;

		CellBuildingOptions* m_cellBuildingOptions;

		CheckerBuildingOptions* m_checkerBuildingOpions;
	};	
}



#endif // !GAMEENGINE_H

