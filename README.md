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
First lets take a look at our main structures that are used in this game. All of their declarations are situated in [**GameEngine.h**](https://github.com/BohdanLytvynov/Checkers_C-/blob/main/Checkers/GameEngine.h) header file. I prefere to use structures against classes. The first structure is the **GameObject** it is a base structure for **Pieces** and **Cells of the board**. Lets look at what behaviour and state it has. 

**GameObject** **state** variables must include the next values:
- Size of the object. (Width and Height)
- Position of the object. Here we can use Vector to describe it's global position.
- Chars that will be used to draw the object in the console. Here I used the pointer to array of chars. The pointer doesn't know anything about the size of the array? so we need the unsigned variable to store the count of chars in our array.
- Additional variable to control focus system.
  
**GameObject Behaviours**:
  To my mind we can give it oly one behaviour and it is Focus behaviour. What is it? Focus, from my point of view, is changing the visual appearence of the object, when some events takes place. In our case it cam be the selection of the piece by the user.



