#include "App.h"
#include "StartupScene.h"

void App::Init()
{
  _CurrentScene = std::make_shared<StartupScene>();
  _CurrentScene->OnEnter();
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
