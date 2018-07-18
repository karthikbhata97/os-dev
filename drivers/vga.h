#define VIDEO_ADDRESS 0xb8000
#define BLACK_ON_WHITE 0x0f
#define RED_ON_WHITE 0xf4
#define MAX_ROWS 25
#define MAX_COLUMNS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void kprint_at(char *, int, int);
void kprint(char *);
int scroll(int);