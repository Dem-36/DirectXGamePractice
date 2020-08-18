#include "Mouse.h"
#include<Windows.h>

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x,y };
}

int Mouse::GetPosX() const noexcept
{
	return x;
}

int Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::IsInWindow() const noexcept
{
	return isInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return rightIsPressed;
}

Mouse::Event Mouse::Read() noexcept
{
	if (buffer.size() > 0u) {
		Mouse::Event e = buffer.front();
		buffer.pop();
		return e;
	}
	else {
		return Mouse::Event();
	}
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Event>();
}

void Mouse::OnMouseMove(int x, int y) noexcept
{
	this->x = x;
	this->y = y;

	buffer.push(Mouse::Event(Mouse::Event::MouseType::Move, *this));
	TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
	isInWindow = false;
	buffer.push(Mouse::Event(Mouse::Event::MouseType::Leave, *this));
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	isInWindow = true;
	buffer.push(Mouse::Event(Mouse::Event::MouseType::Enter, *this));
	TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	leftIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::MouseType::LPress, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	leftIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::MouseType::LRelease, *this));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	rightIsPressed = true;

	buffer.push(Mouse::Event(Mouse::Event::MouseType::RPress, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	rightIsPressed = false;

	buffer.push(Mouse::Event(Mouse::Event::MouseType::RRelease, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::MouseType::WheelUp, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	buffer.push(Mouse::Event(Mouse::Event::MouseType::WheelDown, *this));
	TrimBuffer();
}

void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDeltaCarry += delta;
	//WHEEL_DELTA = 120
	while (wheelDeltaCarry >= WHEEL_DELTA) {
		wheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (wheelDeltaCarry <= -WHEEL_DELTA) {
		wheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}

//バッファのサイズが最大許容を超えているかどうか
void Mouse::TrimBuffer() noexcept
{
	//基底のサイズになるまで先頭要素を削除する
	while (buffer.size() > bufferSize) {
		buffer.pop();
	}
}
