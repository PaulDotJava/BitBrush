#include "EditorScene.h"
#include "raygui.h"
#include <memory>
#include <iostream>

#include <raylib.h>


void PencilTool::OnMousePressed(uint32_t x, uint32_t y)
{

}

void PencilTool::OnMouseReleased(uint32_t x, uint32_t y)
{

}

void PencilTool::OnUpdate()
{

}

void PencilTool::WhileMouseDown(uint32_t x, uint32_t y)
{
  ImageDrawPixel(&_Image, x, y, *_SelectedColor);
}

void BucketTool::OnMousePressed(uint32_t x, uint32_t y)
{

}

void BucketTool::OnMouseReleased(uint32_t x, uint32_t y)
{

}

void BucketTool::OnUpdate()
{

}

void BucketTool::WhileMouseDown(uint32_t x, uint32_t y)
{

}

EditorScene::EditorScene(Image image)
  : _Image(image)
  , _ImgPosition({
      .onScreenPos = { .x = GetWindowPosition().x / 2, .y = GetWindowPosition().y / 2 },
      .scale = 4.0f
    })
  , _SelectedColor({ 0, 0, 0, 255 })
{
  _Tools.push_back(std::make_shared<PencilTool>(_Image, &_SelectedColor));
  _Tools.push_back(std::make_shared<BucketTool>(_Image, &_SelectedColor));

  _CurrentTool = _Tools[0];
}

EditorScene::~EditorScene()
{

}

bool EditorScene::IsMouseOnImage()
{
  Vector2 mousePos = GetMousePosition();
  Rectangle img = { 
    .x = _ImgPosition.onScreenPos.x,
    .y = _ImgPosition.onScreenPos.y,
    .width = _Image.width * _ImgPosition.scale,
    .height = _Image.height * _ImgPosition.scale
  };

  return CheckCollisionPointRec(mousePos, img);
}

Vector2 EditorScene::GetMousePixel()
{
  Vector2 mousePos = GetMousePosition();
  Rectangle img = { 
    .x = _ImgPosition.onScreenPos.x,
    .y = _ImgPosition.onScreenPos.y,
    .width = _Image.width * _ImgPosition.scale,
    .height = _Image.height * _ImgPosition.scale
  };

  float scale = _ImgPosition.scale;

  Vector2 pixel { 
    .x = (mousePos.x - img.x) / scale,
    .y = (mousePos.y - img.y) / scale
  };

  return pixel;
}

void EditorScene::DoTool()
{
  if(IsMouseOnImage())
  {
    Vector2 pixel = GetMousePixel();
    
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      _CurrentTool->OnMousePressed(pixel.x, pixel.y);

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
      _CurrentTool->OnMouseReleased(pixel.x, pixel.y);

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
      _CurrentTool->WhileMouseDown(pixel.x, pixel.y);
  }

  _CurrentTool->OnUpdate();
}

void EditorScene::OnUpdate()
{ 
  if(IsKeyDown(KEY_SPACE) 
    && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
  {
    Vector2 mouseDelta = GetMouseDelta();
    _ImgPosition.onScreenPos.x += _ImgPosition.onScreenPos.x > 140 ? mouseDelta.x : 1;
    _ImgPosition.onScreenPos.y += mouseDelta.y;
  } else if(GetMouseWheelMoveV().y != 0)
  {
    int32_t dv = GetMouseWheelMoveV().y;
    std::cout << "dv: " << dv << std::endl;
    _ImgPosition.scale += (float)dv / 10;
  } else 
  {
    DoTool();
  }

  DrawTextureEx(LoadTextureFromImage(_Image), _ImgPosition.onScreenPos, 0.0f, _ImgPosition.scale, Color{255, 255, 255, 255});

  uint32_t spacing = 40;
  uint32_t i = 0;
  for(auto& tool : _Tools)
  {
    if(GuiButton({ 10, (float)10 + (i * spacing), 80, 30 }, std::string(tool->GetName() + (tool == _CurrentTool ? " (Active)" : "")).c_str()))
    {
      _CurrentTool = tool;
    }
    i++;
  }
  
  Rectangle cr {
    .x = 10,
    .y = (float)GetScreenHeight() - 10 - 100,
    .width = 100,
    .height = 100
  };

  GuiColorPicker(cr, "Color", &_SelectedColor);
}

void EditorScene::OnEnter()
{

}

void EditorScene::OnLeave()
{

}
