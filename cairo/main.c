#include <cairo/cairo.h>

int main()
{

    cairo_surface_t *surface;
    cairo_t *cr; //声明一支画笔
    double width = 1000;
    double y = 300 + sqrt(3) * width / 2;
    int n = 10;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 600, 600);
    cr = cairo_create(surface);        //创建画笔
    cairo_set_source_rgb(cr, 0, 1, 0); //设置画笔颜色，也就是红，绿，蓝，这里设置成绿色。
    cairo_set_line_width(cr, 3);

    cairo_select_font_face(cr,
                           "STSong",
                           CAIRO_FONT_SLANT_NORMAL,
                           CAIRO_FONT_WEIGHT_BOLD); //设置字体样式

    cairo_set_font_size(cr, 20); //设置字体大小

    cairo_move_to(cr, 100, 100);
    cairo_show_text(cr, "hello world"); //绘制英文
    cairo_move_to(cr, 100, 200);
    cairo_show_text(cr, "你好"); //绘制中文

    //cairo_fill(cr);                       //填充，使用的颜色当然是上面设置的颜色。
    cairo_surface_write_to_png(surface, "f.png"); //写入png文件
    cairo_destroy(cr);                            //销毁画笔

    return 0;
}