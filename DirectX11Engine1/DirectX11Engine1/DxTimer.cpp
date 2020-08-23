#include "DxTimer.h"

using namespace std::chrono;

DxTimer::DxTimer()
{
    //開始時点の時間を記録
    last = steady_clock::now();
}

float DxTimer::Mark()
{
    //古い時間を作成
    const steady_clock::time_point old = last;
    //最新にする
    last = steady_clock::now();
    //duration = 単位時間を扱う
    const duration<float> frameTime = last - old;
    return frameTime.count();
}

float DxTimer::Peek() const
{
    return duration<float>(steady_clock::now() - last).count();
}
