
#ifndef CONVERTION_H

#define CONVERTION_H

namespace value_convertion
{
#pragma region Converters
	template<typename In, typename Out>
	struct IConverter
	{
		virtual Out ConvertTo(In input) = 0;
	};

	struct ushort_to_short : public IConverter<unsigned short, short>
	{
		short ConvertTo(unsigned short input) override
		{
			return input;
		}
	};

	struct short_to_ushort : IConverter<short, unsigned short>
	{
		unsigned short ConvertTo(short input) override
		{
			return static_cast<unsigned short>(input);
		}
	};

	struct Converters
	{
		static ushort_to_short USHORT_TO_SHORT;

		static short_to_ushort SHORT_TO_USHORT;
	};
	

#pragma endregion
}

#endif // !CONVERTION_H

