#ifndef V_MATH_H

#define V_MATH_H

#include "v_mathBase.h"

#include<cmath>

#include"convertion.h"

namespace vector_math
{
	Tdecl
	class Vector;

#pragma region Point declaretion

	Tdecl
		class point : public ConsoleCoords<T>
	{
#pragma region Ctors

	public:
		point() : ConsoleCoords<T>() {}

		point(T x, T y) : ConsoleCoords<T>(x, y) {}

		point(const point<T>& other) : ConsoleCoords<T>(other) {}
				
#pragma endregion


#pragma region Interfaces	

		point<T>& operator = (point<T> &other)
		{
			ConsoleCoords<T>::SetXY(other.GetX(), other.GetY());

			return *this;
		}

		Vector<T> operator - (point<T>& start) const
		{
			return Vector<T>(start, *this);
		}

#pragma endregion

	};	

#pragma endregion

#pragma region Vector Declaretion
	
	Tdecl
		class Vector : public ConsoleCoords<T>
	{
	private:
		void ReCalcVectorCoords(const point<T>& start, const point<T>& end)
		{
			ConsoleCoords<T>::SetXY(end.GetX() - start.GetX(), end.GetY() - start.GetY());
		}

	public:
#pragma region Ctor

		/// <summary>
		/// Empty standart ctor
		/// </summary>
		Vector<T>() : ConsoleCoords<T>() {}

		/// <summary>
		/// Main ctor
		/// </summary>
		/// <param name="start">Start Point</param>
		/// <param name="end">End Point</param>
		Vector<T>(const point<T>& start, const point<T>& end)
		{
			ReCalcVectorCoords(start, end);
		}

		/// <summary>
		/// Copy Ctor
		/// </summary>
		/// <param name="other">ref to Object source</param>
		Vector<T>(const Vector<T>& other) : ConsoleCoords<T>(other) {}

		Vector<T>(const T x, const T y)
		{
			ConsoleCoords<T>::SetXY(x, y);
		}

#pragma endregion

#pragma region Operators

#pragma region Logical Functions

		bool Equals(const Vector<T> &other) const
		{
			return this->operator==(other);
		}

		bool IsColinear(const Vector<T>& other) const
		{
			return (this->GetX() * other.GetY() - other.GetX() * this->GetY()) == 0;
		}

		bool IsCoDirectional(const Vector<T>& other)
		{
			if (IsColinear(other))
			{
				//Determine wether vectors are codirectional

				return this->DotProduct(other) > 0;
			}

			return false;
		}

#pragma endregion

#pragma region Logical Operators

		bool operator || (const Vector<T> &other) const
		{
			return IsColinear(other);
		}

		bool operator == (const Vector<T>& other) const
		{
			if (this->GetLength() == other.GetLength())
				return this->GetX() == other.GetX() && this->GetY() == other.GetY();

			return false;
		}

		bool operator != (const Vector<T>& other) const
		{
			return !((*this) == other);
		}

		
		bool operator < (const Vector<T>& other) const
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
				return this->GetLength() < other.GetLength();

			return false;
		}

		bool operator > (const Vector<T>& other) const
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
				return this->GetLength() > other.GetLength();

			return false;
		}

		bool operator >= (const Vector<T>& other) const
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
				return this->GetLength() >= other.GetLength();

			return false;
		}

		bool operator <= (const Vector<T>& other) const
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())
				return this->GetLength() <= other.GetLength();

			return false;
		}

#pragma endregion

#pragma region Math operators

		Vector<T> operator + (const Vector<T>& vector) const
		{
			return vector_math::Vector<T>(this->GetX() + vector.GetX(), this->GetY() + vector.GetY());
		}

		Vector<T>& operator += (const Vector<T>& vector)
		{
			this->SetXY(this->GetX() + vector.GetX(), this->GetY() + vector.GetY());

			return *this;
		}

		Vector<T> operator - (const Vector<T>& vector) const
		{
			return vector_math::Vector<T>(this->GetX() - vector.GetX(), this->GetY() - vector.GetY());
		}

		Vector<T> operator -()
		{
			return Invert();
		}

		Vector<T>& operator -= (const Vector<T> vector)
		{
			this->SetXY(this->GetX() - vector.GetX(), this->GetY() - vector.GetY());

			return *this;
		}

		Vector<T> operator * (const T number) const
		{
			return Vector<T>(this->GetX() * number, this->GetY() * number);
		}

		Vector<T>& operator *= (const T number)
		{
			this->SetXY(this->GetX() * number, this->GetY() * number);

			return *this;
		}

		T operator * (const Vector<T>& other) const
		{
			return this->DotProduct(other);
		}

		explicit operator double() const
		{
			return this->GetLength();
		}

		Vector<T>& operator = (const Vector<T>& other)
		{
			ConsoleCoords<T>::SetXY(other.GetX(), other.GetY());

			return *this;
		}

		Vector<T> operator * (T multiplyers[2])
		{
			return this->MultiplyXYSeparetly(multiplyers);
		}

#pragma endregion

#pragma region Math functions

		Vector<T> Invert() 
		{
			return this->operator* -1;
		}

		double GetLength() const
		{
			return static_cast<double>(sqrtf(this->GetX() * this->GetX() + this->GetY() * this->GetY()));
		}

		T DotProduct(const Vector<T>& vector) const
		{
			return vector.GetX() * this->GetX() + vector.GetY() * this->GetY();
		}

		Vector<T> Normalize()
		{
			T length = this->GetLength() > 1 ? this->GetLength() : 1;

			return this->operator * (1/length);
		}

		Vector<T> MultiplyXYSeparetly(T multiplyers[2])
		{
			return Vector<T>(this->GetX() * multiplyers[0], this->GetY() * multiplyers[1]);
		}


#pragma endregion

#pragma region Indexers

		T operator [] (const int index)
		{
			switch (index)
			{
			case 0:
				return this->GetX();

			case 1:
				return this->GetY();
			default:
				throw std::runtime_error("You are requesting to the dimension that doesn't exist!!!");
			}
		}

		const T operator [] (const int index) const
		{
			switch (index)
			{
			case 0:
				return this->GetX();

			case 1:
				return this->GetY();
			default:
				throw std::runtime_error("You are requesting to the dimension that doesn't exist!!!");
			}
		}

		T operator [] (const std::string &axes)
		{
			if (axes == "X" || axes == "x")
			{
				return this->GetX();
			}
			else if (axes == "Y" || axes == "y")
			{
				return this->GetY();
			}
			else
			{
				throw std::runtime_error("You are requesting to the dimension that doesn't exist!!!");
			}		
		}

		const T operator [] (const std::string &axes) const
		{
			if (axes == "X" || axes == "x")
			{
				return this->GetX();
			}
			else if (axes == "Y" || axes == "y")
			{
				return this->GetY();
			}
			else
			{
				throw std::runtime_error("You are requesting to the dimension that doesn't exist!!!");
			}
		}

#pragma endregion

#pragma region Converter
		template<class Tout>
		Vector<Tout> Convert_To(value_convertion::IConverter<T, Tout> &converter) const
		{
			value_convertion::IConverter<T, Tout>* ptr = &converter;

			return Vector<Tout>(ptr->ConvertTo(ConsoleCoords<T>::GetX()), 
				ptr->ConvertTo(ConsoleCoords<T>::GetY()));
		}
		

#pragma endregion

#pragma region Input

		friend std::istream& operator >> (std::istream& is, Vector<T>& vector)
		{
			ConsoleCoords<T> cords;

			is >> cords;

			return is;
		}

#pragma endregion

#pragma region Output

		friend std::ostream& operator << (std::ostream& os, Vector<T>& vector)
		{
			os <<" ( "<< vector.GetX() <<" ; " << vector.GetY() << " ) " << std::endl;

			return os;
		}

#pragma endregion


#pragma endregion

	};

#pragma endregion




}







#endif
