/* 
 * File:   libAlmondGui.h
 * Author: Devesh Rai <devesh@securifi.com>
 *
 * Created on 18 January, 2012, 9:02 PM
 */

#ifndef LIBALMONDGUI_H
#define	LIBALMONDGUI_H
#ifdef	__cplusplus
extern "C"
{
#endif
#define BUTTON		0
#define BACKBUTTON 	1
#define NEXTBUTTON 	2
#define RADIOBUTTON 	3
#define CHECKBOX 	4
#define TEXTBOX 	5
#define PINBOX 		6
#define CONTAINER       7
#define TEXTLABEL       8
#define COLOREDBUTTON   20

#define BACKGROUND_LAYER		14600
#define WIDGET_CONTAINER_LAYER          35794
#define BUTTON_LAYER                    5311//23284


void libAlmondGuiInit(void);

struct widget
{
    int x, y, color, selectColor, fontColor, selected, width, height, textX, textY, centered, lines, lineSpacing, type;
    float fontSize;
    wchar_t text[180];
    int isPassword;
    int isEnabled;
};

struct touchArea
{
    int x0, x1, y0, y1;
};



void setShowPasswords(int val);

void drawPicture(int x0, int y0, char * filename);
void drawPicture565(int x0, int y0, int width, int height, unsigned int * data);

void drawWidget(struct widget wid);
void unDrawWidget(struct widget wid);
struct touchArea getTouchArea(struct widget wid);
void drawTitle(wchar_t *text);
void unDrawTitle(wchar_t * title);

void fade(void);
void drawModal(void);
void drawPixel(unsigned short x0, unsigned short y0, unsigned short color);
void drawLine(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short color);
void drawRect(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short color);
void fillRect(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short color);
void drawCircle(unsigned short x0, unsigned short y0, unsigned short radius, unsigned short color);
void fillCircle(unsigned short x0, unsigned short y0, unsigned short radius, unsigned short color);
void drawRoundedRectangle(int x0, int y0, int x1, int y1, int color, int transperency);
void drawTransparentRectangle(int x0, int y0, int x1, int y1, int color, int transperency);
void drawLineXWU(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned short color);


void lcd_clear(unsigned int color);
void clearArea(void);
void drawFontBigWhiteString(wchar_t * text, int x, int y);
void unDrawFontBigWhiteString(wchar_t * text, int x, int y);
void drawFontSmallWhiteString(wchar_t * text, int x, int y);
void unDrawFontSmallString(wchar_t * text, int x, int y);
void drawFontSmallBlueString(wchar_t * text, int x, int y);
void drawFontSmallBlackString(wchar_t * text, int x, int y);
void drawFontSmallColorString(wchar_t * text, int x, int y);
void drawText(const wchar_t * text, int x, int y, int width, int lines, int lineSpacing, float size, int color, int center);
void drawTextWithBG(wchar_t * text, int x, int y, int width, int lines, int lineSpacing, float size, int fgColor, int bgColor, int center);
void enableAlphaBlending(void);
void disableAlphaBlending(void);
void setAlphaChannel(int Alpha);

//void drawText(wchar_t * text, int x, int y, int width, int lines, float size, int color, int center);
void turnOn(void);
void turnOff(void);
void loadBuffer(int number);
void copyBuffer(int to, int from);
void shiftScreen(int pixels);
void centerCurrentBuffer(void);
void drawFromBuffer(int buff);
int getCurentBuffer(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LIBALMONDGUI_H */

