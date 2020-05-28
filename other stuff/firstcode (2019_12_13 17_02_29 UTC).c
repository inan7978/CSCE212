//240x160
//ARM7tdmi 16.78MHz
//16 bit color words 
//0x00000000 -> 0x00003fff (System Rom, executable not reachable)
//0x02000000 -> 0x02020000 (External to the CPU RAM 256 KB)
//0x03000000 -> 0x03007fff (Internal to the CPU RAM 32 KB)
//0x04000000 -> 0x040003ff (I/O registers)
//0x05000000 -> 0x050003ff (Color palette)
//0x06000000 -> 0x06017fff (VRAM 96 KB)
//0x07000000 -> 0x070003ff (OAM RAM)
//0x08000000 -> 0x0??????? (Gamepak ROM (up to 32MB))
//0x0E000000 -> 0x0??????? (Gamepak RAM)

#define REG_DISPLAY_VCOUNT (* (volatile unsigned short *)(0x04000006))

void sync()
{
  while(REG_DISPLAY_VCOUNT >=160);
  while(REG_DISPLAY_VCOUNT < 160);

}

int main()

{
volatile unsigned char *ioram = (unsigned char *)0x04000000;
ioram[0] = 0x03; //setting video node to 3
ioram[1] = 0x04; //enables above video mode

volatile unsigned short *vram = (unsigned short *)0x06000000;
int inc = 0;
int clearLine = 0;
while(1)
{
     sync();
     
     vram[clearLine * 240 + 110] = 0x0000;
     vram[clearLine * 240 + 120] = 0x0000;
     vram[clearLine * 240 + 130] = 0x0000;
     
     vram[inc * 240 + 110] = 0x001f;
     vram[inc * 240 + 120] = 0x03e0;
     vram[inc * 240 + 130] = 0x7c00;

     clearLine = inc;
     inc = inc + 1;
     if(inc>=160)
     inc = 0;
}
}
