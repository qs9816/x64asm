/*
Copyright 2103 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef X64ASM_SRC_IMM_H
#define X64ASM_SRC_IMM_H

#include <iostream>

#include "src/operand.h"

namespace x64asm {

/** An immediate value. */
class Imm : public Operand {
	public:
		void write_att(std::ostream& os) const;
		void write_intel(std::ostream& os) const;

	protected:	
		constexpr Imm(uint64_t val) : Operand{val} { }
};

/** An immediate byte value. The imm8 symbol is a signed number between –128 
	  and +127 inclusive. For instructions in which imm8 is combined with a 
		word or doubleword operand, the immediate value is sign-extended to form 
		a word or doubleword. The upper byte of the word is filled with the topmost 
		bit of the immediate value. 
*/
class Imm8 : public Imm {
	public:
		constexpr Imm8(uint64_t i) 
				: Imm{i} { 
		}

		constexpr bool check() {
			return (int64_t)val_ >= -128 && (int64_t)val_ < 128;
		}
};

/** An immediate word value used for instructions whose operand-size attribute 
	  is 16 bits. This is a number between -32,768 and +32,767 inclusive.
*/
class Imm16 : public Imm {
	public:
		constexpr Imm16(uint64_t i) 
				: Imm{i} { 
		}

		constexpr bool check() {
			return (int64_t)val_ >= -32768 && (int64_t)val_ < 32768;
		}
};

/** An immediate doubleword value used for instructions whose operand-size 
	  attribute is 32 bits. It allows the use of a number between 
		+2,147,483,647 and -2,147,483,648 inclusive.
*/
class Imm32 : public Imm {
	public:
		constexpr Imm32(uint64_t i) 
				: Imm{i} { 
		}

		constexpr bool check() {
			return (int64_t)val_ >= -2147483648 && (int64_t)val_ < 2147483648;
		}
};

/** An immediate quadword value used for instructions whose operand-size 
	  attribute is 64 bits. The value allows the use of a number between 
		+9,223,372,036,854,775,807 and -9,223,372,036,854,775,808 inclusive.
*/
class Imm64 : public Imm {
	public:
		constexpr Imm64(uint64_t i) 
				: Imm{i} { 
		}

		template <typename T>
		constexpr Imm64(T* t) 
				: Imm{(uint64_t)t} { 
		}

		constexpr bool check() {
			return true;
		}
};

/** The immediate constant value zero */
class Zero : public Imm8 {
	friend class Constants;

	public:	
		constexpr bool check() {
			return val_ == 0;
		}

	private:
		constexpr Zero() 
				: Imm8{0} { 
		}
};

/** The immediate constant value one */
class One : public Imm8 {
	friend class Constants;

	public:
		constexpr bool check() {
			return val_ == 1;
		}

	private:
		constexpr One() 
				: Imm8{1} { 
		}
};

/** The immediate constant value three */
class Three : public Imm8 {
	friend class Constants;

	public:
		constexpr bool check() {
			return val_ == 3;
		}

	private:
		constexpr Three() 
				: Imm8{3} { 
		}
};

} // namespace x64asm

#endif
