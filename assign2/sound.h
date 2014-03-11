#ifndef   SOUND
#define   SOUND

#include <stdconst.h>

void SoundInit(void);
void SoundSync(ULONG *pattern, UBYTE length, UBYTE rate, UWORD duration);
void SoundAsync(ULONG *pattern, UBYTE length, UBYTE rate, UWORD duration);
void SoundExit(void);
void SoundEnable(void);
void SoundDisable(void);
void SoundIntEnable(void(*handler)(void));
void SoundIntDisable(void);
void sound_handler(void);

#endif
