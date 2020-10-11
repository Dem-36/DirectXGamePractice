#ifndef _MOUSE_H_
#define _MOUSE_H_

#include<queue>
#include<optional> //無効な値をとることができる

class Mouse
{
public:
	class Event {
	public:
		enum class MouseType {
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
		};
	private:
		MouseType type;
		bool leftIsPressed;
		bool rightIsPressed;
		int x, y;
	public:
		Event(MouseType type, const Mouse& parent)noexcept
			:type(type), leftIsPressed(parent.leftIsPressed),
			rightIsPressed(parent.rightIsPressed), x(parent.x), y(parent.y) {
			
		}
		MouseType GetType()const noexcept {
			return type;
		}
		//位置を返す
		std::pair<int, int> GetPosition()const noexcept {
			return{ x,y };
		}
		int GetX()const noexcept {
			return x;
		}
		int GetY()const noexcept {
			return y;
		}
		bool LeftIsPressed()const noexcept {
			return leftIsPressed;
		}
		bool RightIsPressed()const noexcept {
			return rightIsPressed;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	//マウスの座標を返す
	std::pair<int, int> GetPos() const noexcept;
	//マウスの座標のXを返す
	int GetPosX() const noexcept;
	//マウスの座標のYを返す
	int GetPosY() const noexcept;
	//カーソルがウィンドウ内にあるかどうか
	bool IsInWindow()const noexcept;
	//左クリックが押されているかどうか
	bool LeftIsPressed() const noexcept;
	//右クリックが押されているかどうか
	bool RightIsPressed() const noexcept;
	std::optional<Mouse::Event> Read() noexcept;
	//イベントが空かどうか
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;
private:
	//マウスの動き
	void OnMouseMove(int x, int y) noexcept;
	//マウスが画面外に行った
	void OnMouseLeave()noexcept;
	//マウスが画面内に戻った
	void OnMouseEnter()noexcept;
	//左クリックがされたとき
	void OnLeftPressed(int x, int y) noexcept;
	//左クリックが離れたとき
	void OnLeftReleased(int x, int y) noexcept;
	//右クリックがされたとき
	void OnRightPressed(int x, int y) noexcept;
	//右クリックが離れたとき
	void OnRightReleased(int x, int y) noexcept;
	//マウスホイールが前に回転したとき
	void OnWheelUp(int x, int y) noexcept;
	//マウスホイールが後ろに開店したとき
	void OnWheelDown(int x, int y) noexcept;
	void OnWheelDelta(int x, int y,int delta)noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	int x, y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	//ウィンドウ内にいるかどうか
	bool isInWindow = false;
	std::queue<Event> buffer;
	//マウスホイール回転距離保存変数
	int wheelDeltaCarry = 0;
private:
	friend class Window;
};

#endif
