//
// Created by yangyinlong01 on 2020/9/22.
//

#ifndef NIRVANARENDERE_RENDERER_H
#define NIRVANARENDERE_RENDERER_H

typedef struct {
    int width;
    int height;
    UCHAR *frame_buffer;
    float *z_buffer;

    void set_color(int index, color_t color) {
        for (int i = 0; i < 4; frame_buffer[index + i] = color[i], i++);
    }

    void clear_color(color_t color) {
        int pixel_count = width * height;
        for (int i = 0; i < pixel_count; i++) {
            set_color(i * 4, color);
        }
    }

    void draw_pixel(int x, int y, color_t color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            set_color((y * width + x) * 4, color);
        }
    }

    void draw_line(int x1, int y1, int x2, int y2, color_t color) {
        int x, y, rem = 0;
        if (x1 == x2 && y1 == y2) {
            draw_pixel(x1, y1, color);
        } else if (x1 == x2) {
            int inc = (y1 <= y2) ? 1 : -1;
            for (y = y1; y != y2; y += inc) draw_pixel(x1, y, color);
            draw_pixel(x2, y2, color);
        } else if (y1 == y2) {
            int inc = (x1 <= x2) ? 1 : -1;
            for (x = x1; x != x2; x += inc) draw_pixel(x, y1, color);
            draw_pixel(x2, y2, color);
        } else {
            int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
            int dy = (y1 < y2) ? y2 - y1 : y1 - y2;
            if (dx >= dy) {
                if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; x <= x2; x++) {
                    draw_pixel(x, y, color);
                    rem += dy;
                    if (rem >= dx) {
                        rem -= dx;
                        y += (y2 >= y1) ? 1 : -1;
                        draw_pixel(x, y, color);
                    }
                }
                draw_pixel(x2, y2, color);
            } else {
                if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; y <= y2; y++) {
                    draw_pixel(x, y, color);
                    rem += dx;
                    if (rem >= dy) {
                        rem -= dy;
                        x += (x2 >= x1) ? 1 : -1;
                        draw_pixel(x, y, color);
                    }
                }
                draw_pixel(x2, y2, color);
            }
        }
    }

    void draw_triangle_wireframe(vec_t v1, vec_t v2, vec_t v3, color_t color) {
        draw_line(v1.x, v1.y, v2.x, v2.y, color);
        draw_line(v2.x, v2.y, v3.x, v3.y, color);
        draw_line(v3.x, v3.y, v1.x, v1.y, color);
    }

} renderer_t;

renderer_t *create_renderer(int width, int height) {
    assert(width > 0 && height > 0);
    renderer_t *renderer = new renderer_t();
    int frame_size = sizeof(void *) * width * height;
    int z_size = sizeof(float) * width * height;
    renderer->width = width;
    renderer->height = height;
    renderer->frame_buffer = (UCHAR *) malloc(frame_size);
    renderer->z_buffer = (float *) malloc(z_size);
    renderer->clear_color({0, 0, 0, 255});
    return renderer;
}

#endif //NIRVANARENDERE_RENDERER_H
