#ifndef HAVE_EMU_CPU_INSTRUCTION
#define HAVE_EMU_CPU_INSTRUCTION

#include <stdint.h>


struct emu_cpu_instruction;
struct emu_cpu;

struct emu_cpu_instruction_info
{
	int32_t (*function)(struct emu_cpu *, struct emu_cpu_instruction *);
	const char *name;
    
	struct
	{
		uint8_t s_bit : 1;
		uint8_t w_bit : 1;
		uint8_t modrm_byte : 4;
		uint8_t imm_data : 3;
		uint8_t disp_data : 3;
		uint8_t level : 2;
		uint8_t type : 2;
		uint8_t fpu_info : 1;
	} format;
};

struct emu_cpu_instruction
{
	uint8_t opc;
	uint8_t opc_2nd;
	uint16_t prefixes;
	uint8_t s_bit : 1;
	uint8_t w_bit : 1;
	uint8_t operand_size : 2;

	struct /* mod r/m data */
	{
		union
		{
			uint8_t mod : 2;
			uint8_t x : 2;
		};

		union
		{
			uint8_t reg1 : 3;
			uint8_t opc : 3;
			uint8_t sreg3 : 3;
			uint8_t y : 3;
		};

		union
		{
			uint8_t reg : 3;
			uint8_t reg2 : 3;
			uint8_t rm : 3;
			uint8_t z : 3;
		};

		struct
		{
			uint8_t scale : 2;
			uint8_t index : 3;
			uint8_t base : 3;
		} sib;

		union
		{
			uint8_t s8;
			uint16_t s16;
			uint32_t s32;
		} disp;
		
		uint32_t ea;
	} modrm;

	uint32_t imm;
	uint16_t *imm16;
	uint8_t *imm8;

	int32_t disp;

	struct 
	{
		struct 
		{
			uint32_t eflags;
			uint32_t reg[8];
		}init, need;

	} track;

	struct 
	{
		uint8_t has_cond_pos : 1;
		uint32_t norm_pos;
		uint32_t cond_pos;
	} source;
};




#endif
