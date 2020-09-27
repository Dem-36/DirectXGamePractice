#ifndef _DXTIMER_H_
#define _DXTIMER_H_

#include<chrono>

class DxTimer
{
public:
	DxTimer();
	//�O�̃t���[�����獡�̃t���[���܂ł̍�����Ԃ�
	float Mark();
	//���̎��Ԃ���last�̍�����Ԃ�
	float Peek()const;
private:
	std::chrono::steady_clock::time_point last;
};

#endif