#include "widgets.h"

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QVBoxLayout>

int argc = 1;
char* first_arg = "new application";

struct Object : public QObject {};
struct Widget : public QWidget, public Object {
    Widget(Widget *parent = 0) : QWidget(parent) {}
};
struct PushButton : public QPushButton {
    PushButton(Widget *parent) : QPushButton(parent) {}
};
struct Label : public QLabel {
    Label(Widget *parent) : QLabel(parent) {}
};
struct Application : public QApplication {
    Application() : QApplication(argc, &first_arg) {};
};
struct Layout : public QLayout {
    Layout(Widget *parent) : QLayout(parent) {}
};

struct VBoxLayout : public QVBoxLayout {
    VBoxLayout(Widget *parent) : QVBoxLayout(parent) {}
};

const char* Object_GetClassName(struct Object *object) {
    return object->metaObject()->className() + 1;
}

void Object_Delete(struct Object *object) {
    delete object;
}

void Object_SetAllowDeleteChildren(bool v);

struct Application* Application_New() {
    return new Application();
}

int Application_Exec(struct Application *app) {
    return app->exec();
}

struct VBoxLayout* VBoxLayout_New(struct Widget *parent) {
    return new VBoxLayout(parent);
}

void Layout_AddWidget(struct Layout *layout, struct Widget *widget) {
    layout->addWidget(widget);
}

struct Widget* Widget_New(struct Widget *parent) {
    return new Widget(parent);
}

void Widget_SetVisible(struct Widget *widget, bool v) {
    widget->setVisible(v);
}

void Widget_SetWindowTitle(struct Widget *widget, const char *title) {
    widget->setWindowTitle(QString::fromUtf8(title));
}

void Widget_SetLayout(struct Widget *widget, struct Layout *layout) {
    widget->setLayout(layout);
}

void Widget_SetSize(struct Widget *widget, int w, int h) {
    widget->setFixedSize(w, h);
}

struct Label* Label_New(struct Widget *parent) {
    return new Label(parent);
}

void Label_SetText(struct Label *label, const char *text) {
    label->setText(QString::fromUtf8(text));
}

struct PushButton* PushButton_New(struct Widget *parent) {
    return new PushButton(parent);
}

void PushButton_SetText(struct PushButton *button, const char *text) {
    button->setText(QString::fromUtf8(text));
}

void PushButton_SetOnClicked(struct PushButton *button, NoArgumentsCallback *callback) {
    Object::connect(button, &PushButton::clicked, button, [=](){ callback((struct Object*)button); });
}
