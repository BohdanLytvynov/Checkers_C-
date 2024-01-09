#ifndef GAMEENGINE_H

#define GAMEENGINE_H

typedef unsigned short ushort;
#include<cstdlib>
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
			const WORD& focusColor, 
			Vector<ushort> position, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		virtual ~GameObject();
		
		GameObject(const GameObject& other);

		GameObject& operator = (const GameObject& other);

		void virtual Render(console_graphics_utility &utility) = 0;

#pragma region Getters

		ushort GetWidth() const;

		ushort GetHeight() const;

		WORD GetBackColor() const;
		
		Vector<ushort> GetPosition() const;

		char* GetChars() const;

		size_t GetCharsToDrawSize() const;
		
		virtual bool isFocused() const;

		WORD GetFocusColor() const;
			
#pragma endregion

#pragma region Setters

		void SetChars(char* chars);

		void SetWidth(ushort width);

		void SetHeight(ushort height);

		void SetBackColor(const WORD &backColor);
		
		void SetPosition(const Vector<ushort> &v);
		
		void SetCharsToDrawSize(size_t size);

		virtual void Focus();

		virtual void UnFocus();

		void SetFocusColor(WORD selColor);

#pragma endregion

	private:

		char* m_chars;//Контролює з яких символіів буде відмальована шашка (Покажчик)

		size_t m_charsToDrawSize;//Контролює розмір динам массиву чар

		WORD m_backGround;//Колір бєкграунд

		WORD m_focusColor;//Колір фокусування обєкта
		
		Vector<ushort> m_position;//Радіус вектор обєкта

		ushort m_width;//Ширина

		ushort m_height;//Висота

		bool m_focused;//Сфокусовано чи ні		
	};
	
	struct Killable : public GameObject
	{
		Killable();

		Killable(const ushort& width, const ushort& height, const WORD& backGround,	
			const WORD& selColor,
			Vector<ushort> position, char* charsToDraw, size_t charsToDrawSize);

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
		virtual const WORD& GetBorderHighlightColor() const = 0;

		virtual void SetBorderHighlightColor(const WORD& borderSelColor) = 0;

		virtual void HighlightBorder() = 0;

		virtual void UnHighLightBorder() = 0;
	};
	
	struct Cell : public GameObject, public IObjectWithBorder, 
		public IBorderHighLightable
	{
		Cell();

		Cell(const ushort& width, const ushort& height, const WORD& backGround,
			const WORD& border, const WORD& focusColor, const WORD& bordeHighlightColor,			
			Vector<ushort> position, bool isWhite, char* charsToDraw = nullptr, size_t charsToDrawSize = 0);

		void Render(console_graphics_utility& utility) override;

		Cell(const Cell& other);

		Cell& operator = (const Cell& other);

		bool IsWhite() const;

		bool IsMoveSelected() const;

		void SelectMove();

		void DeSelectMove();

#pragma region IObject with border Interface

		WORD GetBorderColor() const override;

		void SetBorderColor(const WORD& borderColor) override;

#pragma endregion

#pragma region IBorder Highlightable Interface

		const WORD& GetBorderHighlightColor() const override;

		void SetBorderHighlightColor(const WORD& borderSelColor) override;

		void HighlightBorder() override;

		void UnHighLightBorder() override;

#pragma endregion

	private:
		bool m_isWhite;

		WORD m_borderColor;

		WORD m_BorderHighlightColor;

		bool m_borderHighLight;

		bool m_Move_Selected;
	};
	
	struct Checker : public Killable
	{
		Checker();

		Checker(const ushort& width, const ushort& height, const WORD& backGround, const WORD& selColor,			
			Vector<ushort> position, bool isWhite, ushort HorBaseLength = 2, ushort VertBaseLength = 2,
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
			WORD borderHighLightColor, WORD FocusColor, WORD sel_BorderColor,
			ushort cellWidth = 10, ushort cellHeight = 6);

		const ushort& GetCellWidth() const;

		const ushort& GetCellHeight() const;

		const WORD& GetBlackColor() const;

		const WORD& GetWhiteColor() const;

		WORD GetBorderColor() const override;

		void SetBorderColor(const WORD& borderColor) override;

		const WORD& GetFocusColor() const;

		const WORD& GetBorderHighlightColor() const;

		const WORD& GetMoveSelectColor() const;

	private:

		ushort m_cellWidth;

		ushort m_cellHeight;

		WORD m_blackColor;

		WORD m_whiteColor;

		WORD m_borderColor;

		WORD m_FocusColor;

		WORD m_BorderHighlightColor;

		WORD m_MoveSelectColor;
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
	
	struct Main_Game_logic
	{	
#pragma region Ctor

		Main_Game_logic(console_graphics_utility* cgu);

		Main_Game_logic() {}

#pragma endregion

		Vector<short> FindOrthogonalVector(const Vector<short>& v) const;

		void FindAllPosibleTurnsForKingRecursive(Checker* selectedChecker, const Vector<short>& position,
			Vector<short>& prevPosition, Checker* checkers, size_t checkers_count,
			bool& onCallback, const Vector<short>& dirVector = Vector<short>(),
			bool checker_under_attack = false);

		void FindPossibleTurns(bool whiteBlack = true, std::function<void(Vector<short> position, Vector<short> PrevPos, bool multiKill)> func = nullptr);

		bool OutOfBorders(const Vector<short>& position);

		bool IsAllPossibleTurnsSelected();

		Cell* FindCellUsingPosition(const Vector<short>& positionVector);

		Checker* FindCheckerUsingPosition(const Vector<short>& positionVector, Checker* checkers,
			size_t checkers_count);//??

		void FindPossibleTurnRecursive(Checker* selectedChecker, const Vector<short>& position, 
			Vector<short>& prevPosition, Checker* checkers, size_t checkers_count,
			const Vector<short>& dirVector = Vector<short>(),
			bool multiKill = false, std::function<void(Vector<short> prev_position,
				Vector<short> current_position, bool multiKill)> func = nullptr);

		void DrawBoard(Cell** board, size_t rows_count, size_t colums_count);

		void DrawCheckers(Checker* checkers, size_t checkers_count);

		void Reset_Game_Logic_State();

#pragma region Checker Board
			
	protected:
		ushort m_boardWidth;

		ushort m_boardHeight;

		static Vector<short> m_dirVectors[4];

		static Vector<short> m_boardBasis[2];

		Vector<ushort> m_Board_position;
		
		Checker* m_checkers;//Array that contains all of the checkers BLACK one at the start of the array,
		//White one from the middle to the end.

		Checker* m_selectedChecker;

		const size_t m_checkersCount = 24;

		Cell** m_board;

		console_graphics_utility* m_console_graphics_utility;

		bool m_use_AI;

#pragma endregion
		
#pragma region Calculations of Turns

		static signed char m_multipleTakes;

#pragma endregion

#pragma region Additional Collections

		linear_data_structures::single_linked_list<Checker*> m_checkersToBeKilled;

		linear_data_structures::single_linked_list<Cell*> m_possibleTurns;

		linear_data_structures::single_linked_list<Cell*> m_selectedRouts;

#pragma endregion		
	};

	namespace ai_modules
	{
		enum difficulty_level
		{
			easy = 0, //Random move selection or selection of a best take move 
			medium, //selection of best take move, using Mini Max for other moves depth = 2
			hard//selection of best take move, using Mini Max for other moves depth = 3
		};

		template<class T>
		struct turn
		{
			turn(T start) : m_start(start), m_Takes(0), m_eur_value(0), m_mini_max_used(false) 
			{ m_current_id = m_id++; }

			turn() {}

			turn(const turn<T>& other)
			{
				this->m_current_id = other.m_current_id;

				this->m_CheckersToBeKilledCoords = other.m_CheckersToBeKilledCoords;

				this->m_ends = other.m_ends;

				this->m_eur_value = other.m_eur_value;

				this->m_mini_max_used = other.m_mini_max_used;

				this->m_prev_dictionary = other.m_prev_dictionary;

				this->m_start = other.m_start;

				this->m_Takes = other.m_Takes;

				this->m_1KillPosition = other.m_1KillPosition;
			}

			turn<T>& operator = (const turn<T>& other)
			{
				this->m_current_id = other.m_current_id;

				this->m_CheckersToBeKilledCoords = other.m_CheckersToBeKilledCoords;

				this->m_ends = other.m_ends;

				this->m_eur_value = other.m_eur_value;

				this->m_mini_max_used = other.m_mini_max_used;

				this->m_prev_dictionary = other.m_prev_dictionary;

				this->m_start = other.m_start;

				this->m_Takes = other.m_Takes;

				this->m_1KillPosition = other.m_1KillPosition;

				return *this;
			}

			~turn() { m_ends.clear(); m_CheckersToBeKilledCoords.Clear(); }
			
			Vector<short> GetFirstKillPosition()
			{
				return m_1KillPosition;
			}

			void SetFirstKillPosition(Vector<short> first_kill_Position)
			{
				m_1KillPosition = first_kill_Position;
			}

			void AddEnd(T end)
			{
				m_ends.push_back(end);
			}

			void AddCheckerToBeKilled_Coord(T checker_for_kill_Coord)
			{
				m_CheckersToBeKilledCoords.AddToTheEnd(checker_for_kill_Coord);
			}

			void Set_Prev_Dictionary(const std::map<T, T>& prev_dictionary)
			{
				m_prev_dictionary = prev_dictionary;
			}

			void Set_CountOfTakes(size_t takes_count)
			{
				m_Takes = takes_count;
			}

			void Set_Eur_Value(size_t eurValue)
			{
				m_mini_max_used = true;

				m_eur_value = eurValue;
			}

			bool Mini_Max_Used() const
			{
				return m_mini_max_used;
			}

			const size_t& GetTakesCount()
			{
				return m_Takes;
			}

			const size_t& GetEurValue()
			{
				return m_eur_value;
			}

			const size_t& Getid()
			{
				return m_current_id;
			}

			const std::map<T, T>& Get_Prev_Dictionary() const
			{
				return m_prev_dictionary;
			}

			const std::vector<T>& GetEndPoints() const
			{
				return m_ends;
			}

			const T& GetStart() const
			{
				return m_start;
			}

			const linear_data_structures::single_linked_list<T>& GetCheckersToBeKilled_Coord() const
			{
				return m_CheckersToBeKilledCoords;
			}
#pragma region Operators

			bool operator == (const turn<T>& other)const
			{
				return this->m_current_id == other.m_current_id;
			}

			bool operator != (const turn<T>& other) const
			{
				return this->m_current_id != other.m_current_id;
			}

#pragma endregion


		private:
			std::vector<T> m_ends;

			std::map<T, T> m_prev_dictionary;

			T m_start;//Checkers coords

			static size_t m_id;

			size_t m_current_id;

			size_t m_Takes;

			size_t m_eur_value;

			bool m_mini_max_used;

			linear_data_structures::single_linked_list<T> m_CheckersToBeKilledCoords;

			Vector<short> m_1KillPosition;
		};

		template<class T>
		size_t game_engine_core::ai_modules::turn<T>::m_id = 0;

		struct checker_ai : public Main_Game_logic
		{		
			checker_ai(console_graphics_utility* cgu);

#pragma region Init
			void Initialize_AI_Variables(ushort board_Width, ushort board_Height,
				Vector<ushort> board_Position, Checker* checkers, Cell** board,
				ushort Cell_height);
#pragma endregion
			game_engine_core::ai_modules::turn<vector_math::Vector<short>> SelectPossibleTurn(bool whiteBlack);
			
			Checker* DeepBoardCopy(Checker* checkers, size_t checkers_countcount);

			void BuildGameTreeRecursive(Checker* current_checker, Checker* prev_checker, bool whiteBlack,
				size_t depth, size_t current_depth, Checker* board_copy, size_t checkers_count,bool init = false);

			void Move(Vector<ushort> selPosition);

			int FindEuristicValue(Checker* board);

			void Set_Difficulty(const difficulty_level& diff);
						
			void ClearPossible_Calculated_Turns();

			size_t GetMaxTakesCount();

			void Reset_Data();

		private:
			//bool who_is_AI;//true - white false - black//May be we use it later now Black Player is AI

			difficulty_level m_difficulty;

			nonlinear_data_structures::edge_list_graph<Vector<ushort>> m_game_tree;

			linear_data_structures::single_linked_list<linear_data_structures::key_value_pair<Vector<short>, int>> m_eur_ValueTable;
			
			ushort m_Cell_Height;

			Vector<ushort> m_Prev_Checker_Temp;

			linear_data_structures::single_linked_list<turn<Vector<short>>> m_Possible_Calculated_Turns;
						
			linear_data_structures::single_linked_list<Vector<short>> m_CheckersToBeKilledCoords;

			int m_id_of_max_takes;

			size_t m_max_takes;					
		};
	}
			
	struct GameController : public Main_Game_logic
	{
		void SetDifficulty(const game_engine_core::ai_modules::difficulty_level& diff);

		void SelectChecker(bool whiteBlack, std::function<void()> PrintFunc = nullptr, 
			std::function<void()> PrintConfirmFunc = nullptr);
						
		void HighLightPossibleTurns(bool whiteBlack);

		void SelectMove(bool whiteBlack = true,std::function<void()> PrintFunc = nullptr,
			std::function<void()> PrintConfirmFunc = nullptr
			);

		void Move();

		void Draw();

		void DeselectAllGameObjects();

		bool IsGameOver(bool &winner);

		static GameController* Initialize(console_graphics_utility* console_graphics_utility, 
			Vector<ushort> controllerPosition, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions *checkerBuildingOptions, 
			ai_modules::checker_ai* ai_module = nullptr);

		GameController(const GameController&) = delete;

		GameController& operator = (const GameController&) = delete;

	private:
				
		ai_modules::checker_ai* m_ai;
						
		GameController(console_graphics_utility *console_graphics_utility,
			Vector<ushort> BoardPosiion, CellBuildingOptions* cellbuildingOptions,
			CheckerBuildingOptions* checkerBuildingOptions, 
			ai_modules::checker_ai* ai_module = nullptr);

		~GameController();
								
		char* m_controls;
		
		static bool m_init;
						
		CellBuildingOptions* m_cellBuildingOptions;

		CheckerBuildingOptions* m_checkerBuildingOpions;
	};	
}

#endif // !GAMEENGINE_H

