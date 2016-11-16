#include "application.h"
#include "application_app.h"
#include "embindcefv8.h"
#include "gui_system.h"

#include <Urho3D/Engine/Engine.h>

gengine::application::App
    *mainApp;

using namespace Urho3D;

EMBINDCEFV8_DECLARE_STRING(String, CString)
EMBINDCEFV8_DECLARE_CLASS(gengine::application::App)

int main(int argc, char *argv[])
{
    gengine::gui::System::getInstance().preinit(argc, argv);

    mainApp = new gengine::application::App();

    embindcefv8::addGlobalObject(*mainApp, "gengine");

    gengine::gui::System::getInstance().init(argc, argv);

#ifdef EMSCRIPTEN
    embindcefv8::executeJavaScript(R"(
        $.ajax({
          url: "generated/main.js",
          dataType: "script",
          cache: false,
          complete: function() {
              console.log("[gengine] main.js loaded!");
              gengine = Module.gengine;
              Main.init();
              gengine.run();
          },
          error: function() {
              console.log("[gengine] Failed to load main.js");
          }
        });
    )");
#else
    auto engine = mainApp->getEngine();
    while(!engine->IsExiting())
    {
        gengine::gui::System::getInstance().update();
    }
#endif
}
