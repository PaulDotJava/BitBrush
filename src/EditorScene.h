#pragma once

#include "App.h"
#include <vector>
#include <raylib.h>

#include <iostream>

class Tool
{
public:
  Tool(Image& image, Color* color, const std::string& name)
    : _Image(image)
    , _Name(name)
    , _SelectedColor(color)
  {}

public:
  virtual const std::string& GetName() const { return _Name; };

  virtual void OnMousePressed(uint32_t x, uint32_t y) = 0;
  virtual void OnMouseReleased(uint32_t x, uint32_t y) = 0;
  virtual void WhileMouseDown(uint32_t x, uint32_t y) = 0;

  virtual void OnUpdate() = 0;
protected:
  Image& _Image;
  std::string _Name;
  Color* _SelectedColor;
};

class PencilTool : public Tool
{
public:
  PencilTool(Image& image, Color* color)
    : Tool(image, color, "Pencil")
  {}

public:
  virtual void OnMousePressed(uint32_t x, uint32_t y) override;
  virtual void OnMouseReleased(uint32_t x, uint32_t y) override;
  virtual void WhileMouseDown(uint32_t x, uint32_t y) override;

  virtual void OnUpdate() override;
};

class BucketTool : public Tool
{
public:
  BucketTool(Image& image, Color* color)
    : Tool(image, color, "Bucket")
  {}

public:
  virtual void OnMousePressed(uint32_t x, uint32_t y) override;
  virtual void OnMouseReleased(uint32_t x, uint32_t y) override;
  virtual void WhileMouseDown(uint32_t x, uint32_t y) override;

  virtual void OnUpdate() override;
};

struct ImagePosition
{
  Vector2 onScreenPos;
  float scale;
};

class EditorScene : public AppScene
{
public:
  EditorScene(Image image);
  ~EditorScene();
public:
  virtual void OnUpdate() override;
  virtual void OnEnter() override;
  virtual void OnLeave() override;

private:
  bool IsMouseOnImage();
  Vector2 GetMousePixel();

  void DoTool();

private:
  Image _Image;
  std::vector<std::shared_ptr<Tool>> _Tools;
  std::shared_ptr<Tool> _CurrentTool;
  ImagePosition _ImgPosition;
  Color _SelectedColor;
};
