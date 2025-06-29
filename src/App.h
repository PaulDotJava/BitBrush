#pragma once

#include <memory>
#include <utility>

class AppScene
{
public:
  virtual void OnUpdate() = 0;
  virtual void OnEnter() = 0;
  virtual void OnLeave() = 0;
};

class App
{
public:
  static void Init();
  static void OnUpdate();

  template <typename Scene, typename... Args>
  static void SwitchScenes(Args&&... args) 
  {
    _NextScene = std::make_shared<Scene>(std::forward<Args>(args)...);   
  }
private:
  static inline std::shared_ptr<AppScene> _CurrentScene;
  static inline std::shared_ptr<AppScene> _NextScene;
};

