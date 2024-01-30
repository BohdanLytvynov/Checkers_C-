Checkers the game. 
  This project was created to enhance my coding and algorithm skills. It is fully written in C++. And all the implementation are done in console manualy.
I have used here a custom Vector math library and a custom data structures library. I understand that better implementations of them can be found in standart libraries but I want
to practice and improve my coding skills. 
  This project consists of header files and source files. I used this technic to make my code more readable. 
As Checkers is a complex game, that requires a lot of functionality and abilities for players. Players should have an opportunities to select and move pieces. To resolve all this cases 
it is better to use OOP aproach. The main concepts of it are Encapsulation, Inheritance, Polymorphism. The last one can be static or dynamic. I have used all of it in my project.
  Encapsulation was used in different objects to provide a safe access to the class invariant. Also it is a hiding of some function realization from the user of the object.
  Using Inheritance I have made a Cell class and Checker class. With a help of dynamic Polymorphism and Inhertance I provided the render system for each object. By overriding
the initial virtual function of the first base class Gameobject, I have an opportunity to determine how I want to render a certain object in a console. For example Cells of 
the checkers board are rendered like a rectangles with borders. Checkers and Kings must be rendered in another way. And to control this I need only to override the function 
render() in each class. And using pointer to base class I can call the propriate render() function for each object. It saves a lot of time and makes code more reusable.
  As I mentioned I used rendering functions. For rendering different objects I created the ConsoleUiGraphicsCotroller. Here I used the design pattern that is called the Singleton.
It means that we only can have one instance of our object in whole our programm. So I thought that we should have only one Console UI Controller.
The Same pattern was used for GameController the main class that manages the game process.
  To manage the game process I needed some Vector math. And here I used static Polymorphism(template classes) and Inheritance. I created Vector math library to make it to work.
I used various types of Vector math operations in this project. I chose the Vector object to describe the current position of my piece. The start point of the position Vector for 
every object is in the origin of the global coordinate system. For 2D apps like in our case it is the Upper left Corner of the console window. To prevent some rendering artifacts 
I made the console to open in a full screen mode. When the board with checkers are initialized in a Game Controller the propriate position Vectors have already been set and the 
GameController object draws each object in a certain position using the origin offset. Also by subtracting two position Vectors we can find out the move direction vector.
Also more Vector calculus functions is used when it comes to taking an other pieces.
