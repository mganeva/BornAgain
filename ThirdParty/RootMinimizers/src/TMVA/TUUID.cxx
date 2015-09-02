#include "TMVA/TUUID.h"
#include <string.h>

TUUID::TUUID() : fTimeLow(0)
{

}

void TUUID::GetUUID(UChar_t uuid[16]) const
{
   // Return uuid in specified buffer (16 byte = 128 bits).

   memcpy(uuid, &fTimeLow, 16);
}
