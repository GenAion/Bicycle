#ifndef CALLBACKS_H
#define CALLBACKS_H

// 窗口重置时调用
void reshape(int w, int h);

// 鼠标按键/释放回调
void mouseButton(int button, int state, int x, int y);

// 鼠标拖动回调
void mouseMotion(int x, int y);

// 键盘回调
void keyboard(unsigned char key, int, int);

// 定时器回调，用于动画更新
void tick(int);

// 渲染回调
void display();

#endif // CALLBACKS_H
