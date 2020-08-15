//https://www.youtube.com/watch?v=D-PC-huX-l8&list=PL2lknG4OSjqi73VvJLR5OUJDxLZ6kj4a4&index=8&t=4s

#pragma once 

#define _WIN32_WINNT 0x0601
#include<sdkddkver.h>
//以下のdefineは未使用のWindoesの要素を無効化してくれる
//いくつかのウィンドウを使用するときにおかしなエラーが出たら
//定義の一部を削除してみる。(ビルド時間が長くなる)

#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSMETRICS
#define NOMENUS
#define NOICONS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOCLIPBOARD
#define NOCOLOR
#define NOCTLMGR
#define NODRAWTEXT
#define NOKERNEL
#define NONLS
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSCROLL
#define NOSERVICE
#define NOSOUND
#define NOTEXTMETRIC
#define NOWH
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX
#define NORPC
#define NOPROXYSTUB
#define NOIMAGE
#define NOTAPE

#define STRICT

#include<Windows.h>