#ifndef _WINEXCEPTION_H_
#define _WINEXCEPTION_H_

#include<exception>
#include<string>

//�G���[�N���X�̊��
class WinException:public std::exception
{
public:
	//�R���X�g���N�^
	WinException(int line, const char* file)noexcept;
	//�G���[���e�̕\��
	const char* what()const noexcept override;
	//�G���[�^�C�v �p����ŕω�����
	virtual const char* GetType()const noexcept;
	//�G���[���o���s��Ԃ�
	int GetLine()const noexcept;
	//�t�@�C�����擾
	const std::string& GetFile()const noexcept;
	//�G���[�̍s�ƃt�@�C�������i�[����string��Ԃ�
	std::string GetOriginString()const noexcept;
private:
	int line;
	std::string file;
protected:
	//mutable : const���\�b�h���ŏ����������\�ɂȂ�
	mutable std::string whatBuffer;

};

#endif