#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template<typename T>
class Singleton {
protected:
	Singleton() {}
	Singleton(const T*) {}
public:
	static T* Instance() {
		if (instance == nullptr)
			instance = new T;
		return instance;
	}

	static void DestroyInstance() {
		if (instance == nullptr)
			return;
		delete instance;
		instance = nullptr;
	}

	virtual void Release() = 0;

private:
	static T* instance;
};

//インスタンスの初期化
template<typename T>
T* Singleton<T>::instance = nullptr;

#endif