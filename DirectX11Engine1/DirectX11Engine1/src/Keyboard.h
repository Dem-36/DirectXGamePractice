#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include<queue>
#include<bitset>
#include<optional> //無効な値をとることができる

class Keyboard
{
public:
	class Event {
	public:
		enum class KeyType {
			Press,
			Release,
		};
	private:
		KeyType type;
		unsigned char code;
	public:
		Event(KeyType type, unsigned char code)noexcept
			:type(type), code(code) {}

		//キーが押されたかどうか
		bool IsPress()const noexcept {
			return type == KeyType::Press;
		}

		//キーが離されたかどうか
		bool IsRelease()const noexcept {
			return type == KeyType::Release;
		}

		unsigned char GetCode()const noexcept {
			return code;
		}
	};
public:
	Keyboard() = default;
	//コピーは必要ないのでデフォルトの機能を禁止する
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;

	//キーのイベント
	bool KeyIsPressed(unsigned char keyCode)const noexcept;
	std::optional<Event> ReadKey()noexcept;
	bool KeyIsEmpty()const noexcept;
	void FlushKey()noexcept;

	//char型のイベント
	std::optional<char> ReadChar()noexcept;
	bool CharIsEmpty()const noexcept;
	void FlushChar()noexcept;
	void Flush();

	//autorepeat control
	void EnableAutoRepeat()noexcept;
	void DisableAutoRepeat()noexcept;
	bool AutoRepeatIsEnabled()const noexcept;

private:
	//特定のWindowsメッセージが呼ばれたときに使う
	void OnKeyPressed(unsigned char keyCode)noexcept;
	void OnKeyReleased(unsigned char keyCode)noexcept;
	void OnChar(char character)noexcept;
	void ClearState()noexcept;

	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer)noexcept;
private:
	//constexprをつけた関数はコンパイル時に計算することもできると表す
	//数字u = 符号なし整数
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autoRepeaEnabled = false;
	//bitsetはコンパイル時点で要素数は確定してなければならない
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char>charBuffer;
private:
	//フレンドクラスの設定(Windowクラス内でKeyboardクラスのprivateが扱える)
	friend class Window;
};
#endif