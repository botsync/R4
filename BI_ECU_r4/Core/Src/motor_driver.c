#include <stdint.h>

#define ACCESS_READONLY  0
#define ACCESS_READWRITE 1

typedef enum {
    TYPE_UNSIGNED8 = 0x0005,
    TYPE_UNSIGNED16 = 0x0006,
    TYPE_UNSIGNED32 = 0x0007,
    TYPE_VISIBLE_STRING = 0x0009
} DataType_t;

typedef struct {
    uint16_t index;
    uint8_t subIndex;
    const char *parameterName;
    uint8_t objectType;
    DataType_t dataType;
    uint8_t accessType;
    union {
        uint32_t u32;
        const char *str;
    } defaultValue;
    uint8_t pdoMapping;
} ObjectDictionaryEntry_t;

// 0x1029 - Error behavior subentries
static ObjectDictionaryEntry_t OD_1029[] = {
    {0x1029, 4, "generic", 0x7, TYPE_UNSIGNED16, ACCESS_READWRITE, {.u32=0x00}, 0},
    {0x1029, 5, "device profile", 0x7, TYPE_UNSIGNED16, ACCESS_READWRITE, {.u32=0x00}, 0},
    {0x1029, 6, "manufacturer specific", 0x7, TYPE_UNSIGNED16, ACCESS_READWRITE, {.u32=0x00}, 0}
};

// 0x1200 - SDO server parameter
static ObjectDictionaryEntry_t OD_1200[] = {
    {0x1200, 0, "highest sub-index supported", 0x7, TYPE_UNSIGNED8, ACCESS_READONLY, {.u32=0x2}, 0},
    {0x1200, 1, "COB-ID client to server", 0x7, TYPE_UNSIGNED32, ACCESS_READONLY, {.u32=0x600 /* $NODEID+0x600 */}, 0},
    {0x1200, 2, "COB-ID server to client", 0x7, TYPE_UNSIGNED32, ACCESS_READONLY, {.u32=0x580 /* $NODEID+0x580 */}, 0}
};

// 0x1400 to 0x1403 - RPDO communication parameters
static ObjectDictionaryEntry_t OD_1400[] = {
    {0x1400, 0, "highest sub-index supported", 0x7, TYPE_UNSIGNED8, ACCESS_READONLY, {.u32=0x2}, 0},
    {0x1400, 1, "COB-ID used by RPDO", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x200 /* $NODEID+0x200 */}, 0},
    {0x1400, 2, "transmission type", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0xff}, 0}
};

static ObjectDictionaryEntry_t OD_1401[] = {
    {0x1401, 0, "highest sub-index supported", 0x7, TYPE_UNSIGNED8, ACCESS_READONLY, {.u32=0x2}, 0},
    {0x1401, 1, "COB-ID used by RPDO", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x300 /* $NODEID+0x300 */}, 0},
    {0x1401, 2, "transmission type", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0xfe}, 0}
};

static ObjectDictionaryEntry_t OD_1402[] = {
    {0x1402, 0, "highest sub-index supported", 0x7, TYPE_UNSIGNED8, ACCESS_READONLY, {.u32=0x2}, 0},
    {0x1402, 1, "COB-ID used by RPDO", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x400 /* $NODEID+0x400 */}, 0},
    {0x1402, 2, "transmission type", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0xfe}, 0}
};

static ObjectDictionaryEntry_t OD_1403[] = {
    {0x1403, 0, "highest sub-index supported", 0x7, TYPE_UNSIGNED8, ACCESS_READONLY, {.u32=0x2}, 0},
    {0x1403, 1, "COB-ID used by RPDO", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x500 /* $NODEID+0x500 */}, 0},
    {0x1403, 2, "transmission type", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0xfe}, 0}
};

// 0x1600 - RPDO mapping parameter with 9 subindices
static ObjectDictionaryEntry_t OD_1600[] = {
    {0x1600, 0, "number of mapped application objects in RPDO", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0x1}, 0},
    {0x1600, 1, "1st application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x60400010}, 0},
    {0x1600, 2, "2nd application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 3, "3rd application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 4, "4th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 5, "5th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 6, "6th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 7, "7th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1600, 8, "8th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0}
};

// 0x1601 - RPDO mapping parameter with 9 subindices
static ObjectDictionaryEntry_t OD_1601[] = {
    {0x1601, 0, "number of mapped application objects in RPDO", 0x7, TYPE_UNSIGNED8, ACCESS_READWRITE, {.u32=0x2}, 0},
    {0x1601, 1, "1st application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x60400010}, 0},
    {0x1601, 2, "2nd application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x607A0020}, 0},
    {0x1601, 3, "3rd application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1601, 4, "4th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1601, 5, "5th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1601, 6, "6th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1601, 7, "7th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0},
    {0x1601, 8, "8th application object", 0x7, TYPE_UNSIGNED32, ACCESS_READWRITE, {.u32=0x00000000}, 0}
};




