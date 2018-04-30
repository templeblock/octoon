#ifndef OCTOON_INPUT_CONTENT_H_
#define OCTOON_INPUT_CONTENT_H_

#include <octoon/input/input_key.h>
#include <octoon/input/input_button.h>

#include <vector>

namespace octoon
{
	namespace input
	{
		struct InputContent
		{
			enum Type
			{
				Keyboard,
				Mouse,
				PS3,
				Xbox,

				Sep
			};

			Type input;
			std::uint16_t code;
		};

		typedef std::vector<InputContent> InputOp;

		InputOp operator+(InputKey::Code code1, InputKey::Code code2);
		InputOp operator+(InputKey::Code code1, InputButton::Code code2);
		InputOp operator+(InputButton::Code code1, InputKey::Code code2);
		InputOp operator+(InputButton::Code code1, InputButton::Code code2);

		InputOp operator+(InputOp codes, InputKey::Code code);
		InputOp operator+(InputOp codes, InputButton::Code code);
	}
}
#endif // !OCTOON_INPUT_CONTENT_H_
