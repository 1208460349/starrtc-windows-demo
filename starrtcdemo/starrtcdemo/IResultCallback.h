#pragma once
#include <string>
using namespace std;
class IResultCallback
{
public:
	/**
	 * �ɹ�
	 * @param data
	 */
	virtual void success() = 0;

	/**
	 * ʧ��
	 * @param errMsg
	 */
	virtual void failed(string errMsg) = 0;
};

