//
// Created by yangyinlong01 on 2020/9/22.
//

#ifndef NIRVANARENDERE_WIN_H
#define NIRVANARENDERE_WIN_H

#include <windows.h>
#include "../Core/input.h"

struct win_t {
    HWND handle;
    int width;
    int height;
    HDC memory_dc;

    void update_renderer(renderer_t renderer) {
        //renderer.draw_triangle_wireframe()
    }

    void update_win() const {
        HDC hDC = GetDC(handle);
        BitBlt(hDC, 0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
        ReleaseDC(handle, hDC);
    }
};

float get_aspect(win_t *win) {
    return (float) win->width / win->height;
}

win_t *create_win(int, int, const char *, renderer_t *);

WNDCLASS register_class(const char *);

static LRESULT CALLBACK event_win(HWND, UINT, WPARAM, LPARAM);

win_t *create_win(int width, int height, const char *title, renderer_t *renderer) {
    WNDCLASS wc = register_class(title);
    assert(RegisterClass(&wc));

    HWND handle = CreateWindow(title, title,
                               WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                               0, 0, 0, 0,
                               nullptr, nullptr,
                               wc.hInstance, nullptr);
    assert(handle != nullptr);

    HDC window_dc = GetDC(handle);
    HDC memory_dc = CreateCompatibleDC(window_dc);
    ReleaseDC(handle, window_dc);

    // 分配bitmap和framebuffer
    LPVOID ptr;
    BITMAPINFOHEADER bitmap_header;
    memset(&bitmap_header, 0, sizeof(BITMAPINFOHEADER));
    bitmap_header.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_header.biWidth = width;
    bitmap_header.biHeight = height;
    bitmap_header.biPlanes = 1;
    bitmap_header.biBitCount = 32;
    bitmap_header.biCompression = BI_RGB;
    HBITMAP hbitmap = CreateDIBSection(memory_dc, (BITMAPINFO *) &bitmap_header,
                                       DIB_RGB_COLORS, &ptr, nullptr, 0);
    assert(hbitmap != nullptr);
    HBITMAP old_bitmap = (HBITMAP) SelectObject(memory_dc, hbitmap);
    DeleteObject(old_bitmap);
    // 分配bitmap和framebuffer

    // 调整界面大小
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, GetWindowLong(handle, GWL_STYLE), 0);
    int wx = rect.right - rect.left;
    int wy = rect.bottom - rect.top;
    int sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
    int sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
    if (sy < 0) sy = 0;
    SetWindowPos(handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
    // 调整界面大小

    memset(keys, 0, (sizeof(int) * 512));

    ShowWindow(handle, SW_SHOW);
    UpdateWindow(handle);

    renderer->width = width;
    renderer->height = height;
    renderer->frame_buffer = (UCHAR *) ptr;

    win_t *win = new win_t();
    win->handle = handle;
    win->width = width;
    win->height = height;
    win->memory_dc = memory_dc;
    return win;
}

WNDCLASS register_class(const char *title) {
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpfnWndProc = event_win;
    wc.lpszClassName = title;
    wc.lpszMenuName = nullptr;
    wc.style = CS_BYTEALIGNCLIENT;
    return wc;
}

static LRESULT CALLBACK event_win(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    float offset;
    switch (msg) {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            keys[wParam & 511] = 1;
            break;
        case WM_KEYUP:
            keys[wParam & 511] = 0;
            break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

#endif //NIRVANARENDERE_WIN_H
