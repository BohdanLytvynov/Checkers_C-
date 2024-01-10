
////Header guard
#ifndef V_MATHBASE_H

#define V_MATHBASE_H

#define Tdecl template<typename T>


Tdecl
class ConsoleCoords
{
private:

#pragma region State
	//Private section of the class
	T m_x;//Position of the object with respect to X axis

	T m_y;//Position of the object with respect to Y axis
	
	static unsigned char m_DIMENSIONS;

	static std::string m_InputMsg;
#pragma endregion
	
protected:


public:


	//Public section of the class
#pragma region Ctor
	/// <summary>
	/// Empty ctor, inirializes ConsoleCoords object with 0 , 0 
	/// </summary>
	ConsoleCoords() : m_x(0), m_y(0) {}

	/// <summary>
	/// Main ctor
	/// </summary>
	/// <param name="x">X coord</param>
	/// <param name="y">Y coord</param>
	ConsoleCoords(T x, T y) : m_x(x), m_y(y) {}

	/// <summary>
	/// Copy ctor
	/// </summary>
	/// <param name="other">Object to copy values from</param>
	ConsoleCoords(const ConsoleCoords<T>& other) :m_x(other.m_x), m_y(other.m_y) {}


#pragma endregion

#pragma region Methods
	/// <summary>
	/// Gets the value of the X coord
	/// </summary>
	/// <returns>Object position according to X Axis</returns>
	T GetX() const
	{
		return m_x;
	}

	/// <summary>
	/// Sets the X coord of the object 
	/// </summary>
	/// <param name="x">New x coord value</param>
	void SetX(T x)
	{
		m_x = x;
	}

	/// <summary>
	/// Gets Y coord of the object
	/// </summary>
	/// <returns>Object position according to Y axis</returns>
	T GetY() const
	{
		return m_y;
	}

	/// <summary>
	/// Set new Y coordinate value
	/// </summary>
	/// <param name="y">New y coord value</param>
	void SetY(T y)
	{
		m_y = y;
	}

	/// <summary>
	/// Set new X and Y coordinate values
	/// </summary>
	/// <param name="x">New x coord value</param>
	/// <param name="y">New y coord value</param>
	void SetXY(T x, T y)
	{
		m_x = x;

		m_y = y;
	}

#pragma endregion

#pragma region Operators
	/// <summary>
	/// Arithmetic assignment operator
	/// </summary>
	/// <param name="cc">ConsoleCoords Object</param>
	/// <returns>ref to current object</returns>
	ConsoleCoords<T>& operator = (const ConsoleCoords<T>& other)
	{
		m_x = other.m_x;

		m_y = other.m_y;

		return *this;
	}

#pragma region Input Output

	friend std::istream& operator >> (std::istream& is, ConsoleCoords<T>& c)
	{
		std::string str;
		std::string error;

		T temp;

		for (int i = 1; i <= m_DIMENSIONS; ++i)
		{
			do
			{
				if (error.size() > 0)
					std::cout << error << std::endl;

				std::cout << m_InputMsg << ((i == 1) ? "X" : "Y") << std::endl;

				is >> str;

			} while (!isNumber(str, error, temp));

			error.clear();

			i == 1 ? c.m_x = temp :
				c.m_y = temp;
		}

		return is;
	}

	friend std::ostream& operator << (std::ostream& os, ConsoleCoords<T>& c)
	{
		os << "X: " << c.m_x << std::endl << "Y: " << c.m_y << std::endl;

		return os;
	}

#pragma endregion




#pragma endregion

};

Tdecl
unsigned char ConsoleCoords<T>::m_DIMENSIONS = 2;

Tdecl
std::string ConsoleCoords<T>::m_InputMsg = "Enter Coordinate ";

#endif // !V_MATHBASE_H

