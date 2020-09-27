#include <iostream>
#include "api.h"

using namespace std;

static int screen_width = 800;
static int screen_height = 600;
static float z_near = 1.0f;
static float z_far = 500.0f;

#define PI 3.1415926f
#define aspect ((float)screen_width / (float)screen_height)

int main() {

    renderer_t *renderer = create_renderer(screen_width, screen_height);

    win_t *win = create_win(screen_width, screen_height, "NirvanaRenderer", renderer);

    Model *cube = new Model(R"(..\Model\cube.obj)");

    mat4_t world = mat4_t::identity();
    mat4_t view = mat4_look_at({3, 0, 0}, {0, 0, 0});
    mat4_t projection = mat4_perspective(PI * 0.5f, aspect, z_near, z_far);
    mat4_t viewport = mat4_viewport(0, 0, screen_width, screen_height, z_near, z_far);
    mat4_t transform = world * view * projection * viewport;
    for (int i = 0; i < cube->face_size(); i++) {
        vec4_t v1 = transform * cube->vert(i, 0);
        vec4_t v2 = transform * cube->vert(i, 1);
        vec4_t v3 = transform * cube->vert(i, 2);
        cout << v1.toString() << endl << v2.toString() << endl << v3.toString() << endl << endl;
        renderer->draw_triangle_wireframe(v1, v2, v3, {255, 0, 0});
    }

    delete cube;

    win->update_win();

    MSG msg;
    while (GetMessage(&msg, (HWND) nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
