#ifndef __program_h
#define __program_h

#include <asm/types.h>

#define DEVICE_JOYSTICK		128
#define DEVICE_KBD		64
#define DEVICE_MOUSE		32
#define DEVICE_NONE		0

#define TYPE_AXIS		1
#define TYPE_BUTTON		2
#define TYPE_SHIFT		3 //the shift button, target for button remap

#define FLAG_NONE		0
#define FLAG_AUTO_RELEASE 	1
#define FLAG_INVERT	 	2
#define FLAG_RELEASE		4
#define FLAG_SHIFT		8 //only if shifted
#define FLAG_PRESS		16 //not used by driver
#define KEYMASK			0xfff
#define RELEASEMASK		32768
#define SEQUENCE_DONE		65535

#define PROGRAM_AXIS_REMAP	1
#define PROGRAM_BUTTON_REMAP	2
#define PROGRAM_AXIS_PROPERTIES 3
#define PROGRAM_CODE		4

#define MAX_SEQUENCE		16	//approximately 8 keys max
#define JOYSTICK_USE_VENDOR	255
#define JOYSTICK_CODE		255 
#define JOYSTICK_CODE_VENDOR	0 
#define JOYSTICK_CODE_PRODUCT	0 

#define MAX_CODE_SIZE		16384

//virtual machine instructions
#define HALT	0  
#define JZ	1  
#define JUMP	2 
#define JUMPREL	3
#define ADD	4 
#define SUB	5
#define MUL	6
#define DIV	7 
#define LT	8
#define LE	9
#define GT	10
#define GE	11
#define EQ	12
#define NEQ	13
#define AND	14
#define OR	15
#define NOT	16
#define PUSH	17
#define POP	18
#define DEC	19
#define INC	20
#define KEY	21 //press a key
#define SIGNAL	22 //send a signal to a daemon
#define THREAD	23 //context switch, gets two jump targets from the stack: 
			//1-where to return when thread stops  
			//2-where to start the thread 
#define YIELD   24 //return from a thread (back to main thread)
#define NEG	25
#define JOIN	26 //stop an executing thread
#define PUSHA	27 //for arrays
#define POPA	28 //for arrays
#define DECA	29 //for arrays
#define INCA	30 //for arrays

//address types
#define GP	0
#define CODEB	1
#define CODEA	2
#define JS	3
#define CONST	4	

//registers, first 10 are reserved or fixed function
#define RESERVED	10
#define FIRSTSCAN	0
#define CLOCKTICK	1
#define XREL		2
#define YREL		3
#define ZREL		4
#define TIMESTAMP	5
#define	CURRENTMODE	6
//the offset register, always added to any address 
//registers, joystick etc) but not constants or stack
//the ofsreg is reset to zero after every instruction
#define OFSREG		7

//use the joystick if specified, if joystick is 255
// then use the vendor and product to identify the 
// joystick. This device should already be present in the
//	system. Otherwise the map is ignored.
// if vendor=255 and product=0, then this refers to the virtual CODE joystick
struct program_axis_remap {
	__u8 program;   //PROGRAM_AXIS_REMAP
	__u8 joystick;
	__u16 vendor;
	__u16 product;
	__u8 srcaxis;   
	__u8 device;	//low bits of device identify joystick
	__u8 type;
	__u8 flags;
	__u16 axis;
	__u16 plus;	//can be a key or button
	__u16 minus;
};

struct program_axis_properties {
	__u8 program;   //PROGRAM_AXIS_PROPERTIES
	__u8 joystick;
	__u16 vendor;
	__u16 product;
	__u8 srcaxis;   
	__u8 flags;
	__s16 scale;	//8.8 fixed point
	__s16 bias;	//shift after scale
	__u16 threshhold;
};

#define press sequence[0]
#define release sequence[0]
struct program_button_remap {
	__u8 program;   //PROGRAM_BUTTON_REMAP
	__u8 joystick;
	__u16 vendor;
	__u16 product;
	__u16 srcbutton;   
	__u8 device;	//low bits of device identify joystick
	__u8 type;
	__u8 flags;
	__u16 sequence[MAX_SEQUENCE];   //if top bit set, release
//	__u16 press;		//can also be a target button or axis
//	__u16 release;		//release is ignored for an axis
};

struct program_code {
	__u8 program;   //PROGRAM_CODE
	unsigned char code[MAX_CODE_SIZE]; //1024 4 byte codes
};

#endif

