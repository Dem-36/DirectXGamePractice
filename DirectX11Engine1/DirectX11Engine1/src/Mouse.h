#ifndef _MOUSE_H_
#define _MOUSE_H_

#include<queue>
#include<optional> //�����Ȓl���Ƃ邱�Ƃ��ł���

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
		//�ʒu��Ԃ�
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
	//�}�E�X�̍��W��Ԃ�
	std::pair<int, int> GetPos() const noexcept;
	//�}�E�X�̍��W��X��Ԃ�
	int GetPosX() const noexcept;
	//�}�E�X�̍��W��Y��Ԃ�
	int GetPosY() const noexcept;
	//�J�[�\�����E�B���h�E���ɂ��邩�ǂ���
	bool IsInWindow()const noexcept;
	//���N���b�N��������Ă��邩�ǂ���
	bool LeftIsPressed() const noexcept;
	//�E�N���b�N��������Ă��邩�ǂ���
	bool RightIsPressed() const noexcept;
	std::optional<Mouse::Event> Read() noexcept;
	//�C�x���g���󂩂ǂ���
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;
private:
	//�}�E�X�̓���
	void OnMouseMove(int x, int y) noexcept;
	//�}�E�X����ʊO�ɍs����
	void OnMouseLeave()noexcept;
	//�}�E�X����ʓ��ɖ߂���
	void OnMouseEnter()noexcept;
	//���N���b�N�����ꂽ�Ƃ�
	void OnLeftPressed(int x, int y) noexcept;
	//���N���b�N�����ꂽ�Ƃ�
	void OnLeftReleased(int x, int y) noexcept;
	//�E�N���b�N�����ꂽ�Ƃ�
	void OnRightPressed(int x, int y) noexcept;
	//�E�N���b�N�����ꂽ�Ƃ�
	void OnRightReleased(int x, int y) noexcept;
	//�}�E�X�z�C�[�����O�ɉ�]�����Ƃ�
	void OnWheelUp(int x, int y) noexcept;
	//�}�E�X�z�C�[�������ɊJ�X�����Ƃ�
	void OnWheelDown(int x, int y) noexcept;
	void OnWheelDelta(int x, int y,int delta)noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	int x, y;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	//�E�B���h�E���ɂ��邩�ǂ���
	bool isInWindow = false;
	std::queue<Event> buffer;
	//�}�E�X�z�C�[����]�����ۑ��ϐ�
	int wheelDeltaCarry = 0;
private:
	friend class Window;
};

#endif
