#include <iostream>
#include "api.h"

using namespace std;

static int width = 800;
static int height = 600;
#define PI 3.1415926f

int main() {

    renderer_t *renderer = create_renderer(width, height);

    win_t *win = create_win(width, height, "NirvanaRenderer", renderer);

    Model *cube = new Model(R"(D:\Work\Git\NirvanaRenderer\Model\cube.obj)");

    mat_t world, view, projection;
    world.set_identity();
    view.set_lookat({3, 0, 0}, {0, 0, 0}, {0, 0, 1});
    float aspect = (float) width / (float) height;
    projection.set_perspective(PI * 0.5f, aspect, 1.0f, 500.0f);
    mat_t transform = world * view * projection;
    for (int i = 0; i < cube->face_size(); i++) {
        vec_t v1 = cube->vert(i, 0) * transform;
        vec_t v2 = cube->vert(i, 1) * transform;
        vec_t v3 = cube->vert(i, 2) * transform;
        cout << v1.toString() << endl;
        v1.to_screen_point(width, height);
        v2.to_screen_point(width, height);
        v3.to_screen_point(width, height);
        cout << v1.toString() << endl << endl;
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
