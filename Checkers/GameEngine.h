#ifndef GAMEENGINE_H

#define GAMEENGINE_H

typedef unsigned short ushort;

#include"v_math.h"
#include"Console_graphics.h"
#include"DataStructures.h"

namespace game_engine_core
{	
	using namespace vector_math;
	using namespace console_graphics;

	struct GameObject
	{		
		GameObject();

		GameObject(const ushort& width, const ushort& height, const WORD& backGround,	
			const WORD& selColor, 
			vector<ushort> position, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		virtual ~GameObject();
		
		GameObject(const GameObject& other);

		GameObject& operator = (const GameObject& other);

		void virtual Render(console_graphics_utility &utility) = 0;

#pragma region Getters

		ushort GetWidth() const;

		ushort GetHeight() const;

		WORD GetBackColor() const;
		
		vector<ushort> GetPosition() const;

		char* GetChars() const;

		size_t GetCharsToDrawSize() const;
		
		virtual bool isSelected() const;

		WORD GetSelectionColor() const;
			
#pragma endregion

#pragma region Setters

		void SetChars(char* chars);

		void SetWidth(ushort width);

		void SetHeight(ushort height);

		void SetBackColor(const WORD &backColor);
		
		void SetPosition(const vector<ushort> &v);
		
		void SetCharsToDrawSize(size_t size);

		virtual void Select();

		virtual void Deselct();

		void SetSelectionColor(WORD selColor);

#pragma endregion

	private:

		char* m_chars;

		size_t m_charsToDrawSize;

		WORD m_backGround;

		WORD m_selectionColor;
		
		vector<ushort> m_position;

		ushort m_width;

		ushort m_height;

		bool m_selected;			
	};
	
	struct Killable : public GameObject
	{
		Killable();

		Killable(const ushort& width, const ushort& height, const WORD& backGround,	
			const WORD& selColor,
			vector<ushort> position, char* charsToDraw, size_t charsToDrawSize);

		Killable(const Killable& other);		

		Killable& operator =(const Killable& other);

		virtual bool isAlive() const;

		virtual void Kill();

		virtual void Render(console_graphics_utility& utility) = 0;

		private:

		bool m_alive;
	};

	struct IObjectWithBorder
	{
		virtual WORD GetBorderColor() const = 0;

		virtual void SetBorderColor(const WORD& foreGroundColor) = 0;
	};

	struct IBorderHighLightable
	{
		virtual const WORD& GetBorderSelectionColor() const = 0;

		virtual void SetBorderSelectionColor(const WORD& borderSelColor) = 0;

		virtual void HighlightBorder() = 0;

		virtual void UnHighLightBorder() = 0;
	};

	struct Cell : public GameObject, public IObjectWithBorder, public IBorderHighLightable
	{
		Cell();

		Cell(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border, const WORD& selColor, const WORD& bordeHighlightColor,
			vector<ushort> position, bool isWhite, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		void Render(console_graphics_utility& utility) override;

		Cell(const Cell& other);

		Cell& operator = (const Cell& other);

		bool IsWhite() const;

#pragma region IObject with border Interface

		WORD GetBorderColor() const override;

		void SetBorderColor(const WORD& borderColor) override;

#pragma endregion

#pragma region IBorder Highlightable Interface

		const WORD& GetBorderSelectionColor() const override;

		void SetBorderSelectionColor(const WORD& borderSelColor) override;

		void HighlightBorder() override;

		void UnHighLightBorder() override;

#pragma endregion


	private:
		bool m_isWhite;

		WORD m_borderColor;

		WORD m_BorderHighlightColor;

		bool m_borderHighLight;
	};
	
	struct Checker : public Killable
	{
		Checker();

		Checker(const ushort& width, const ushort& height, const WORD& backGround, const WORD& selColor,			
			vector<ushort> position, bool isWhite, ushort HorBaseLength = 2, ushort VertBaseLength = 2,
			char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		Checker(const Checker& other);
		
		void Render(console_graphics_utility& utility) override;

		void MakeDamka();

		Checker& operator = (const Checker& other);

		bool IsCheckerWhite() const;

		bool IsDamka() const;

	private:
		ushort m_HorbaseLength;

		ushort m_VertBaseLength;

		bool m_isDamka;

		bool m_isWhite;		
	};

	struct CellBuildingOptions : public IObjectWithBorder
	{				
		CellBuildingOptions(ushort cellWidth = 10, ushort cellHeight = 6);

		CellBuildingOptions(WORD BlackColor,
			WORD WhiteColor, WORD borderColor, 
			WORD borderHighLightColor, WORD SelColor,
			ushort cellWidth = 10, ushort cellHeight = 6);

		const ushort& GetCellWidth() const;

		const ushort& GetCellHeight() const;

		const WORD& GetBlackColor() const;

		const WORD& GetWhiteColor() const;

		WORD GetBorderColor() const override;

		void SetBorderColor(const WORD& borderColor) override;

		const WORD& GetSelectionColor() const;

		const WORD& GetBorderHighlightColor() const;

	private:

		ushort m_cellWidth;

		ushort m_cellHeight;

		WORD m_blackColor;

		WORD m_whiteColor;

		WORD m_borderColor;

		WORD m_SelectionColor;

		WORD m_BorderHighlightColor;
	};

	struct CheckerBuildingOptions
	{		
		CheckerBuildingOptions();

		CheckerBuildingOptions(WORD whiteCheckerColor, WORD blackCheckerColor,	
			WORD selectionColor,
			ushort width = 10, ushort height = 6);
		
		const WORD& GetWhiteCheckerColor() const;

		const WORD& GetBlackCheckerColor() const;

		const WORD& GetSelectionColor() const;

		const ushort& GetCheckerWidth() const;

		const ushort& GetCheckerHeight() const;

	private:
		WORD m_blackCheckerColor;

		WORD m_whiteCheckerColor;

		WORD m_SelectionColor;

		ushort m_CheckerWidth;

		ushort m_CheckerHeight;

	};

	struct GameController
	{
	public:		
				
		void SelectChecker(bool whiteBlack, std::function<void()> PrintFunc = nullptr, 
			std::function<void()> PrintConfirmFunc = nullptr);
				
		void FindPossibleTurns();

		void HighLightPossibleTurns();

		void SelectMove(std::function<void()> PrintFunc = nullptr,
			std::function<void()> PrintConfirmFunc = nullptr
			);

		void Move();

		void Draw();

		void DeselectAllGameObjects();

		bool IsGameOver(bool &winner);

		static GameController* Initialize(console_graphics_utility* console_graphics_utility, 
			vector<ushort> controllerPosition, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions *checkerBuildingOptions);

		GameController(const GameController&) = delete;

		GameController& operator = (const GameController&) = delete;

	private:
		
		bool OutOfBorders(const vector<short> &position);

		bool IsAllPossibleTurnsSelected();		

		Cell* FindCellUsingPosition(const vector<short>& positionVector);

		Checker* FindCheckerUsingPosition(const vector<short>& positionVector);//??

		void FindPossibleTurnRecursive(const vector<short> &position, vector<short>& prevPosition, const vector<short>& dirVector = vector<short>(), bool multiKill = false);

		void DrawBoard();

		void DrawCheckers();

		GameController(console_graphics_utility *console_graphics_utility,
			vector<ushort> BoardPosiion, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions* checkerBuildingOptions);

		~GameController();
		
		ushort m_boardWidth;

		ushort m_boardHeight;

		linear_data_structures::single_linked_list<Checker*> m_checkersToBeKilled;

		linear_data_structures::single_linked_list<Cell*> m_possibleTurns;

		linear_data_structures::single_linked_list<Cell*> m_selectedRouts;

		console_graphics_utility* m_console_graphics_utility;

		char* m_controls;

		Cell** m_board;

		Checker* m_checkers;//Array that contains all of the checkers BLACK one at the start of the array,
		//White one from the middle to the end.

		Checker* m_selectedChecker;

		const size_t m_checkersCount = 24;

		static bool m_init;

		static signed char m_multipleMoves;		

		static vector<short> m_dirVectors [4];

		static vector<short> m_boardBasis[2];

		vector<ushort> m_Board_position;

		CellBuildingOptions* m_cellBuildingOptions;

		CheckerBuildingOptions* m_checkerBuildingOpions;

	};	
}



#endif // !GAMEENGINE_H

