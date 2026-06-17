// defines.h

// Reads a specific bit from WORD at position BIT (returns 0 or 1)
#define READBIT(WORD,BIT) ((WORD>>BIT)&1)

// Writes a 4-bit value (VAL) into WORD starting at bit position NIBBLESTARTBITPOS
// Clears the target nibble and sets it with VAL (masked to 4 bits)
#define WRITENIBBLE(WORD,NIBBLESTARTBITPOS,VAL) WORD=((WORD&(~(15<<NIBBLESTARTBITPOS))) | (((VAL&15)<<NIBBLESTARTBITPOS)))

// Reads a 4-bit nibble from WORD starting at bit position NIBBLESTARTBIT
#define READNIBBLE(WORD,NIBBLESTARTBIT) ((WORD>>NIBBLESTARTBIT)&15)

// Writes an 8-bit value (VAL) into WORD starting at bit position BYTESTARTBITPOS
// Clears the target byte and replaces it with VAL (masked to 8 bits)
#define WRITEBYTE(WORD,BYTESTARTBITPOS,VAL) WORD=((WORD&(~(255<<BYTESTARTBITPOS))) | (((VAL&255)<<BYTESTARTBITPOS)))

// Writes a single bit (BIT: 0 or 1) to WORD at bit position BITPOS
// Clears the bit at BITPOS and sets it to BIT
#define WRITEBIT(WORD,BITPOS,BIT) WORD=((WORD&(~(1<<BITPOS))) | (BIT<<BITPOS))
