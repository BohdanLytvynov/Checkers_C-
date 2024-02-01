# Checkers the game. 
  This project was created to enhance my coding and algorithm skills. It is fully written in C++. And all the implementation are done in console manualy.
I have used here a custom **Vector math library** and a **custom data structures library**. I understand that better implementations of them can be found in standart libraries but I want
to practice and improve my coding skills. 

  This project consists of header files and source files. I used this technic to make my code more readable. 
  
As Checkers is a complex game, that requires a lot of functionality and abilities for players. Players should have an opportunities to select and move pieces. To resolve all this cases 
it is better to use **OOP aproach**. The main concepts of it are: 

- **Encapsulation**
- **Inheritance** 
- **Polymorphism**. (Сan be static or dynamic). 

I have used all of it in my project.

  **Encapsulation** was used in different objects to provide a safe access to the class invariant. Also it is a hiding of some function realization from the user of the object.
  
  Using **Inheritance** I have made a Cell class and Checker class. With a help of dynamic **Polymorphism** and **Inheritance** I provided the render system for each object. By overriding
the initial virtual function of the first base class Gameobject, I have an opportunity to determine how I want to render a certain object in a console. For example Cells of 
the checkers board are rendered like a rectangles with borders. Checkers and Kings must be rendered in another way. And to control this I need only to override the function 
render() in each class. And using pointer to base class I can call the propriate render() function for each object. It saves a lot of time and makes code more reusable.

  As I mentioned I used rendering functions. For rendering different objects I created the **ConsoleUiGraphicsCotroller**. Here I used the design pattern that is called the **Singleton**.
It means that we only can have one instance of our object in whole our programm. So I thought that we should have only one Console UI Controller.
The Same pattern was used for **GameController** the main class that manages the game process.

  To manage the game process I needed some **Vector math**. And here I used **static Polymorphism(template classes)** and **Inheritance**. I created **Vector math library** to make it to work.
I used various types of Vector math operations in this project. I chose the Vector object to describe the current position of my piece. The start point of the position Vector for 
every object is in the origin of the global coordinate system. For 2D apps like in our case it is the Upper left Corner of the console window. To prevent some rendering artifacts 
I made the console to open in a full screen mode. When the board with checkers are initialized in a **Game Controller** the propriate position Vectors have already been set and the 
GameController object draws each object in a certain position using the origin offset. Also by subtracting two position Vectors we can find out the move direction vector.
And more Vector calculus functions is used when it comes to taking an other pieces. This was my **short Overview** of this project. And now we can dive deeper in its logic.

## More detailed View.
First of all lets find out what kind of game **Checkers** is. It is a game where a special board is used. Also we have pieces on the board. We should be able to move pices in four directios. All of them we can describe using 4 Vectors. When the piece comes to an opposite side of the board it should be transformed into the new object? called **King**. And the King has much more movement opportunities in comparison with ordinary piece or checker. There is a game cycle in all games. Games are a cyclic system. Lets determine what kind of cycle we should implement for our game.
- **Game Cycle**:
	- Select piece.
   	- Find all possible moves for the selected piece.
   	- By interaction with our primitive graphic UI class highlight the possible turns.
   	- User must select the propriate move.
   	- Perform move.
   	- Reset all UI for next turn.
   	- Check the condition when game can be finished with some results:
   	  	- One of the users is going to becaome a winner and other one - loser.
   	  	- No winners, no losers.
And all this game cycles parts will repeat until game will finish.

Also I would like to say a few words about general approach. I have some experience with game engines, and I tried to establish their approach in building games. 
According to this concept all our game is a system. System consists of many modules, that have some functions. And also we have some connections between all this modules. To establish it, as I said earlier, we need to use **OOP**. The main idea is that while game is played the state or invariant of all our objects in a system changes. And after that render system redraws the UI part of the game. In next part we will see the structure of our system.

## Structure
First lets take a look at our main structures that are used in this game. All of their declarations are situated in [**GameEngine.h**](https://github.com/BohdanLytvynov/Checkers_C-/blob/main/Checkers/GameEngine.h) header file. I prefere to use structures against classes. The first structure is the **GameObject** it is a base structure for **Pieces** and **Cells of the board**. Lets look at what behavior and state it has. 

**GameObject** **state** variables must include the next values:
- Size of the object. (Width and Height)
- Position of the object. Here we can use Vector to describe it's global position.
- Chars that will be used to draw the object in the console. Here I used the pointer to array of chars. The pointer doesn't know anything about the size of the array? so we need the unsigned variable to store the count of chars in our array.
- Additional variable to control focus system.
  
**GameObject behaviors**:
  To my mind we can give it oly one behavior and it is Focus behavior. What is it? Focus, from my point of view, is changing the visual appearence of the object, when some events takes place. In our case it can be the selection of the piece by the user. Later we will use the 2 dim array to store cells in our game. It means that we will deal with a copying and an assignment. Since the 2 dim. array will initialize all it's objects, and also for this we need **empty default constructor**. the fact that we will use copying requires the **Copy Constructor** and **Assignment operator**. Furthermore each our object can have an opportunity to be rendered in a console. To provide it I made the virtual abstract function **Render()**. By doing this GameObject structure became **abstract**. Using virtualization and pointers we can draw different objects by calling only one similar function **Render()**. It is a key concept of **Dynamic Polymorphism** Ok, it is enough for the base class.

As our game will contain takes, we need to establish this behavior. Not all the **GameObjects** must be taken in our game. This opportunity must have only **Pieces** and **Kings**. I decided to use **Inheritance** for this. I expanded **GameObject** structure with **Killable** and provided there new state, such as bool field that determine wether Object is dead or not. If the current Object is dead it can't interact with other objects, and it is prevented from rendering. We don't know for sure what is **Killable** for now, so I made this object abstaract too.

Now things comes more interesting. Lets take a look at **Cell**. Our playing field or the Board consists of pointers to Cells. As I mentioned we will store it in a 2 dim. array. **Cell** definitly must have an ability to render itself in a console. To get this behavior we need to override virtual abstract **Render** function that comes from **GameObject** base class. The **Implementation** or **definition** of it is very complex, aspecially if we say about the rendering of the piece or king. The declaration can be found here: [Render Function implementation for Cell](https://github.com/BohdanLytvynov/Checkers_C-/blob/main/Checkers/GameEngine.cpp). 

## Benefits of the Pointers Usage
We use pointers to Cells in our Board to have an opportunity to use **dynamic Polymorphism** and to reduce memory Usage, because when we use pointers we use only the amount of bits that are required to store the adress of the object in a memory. This is significantly less then frequently copying the big objects that requires a big amount of bits in the memory to pass the object to some functions. By using dereferencing we can contact to a propriate instance of the object in the memory and change it's state. 

Since Cells can't be killed I expanded it using **GameObject** base class. When we do this, it can use all the members that are **not private** form the **GameObject** structure. Now lets think what behavior we need for **Cell**. 

**Cell behavior:**
- We need to show player the possible paths to chose. I thougth, that we could use the border highlight for this. We can highlight border of the **Cells**. it will show the paths for possible moves.
- We required the mechanism to show the current location of the player's selection. We can use Focus system for this.
- Also we need to show that this **Cell** was selected. We can establish the SelectMove function and variable that will store the color for this selection.

**First issue to solve**
When I was creating the **Cell** structure I noticed that I need to modify it. I realized it, only when I was creating main game logic and I was writing **Game Controller Structure**. Firstly I wanted to modify base class **GameObject**, but I realized that it could make my **inheritance hierarchy** very complex, and changing of previous derivative classes would be required. Moreover, I will have the situation when I have an object with unused behaviors and fields if I do so. I am talking now about **Checker** structure. We will come to it later. 
**Issue Solving:**
I decided to prefere interface approach, rather then using **Inheritenece**. The reasons for that were:
- Interfaces are structures that contains only behavior, and no fields. Ordinary interface structures contains only virtual abstract functions, that can be implemented later in structures, that implement them. So we can define the propriate field in a **Cell** structure and then implement propriate behaviors for them.
- We can **"inject"** new behavior without changing previous and next derivative structures. We can say, that **interfaces** has less power bound in structures hierarchy then inheritence has.
- Modern design patterns uses interfaces.

For that reasons I created 2 interface structures. They are:
- IObjectWithBorder. -> It is the behavior expand, to have an ability to control border color.
- IBorderHighLightable -> It is the behavior for changing the border color.

## Interfaces vs Virtual Inheritance

After that I inherit **Cell** from **GameObject** and **IObjectWithBorder** and  **IBorderHighLightable**. It is an example of so called **multiple inheritance**.
Using interface approach also saved me from other bad issue, that can take place while using multiple inheritance. We can get cycles in our inheritabce graph. And to resolve that we can use **virtual inheritance** but it's rather complex in comparison with using of **interfaces**. So I decided to go that way.

So I implement all the interfaces that I required, and all fields for that behavior I placed in the **Cell**. All the significent changings were made in function that renders **Cell**. 

## Checker itself

This object is very simple. I just used the **Killable** and inheritance. The main **Complex Thing** here is the drawing of the **Checker** and the **King**.
In real world checkers are circular in shape. But unfortunatly in console we have no possibility to use float numbers for coordinates. We can use only **positive integer numbers** that determine the position of the cursor in the console. Also we can't use sine and cosine functions to draw circles. I decided to draw something that looks like a circle. I have got something like this:

![Game_screenshot_Checker](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/0d4d6c6f-9212-4358-be9e-1ec9198f673f) 

As you can see it is something similar to a piece. The piece is drawn using the Render Function. So the main parts of the drawing logic are implemented there. I used to additional fields:
- m_HorbaseLength. Controls the width of the upper and lower bases.
- m_VertBaseLength. Controls the width of the left and right bases.

  ![Game_screenshot_Checker Sizes](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/b0f7c027-3d00-4832-9563-389bad86ccc8)

  Let me try to explain the drawing mechanism. First we need to find the center of our CHecker. It can be done by using: **width of the checker / 2** expresion.
  
  > [!IMPORTANT]
  > Since we use a console to draw our graphics we have one more problem. Our **"so called pixel"** *console cursor* is twice larger in height with respect to it's width.

I have found an ideal width and height for pieces, and it is 10 for width and 6 for height.
  Ok, lets return to our problem. We have already calculated the center of our Checker it is 5, since 10 / 2 is 5. Then we need to calculate second point, let it be **Hormid2** and it is Previous value, let it be **Hormid1** + m_HorbaseLength - 1. By the way m_HorbaseLength and m_VertBaseLength better to se to 2.
  Using this we can calculate the conditions where we have the end and the start of the Checker's **"first row"**, like this:

![Game_screenshot_Checker_Drawing](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/9beee486-6d1e-4041-a412-1097aee56f5e)

If weknow the Start and End we can easily create a condition, that allows us to print the symbols in that range. The same things could be done for Vertical length base controlling:

![Game_screenshot_Checker_Drawing 02](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/3c6fb8f2-0ce3-43e7-925f-1af39f4ab665)

Here the Start value was our center, since 6/2 = 3. And now the main part. We draw the first raw, then cache the values of start and end, expand first raw by 1 additional pixel at the end and start, and keep drawing it until the Vertical base length range will be passed. After that return previous values to Horizontal **Start** and **End**. As you see it is a very complex mechanism. Maybe I will modify it in future.

## Building Options Structures
In our game, at the start of it, we have to initialize 8 by 8 matrix of cells, and 12 instances of checkers. Instances of cells are all the same. It is also true for Checkers. So I decided to create **Building options Structures** to store preferences for initializing this 2 essential for game objects.

## Main Game Controller
The main game logic is controlled with the help of the **Game Controller** functions. Later I have implemented the **AI** module. I realized that **Game Controller** and **AI** module must have similar functions to use in the game. So we can treat to **AI** module like the version of the smart **Game Contorller**, that uses **Graph Algorithms** to calculate a propriate turn. I created the base class **Main Game Logic**, where I implemented all the functions which were needed for gameplay,
without those one, which influence UI. Here is a short listing of them:

- FindOrthogonalVector(const Vector<short>& v) const; Used to find Orthogonal Vector 

- FindAllPosibleTurnsForKingRecursive(Checker* selectedChecker, const Vector<short>& position,
			Vector<short>& prevPosition, Checker* checkers, size_t checkers_count,
			bool& onCallback, const Vector<short>& dirVector = Vector<short>(),
			bool checker_under_attack = false); Used to find all possible turns for King

- void FindPossibleTurns(bool whiteBlack = true, std::function<void(Vector<short> position, Vector<short> PrevPos, bool multiKill, bool on_take)> func = nullptr);The same as previous, but is used for ordinary Checker.
  
- bool OutOfBorders(const Vector<short>& position); Indicates wether checker is out of the Border

- bool IsOnTheMarginOfTheBoard(const Vector<ushort>& position); Indicates wether checker is about to be out of the Border

- bool IsAllPossibleTurnsSelected(); Indicates wether all possible turns selected or not.

- Cell* FindCellUsingPosition(const Vector<short>& positionVector); Iterates the matrix, that stores Pointers to Cells and gets the cell pointer according to the position Vector

- Checker* FindCheckerUsingPosition(const Vector<short>& positionVector, Checker* checkers,
			size_t checkers_count); The same as previous but returns the pointer to the Checker according to position Vector.

- void FindPossibleTurnRecursive(Checker* selectedChecker, const Vector<short>& position, 
			Vector<short>& prevPosition, Checker* checkers, size_t checkers_count,
			const Vector<short>& dirVector = Vector<short>(),
			bool multiKill = false, std::function<void(Vector<short> prev_position,
				Vector<short> current_position, bool multiKill, bool on_take)> func = nullptr);Used to find all possible turns for piece.

- void DrawBoard(Cell** board, size_t rows_count, size_t colums_count); Call the Render function to draw all the elements

- void DrawCheckers(Checker* checkers, size_t checkers_count); render all the checkers

- void Reset_Game_Logic_State(); Resets main control variables

- const bool& AI_Used() const; Determines wether AI is active

- const size_t& GetCountOfPossibleTurns() const; Used to find out wether AI has find some possible turns or not.

Some of this functions are used by AI too. 
> [!Note]
> As you can see AI can have some Render functions, They are used to show the human player the AI moves.

**Game Controller** class is a **Singleton** that derrives from the Main_Game_Logic base class, like **checker_ai**. 
**Game Controller** has a pointer to the AI module, so I cann modify AI module by expanding the **checker_ai** structure.
Also **Game Controller** has some additional drawing functions to Draw all our system and to make visible possible turns or User selected routes. 

## Deeper inside the Game cycle

### How to Store Pieces

As I mentioned before the first instruction of our game cycle is to let the player to chose the propriate Piece that he would like to use for hus turn. Of course it has some differences between the human's selector of moves and the AI's one. First I have to show you the structure that stores all the pieces. I decided to use a symple array of pointers at the **Checker**. To save a memory space I decided to put all the pieces of all colors inside the one array of pointers. totaly we have 24 pieces. 12 white checkers - for 1 player and 12 black - for 2 player. In my game the white checkers are blue and the black one are red. I have chosen this color scheme cause it looks like good with my Black and White cells. Now lets determine a propriate indexes of our arrar. The **Total length of our array willl be 24.** I placed black checkers first, then white checkers. So the **"range for Black pieces"** is from 0 to (0 + 23)/2 => from 0 to 11. and the **"White pieces range"** is from 12 to 23. So using propriate conditions we can operate with white or black pieces.

## Selection of the Propriate Piece

For selection I used Focus behavior. I just change the background color of the piece and Darw everything again. For focusing I decided to use the green Color. Also I read the input from the keyboard. I  expect to have such inputs^
- **A**. It moves the selection left.
- **D**. It moves the selection right
- **S**. Makes the Selection.
- **C**. Confirms the selection.
- **R**. Gives an opportunity to make selection again.

 The same controls are used all over the game. When the game starts we should operate with white pieces in range from 0 to 11, and the piece under the 0 index is Focused. When we press the **A** or **D** buttons we must Unfocus previous Piece and move ether left or right, it depends from the pressed Key, and call the Focus function on new piece, after that we redraw all the scene. Also when we reach the end of the range, for example 11 we will go back to satrt to the 0 index, similarly when we reach the beginig, and if we continue to go in the same direction, we will be moved to the end of the range. This how the selector for human works. Now lets dive into an AI Selection Module.

 ## Basic Principles of My AI

 My variant of **AI**, for now has only one difficulty mode. It's easy. But I am continue working on more complex and more smart **AI**. ain principles are^
 - I want my AI to find the piece with the best routes. 





  


  





