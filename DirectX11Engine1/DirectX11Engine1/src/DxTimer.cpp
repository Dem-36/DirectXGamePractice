#include "DxTimer.h"

using namespace std::chrono;

DxTimer::DxTimer()
{
    //�J�n���_�̎��Ԃ��L�^
    last = steady_clock::now();
}

float DxTimer::Mark()
{
    //�Â����Ԃ��쐬
    const steady_clock::time_point old = last;
    //�ŐV�ɂ���
    last = steady_clock::now();
    //duration = �P�ʎ��Ԃ�����
    const duration<float> frameTime = last - old;
    return frameTime.count();
}

float DxTimer::Peek() const
{
    return duration<float>(steady_clock::now() - last).count();
}
