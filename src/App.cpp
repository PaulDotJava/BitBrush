#include "App.h"

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
