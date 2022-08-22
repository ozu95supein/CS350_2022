#include "common.hpp"
#include "debug_system.hpp"
#include "camera.hpp"

namespace {
    constexpr unsigned window_width  = 1024;
    constexpr unsigned window_height = 576;

    /**
     * @brief
     *  Setups the scene
     */
    void setup_scene(camera& c)
    {
        // Setup frame
        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, window_width, window_height);

        // Camera
        c.set_position({0, 0, 10});
        c.set_target({0, 0, 0});
        c.set_projection(60.0f, {window_width, window_height}, 0.01f, 1000.0f);
        c.update();
    }

    /**
     * @brief
     * @return
     */
    std::string current_test_image_filename()
    {
        return std::string(WORKDIR "out/") + test_name() + ".png";
    }

}

TEST(basic, draw_point)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    debug.draw_point({0, 0, 0}, {1, 0, 0, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

/*
TEST(basic, draw_segment)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    // White quad
    debug.draw_segment({0, 0, 0}, {1, 0, 0}, {1, 1, 1, 1});
    debug.draw_segment({1, 0, 0}, {1, 1, 0}, {1, 1, 1, 1});
    debug.draw_segment({1, 1, 0}, {0, 1, 0}, {1, 1, 1, 1});
    debug.draw_segment({0, 1, 0}, {0, 0, 0}, {1, 1, 1, 1});

    // Random
    debug.draw_segment({0, 1, 0}, {1, 0, 0}, {1, 1, 0, 1});
    debug.draw_segment({0, 0, 1}, {5, 3, -1}, {1, 0, 1, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

TEST(basic, draw_triangle)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    debug.draw_triangle({0, 1, 0}, {-1, -1, 0}, {1, -1, 0}, {1, 1, 1, 1});
    debug.draw_triangle({2, 1, 0}, {1, -1, 0}, {3, -1, 0}, {1, 0, 0, 1});
    debug.draw_triangle({-2, 1, 0}, {-3, -1, 0}, {-1, -1, 0}, {0, 1, 0, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

TEST(basic, draw_aabb)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    {                                                      // Set style
        glDepthMask(GL_TRUE);                              // Write depth,
        glEnable(GL_DEPTH_TEST);                           // And test depth
        glDepthFunc(GL_LESS);                              //
        glEnable(GL_CULL_FACE);                            // Culling
        glCullFace(GL_BACK);                               // Cull inner faces
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);         // Full triangles
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Blending
    }

    debug.draw_aabb({0, 0, 0}, {1, 1, 1}, {1, 1, 1, 1});
    debug.draw_aabb({-4, -2.5, -4}, {1, 2.5, 1}, {1, 0, 1, 1});
    debug.draw_aabb({2.5, 3, 0.5}, {0.5, 1, 0.5}, {0, 0, 1, 0.15});

    { // Different style
        //
        glDepthMask(GL_FALSE);                     // Do not write depth,
        glEnable(GL_DEPTH_TEST);                   // but test depth
        glDepthFunc(GL_LEQUAL);                    // Try to solve ZFighting
        glDisable(GL_CULL_FACE);                   // Culling
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Lines
        glDisable(GL_BLEND);                       // Blending
    }

    debug.draw_aabb({0, 0, 0}, {1, 1, 1}, {0, 0, 0, 1});
    debug.draw_aabb({-4, -2.5, -4}, {1, 2.5, 1}, {0, 0, 0, 1});
    debug.draw_aabb({2.5, 3, 0.5}, {0.5, 1, 0.5}, {0, 0, 0, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

TEST(basic, draw_plane)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    glEnable(GL_CULL_FACE); // Culling
    glCullFace(GL_BACK);    // Cull inner faces

    // White quad front facing the camera
    debug.draw_plane({0, 0, 0}, glm::normalize(glm::vec3({1, 1, 1})), 1.0f, {1, 1, 1, 1});

    // Big plane backfacing the camera
    debug.draw_plane({5, 0, 0}, glm::normalize(glm::vec3({1, 1, -1})), 2.0f, {1, 1, 1, 1}); // SHOULD NOT VISIBLE!

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

TEST(basic, draw_spheres)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    debug_system debug(&c);

    glEnable(GL_CULL_FACE); // Culling
    glCullFace(GL_BACK);    // Cull inner faces

    debug.draw_sphere({0, 0, 0}, 1.0f, {1, 1, 1, 1});
    // To see horizon disc
    debug.draw_sphere({1, 0, 8}, 0.5f, {0, 1, 1, 1});
    debug.draw_sphere({-1, 0, 8}, 0.5f, {1, 0, 0, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}

TEST(extra, draw_frustum)
{
    window w(window_width, window_height, test_name(), false);
    camera c;
    setup_scene(c);
    c.set_position({10,10,10});
    c.set_target({});
    c.update();
    debug_system debug(&c);

    glDisable(GL_CULL_FACE);                   // Culling
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe
    mat4 vp = glm::perspective(glm::radians(30.0f), 1920 / 1080.0f, 2.0f, 10.0f) *
              glm::lookAt(vec3{-4, 0, 0}, vec3{3, 1, -1}, vec3{0, 1, 0});
    debug.draw_frustum_lines(vp, {1, 1, 1, 1});

    save_screenshoot(window_width, window_height, current_test_image_filename());
}*/