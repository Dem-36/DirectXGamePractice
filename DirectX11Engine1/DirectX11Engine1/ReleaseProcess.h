//https://w.atwiki.jp/bokuyo/pages/65.html

#ifndef _RELEASEPROCESS_H_
#define _RELEASEPROCESS_H_

template<typename T>
inline void SafeDelete(T*& p) {
	if (p != NULL) {
		delete (p);
		(p) = NULL;
	}
}

template <typename T>
inline void SafeDeleteArray(T*& p) {
	if (p != NULL) {
		delete[](p);
		(p) = NULL;
	}
}

template <typename T>
inline void SafeRelease(T*& p) {
	if (p != NULL) {
		(p)->Release();
		(p) = NULL;
	}
}

#endif