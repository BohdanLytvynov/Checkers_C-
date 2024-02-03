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

 The same controls are used all over the game. When the game starts we should operate with white pieces in range from 0 to 11, and the piece under the 0 index is Focused. When we press the **A** or **D** buttons we must Unfocus previous Piece and move ether left or right, it depends from the pressed Key, and call the Focus function on new piece, after that we redraw all the scene. Also when we reach the end of the range, for example 11 we will go back to satrt to the 0 index, similarly when we reach the beginig, and if we continue to go in the same direction, we will be moved to the end of the range. This how the selector for human works. We will come back to the AI Selection module later. We need the understanding how turn finder system works.

## Possible Turns Calcultor
The mechanism is slightly differ for the **Piece** and the **King**. For the **Piece** we will use **FindAllPossibleTurns** function. The process of route finding must be recursive. So I have created an envelope, it is **FindAllPossibleTurns**, and there is a recursive function, called **FindAllPossibleTurnsRecursive** inside it.
I have used recurtion principle here cause I noticed that we need to repeat the same logic until some base conditions will be reached. When the Checker was chosen, we call the **FindAllPossibleTurns** function. It starts from the current Checker position. Let me remind you, that Checker can move in diagonal directions, only one Cell per one Move. That diagonal directions can be described by the Vectors { (1, 1), (1, -1), (-1, -1), (-1, 1) }, we can multiply each vector component by the width and the height of the Cell. And we'll get 4 dir Vectors: 

![Checkers Dir Vectors](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/82ab3bd7-e079-4bf3-b0d3-4823f67672b2)

Look at this picture. The red dot is a local coordinate origin of the object. Green Vectors are -> dirvectors that are modified, using width and height of the Cell. According to our approach: "each object in a scene has it's own position Vector." Again look at this:

![Object position vectors](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/05b08d21-e39d-4d09-bee4-4c11413896e2)

Orange Vectors {r1, r2, r3} are the position vectors of our objects. And using some Vector math laws, like adding we can move to the next cell in certain direction.

![Calc new position](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/ff7c1925-5af2-4f11-bf93-5b218914e318)

Here we have r1 - position Vector, d1 - one of the direction Vectors. If we do r1 + d1 = r2, new position Vector that points at another diagonaly placed **Cell**, that is exactly what we need, to perform the route examination. So we can add 1 of the direction Vectors to the current position Vector and get the new position. 

### Algorithm for ordinary Checker

- First we have the initial position, it is equal to the position of the selected Checker. We have to examine all the 4 Cells near the selected piece.
- Then we examine the new position.
	- If it is Empty, no pieces exists at this position, we can add this position to a **Possible Turns** collection.
  	- If it contains checker, we have two variants:
    		- Checker is ours, so we need to stop examine this rote, and we will come to **Recurtion CallBack** of this branch.
    		- It is enemy Checker, ok, again we have to check 2 cases:
    			- The cell behind the enemy Checker is empty, so we can perform a take. And we add this Checker, I want to remind, it is a pointer, to the Collections, that store Checkers to be Killed. Also we need to continue rout examination from this position.
    			- The enemy checker is covered, and take is impossible.
	- Next position Vector points outside the board, we need to stop here.
	- Also we need to stop if we are about to go outside the Board.

> [!NOTE]
> In Checkers we have the certain rules, how we can move pieces. If there are no takes, piece can move diagonaly only forward to the oposite side. To move it backward we > need to have a possibility to make a take, that requires backward movement. We can use Vector math again, asspecialy **Dot Product** of two Vectors. **Dot Product** is > the value, that we get, when we are projecting one Vector on another. According to the Angle between 2 Vectors we can get such results:
- Greater then 0. -> It means that angle is in range 0 to 89 deg.
- 0 -> Angle is 90 deg.
- Lower then 0 -> Angle is in range 91 to 180 deg.
Also we must introduce 2 **Basis Vectors** { (1, 0), (0, 1) }, now look at the Picture:

![Basis and Dir Vectors](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/80fb7734-0d01-41f0-b217-36bdc3863b77)

Here we have b1 and b2 vectors, it is our global basis. Vector d1 is one of the direction vectors. We can do the Dot Product between each basis Vector b1 and b2 and the direction Vectors. After that we will get 2 scalars. When we Dot Product b1 and d1, we will get the positive result, since the angle between this vectors in range (0 to 89). Opposite, the result of Dot Product between b2 and d1 will be less then 0. And we can use this facts to determine what correct direction should be chosen for turn. 
Using this principle we can determine the coorect movement direction.

### Algorithm for King
> [!NOTE]
> In checkers Kings can move in any directions, diagonaly, unlimited. And it can make the Algorithm much complex. It also can perform multitakes. 

We can use the previous Concept of Recursive turn search. Lets see what I have created.
- As in previous algorithm we start from the position of the current checker. We need to explore all the diagonal routes.
- If we have possible take, we mark this checker, that it can be taken by adding it to the Checkers to be killed collection.
- And if the checker for take detected we just start this Algorithm again from the position, behind the Checker to be Taken.

It seems very simple, but when I started to implement it I ran into a problem. When the King perform the last take it should stop at the position behind the taken Checker. Moreover we have to explore more complex routes. Lets see pictures again:

![King Principles 2](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/3f74e141-1280-4b17-9216-58afa83a8cb4)

This picture is very complex from the first View. But it is exactly the way how we can find Checkers for taking. As I said, we start from the same position, where the king is situated, after that we explore 4 diagonal directions, each per one time. We use for cycle and call function recursively and pass there the current position + one of the direction Vectors for move, each for iteration. When we have no checkers in front, we continue to examine Cells in that direction, it is a straight line.
But if the checker for take was found, we calculate two orthogonal Vectors to the move Vector, and start to examine all 4 directions form that points. For now we examine routes in 4 directions only once, when we are at the position where 2 orthogonal Vectors points at. If we look at previous picture, Green arrows are calls of recurtion function and they create routes, red arrows are routs when recursive callback takes place. Red crosses are places where we should stop examination. Orange arrows are the routes that also would be explored after deectiong of the checker for take. Here when we don't meet the new checker for taking, we need to remove Cells from possible turns collection, while recursive callBack takes place.

## What are the so called "Collections"
I have mentioned the word collections in previous chapters. I used them to store some temporary information. For example we need to store somewhere Checkers for takes, also we need to store Cells, that represent the possible turns. And, of course we required a storage for Cells that were selected by user. For all this requirements we can use linked list data structures, for example, for collecions I used **single linked list**. It is a data structure, that consists of Notes, that are linked with each other by pointers. The typical Note consists of data segment and the pointer to other Note. I used here template class and it gives us an opportunity to store data of various types. Also I implemented there functions for adding, deleting, and iterating the elements. Single linked lists has a good time complexity when we add elements to the begining of the list, also we can store the pointer to the end of list and make the time complexity good to. We will get O(1). Iteration has time complexity O(n), where n is a length of the list. But we need to use linked list in this situation, cause we don't know how many objects we will store. Arrays are no suitable in this case, they have a constant length after initialization, and, of course we can create the resize function, but better to use an unlimited collection. By the way we can use vector<T> from the STL library, but I decided to create my own linked_lists. In future I am going to replace single_linked list collection, where all possible turns stored by the circular_doubled linked list collection. It will make more comfortable the selection of the route for player. Now everything became more clear, and we can move to the most interesting section. 

> [!NOTE]
> And you can notice, that we have some std::functions, it is used to be able to use lambda functions, outside this function to be able to process data outside. It is used in AI, to build **Graphs**.
> This approach allows us to get the information form the functions, while we explore all possible routs.

## Basic Principles of My AI

 My variant of **AI**, for now has only one difficulty mode. It's easy one. But I am continue working on more complex and more smart **AI**. The main principles are^
- I want my AI to find the piece with the best routes.

To do this I need to iterate all the pieces of AI player, calculate all the possible turns for each one and determine the turn, that will lead to the Take of the piece,
or, moreover, several pieces. If there are no such turns, we choose piece randomly for move. 

For this purpose I have created a special structure called turn. I made it as a template class. The type, that I used there is a Vctor. Cause the turn structure stores, some kind of a Graph. For optimization purposes we don't store the Graph itself there, I'll explain it later. Lets get back to the **turn**.
It has fields, such as:
- std::vector<T> m_ends; Here we store the coordinates of the ends of the routes. We need this for path reconstruction
- std::map<T, T> m_prev_dictionary; Special data structure that stores intermediate path information for path reconstruction algorithm. 
- T m_start; Position where the selected Checker is placed
- static size_t m_id; Used to create an id for each new turn. We will increase this value by 1, when the turn structure will be created.
- size_t m_current_id; Id of the current turn
- size_t m_Takes; Count of takes in each turn
- size_t m_eur_value; Will be used later in modifications
- bool m_mini_max_used; Will be used later in modifications
- linear_data_structures::single_linked_list<T> m_CheckersToBeKilledCoords; Stores Checkers for takes.
- Vector<short> m_1KillPosition; Stores the position of the first detected checker for take.

  ### About Graphs
  This is a key concept for AI. Let me remind you what is it. Graphs are the data structures that consists of points. Better to call them Verteces. We can say, that it is the set of Verteces. And this Verteces are connected with each other by edges. It looks something like this:

  [Graph Example](https://www.simplilearn.com/ice9/free_resources_article_thumb/Graph%20Data%20Structure%20-%20Soni/what-is-graphs-in-data-structure.png)

But how we can do this in C++. There are a three main ways how to do this.
- Matrix representation of the graph. We create a set that relates to itself. And special rules define the connections between points. In this case we have a big space complexity. And, moreover, we again need the data structure, that can be expanded during the run_time. Matrices is a 2 dimensional arrays in C++, it means that, like the ordinary arrays, they are constant.
- List of adjacent Verteces. The main idea here is that we can make the associative array, something simillar to Dictionaries, like in C# language. The key will be the Vertex, and the Value will be the linked list of Verteces that are adjacent to the key Vertex. A bit complex realization.
- List of edges. I chose this one. Edge is a structure that has fields From and To, and in some cases the Weight. But we don't need to use Weight, lets say that Weight is 1. From is the name of the Vertex where the edge starts, and to is the name of the Vertex where the edge ends. For me it is an ideal approach for this case.

For all Graph algorithms we need the mechanism of searching the adjecent Verteces. It is very simple. We have a Vertex, and we want to get the verteces, that are connected with this Vertex. We have to Iterate the List of edges, and compare the From value of the each Edge with our Vertex, and if they are equal, we take the To value of the Edge Structure. And put it all into the vector<T> from the STL library.

As I said, using lambda functions, we can get all required values while turns are processing. And using this information we can build a graph. We use to determine the previous and the current point, after that we'll get an edge and add to the edge list. Also we need to cache the position of the first checker for Take. 
We can get sush types of graphs:

![Checkers Graph 2](https://github.com/BohdanLytvynov/Checkers_C-/assets/90960952/cf1b82ad-ff5c-4916-815b-a82b5a9febfd)

Here is the examples of a graphs for the ordinary **Checkers**. For **Kings** graphs can be more complex. But all of them are **Direct Unweighted Graphs**. The process of graph building can be very complex. As I mentioned, we need two points the previous one and the current point. By creating an edge and connecting them with each other we can get the desired result, like that 3 Vertex graph that is situated in the left part of the previous picture. I marked it as an capital letter A. It is very simple graph. The problem can take place, when we have the first take. See graph **B**, there are 2 points, named 2 and 3. It is clear, that we have to skip 2 - nd point, and connect 1 point and the 3 directly, so we can say, that 2-nd point doesn't exist. Also we need to mark the first position Vector of the 1-st Checker for take. It is necessary for the seletion of the correct route to perform take. Also we can have the graph, that is simillar to graph **C**. Again, the mechanism of graph building is the same as in the graph **B**. Here we have to track the **MultiKill Cases**. When we have this case we need to update the previous Vertex for our Edge building mechanism. As I said, I used lambda functions to get proprite data for this. 

### So Called Prev_Dictionary Data Structure.
Now it is time to speak about this. Store Graph in memory in a form of List of Edges is rather space complex. Instead of this approach we can calculate the So called Prev_Dictionary. Using this we can calculate any path in a static Graph. Yeah if the graph changes, we need to recalculate the Prev_Dictionary. Frankly speaking, this data structure represent the relations between verteces of the graph. For this purposes it is better to use associative array or Dictionary. I want to remind it has Keys and Values. As keys we use all the Graph's Verteces that are exists. For example, for graph **A** Prev Dictionary will be: { { 1, 0 }, {2 , 0}, {3 , 0} }, as we see the Values are put to 0. Also we need to track visited Verteces. We can use again Dictionary, where keys are Verteces and the values are the bool values true and false. True, if we have alredy visited current Vertex and False if the Vertex hasn't been visited yet. It will be something like this: { {1, false}, {2, false}, {3, false} }. Ok. 

Now to create the propriate Prev_Dictionary we have to use one of the Graph traversal algorithms:
- 1 Breadth first search
- 2 Depth first search
Both of them are suitable for this situation. I used Depth first search algorithm. It's time complexity is **O(V + E)**, where **V** is the Vertex count of the graph, in case of graph A, it'll be 3, and **E** is Egdes in case of graph A is 2. Mostly all over graphs will be Trees. They can have only one root, and only the connection in one direction between the Verteces. So the amount of edges can be described by this Formula: E = V - 1. By the way. the time complexity of the Breadth first search is the same.

Depth first search algorithm uses recursive traversal. We start from the origin. It will be the Vertex 1 in the each graph. At first, we marked the 1 Vertex as visited:
{ {1, true}, {2, false}, {3, false} }, and then we search for adjacent Verteces: they are 2 and 3. After that we explore the 2 and the 3 Verteces recursively. During the each Vertex exploration we get the previous and the next Verteces. After that we can create the relation between them in Prev_Dictionary. When we are at the 1 Vertex, prev_dictionary will be like this: { { 1, 1 }, {2 , 0}, {3 , 0} }, since during the first call we pass the starting Vertex as parameters of the previous vertex and the current one. The second recursive call will give us: { { 1, 1 }, {2 , 1}, {3 , 0} }, since Verteces 2 and 1 connected with each other. And the last Call:
{ { 1, 1 }, {2 , 1}, {3 , 1} }, it is the Prev_Dictionary for graph **A**. Here we can see the relations between the Verteces. from Vertex 1 we can move to itself or the 2 or the 3 Verteces. So it is the main Principle of DFS algorithm and main princeple of building Prev_Dictionary data Structure. Here is my own implementaation: [DFS Implementation](https://github.com/BohdanLytvynov/Checkers_C-/blob/main/Checkers/DataStructures.h) 



 






  


  





