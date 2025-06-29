#include "App.h"
#include "EditorScene.h"
#include "StartupScene.h"
#include <memory>

void App::Init()
{
  Image image;
  image.width = 64;
  image.height = 64;
  image.data = new char[64 * 64 * 3];
  image.format = 4;
  _CurrentScene = std::make_shared<EditorScene>(image);
}

void App::OnUpdate()
{
  if(_NextScene)
  {
    _CurrentScene->OnLeave();
    _CurrentScene = _NextScene;
    _CurrentScene->OnEnter();

    _NextScene.reset();
  }

  _CurrentScene->OnUpdate();
}
