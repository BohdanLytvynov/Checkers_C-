#ifndef V_MATH_H

#define V_MATH_H

#include "v_mathBase.h"

#include<cmath>

namespace vector_math
{


	Tdecl
	class vector;

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

		vector<T> operator - (point<T>& start) const
		{
			return vector<T>(start, *this);
		}

#pragma endregion

	};	

	Tdecl
		class vector : public ConsoleCoords<T>
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
		vector<T>() : ConsoleCoords<T>() {}

		/// <summary>
		/// Main ctor
		/// </summary>
		/// <param name="start">Start Point</param>
		/// <param name="end">End Point</param>
		vector<T>(const point<T>& start, const point<T>& end)
		{
			ReCalcVectorCoords(start, end);
		}

		/// <summary>
		/// Copy Ctor
		/// </summary>
		/// <param name="other">ref to Object source</param>
		vector<T>(const vector<T>& other) : ConsoleCoords<T> (other) {}
		
		vector<T>(const T x, const T y)
		{
			ConsoleCoords<T>::SetXY(x, y);
		}

#pragma endregion

#pragma region Operators

#pragma region Logical Operators

		bool operator == (const vector<T>& other)
		{
			if (this->GetLength() == other.GetLength())			
				return this->GetX() == other.GetX() && this->GetY() == other.GetY();
			
			return false;
		}

		bool operator != (const vector<T>& other)
		{
			return !((*this) == other);
		}

		bool operator < (const vector<T> other)
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())			
				return this->GetLength() < other.GetLength();
			
			return false;
		}

		bool operator > (const vector<T> other)
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())			
				return this->GetLength() > other.GetLength();			

			return false;
		}

		bool operator >= (const vector<T> other)
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())			
				return this->GetLength() >= other.GetLength();			

			return false;
		}

		bool operator <= (const vector<T> other)
		{
			if (this->GetX() == other.GetX() && this->GetY() == other.GetY())			
				return this->GetLength() <= other.GetLength();			

			return false;
		}

#pragma endregion

#pragma region Math operators

		vector<T> operator + (const vector<T>& vector) const
		{
			return vector_math::vector<T>(this->GetX() + vector.GetX() , this->GetY() + vector.GetY());
		}

		vector<T>& operator += (const vector<T>& vector)
		{
			this->SetXY(this->GetX() + vector.GetX(), this->GetY() + vector.GetY());

			return *this;
		}

		vector<T> operator - (const vector<T>& vector) const
		{
			return vector_math::vector<T>(this->GetX() - vector.GetX(), this->GetY() - vector.GetY());
		}

		vector<T>& operator -= (const vector<T> vector)
		{
			this->SetXY(this->GetX() - vector.GetX(), this->GetY() - vector.GetY());

			return *this;
		}

		vector<T> operator * (const T number) const
		{
			return vector<T>(this->GetX() * number, this->GetY() * number);
		}

		vector<T>& operator *= (const T number)
		{
			this->SetXY(this->GetX() * number, this->GetY() * number);

			return *this;
		}

		explicit operator double () const
		{
			return this->GetLength();
		}

		vector<T>& operator = (const vector<T>& other)
		{
			ConsoleCoords<T>::SetXY(other.GetX(), other.GetY());

			return *this;
		}

#pragma endregion

#pragma region Math functions

		double GetLength() const
		{
			return static_cast<double>(sqrtf(this->GetX() * this->GetX() + this->GetY() * this->GetY()));
		}

		T DotProduct(const vector<T> &vector) const
		{
			return vector.GetX() * this->GetX() + vector.GetY() * this->GetY();
		}

		vector<T> Normalize()
		{
			T length = this->GetLength() > 1? this->GetLength() : 1;

			return (*this) * length;
		}

		

#pragma endregion

#pragma region Indexer

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



#pragma endregion


#pragma endregion


	};
}



#pragma endregion


#endif
