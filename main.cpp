#include <iostream>
#include "api.h"

using namespace std;

static int screen_width = 800;
static int screen_height = 600;

void update_input() {

}

int main() {
    renderer_t *renderer = create_renderer(screen_width, screen_height);
    win_t *win = create_win(screen_width, screen_height, "NirvanaRenderer", renderer);
    camera_t *camera = create_camera({0, 0, 100});
    Model *model = new Model(R"(..\Model\qlsn.obj)");

    MSG msg;
    while (GetMessage(&msg, (HWND) nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (keys[VK_UP]) model->transform->rotation.x -= 1;
        if (keys[VK_DOWN]) model->transform->rotation.x += 1;
        if (keys[VK_LEFT]) model->transform->rotation.y -= 1;
        if (keys[VK_RIGHT]) model->transform->rotation.y += 1;
        if (keys[VK_E]) model->transform->position.y += 1;
        if (keys[VK_Q]) model->transform->position.y -= 1;
        if (keys[VK_A]) model->transform->position.x -= 1;
        if (keys[VK_D]) model->transform->position.x += 1;
        if (keys[VK_W]) model->transform->position.z += 1;
        if (keys[VK_S]) model->transform->position.z -= 1;
        if (keys[VK_R]) model->transform->scale = {2, 2, 2};
        if (keys[VK_T]) model->transform->scale = {1, 1, 1};

        renderer->clear_color({0, 0, 0});

        mat4_t world = model->get_transform_matrix();
        mat4_t view = get_view_matrix(camera);
        mat4_t projection = get_projection_matrix(camera, get_aspect(win));
        mat4_t transform = projection * view * world;
        for (int i = 0; i < model->face_size(); i++) {
            vec4_t screen_point[3];
            for (int j = 0; j < 3; j++) {
                vec4_t ndc_point = transform * model->vert(i, j);
                screen_point[j] = viewport_transform(screen_width, screen_height, ndc_point);
            }
            renderer->draw_triangle_wireframe(screen_point, {255, 0, 0});
        }

        win->update_win();
    }

    return 0;
}