#include "plugin.hpp"


Plugin *pluginInstance;

extern Model *modelJTChords;
extern Model *modelChords;
extern Model* modelAG;
extern Model* modelACC;
extern Model* modelCV;
extern Model* modelKlee;
extern Model* modelM851;
extern Model* modelCYC;
extern Model* modelPwmClock;
extern Model* modelTD4;
extern Model* modelP4;
extern Model* modelP16;
extern Model* modelPXY;
extern Model* modelC42;
extern Model* modelC42E;
extern Model* modelSum;
extern Model* modelSE;
extern Model* modelUno;
extern Model* modelUnoE;
extern Model* modelTheMatrix;

void init(Plugin *p) {
  pluginInstance=p;

  p->addModel(modelJTChords);
  p->addModel(modelChords);
	p->addModel(modelAG);
	p->addModel(modelACC);
	p->addModel(modelCV);
	p->addModel(modelKlee);
	p->addModel(modelM851);
	p->addModel(modelCYC);
	p->addModel(modelPwmClock);
	p->addModel(modelTD4);
	p->addModel(modelP4);
	p->addModel(modelP16);
	p->addModel(modelPXY);
	p->addModel(modelC42);
	p->addModel(modelC42E);
	p->addModel(modelSum);
	p->addModel(modelSE);
	p->addModel(modelUno);
	p->addModel(modelUnoE);
	p->addModel(modelTheMatrix);
}

void SmallButtonWithLabel::draw(const Widget::DrawArgs &args) {
  std::shared_ptr<Font> font=APP->window->loadFont(fontPath);
  SvgSwitch::draw(args);
  if(label.length()>0) {
    nvgFontSize(args.vg,8);
    nvgFontFaceId(args.vg,font->handle);
    NVGcolor textColor=nvgRGB(0xff,0xff,0xaa);
    nvgTextAlign(args.vg,NVG_ALIGN_CENTER);
    nvgFillColor(args.vg,textColor);
    nvgText(args.vg,11,7,label.c_str(),NULL);
  }
}

void SmallButtonWithLabelV::draw(const Widget::DrawArgs &args) {
  std::shared_ptr<Font> font=APP->window->loadFont(fontPath);
  SvgSwitch::draw(args);
  if(label.length()>0) {
    nvgFontSize(args.vg,8);
    nvgFontFaceId(args.vg,font->handle);
    NVGcolor textColor=nvgRGB(0xff,0xff,0xaa);
    nvgTextAlign(args.vg,NVG_ALIGN_CENTER|NVG_ALIGN_MIDDLE);
    nvgFillColor(args.vg,textColor);
    nvgText(args.vg,box.size.x/2.f, box.size.y/2.f,label.c_str(),NULL);
  }
}

void UpButtonWidget::onButton(const ButtonEvent& e) {

  if(e.action == GLFW_PRESS && e.button==GLFW_MOUSE_BUTTON_LEFT) {
    pressed = true;
    auto paramWidget=getAncestorOfType<ParamWidget>();
    assert(paramWidget);
    engine::ParamQuantity *pq=paramWidget->getParamQuantity();
    if(pq) {
      if(pq->getValue()<pq->getMaxValue()) {
        pq->setValue(pq->getValue()+1);
        ChangeEvent c;
        paramWidget->onChange(c);
      }
    } else {
      INFO("no pq");
    }
    e.consume(this);
  }
  if(e.action == GLFW_RELEASE && e.button==GLFW_MOUSE_BUTTON_LEFT) {
    pressed = false;
  }
}

void DownButtonWidget::onButton(const ButtonEvent& e) {
  if(e.action == GLFW_PRESS && e.button==GLFW_MOUSE_BUTTON_LEFT) {
    pressed = true;
    auto paramWidget=getAncestorOfType<ParamWidget>();
    assert(paramWidget);
    engine::ParamQuantity *pq=paramWidget->getParamQuantity();
    if(pq) {
      if(pq->getValue()>pq->getMinValue()) {
        pq->setValue(pq->getValue()-1);
        ChangeEvent c;
        paramWidget->onChange(c);
      }
    }
    e.consume(this);
  }
  if(e.action == GLFW_RELEASE && e.button==GLFW_MOUSE_BUTTON_LEFT) {
    pressed = false;
  }
}
void SelectButton::onDragEnter(const event::DragEnter &e) {
  if (e.button == GLFW_MOUSE_BUTTON_LEFT) {
    //auto origin = dynamic_cast<SelectParam*>(e.origin);
    //if (origin) {
      auto paramWidget = getAncestorOfType<ParamWidget>();
      assert(paramWidget);
      engine::ParamQuantity* pq = paramWidget->getParamQuantity();
      if (pq) {
        pq->setValue(_value);
      }
    //}
  }
  Widget::onDragEnter(e);
}
