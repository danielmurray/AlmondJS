#ifndef LIBALMONDPNG_H
#define	LIBALMONDPNG_H
#define DRAW_PNG                        20      // Draw png files use lcdPNG structure
#define READ_LCD_AREA			32

#define getR(RGB)           ((RGB & 0xF800) >> 8)
#define getG(RGB)           ((RGB & 0x7E0) >> 3)
#define getB(RGB)           ((RGB & 0x1F) << 3)

typedef struct RGBA {
    unsigned char *r, *g, *b, *a;
} rgba;

typedef struct PNG {
    int x0, y0, width, height, bg;
    rgba data;
    unsigned char transparent;

} lcdPNG;

typedef struct IMAGE {
    int x0, y0, width, height;
    int* data;
} lcdImage;

class ImagePNG {
public:
    ImagePNG();
    ~ImagePNG();
    void drawPNG(int x0, int y0, int isTransparent, int backgroundColor, int which);
    int loadPNG(const char file_name[255]);
    void deletePNG(int which);

private:
    void abort_(const char * s, ...);
    lcdPNG *imagePNG[50];
    int n;

};

class ScreenshotPNG {
public:
    ScreenshotPNG();
    ~ScreenshotPNG();
    void write_png_file(char* file_name, int x0, int y0, int width, int height);
    void create_png(char *png_filename, int height_png, int width_png, unsigned char *data);
private:
    void abort_(const char * s, ...);


};


#endif	/* LIBALMONDPNG_H */




