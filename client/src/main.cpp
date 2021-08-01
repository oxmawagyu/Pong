#include "main.hpp"
#include "ui/test_menu.hpp"

int main() {
    std::shared_ptr<GraphicsContext> g_context = std::make_shared<GraphicsContext>(800, 600);
    std::cout << "Succesfully initialised graphicsContext!\n";

    std::shared_ptr<EventHandler> handler { std::make_shared<EventHandler>() };
    std::unique_ptr<Menu> test_menu = Test_Menu(g_context, handler);

    bool done {false};
    Event event;
    while(!done) {
        test_menu->render();
        g_context->display();

        // test_menu->update();
        // SDL_PollEvent(&event);
        event = handler->PollEvent();
        if(event.type == EVENT_TYPES::UNHANDLED_SDL_EVENT) {
            switch (event.sdl_event.type) {
                case (SDL_QUIT): {
                    done = true;
                    break;
                }
                case (SDL_WINDOWEVENT): {
                    if(event.sdl_event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        g_context->updateWindowSize(event.sdl_event.window.data1, event.sdl_event.window.data2);
                        test_menu->updateSize();
                        // std::cout << "Resized window:\t" << event.window.data1 << ", " << event.window.data2 << "\t" << g_context.getWidth() << ", " << g_context.getHeight() << "\n";
                    }
                    break;
                }
            }
        }
    }
    return 0;
}