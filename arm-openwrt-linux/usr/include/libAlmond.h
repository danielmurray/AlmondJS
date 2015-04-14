/* 
 * File:   libAlmond.h
 * Author: devesh
 *
 * Created on 27 January, 2012, 5:22 PM
 */

#ifndef LIBALMOND_H
#define	LIBALMOND_H
#include "libAlmondGui.h"
#include "libTouch.h"
#include "libAlmondPNG.h"
#include "libuci.h"

#define NUMERIC			0
#define	ALPHANUMERIC            1
#define FORCE_NUMERIC		2
#define SPECIAL                 3
#define FORCE_SPECIAL           4
#define NUMBER_ONLY             5
#define	ALPHANUMERIC_NOSAVE     6


#define MODAL_TYPE_INFORMATION  1
#define MODAL_TYPE_CRITICAL     2
#define ASWPL                   255
#define ASWPLFMT                255     

class WidgetType {
public:
    WidgetType();
    int TextLabel, Button, ColoredButton, BackButton, NextButton, RadioButton,
    CheckBox, TextBox, PinBox, Container;
};
void draw_screenLock(void);
void get_screenLock_touch(int x, int y);
int isLocked();
int isLockScreen();
void slkHandle(void);

char* itoa(int i, char b[ASWPL]);
char* dtoa(double i, char b[ASWPL]);
char* utoxa(unsigned int i, char b[ASWPL]);
char* uitoa(unsigned int i, char b[ASWPL]);
int aswprintf(wchar_t *ret, int buff_len, wchar_t *args, ...);

class Widget {
public:

    Widget();
    Widget(int type, int x, int y, int width, int height, int selected, wchar_t text[180]);
    Widget(int type, int x, int y, int width, int height, int selected, int color, wchar_t text[180]);
    Widget(int type, int x, int y, int width, int height, int selected, int color, int selectColor, float size, int fontColor, wchar_t text[180]);
    Widget(int x, int y, int width, int lines, int lineSpacing, float size, int centered, int color /* = 65536 */, wchar_t text[180]); // For Text

    Widget(Widget& orig);
    virtual ~Widget();
    void draw(void);
    void unDraw(void);
    void isPassword(int isPassword);
    bool checkTouch(int x, int y);
    void (*onTouch) (void);
    void useKeyboard(bool useKbrd, char * setting); //Works only with PinBox and TextBox
    bool FIRST;
    bool LAST;
    void addWidget(Widget w);
    int id;
    Widget * next;
    Widget * prev;
    int getType(void);
    void setSelected(int state);
    void setText(wchar_t * text);
    struct widget W;
private:

    struct touchArea tA;
    bool useKey;
    char* settingName;

};

class Memory {
public:
    void getSetting(char *name, char *output);
    void getNoSaveSetting(char *name, char output[180]);
    void saveSetting(char *name, char *value);
    void commit(void);
    void addValue(char *name, char *value);
    void delSetting(char*name);
    void saveValues(void);
    void createSettingsFile(char *fileName);
    void getMac(char* output);
    void getCloudID(char* output);
    ~Memory();
private:
    char outputstring[180];
    char tempArea[180];
};

void setKeyboardValidationFunction(bool (*keyboardValidationFunction)(wchar_t* keyboardText));
void keyBoardSaveMode(bool save); //Default True

class Keyboard {
public:
    Keyboard();
    Keyboard(Keyboard& orig);
    virtual ~Keyboard();
    void getTouch(int x, int y);
    void draw(char * setting);
    void unDraw(void);
    void keyboardMode(int keyboardMode);
    void drawText(char * setting, wchar_t *ret);
    bool enabled;
    bool noCommit;
    void (*keyboardReturn)(void);
    void validateLT(int LT);
    void validateGT(int GT);
    int LT, GT, hideChar;
    wchar_t *retText;
private:
    char settingToChange[80];
    char settingData[180];
    void draw_NumericKeyboard(void);
    void draw_SpecialKeyboard(void);
    void get_SpecialKeyboard_touch(int x, int y);
    void get_NumericKeyboard_touch(int x, int y);
    void drawKeyboard(void);
    void get_Keyboard_touch(int x, int y);
    void keyboardDeleteChar();
    void keyboardAppendChar(wchar_t * c);
    Memory m;
    int mode;
    bool drawTextKb;
};
void setLockHandler(void (*lockHandlerToSet)(void));

class Screen {
public:
    Screen();
    Screen(wchar_t * Title);
    Screen(Screen& orig);
    void draw(void);
    void undraw(void);
    Widget *widgets;
    virtual ~Screen();
    void getTouch(int x, int y);
    Keyboard keyboard;
    void(*onExit)(void);
    bool backEn;
    bool exitEn;
    bool langEn;
    bool showHome;
    bool showHomeGrayed;
    void (*backHandler)(void);
    void (*languageReturn)(void);
    void (*homeHandler)(void);
    void setTitle(wchar_t title[25]);
    bool drawClear;
private:
    wchar_t title[25];
    void drawBaseScreen(int backEnabled);
};

class Modal {
public:
    Modal();
    void drawTimed(int type);
    void draw(int type, int timeout /* = 10 */);
    void setLine1(wchar_t line1[25]);
    void setLine2(wchar_t line2[25]);
    void setLine3(wchar_t line3[25]);
    void setLine4(wchar_t line4[25]);
    void setLine5(wchar_t line5[25]);
    void setPeriod(int period);
    void time(int t);
    void(*modalReturn)(void);
    ~Modal();
private:
    wchar_t text1[25];
    wchar_t text2[25];
    wchar_t text3[25];
    wchar_t text4[25];
    wchar_t text5[25];
    ImagePNG modalImages;

};

class Languages {
public:
    void refresh(void);
    wchar_t * get(char *tag_name, char *page_name);
    int gett(wchar_t opt[255], char* tag_name, char* page_name);
    Languages();
    //~Languages();
private:
    char output[180];
    char Lang[180];
    wchar_t * getvalue(char *file_name, char *tag_name, char *page_name);
    int gettext(wchar_t opt[255], char *file, char *tag, char *page);
};

class Persistence {
public:
    Persistence(char* app_id, char* app_ex);
    ~Persistence();
    void persist(char* volatileLocation, char* filename);
    void depersist(char* filename);
    void copyFile(char* persistentFile, char* location);
private:
    char persistDir[150];
};

#endif	/* LIBALMOND_H */

