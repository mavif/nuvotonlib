#ifndef _lcd_h_
#define _lcd_h_
extern void lcd(void);
extern void backlight(void);
extern void text(unsigned char line, char *str);
extern void clear(void);
#endif
