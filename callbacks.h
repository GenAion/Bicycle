#ifndef CALLBACKS_H
#define CALLBACKS_H

// ��������ʱ����
void reshape(int w, int h);

// ��갴��/�ͷŻص�
void mouseButton(int button, int state, int x, int y);

// ����϶��ص�
void mouseMotion(int x, int y);

// ���̻ص�
void keyboard(unsigned char key, int, int);

// ��ʱ���ص������ڶ�������
void tick(int);

// ��Ⱦ�ص�
void display();

#endif // CALLBACKS_H
