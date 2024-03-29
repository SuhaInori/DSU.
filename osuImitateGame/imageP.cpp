/*                  easyX扩展图片处理库
* @version -1.0                                                              
* 1.透明图片显示
* 2.图片旋转
*/
#ifndef EX_EASYX_H
#define EX_EASYX_H
#define _USE_MATH_DEFINES
#include "libH.h"
#ifndef M_RD
#define M_RD 0.01745329251994329576923690768489
#endif
//2x3矩阵
class gdimat2 : public XFORM
{
public:
    gdimat2(){
        this->identity();
    }
    void identity(){
        eM11 = 1.0f; eM12 = 0.0f;
        eM21 = 0.0f; eM22 = 1.0f;
        eDx = 0.0f; eDy = 0.0f;
    }
    void translate(float x, float y){
        XFORM mat;
        mat.eM11 = 1.0f; mat.eM12 = 0.0f;
        mat.eM21 = 0.0f; mat.eM22 = 1.0f;
        mat.eDx = x;
        mat.eDy = y;
        CombineTransform(this, this, &mat);
    }
    void scale(float x, float y){
        XFORM mat;
        mat.eM11 = x;    mat.eM12 = 0.0f;
        mat.eM21 = 0.0f; mat.eM22 = y;
        mat.eDx = 0.0f;
        mat.eDy = 0.0f;
        CombineTransform(this, this, &mat);
    }
    void rotate(float angle){
        using namespace std;
        XFORM mat;
        angle *= M_RD;
        float cosin = cos(angle);
        float sine = sin(angle);
        mat.eM11 = cosin; mat.eM12 = sine;
        mat.eM21 = -sine; mat.eM22 = cosin;
        mat.eDx = 0.0f;
        mat.eDy = 0.0f;
        CombineTransform(this, this, &mat);
    }
    //应用到目标HDC
    void use(HDC dc){
        SetWorldTransform(dc, this);
    }
};

//easyx扩展，绘制透明png图片
#pragma comment (lib, "MSIMG32.lib")
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1){
    BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    int width = image.getwidth();
    int height = image.getheight();
    if (w == -1)w = width;
    if (h == -1)h = height;
    AlphaBlend(GetImageHDC(), x, y, w, h, GetImageHDC(&image), 0, 0, width, height, blendfunc);
}

//绘制旋转的图片，支持透明png图片
void rotate(IMAGE& image, int x, int y, int w, int h, float angle){
    HDC dc = GetImageHDC();//获取当前绘图dc 
    gdimat2 m; //矩阵
    m.rotate(angle);    //旋转
    m.translate(x, y);  //平移
    m.use(dc);
    BLENDFUNCTION blendfunc = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    int width = image.getwidth();
    int height = image.getheight();
    x = -w / 2; //绘制位置设置图片的中心点
    y = -h / 2;
    AlphaBlend(dc, x, y, w, h, GetImageHDC(&image), 0, 0, width, height, blendfunc);
    m.identity(); //初始化矩阵
    m.use(dc); //恢复dc初始变换
}


#endif EX_EASYX_H